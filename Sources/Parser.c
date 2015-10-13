/* Parser.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//~ #include <ctype.h>

#include "Logic.h"
#include "Model.h"
#include "Parser.h"
#include "Expressions.h"
#include "Interpretation.h"


/* === local declarations === */

static const char* typeNames_g[] = {
	"Program", 		"Decls",	"Facts",	"Restrs", 	"FuncDecl",	"Variable",
	"Named_const",	"Pred",		"Func",		"Axiom", 	"Conj",		"ResConj",
	"All",			"Ext", 		"&",		"|",		"=>",		"=",
	"<=>",			"!",		"Name",		"Ax_vars",	"Premise",	"Result",
	"Integer",		"Real",		"S_decl",	"S_fact",	"S_axiom",	"S_restr",
	"Query",		"NULL"
};


void parse(_md);

extern int yyparse(Source* sourcePtr, ParserNode* programPtr,
					Vector* errVectPtr);

void printParserNode(ParserNode* nodePtr, int layer);	/* for debug only */

void acceptDeclaration(ParserNode* pnDeclPtr, _md);
void acceptFact(ParserNode* pnFactPtr, _md);
void acceptRestriction(ParserNode* pnRestrPtr, _md);

void acceptAxiom(ParserNode* pnAxPtr, _md);

ExprNode* acceptExprNode(ParserNode* pnExprPtr, Vector* varVectPtr,
						 DataTypeId expecType, _md);

ssize_t addNewVariable(ParserNode* pnVarPtr, Vector* varVectPtr, _md);

void checkVarsForUsing(ExprIter iter, Boolean* usingMask);
Boolean hasNullNode(ParserNode* pnVarPtr);



/* === realization === */

void parse(_md)
{	
	ParserNode* parseTreePtr = createNode(ND_NULL, NULL, 0, 0);
	Vector errVect;
	initVect(errVect, Error);
	
	/* call bison's parser */
	yyparse(modelPtr->currSrcPtr, parseTreePtr, &errVect);
	
	//~ printParserNode(parseTreePtr, 0);		/* debug output */
	
	/* save errors in model */
	size_t errNum;
	forVect(errNum, errVect)
		addError(ptr(Error, errVect)[errNum], modelPtr);
	
	switch (parseTreePtr->type)
	{
		case ND_PROG:
		{
			ParserNode* segmentPtr = parseTreePtr->params;
	
			for (; segmentPtr != NULL; segmentPtr = segmentPtr->next)
			{
				ParserNode* nodePtr = segmentPtr->params;
				
				for (; nodePtr != NULL; nodePtr = nodePtr->next)
					switch (segmentPtr->type)
					{
						case ND_DECLS:
							acceptDeclaration(nodePtr, modelPtr);
							break;
						case ND_FACTS:
							acceptFact(nodePtr, modelPtr);
							break;
						case ND_RESTRS:
							acceptRestriction(nodePtr, modelPtr);
							break;
						default: break;
					}
			}
		}
		break;
		case ND_S_DECL:
			acceptDeclaration(parseTreePtr->params, modelPtr);	break;
		case ND_S_FACT:
			acceptFact(parseTreePtr->params, modelPtr);			break;
		case ND_S_AXIOM:
			acceptAxiom(parseTreePtr->params, modelPtr);		break;
		case ND_S_RESTR:
			acceptRestriction(parseTreePtr->params, modelPtr);	break;
		default:
			addParserError("unknown syntax error", 1, 1, modelPtr);
		break;
	}

	freeVect(errVect);
	freeNode(parseTreePtr);
}


void parseFile(char fileName[], _md)
{
	FILE* infile = fopen(fileName, "r");
	
	if (!infile)
	{
		Error error = createParserError("can't open file ", NULL, 0, 0);
		addTextToError(&error, fileName);
		addError(error, modelPtr);
		return;
	}
	
	size_t 	factCt = modelPtr->totalFactCt,
			axCt = axioms_m.len,
			restrCt = restrs_m.len;
	
	Source source = createFileSource(fileName);
	source.file = infile;
	addBack(modelPtr->sources, Source, source);
	Source* sourcePtr = ptr(Source, modelPtr->sources)
						+ (modelPtr->sources.len - 1);
	modelPtr->currSrcPtr = sourcePtr;
	
	parse(modelPtr);
	
	if (sourcePtr->file != NULL)
		fclose(sourcePtr->file);
	
	addBack(sourcePtr->charVect, char, '\0');
	modelPtr->currSrcPtr = NULL;
	
	if (modelPtr->debugStream != NULL)
	{
		factCt = modelPtr->totalFactCt - factCt;
		axCt = axioms_m.len - axCt;
		restrCt = restrs_m.len - restrCt;
		
		fprintf(modelPtr->debugStream, "%u facts, %u axioms, %u restrictions"
				" were read from \'%s\'\n", factCt, axCt, restrCt, fileName);
	}
}


void parseString(char string[], _md)
{
	Source source = createStringSource(string);
	addBack(modelPtr->sources, Source, source);
	Source* sourcePtr = ptr(Source, modelPtr->sources)
						+ (modelPtr->sources.len - 1);
	modelPtr->currSrcPtr = sourcePtr;
	
	parse(modelPtr);
	
	addBack(sourcePtr->charVect, char, '\0');
	modelPtr->currSrcPtr = NULL;
}


Query parseQuery(char string[], _md)
{
	Source source = createStringSource(string);
	addBack(modelPtr->sources, Source, source);
	Source* sourcePtr = ptr(Source, modelPtr->sources)
						+ (modelPtr->sources.len - 1);
	modelPtr->currSrcPtr = sourcePtr;
	
	ParserNode* parseTreePtr = createNode(BAD_INDEX, NULL, 0, 0);
	Vector errVect;
	initVect(errVect, Error);
	yyparse(modelPtr->currSrcPtr, parseTreePtr, &errVect); /* yyparse */
	
	//~ printParserNode(parseTreePtr, 0);
	
	Query query;
	query.funcPtr = NULL; query.params = NULL;
	
	if (parseTreePtr->type == ND_QUERY)
	{
		ParserNode* pnQueryPtr = parseTreePtr->params;
		
		Func* funcPtr = getFuncOrPredByName(pnQueryPtr->name, modelPtr);
		
		if (funcPtr == NULL)
		{
			addParserError("unknown function or predicate",
				pnQueryPtr->lineNum, pnQueryPtr->columnNum, modelPtr);
			
			freeVect(errVect);
			freeNode(parseTreePtr);
			addBack(sourcePtr->charVect, char, '\0');
			modelPtr->currSrcPtr = NULL;
			return query;
		}
		
		Vector paramVect, varVect;
		initVect(paramVect, supp);
		initVect(varVect, Variable);
		ParserNode* pnParPtr = pnQueryPtr->params;
		ParserNode* pnResPtr = pnQueryPtr->next;
		size_t parNum = 0;
		
		for (; pnParPtr != NULL && parNum < funcPtr->parCt;
			pnParPtr = pnParPtr->next, ++parNum)
		{
			if (strlen(pnParPtr->name) == 0)
				addBack(paramVect, supp, CONST_IDC)
			else
			{
				ExprNode* nodePtr = acceptExprNode(pnParPtr, &varVect,
										funcPtr->parTypes[parNum], modelPtr);
				addBack(paramVect, supp, nodePtr->value);
				freeExprNode(nodePtr);
			}
		}
		
		if (parNum != funcPtr->parCt || pnParPtr != NULL)
		{
			addParserError("wrong number of parametrs",
				pnQueryPtr->lineNum, pnQueryPtr->columnNum, modelPtr);
			
			freeVect(errVect);
			freeNode(parseTreePtr);
			addBack(sourcePtr->charVect, char, '\0');
			modelPtr->currSrcPtr = NULL;
			return query;
		}
		
		supp res = CONST_IDC;
		
		if (strlen(pnResPtr->name) != 0)
		{
			ExprNode* nodePtr = acceptExprNode(pnResPtr, &varVect,
									funcPtr->dataType, modelPtr);
			res = nodePtr->value;
			freeExprNode(nodePtr);
		}
		
		query = createQuery(funcPtr, ptr(supp, paramVect));
		query.value = res;
	}
	
	/* save errors in model */
	size_t errNum;
	forVect(errNum, errVect)
		addError(ptr(Error, errVect)[errNum], modelPtr);
	
	freeVect(errVect);
	freeNode(parseTreePtr);
	addBack(sourcePtr->charVect, char, '\0');
	modelPtr->currSrcPtr = NULL;
	
	return query;
}



void acceptDeclaration(ParserNode* pnDeclPtr, _md)
{
	if (pnDeclPtr == NULL
		|| (pnDeclPtr->type != ND_FUNC_DEC && pnDeclPtr->type != ND_NULL))
	{
		addInnerError("acceptDeclaration: invalid node\n", modelPtr);
		return;
	}
	
	if (hasNullNode(pnDeclPtr)) return;
	
	Vector parTypesVect;
	initVect(parTypesVect, DataTypeId);
	
	char* funcName = pnDeclPtr->name;

	ParserNode* paramPtr = pnDeclPtr->params;

	for (; paramPtr != NULL; paramPtr = paramPtr->next) /* in params */
	{
		DataTypeId typeId = getTypeIdByName(paramPtr->name, modelPtr);
		if (typeId == BAD_INDEX)
			typeId = addDataType(paramPtr->name, modelPtr);
		
		if (typeId == BAD_INDEX)
			addInnerError("acceptDeclaration: can't create datatype\n", modelPtr);
		
		addBack(parTypesVect, DataTypeId, typeId);
	}
	
	size_t parCt = parTypesVect.len - 1;
	DataTypeId* parTypes = ptr(DataTypeId, parTypesVect);
	DataTypeId type = parTypes[parCt];
	Func func = createFunc(funcName, parCt, parTypes, parTypes[parCt]);
	
	if (type == DT_BOOL)
		addPred(func, modelPtr);
	else
		addFunc(func, modelPtr);
}


void acceptFact(ParserNode* pnFactPtr, _md)
{
	if (pnFactPtr == NULL)
	{
		addInnerError("acceptFact: invalid node\n", modelPtr);
		return;
	}
	
	if (hasNullNode(pnFactPtr)) return;
	
	if (pnFactPtr->type == ND_AXIOM)
	{
		acceptAxiom(pnFactPtr, modelPtr);	/* work with axiom */
		return;
	}
	
	Vector varVect;
	initVect(varVect, Variable);
	ExprNode* nodePtr = acceptExprNode(pnFactPtr, &varVect,
										DT_BOOL, modelPtr);
	
	ExprIter iter = getIter(&varVect, nodePtr);
	supp value;
	
	if (nodePtr == NULL) return;
	
	switch (ndType(iter))
	{
		case EXPR_PRED:	value = CONST_TRUE;					break;
		case EXPR_NOT:	value = CONST_FALSE;  into(iter);	break;
		case EXPR_EQ:
			value = iter.nodePtr->params->next->value;
			into(iter);
			break;
		default:
			addInnerError("acceptFact: invalid node\n", modelPtr);
			return;
			break;
	}
	
	Func* funcPtr = (ndType(iter) == EXPR_PRED)
						? getPredPtr(ndVal(iter).id)
						: getFuncPtr(ndVal(iter).id);
	
	Vector paramVect;
	initVect(paramVect, supp);
	forParams(iter) addBack(paramVect, supp, ndVal(iter));
	
	/* set new fact */
	Fact fact = createFact(funcPtr, ptr(supp, paramVect), value);
	setFact(&fact, modelPtr);
	
	freeFact(&fact);
	freeVect(paramVect);
}


void acceptRestriction(ParserNode* pnRestrPtr, _md)
{
	if (pnRestrPtr == NULL) return;
	
	Restriction restr;
	initRestriction(&restr);
	
	restr.root = acceptExprNode(pnRestrPtr, &restr.vars, DT_BOOL, modelPtr);
	
	if (restr.root != NULL)
		addBack(restrs_m, Restriction, restr);
}


ExprNode* acceptExprNode(ParserNode* pnExprPtr, Vector* varVectPtr,
						 DataTypeId expecType, _md)
{
	/* Recursive creation of ExprNode.
	 * 'varVectPtr' is pointer of initialized Vector of 'Variable' */
	
	if (hasNullNode(pnExprPtr)) return NULL;
	
	Boolean hasError = false;
	ExprType nodeType;
	DataTypeId nodeDataTypeId = DT_BOOL;
	supp nodeValue;
	Vector paramVect;
	initVect(paramVect, ExprNode*);
	
	
	if (pnExprPtr->type == ND_NAMED_CONST)	/* constant or variable */
	{
		size_t varNum;
		Boolean isVariable = false;
		
		/* check if there is variable with the same name */
		for (varNum = 0; varNum < varVectPtr->len && !isVariable; ++varNum)
			isVariable
				= (strcmp(ptr(Variable, *varVectPtr)[varNum].name,
						  pnExprPtr->name) == 0);
		
		if (isVariable)
		{
			varNum--;
			nodeType = EXPR_VAR;
			nodeDataTypeId = ptr(Variable,*varVectPtr)[varNum].dataType;
			nodeValue.id = varNum;
		}
		else /* else it's constant */
		{
			nodeType = EXPR_CONST;
			nodeDataTypeId = expecType;
			nodeValue = getOrAddConstant(pnExprPtr->name, expecType, modelPtr);
			
			if (conCmp(nodeValue, CONST_NULL))
			{
				addParserError("invalid constant",
						pnExprPtr->lineNum, pnExprPtr->columnNum, modelPtr);
				hasError = true;
			}
		}
	}
	else if (pnExprPtr->type == ND_INTEGER)
	{
		nodeType = EXPR_CONST;
		nodeDataTypeId = DT_INT;
		sscanf(pnExprPtr->name, "%ld", &(nodeValue.integer));
		shiftSupp(nodeValue);
	}
	else if (pnExprPtr->type == ND_REAL)
	{
		nodeType = EXPR_CONST;
		nodeDataTypeId = DT_REAL;
		sscanf(pnExprPtr->name, "%lf", &(nodeValue.real));
		shiftSupp(nodeValue);
	}
	else if (pnExprPtr->type == ND_EQ)	/* t1 = t2 */
	{
		nodeType = EXPR_EQ;
		ParserNode* pnPar1 = pnExprPtr->params;
		ParserNode* pnPar2 = pnExprPtr->params->next;
		ExprNode *exprPar1, *exprPar2;
		
		if (pnPar1->type == ND_NAMED_CONST && pnPar2->type == ND_NAMED_CONST)
		{
			addParserError("primitive equality is not supported",
					pnPar1->lineNum, pnPar1->columnNum, modelPtr);
			hasError = true;
		}
		else
		{
			if (pnPar1->type == ND_NAMED_CONST)
				_SWAP(pnPar1, pnPar2, ParserNode*);
			
			exprPar1 = acceptExprNode(pnPar1, varVectPtr, BAD_INDEX, modelPtr);
			
			if (!(hasError = (exprPar1 == NULL)))
			{
				exprPar2 = acceptExprNode(pnPar2, varVectPtr,
									  exprPar1->dataType, modelPtr);
				
				addBack(paramVect, ExprNode*, exprPar1);
				addBack(paramVect, ExprNode*, exprPar2);
			}
		}
	}
	else if (	pnExprPtr->type == ND_LEQ	|| pnExprPtr->type == ND_AND
			|| 	pnExprPtr->type == ND_OR 	|| pnExprPtr->type == ND_IMP)
	{
		switch (pnExprPtr->type)
		{
			case ND_LEQ:	nodeType = EXPR_LEQ;	break;	/* f1 <=> f2	*/
			case ND_IMP:	nodeType = EXPR_IMP;	break;	/* f1 => f2		*/
			case ND_AND:	nodeType = EXPR_AND;	break;	/* f1 & f2		*/
			case ND_OR:		nodeType = EXPR_OR;		break;	/* f1 | f2		*/
			default: break;
		}
		
		ExprNode* exprPar1 = acceptExprNode(pnExprPtr->params,
									varVectPtr,	DT_BOOL, modelPtr);
		ExprNode* exprPar2 = acceptExprNode(pnExprPtr->params->next,
									varVectPtr, DT_BOOL, modelPtr);

		addBack(paramVect, ExprNode*, exprPar1);
		addBack(paramVect, ExprNode*, exprPar2);
	}
	else if (pnExprPtr->type == ND_NOT)	/* ! formula */
	{
		nodeType = EXPR_NOT;
		ExprNode* exprParPtr = acceptExprNode(pnExprPtr->params,
									varVectPtr,	DT_BOOL, modelPtr);

		addBack(paramVect, ExprNode*, exprParPtr);
	}
	else if (	pnExprPtr->type == ND_PRED
			||	pnExprPtr->type == ND_FUNC)	/* predicate or function */
	{
		//~ Func* funcPtr;
		long long funcNum;
		
		if (pnExprPtr->type == ND_PRED)
		{
			nodeType = EXPR_PRED;
			funcNum = getPredNumByName(pnExprPtr->name, modelPtr);
			//~ funcPtr = getPredPtr(funcNum);
		}
		else
		{
			nodeType = EXPR_FUNC;
			funcNum = getFuncNumByName(pnExprPtr->name, modelPtr);
			//~ funcPtr = getFuncPtr(funcNum);
		}
		
		if (funcNum == BAD_INDEX)
		{
			Error error = createParserError("", modelPtr->currSrcPtr,
								pnExprPtr->lineNum, pnExprPtr->columnNum);
			
			if (pnExprPtr->type == ND_PRED)
				 addTextToError(&error, "undefined predicate \'");
			else addTextToError(&error, "undefined function \'");
			
			addTextToError(&error, pnExprPtr->name);
			addTextToError(&error, "\'");
			addError(error, modelPtr);
			
			hasError = true;
		}
		else
		{
			Func* funcPtr = (pnExprPtr->type == ND_PRED)
						? getPredPtr(funcNum)
						: getFuncPtr(funcNum);
			
			nodeDataTypeId = funcPtr->dataType;
			nodeValue.id = funcNum;
			ParserNode* pnParPtr = pnExprPtr->params;
			size_t parNum;
			
			/* recursive create parametrs */
			for (parNum = 0; pnParPtr != NULL && parNum < funcPtr->parCt;
				 pnParPtr = pnParPtr->next, ++parNum)
			{
				ExprNode* parNode = acceptExprNode(pnParPtr, varVectPtr,
										funcPtr->parTypes[parNum], modelPtr);
				
				addBack(paramVect, ExprNode*, parNode);
			}
			
			if (parNum != funcPtr->parCt || pnParPtr != NULL)
			{
				char msg[] = "wrong number of parametrs\n\texpected 9999999999";
				sprintf(msg + strlen(msg) - 10, "%u", funcPtr->parCt);
				addParserError(msg, pnExprPtr->lineNum, pnExprPtr->columnNum,
								modelPtr);
				hasError = true;
			}
			
			/* set data type for arithmetic functions */
			if (pnExprPtr->type == ND_FUNC
				&& 	funcNum < ARITHMETIC_FUNCTION_COUNT)
			{
				Boolean hasReal = false;
			
				forVectIf(parNum, paramVect, !hasReal)
					hasReal = ptr(ExprNode*, paramVect)[parNum]->dataType
							== DT_REAL;
				
				nodeDataTypeId = (hasReal || expecType == DT_REAL)
								? DT_REAL : DT_INT;
			}
			
			/* additional control of parametrs types */
			if (pnExprPtr->type != ND_FUNC
				|| funcNum >= ARITHMETIC_FUNCTION_COUNT)
			{
				forVect(parNum, paramVect)
					if (ptr(ExprNode*, paramVect)[parNum] != NULL)
						ptr(ExprNode*, paramVect)[parNum]->dataType
							= funcPtr->parTypes[parNum];
			}
		}
	}
	else if (	pnExprPtr->type == ND_ALL
			||	pnExprPtr->type == ND_EXT)	/* All x, Ext x */
	{
		if (pnExprPtr->type == ND_ALL)
			 nodeType = EXPR_ALL;
		else nodeType = EXPR_EXT;
		
		ssize_t varNum = addNewVariable(pnExprPtr->params, varVectPtr,modelPtr);
		
		if (varNum != BAD_INDEX)
		{
			nodeValue.id = varNum;
			ExprNode* formNodePtr = acceptExprNode(pnExprPtr->params->next,
											varVectPtr, DT_BOOL, modelPtr);
			addBack(paramVect, ExprNode*, formNodePtr);
		}
		else hasError = true;
	}
	else
	{
		//~ /* TODO: Parser error. Invalid type of expression. */
		addInnerError("acceptExprNode: invalid type of node\n", modelPtr);
		hasError = true;
	}

	/* common processing */
	
	/* check params */
	size_t parNum;
	
	for (parNum = 0; parNum < paramVect.len && !hasError; ++parNum)
		hasError = (ptr(ExprNode*, paramVect)[parNum] == NULL);
	
	/* check for compatibility with exprcted type */
	if (expecType != BAD_INDEX && !hasError && expecType != nodeDataTypeId
		&&	(	(expecType != DT_INT && expecType != DT_REAL)
			||	(nodeDataTypeId != DT_INT && nodeDataTypeId != DT_REAL)
			)
		)
	{
		Error error = createParserError("incompatible types\n\texpected: ",
			modelPtr->currSrcPtr, pnExprPtr->lineNum, pnExprPtr->columnNum);
		addTextToError(&error, getTypePtr(expecType)->name);
		addTextToError(&error, ", resived: ");
		addTextToError(&error, getTypePtr(nodeDataTypeId)->name);
		addError(error, modelPtr);
		
		hasError = true;
	}
	
	if (hasError)
	{
		for (parNum = 0; parNum < paramVect.len; ++parNum)
			freeExprNode(ptr(ExprNode*, paramVect)[parNum]);
		
		freeVect(paramVect);
		return NULL;
	}
	
	ExprNode* exprNode = createExprNode(nodeType);
	ExprNode* lastNode = NULL;
	exprNode->dataType = nodeDataTypeId;
	exprNode->value = nodeValue;
	
	forVect(parNum, paramVect)
	{
		ExprNode* parNode = ptr(ExprNode*, paramVect)[parNum];
		
		if (lastNode == NULL)
			 lastNode = exprNode->params = parNode;
		else lastNode = lastNode->next = parNode;
	}
	
	freeVect(paramVect);
	return exprNode;
}



void acceptAxiom(ParserNode* pnAxPtr, _md)
{
	if (pnAxPtr == NULL
		|| (pnAxPtr->type != ND_AXIOM && pnAxPtr->type != ND_NULL))
	{
		addInnerError("acceptAxiom: invalid node\n", modelPtr);
		return;
	}
	
	if (hasNullNode(pnAxPtr)) return;
	
	/* initialize new axiom */
	Axiom axiom;
	axiom.itemCt = axiom.premCt = axiom.mainCt = axiom.actCt = 0;
	initVect(axiom.vars, Variable);
	axiom.items = NULL; axiom.servData = NULL;
	
	ParserNode* pnVarsPtr = pnAxPtr->params;
	ParserNode* pnPremPtr = pnAxPtr->params->next;
	ParserNode* pnResPtr  = pnAxPtr->params->next->next;
	
	/* get variables */
	ParserNode* pnVarPtr = pnVarsPtr->params;
	Boolean hasError = false;
	
	for (; pnVarPtr != NULL; pnVarPtr = pnVarPtr->next)	/* in vars */
		if (addNewVariable(pnVarPtr, &axiom.vars, modelPtr) == BAD_INDEX)
			//~ return freeAxiom(&axiom), false;
			//~ return freeAxiom(&axiom);
			hasError = true;
	
	/* get items */
	Vector itemVect;
	initVect(itemVect, ExprNode*);
	ParserNode* pnItemPtr = (pnPremPtr != NULL) ? pnPremPtr->params : NULL;
	Boolean inPremise = true;
	
	for (; pnItemPtr != NULL /*&& !hasError*/; /*pnItemPtr = pnItemPtr->next*/)
	{
		ExprNode* itNodePtr = acceptExprNode(pnItemPtr, &axiom.vars,
											DT_BOOL, modelPtr);
		hasError |= itNodePtr == NULL;
		addBack(itemVect, ExprNode*, itNodePtr);
		
		axiom.itemCt++;
		if (inPremise) axiom.premCt++;
		
		if ((pnItemPtr = pnItemPtr->next) == NULL && inPremise)
		{
			pnItemPtr = (pnResPtr != NULL) ? pnResPtr->params : NULL;
			inPremise = false;
		}
	}
	
	/* move items to axiom */
	_SWAP(axiom.items, itemVect.addr, ExprNode**);
	
	/* sort items */
	size_t itNum;
	
	for (itNum = 0; itNum < axiom.premCt && !hasError; ++itNum)
	{
		/* define if item is 'active' */
		ExprIter iter = getIter(&axiom.vars, axiom.items[itNum]);
		Boolean isActive = ndType(iter) == EXPR_PRED
						&& ndVal(iter).id >= ARITHMETIC_RELATIONS_COUNT;
		
		forParamsIf(iter, isActive)
			isActive = ndType(iter) == EXPR_CONST || ndType(iter) == EXPR_VAR;
		
		if (isActive)
		{
			_SWAP(axiom.items[itNum],
				 axiom.items[axiom.mainCt], ExprNode*);
			axiom.mainCt++;
		}
	}
	
	/* check if all variables occurs in main part */
	if (!hasError)
	{
		Boolean* usingMask = (Boolean*)calloc(axiom.vars.len, sizeof(Boolean));
		
		//~ for (itNum = 0; itNum < axiom.mainCt && !hasError; ++itNum)
		for (itNum = 0; itNum < axiom.mainCt; ++itNum)
			if (axiom.items[itNum] != NULL)
				checkVarsForUsing(getIter(&axiom.vars, axiom.items[itNum]), usingMask);
		
		size_t varNum;
		
		forVect(varNum, axiom.vars)
			if (!usingMask[varNum])
			{
				size_t varNum2;
				pnVarPtr = pnVarsPtr->params;
				for (varNum2 = 0; varNum2 < varNum; varNum2++)
					pnVarPtr = pnVarPtr->next;
				
				Error error = createParserError("variable ", modelPtr->currSrcPtr,
									pnVarPtr->lineNum, pnVarPtr->columnNum);
				addTextToError(&error, pnVarPtr->name);
				addTextToError(&error, " isn't used in main part of axiom premise");
				addError(error, modelPtr);
				
				hasError = true;
			}
			
		freePtr(usingMask);
	}
	
	if (hasError)
	{
		freeVect(itemVect);
		freeAxiom(&axiom);
		//~ return false;
		return;
	}
	
	/* add new axiom */
	addBack(axioms_m, Axiom, axiom);
	prepareServData(getAxPtr(axioms_m.len - 1));
	freeVect(itemVect);
}


void checkVarsForUsing(ExprIter iter, Boolean* usingMask)
{
	if (ndType(iter) == EXPR_VAR)
		usingMask[ndVal(iter).id] = true;
	else
		forParams(iter)
			checkVarsForUsing(iter, usingMask);
}

Boolean hasNullNode(ParserNode* pnPtr)
{
	if (pnPtr == NULL) return false;
	if (pnPtr->type == ND_NULL) return true;
	
	return hasNullNode(pnPtr->next) || hasNullNode(pnPtr->params);
}



ssize_t addNewVariable(ParserNode* pnVarPtr, Vector* varVectPtr, _md)
{
	if (pnVarPtr->type != ND_VAR)
	{
		addInnerError("addNewVariable: invalid variable node\n", modelPtr);
		return BAD_INDEX;
	}
	
	ParserNode* pnTypePtr = pnVarPtr->params;
	DataTypeId typeId = getTypeIdByName(pnTypePtr->name, modelPtr);
	
	if (typeId == BAD_INDEX)
		typeId = addDataType(pnTypePtr->name, modelPtr);
	
	if (typeId == BAD_INDEX)
	{
		addParserError("can't create new data type",
						pnTypePtr->lineNum, pnTypePtr->columnNum, modelPtr);
		return BAD_INDEX;
	}
	
	size_t varNum;
	Boolean isFound = false;
	
	/* check if there is variable with the same name */
	forVectIf(varNum, *varVectPtr, !isFound)
		isFound = (
			strcmp(ptr(Variable, *varVectPtr)[varNum].name,
					pnVarPtr->name) == 0 );
	
	if (isFound)
		addParserError("duplication of variable",
						pnVarPtr->lineNum, pnVarPtr->columnNum, modelPtr);
	
	Variable variable;
	variable.name = getDynamicStr(pnVarPtr->name);
	variable.dataType = typeId;
	addBack(*varVectPtr, Variable, variable);
	
	return varVectPtr->len - 1;
}




/* work with ParserNode */

void printParserNode(ParserNode* nodePtr, int layer)
{
	int i;
	for (i = 0; i < layer; i++) printf("  ");
	
	printf("%s", typeNames_g[nodePtr->type]);
	
	if (hasNodeName(nodePtr->type))
	{
		//~ setFormat(FM_YELL);
		printf(" %s", nodePtr->name);
		//~ setFormat(FM_NORM);
	}
	
	printf(" [%uld; %uld]", nodePtr->lineNum, nodePtr->columnNum);
	printf("\n");
	
	for (nodePtr = nodePtr->params; nodePtr != NULL; nodePtr = nodePtr->next)
		printParserNode(nodePtr, layer + 1);
}



Boolean hasNodeName(ParserNodeType type)
{
	return type == ND_NAME 		|| type == ND_FUNC 	|| type == ND_FUNC_DEC
		|| type == ND_VAR	 	|| type == ND_PRED 	|| type == ND_NAMED_CONST
		|| type == ND_INTEGER	|| type == ND_REAL;
		//~ || type == ND_TYPED_CONST;
}

void initNode(ParserNode* nodePtr, ParserNodeType type, char name[],
				int lineNum, int columnNum)
{
	nodePtr->type = type;
	nodePtr->lineNum = lineNum;
	nodePtr->columnNum = columnNum;
	nodePtr->params = nodePtr->next = NULL;
	
	if (hasNodeName(type))
	{
		nodePtr->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
		strcpy(nodePtr->name, name);
	}
	else nodePtr->name = NULL;
}


ParserNode* setType(ParserNode* nodePtr, ParserNodeType type)
{
	nodePtr->type = type;
	return nodePtr;
}

ParserNode* addParamToNode(ParserNode* nodePtr, ParserNode* paramPtr)
{
	if (nodePtr  == NULL) return paramPtr;
	if (paramPtr == NULL) return nodePtr;
	
	ParserNode* nodePtr_o = nodePtr;
	
	if (nodePtr->params == NULL)
		nodePtr->params = paramPtr;
	else
	{
		for (nodePtr = nodePtr->params; nodePtr->next != NULL;
			 nodePtr = nodePtr->next);
		
		nodePtr->next = paramPtr;
	}
	return nodePtr_o;
}


ParserNode* addNeighborToNode(ParserNode* nodePtr, ParserNode* neigPtr)
{
	if (nodePtr == NULL) return neigPtr;
	if (neigPtr == NULL) return nodePtr;
	
	ParserNode* nodePtr_o = nodePtr;
	for (; nodePtr->next != NULL; nodePtr = nodePtr->next);
	nodePtr->next = neigPtr;
	return nodePtr_o;
}


ParserNode* createNode(ParserNodeType type, char name[],
						int lineNum, int columnNum)
{
	ParserNode* nodePtr = (ParserNode*) malloc(sizeof(ParserNode));
	initNode(nodePtr, type, name, lineNum, columnNum);
	
	return nodePtr;
}

void freeNode(ParserNode* nodePtr)
{
	if (nodePtr == NULL) return;
	
	freeNode(nodePtr->params);
	freeNode(nodePtr->next);
	
	if (nodePtr->name != NULL)
		free(nodePtr->name);
	free(nodePtr);
}


/* garbage */

//~ void acceptRestrictions(ParserNode* pnRestrsPtr, _md)
//~ {
	//~ ParserNode* pnParPtr = pnRestrsPtr->params;
	//~ 
	//~ for (; pnParPtr != NULL; pnParPtr = pnParPtr->next)
	//~ {
		//~ Restriction restr;
		//~ initRestriction(&restr);
		//~ 
		//~ restr.root = acceptExprNode(pnParPtr, &restr.vars, DT_BOOL, modelPtr);
		//~ 
		//~ if (restr.root != NULL)
			//~ addBack(restrs_m, Restriction, restr);
	//~ }
//~ }

//~ void acceptFacts(ParserNode* pnFactsPtr, _md)
//~ {
	//~ if (pnFactsPtr->type != ND_FACTS)
		//~ return;
	//~ 
	//~ ParserNode* pnFactPtr = pnFactsPtr->params;
	//~ 
	//~ for (; pnFactPtr != NULL; pnFactPtr = pnFactPtr->next)
		//~ if (pnFactPtr->type == ND_AXIOM)
		//~ {
			//~ acceptAxiom(pnFactPtr, modelPtr);	/* work with axiom */
		//~ }
		//~ else if (pnFactPtr->type == ND_PRED || pnFactPtr->type == ND_NOT
				//~ || pnFactPtr->type == ND_EQ)	/* work with fact */
		//~ {
			//~ Vector varVect;
			//~ initVect(varVect, Variable);
			//~ ExprNode* nodePtr = acceptExprNode(pnFactPtr, &varVect,
												//~ DT_BOOL, modelPtr);
			//~ 
			//~ ExprIter iter = getIter(&varVect, nodePtr);
			//~ supp value;
			//~ 
			//~ if (nodePtr != NULL)
			//~ {
				//~ switch (ndType(iter))
				//~ {
					//~ case EXPR_PRED:	value = CONST_TRUE;					break;
					//~ case EXPR_NOT:	value = CONST_FALSE;  into(iter);	break;
					//~ case EXPR_EQ:
						//~ value = iter.nodePtr->params->next->value;
						//~ into(iter);
					//~ break;
					//~ default: break;
				//~ }
				//~ 
				//~ Func* funcPtr = (ndType(iter) == EXPR_PRED)
									//~ ? getPredPtr(ndVal(iter).id)
									//~ : getFuncPtr(ndVal(iter).id);
				//~ 
				//~ Vector paramVect;
				//~ initVect(paramVect, supp);
				//~ forParams(iter) addBack(paramVect, supp, ndVal(iter));
				//~ 
				//~ /* set new fact */
				//~ Fact fact = createFact(funcPtr, ptr(supp, paramVect), value);
				//~ setFact(&fact, modelPtr);
				//~ 
				//~ freeFact(&fact);
				//~ freeVect(paramVect);
			//~ }
		//~ }
//~ }

//~ void acceptDeclarations(ParserNode* pnDeclsPtr, _md)
//~ {
	//~ /* TODO: add more comments */
	//~ if (pnDeclsPtr->type != ND_DECLS)
		//~ return;
	//~ 
	//~ Vector parTypesVect;
	//~ initVect(parTypesVect, DataTypeId);
	//~ ParserNode* pnDeclPtr = pnDeclsPtr->params;
	//~ 
	//~ for (; pnDeclPtr != NULL; pnDeclPtr = pnDeclPtr->next)	/* in declarations*/
	//~ {
		//~ parTypesVect.len = 0;
		//~ char* funcName = pnDeclPtr->name;
//~ 
		//~ ParserNode* paramPtr = pnDeclPtr->params;
//~ 
		//~ for (; paramPtr != NULL; paramPtr = paramPtr->next) /* in params */
		//~ {
			//~ DataTypeId typeId = getTypeIdByName(paramPtr->name, modelPtr);
			//~ if (typeId == BAD_INDEX)
				//~ typeId = addDataType(paramPtr->name, modelPtr);
			//~ 
			//~ /* TODO: here must be error handling */
			//~ 
			//~ addBack(parTypesVect, DataTypeId, typeId);
		//~ }
		//~ 
		//~ size_t parCt = parTypesVect.len - 1;
		//~ DataTypeId* parTypes = ptr(DataTypeId, parTypesVect);
		//~ DataTypeId type = parTypes[parCt];
		//~ Func func = createFunc(funcName, parCt, parTypes, parTypes[parCt]);
		//~ 
		//~ if (type == DT_BOOL)
			//~ addPred(func, modelPtr);
		//~ else
			//~ addFunc(func, modelPtr);
	//~ }
//~ }

//~ Boolean checkAxiomStructure(ParserNode* pnExprPtr, _md)
//~ {
	//~ ParserNode* pnExprPtr_origin = pnExprPtr;
	//~ 
	//~ for (; pnExprPtr != NULL && pnExprPtr->type == ND_ALL;
		//~ pnExprPtr = pnExprPtr->params->next)
		//~ ;
	//~ 
	//~ if (pnExprPtr == NULL)
	//~ {
		//~ /* TODO: Parsing error. Empty axiom body. */
		//~ printf("Parsing error. Empty axiom body.");
		//~ return false;
	//~ }
	//~ 
	//~ Boolean isCorrect = pnExprPtr->type == ND_IMP && pnExprPtr != pnExprPtr_origin;
	//~ 
	//~ ParserNode* pnPremPtr = pnExprPtr->params;
	//~ ParserNode* pnResPtr  = pnExprPtr->params->next;
	//~ 
	//~ if (pnPremPtr->type == ND_AND)	pnPremPtr = pnPremPtr->params;
	//~ if (pnResPtr->type == ND_AND)	pnResPtr  = pnResPtr->params;
	//~ 
	//~ pnExprPtr = pnPremPtr;
	//~ Boolean isInPremise = true;
	//~ 
	//~ for (; pnExprPtr != NULL && isCorrect; )
	//~ {	
		//~ if (isInPremise)
			//~ isCorrect = pnExprPtr->type == ND_PRED || pnExprPtr->type == ND_EQ
						//~ || (pnExprPtr->type == ND_NOT
						//~ && pnExprPtr->params->type == ND_PRED);
		//~ else
			//~ isCorrect = pnExprPtr->type == ND_PRED || (pnExprPtr->type == ND_EQ
						//~ && pnExprPtr->params->type == ND_FUNC);
		//~ 
		//~ pnExprPtr = pnExprPtr->next;
		//~ 
		//~ if (isInPremise && (pnExprPtr == NULL || pnExprPtr == pnResPtr))
			 //~ pnExprPtr = pnResPtr, isInPremise = false;
	//~ }
	//~ 
	//~ if (!isCorrect)
	//~ {
		//~ /* TODO: Parsing error. Unexpected node type in axiom. */
		//~ printf("Parsing error. Unexpected node type \'%s\' in axiom.",
				//~ typeNames_g[pnExprPtr->type]);
		//~ return false;
	//~ }
	//~ 
	//~ return true;
//~ }


//~ void printExpr(Expression* exprPtr)
//~ {
	//~ if (exprPtr->type == EXPR_PRED || exprPtr->type == EXPR_CONST)
		//~ printf("%s", exprPtr->name);
	//~ 
	//~ if (exprPtr->params == NULL) return;
	//~ 
	//~ char* dev = "";
	//~ 
	//~ switch (exprPtr->type)
	//~ {
		//~ case EXPR_PRED:	dev = ", "; 	break;
		//~ case EXPR_AND: 	dev = " & "; 	break;
		//~ case EXPR_OR:  	dev = " | "; 	break;
		//~ default:						break;
	//~ }
	//~ 
	//~ printf("(");
	//~ 
	//~ for (exprPtr = exprPtr->params; exprPtr != NULL; exprPtr = exprPtr->next)
	//~ {
		//~ printExpr(exprPtr);
		//~ if (exprPtr->next != NULL)
			//~ printf("%s", dev);
	//~ }
	//~ 
	//~ printf(")");
//~ }
