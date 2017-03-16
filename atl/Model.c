/* Model.c
 * Defines functions for work with model and basic
 * data structures */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "Logic.h"
#include "Model.h"
#include "Parser.h"
#include "Expressions.h"
#include "Interpretation.h"


/* === Implementation === */

/* work with structures */

DataType createDataType(const char name[])
{
	size_t conNum;
	DataType type;
	type.name = getDynamicStr(name);
	initVect(type.constNames, char*);

	/* CONST_IDC, CONST_NULL */
	for (conNum = 0; conNum < RESERVED_CONST_COUNT; ++conNum)
		addBack(type.constNames, char*, NULL);

	return type;
}

void freeDataType(DataType* typePtr)
{
	freePtr(typePtr->name);
	freeVect(typePtr->constNames);
}


ExprNode* createExprNode(ExprType type)
{
	ExprNode* nodePtr = (ExprNode*) malloc(sizeof(ExprNode));
	nodePtr->type = type;
	nodePtr->dataType = 0;
	nodePtr->params = nodePtr->next = NULL;
	
	return nodePtr;
}

void freeExprNode(ExprNode* nodePtr)
{
	if (nodePtr == NULL) return;
    
    freeExprNode(nodePtr->params);
    freeExprNode(nodePtr->next);
    freePtr(nodePtr);
}


void initRestriction(Restriction* restrPtr)
{
	restrPtr->root = NULL;
	initVect(restrPtr->vars, Variable);
}

void freeRestriction(Restriction* restrPtr)
{
	freeExprNode(restrPtr->root);
	restrPtr->root = NULL;
	freeVect(restrPtr->vars);
}


Func createFunc(const char name[], size_t parCt, DataTypeId parTypes[],
										   DataTypeId dataType)
{
	Func func;
	func.name = getDynamicStr(name);
	func.parCt = parCt;
	func.oldFactId = 0;
	func.parTypes = (DataTypeId*) malloc(sizeof(DataTypeId) * parCt);
	memcpy(func.parTypes, parTypes, sizeof(DataTypeId) * parCt);
	func.dataType = dataType;
	
	initVect(func.data, supp);
	initVect(func.waitList, Task*);
	
	return func;
}

void freeFunc(Func* funcPtr)
{
	freePtr(funcPtr->name);
	freePtr(funcPtr->parTypes);
	freeVect(funcPtr->data);
	freeVect(funcPtr->waitList);
}


void freeAxiom(Axiom* axiomPtr)
{
	size_t itNum;
	
	if (axiomPtr->items != NULL)
		for (itNum = 0; itNum < axiomPtr->itemCt; ++itNum)
		{
			freeExprNode(axiomPtr->items[itNum]);
		}
	
	freePtr(axiomPtr->items);
	freeVect(axiomPtr->vars);
}

Fact createFact(Func* funcPtr, supp* params, supp value)
{
	Fact fact;
	fact.funcPtr = funcPtr;
	fact.params = (supp*) malloc(sizeof(supp) * funcPtr->parCt);
	memcpy(fact.params, params,  sizeof(supp) * funcPtr->parCt);
	fact.value = value;
	fact.axiomNum = BAD_INDEX;

	return fact;
}

Query createQuery(Func* funcPtr, supp* params)
{
	return createFact(funcPtr, params, CONST_IDC);
}

void freeFact(Fact* factPtr)
{
	freePtr(factPtr->params);
}

void freeQuery(Query* queryPtr)
{
	freeFact(queryPtr);
}

Task* createTask(Axiom* axPtr, supp* varValues)
{
	Task* taskPtr = (Task*)malloc(sizeof(Task));
	taskPtr->axPtr = axPtr;
	taskPtr->lastItNum = axPtr->mainCt;
	taskPtr->resultPtr =
		createExprResult(varValues, axPtr->vars.len, MD_NORMAL);
	initVect(taskPtr->tmpFacts, Fact);

	return taskPtr;
}

void freeTask(Task* taskPtr)
{
	freeVect(taskPtr->tmpFacts);
	freeExprResult(taskPtr->resultPtr);
	freePtr(taskPtr);
}


QueryIterator createQueryIterator(Query query)
{
	QueryIterator qiter;
	qiter.query = query;
	
	resetQIterator(&qiter);
	return qiter;
}

void resetQIterator(QueryIterator* qiterPtr)
{
	if (qiterPtr->query.funcPtr != NULL)
	{
		qiterPtr->pos = -(qiterPtr->query.funcPtr->parCt + 1);
		moveQIterator(qiterPtr);
	}
}

///////////////////
//~ supp ask(Query* queryPtr, _md)
//~ {
	//~ size_t parCt  = queryPtr->funcPtr->parCt;
	//~ size_t factCt = queryPtr->funcPtr->data.len / (parCt + 1);
	//~ size_t factNum, parNum;
	//~ supp* data = ptr(supp, queryPtr->funcPtr->data);
	//~ 
	//~ for (factNum = 0; factNum < factCt; factNum++)
	//~ {
		//~ for (parNum = 0; parNum < parCt
						 //~ && conCmp(queryPtr->params[parNum], data[parNum]);
						 //~ ++parNum);
//~ 
		//~ if (parNum == parCt)
			//~ return queryPtr->value = data[parCt];
		//~ 
		//~ data += (parCt + 1);
	//~ }
	//~ return queryPtr->value = CONST_IDC;
//~ }
///////////////

void moveQIterator(QueryIterator* qiterPtr)
{
	Func* funcPtr = qiterPtr->query.funcPtr;
	size_t parCt  = funcPtr->parCt;
	ssize_t dataLen = funcPtr->data.len;
	size_t parNum;
	supp* data = ptr(supp, funcPtr->data);
	supp* params = qiterPtr->query.params;
	Boolean isFound = false;
	
	qiterPtr->pos += parCt + 1;
	
	for (; !isFound && qiterPtr->pos < dataLen; qiterPtr->pos += parCt + 1)
	{
		isFound = true;
		
		for (parNum = 0; parNum < parCt && isFound; ++parNum)
			isFound &= conCmp(params[parNum], CONST_IDC)
					|| conCmp(params[parNum], data[qiterPtr->pos + parNum]);
		
		isFound &= conCmp(qiterPtr->query.value, CONST_IDC)
				|| conCmp(qiterPtr->query.value, data[qiterPtr->pos + parNum]);
	}
	
	if (isFound) qiterPtr->pos -= parCt + 1;
}


Boolean qiterIsValid(QueryIterator* qiterPtr)
{
	return 	qiterPtr->query.funcPtr != NULL &&
			qiterPtr->pos < qiterPtr->query.funcPtr->data.len;
}


Fact getFact(QueryIterator* qiterPtr)
{
	Func* funcPtr = qiterPtr->query.funcPtr;
	supp* dataPtr = ptr(supp, funcPtr->data);
	return createFact(funcPtr, dataPtr + qiterPtr->pos,
					dataPtr[qiterPtr->pos + funcPtr->parCt]);
}


/* work with model */

void initModel(_md)
{
	/* initialize vectors */
	initVect(preds_m,		Pred);
	initVect(funcs_m,		Func);
	initVect(axioms_m,		Axiom);
	initVect(taskPtrs_m,	Task*);
	initVect(tmpFacts_m,	Fact);
	initVect(restrs_m,		Restriction);
	initVect(types_m,		DataType);

	/* create standart datatypes */
	addDataType("Boolean",	modelPtr);
	addDataType("Integer",	modelPtr);
	addDataType("Real",		modelPtr);
	
	/* CONST_TRUE, CONST_FALSE */
	//~ DataType* boolPtr = ptr(DataType, types_m) + DT_BOOL;
	DataType* boolPtr = getTypePtr(DT_BOOL);
	addBack(boolPtr->constNames, char*, getDynamicStr("True"));
	addBack(boolPtr->constNames, char*, getDynamicStr("False"));
	
	/* create arithmetic fuctions */
	size_t funcNum;
	DataTypeId paramTypes[] = {DT_INT, DT_INT};
	
	for (funcNum = 0; funcNum < ARITHMETIC_FUNCTION_COUNT; ++funcNum)
	{	
		Func func = createFunc(	(char*)ARITH_FUNCTION_NAMES[funcNum],
								ARITH_FUNCTION_PAR_COUNTS[funcNum],
								paramTypes, DT_REAL);
		addFunc(func, modelPtr);
	}
	
	/* create arithmetic relations */
	size_t predNum;
	
	for (predNum = 0; predNum < ARITHMETIC_RELATIONS_COUNT; ++predNum)
	{	
		Pred pred = createFunc(	(char*)ARITH_RELATION_NAMES[predNum],
								ARITH_RELATION_PAR_COUNTS[predNum],
								paramTypes, DT_BOOL);
		addPred(pred, modelPtr);
	}
	
	/* other initialization */
	initVect(modelPtr->errors, Error);
	initVect(modelPtr->sources, Source);
	modelPtr->currSrcPtr = NULL;
	modelPtr->totalFactCt = 0;
	modelPtr->debugStream = modelPtr->errorStream = NULL;
}


void freeModel(_md)
{
	size_t predNum, funcNum, axNum, taskNum,
		   factNum, restrNum, typeNum, srcNum, errNum;

	freeServData(modelPtr);

	/* Predicates */
	forVect(predNum, preds_m)
		freeFunc(getPredPtr(predNum));
	
	/* Functions */
	forVect(funcNum, funcs_m)
		freeFunc(getFuncPtr(funcNum));
		
	/* Axioms */
	forVect(axNum, axioms_m)
		freeAxiom(getAxPtr(axNum));

	/* Tasks */
	forVect(taskNum, taskPtrs_m)
		freeTask(getTaskPtr(taskNum));

	/* Temp Facts */
	forVect(factNum, tmpFacts_m)
		freeFact(ptr(Fact, tmpFacts_m) + factNum);

	/* Restrictions */
	forVect(restrNum, restrs_m)
		freeRestriction(getRestrPtr(restrNum));

	/* DataTypes */
	forVect(typeNum, types_m)
		freeDataType(getTypePtr(typeNum));

	/* Sources */
	forVect(srcNum, modelPtr->sources)
		freeSource(ptr(Source, modelPtr->sources) + srcNum);
	
	/* Errors */
	forVect(errNum, modelPtr->errors)
		freeError(ptr(Error, modelPtr->errors) + errNum);

	/* Vectors */
	freeVect(preds_m);
	freeVect(funcs_m);
	freeVect(axioms_m);
	freeVect(taskPtrs_m);
	freeVect(tmpFacts_m)
	freeVect(restrs_m); 
	freeVect(types_m);
	freeVect(modelPtr->errors);
	freeVect(modelPtr->sources);
}


DataTypeId addDataType(const char name[], _md)
{
	if (getTypeIdByName(name, modelPtr) != BAD_INDEX)
	{
		return BAD_INDEX;
	}
	
	addBack(types_m, DataType, createDataType(name));
	return types_m.len - 1;
}

DataTypeId getTypeIdByName(const char name[], _md)
{
	size_t typeNum;
	
	forVect(typeNum, types_m)
	{
		DataType* typePtr = ptr(DataType, modelPtr->dataTypes) + typeNum;
		if (strcmp(typePtr->name, name) == 0)
			return typeNum;
	}
	return BAD_INDEX;
}

ssize_t addFunc(Func func, _md)
{
	if (getFuncOrPredByName(func.name, modelPtr) != NULL)
	{
		/* TODO: multi declaration of function */
		return BAD_INDEX;
	}
	
	addBack(funcs_m, Func, func);
	return funcs_m.len - 1;
}

ssize_t addPred(Pred pred, _md)
{
	if (getFuncOrPredByName(pred.name, modelPtr) != NULL)
	{
		/* TODO: multi declaration of function */
		return BAD_INDEX;
	}
	
	addBack(preds_m, Pred, pred);
	return preds_m.len - 1;
}


ssize_t getFuncNumByName(const char name[], _md)
{
	size_t funcNum;
	
	forVect(funcNum, funcs_m)
		if (strcmp(getFuncPtr(funcNum)->name, name) == 0)
			return funcNum;
	
	return BAD_INDEX;
}


ssize_t getPredNumByName(const char name[], _md)
{
	size_t predNum;
	
	forVect(predNum, preds_m)
		if (strcmp(getPredPtr(predNum)->name, name) == 0)
			return predNum;
		
	return BAD_INDEX;
}


Func* getFuncOrPredByName(const char name[], _md)	/* returns Func or Pred pointer */
{
	ssize_t predNum = getPredNumByName(name, modelPtr);
	
	if (predNum != BAD_INDEX)
		return getPredPtr(predNum);
	
	ssize_t funcNum = getFuncNumByName(name, modelPtr);
	
	if (funcNum != BAD_INDEX)
		return getFuncPtr(funcNum);
	
	return NULL;
}


supp getOrAddConstant(const char name[], DataTypeId typeId, _md)
{
	if (typeId < 0 || typeId >= types_m.len)
	{
		addInnerError("getOrAddConstant: invalid typeId\n", modelPtr);
		return CONST_NULL;
	}
	
	supp result;
	DataType* typePtr = getTypePtr(typeId);
	char** names = ptr(char*, typePtr->constNames);
	IdType conNum = RESERVED_CONST_COUNT;
	
	/* find existing constant */
	for (; conNum < typePtr->constNames.len; ++conNum)
		if (strcmp(name, names[conNum]) == 0)
		{
			result.id = conNum;
			return result;
		}
	
	/* or add new constant */
	if (typeId < RESERVED_DATA_TYPE_COUNT)
	{
		addInnerError("getOrAddConstant: try to modify reserved data type\n",
						modelPtr);
		return CONST_NULL;
	}
	
	if (typePtr->constNames.len == ID_CAPACITY)
	{
		addInnerError("getOrAddConstant: carrier power exited\n", modelPtr);
		return CONST_NULL;
	}
	
	name = getDynamicStr(name);
	addBack(typePtr->constNames, const char*, name);
	result.id = typePtr->constNames.len - 1;
	return result;
}



supp ask(Query* queryPtr, _md)
{
	size_t parCt  = queryPtr->funcPtr->parCt;
	size_t factCt = queryPtr->funcPtr->data.len / (parCt + 1);
	size_t factNum, parNum;
	supp* data = ptr(supp, queryPtr->funcPtr->data);
	
	for (factNum = 0; factNum < factCt; factNum++)
	{
		for (parNum = 0; parNum < parCt
						 && conCmp(queryPtr->params[parNum], data[parNum]);
						 ++parNum);

		if (parNum == parCt)
			return queryPtr->value = data[parCt];
		
		data += (parCt + 1);
	}
	return queryPtr->value = CONST_IDC;
}


Boolean setFact(Fact* factPtr, _md)
{
	Func* funcPtr = factPtr->funcPtr;
	supp value = factPtr->value;
	supp oldVal = ask(factPtr, modelPtr);	/* now factPtr->value is rewrited */
	size_t parNum;
	
	//~ printConstant(factPtr->value, funcPtr->type, modelPtr);
	//~ printf("\n");
	
	if (conCmp(oldVal, CONST_IDC))
	{
		/* write fact into func data	*/
		for (parNum = 0; parNum < funcPtr->parCt; ++parNum)
			addBack(funcPtr->data, supp, factPtr->params[parNum]);

		addBack(funcPtr->data, supp, value);
		modelPtr->totalFactCt++;

		/* check for tasks which are waiting for value
		 * of this fuction on this parametrs */
		size_t taskNum;
		
		forVect(taskNum, funcPtr->waitList)
		{
            Task* taskPtr = ptr(Task*, funcPtr->waitList)[taskNum];
			
            for (parNum = 0; parNum < funcPtr->parCt
				&& conCmp(factPtr->params[parNum],
					taskPtr->resultPtr->stopParams[parNum]); parNum++);
			
			if (parNum == funcPtr->parCt)
			{
				ExprValue answer;
				answer.nodePtr = taskPtr->resultPtr->stopIter.nodePtr;
				answer.value = value;
                addBack(taskPtr->resultPtr->valueCache, ExprValue, answer);
			
				/* move task to active tasks */
                addBack(taskPtrs_m, Task*, taskPtr);
                delFrom(funcPtr->waitList, Task*, taskNum);
                taskNum--;
			}
		}
		
		if (factPtr->axiomNum != BAD_INDEX && modelPtr->debugStream != NULL)
		{
			/* debug output */
			fprintf(modelPtr->debugStream, "Axiom ");
			fprintf(modelPtr->debugStream, "%u => ", factPtr->axiomNum + 1);
			factPtr->value = value;
			char* factStr = getFactStr(factPtr, modelPtr);
			fprintf(modelPtr->debugStream, "%s\n", factStr);
			freePtr(factStr);
			/* ============ */
		}
		
		return true;
	}
	else if (!conCmp(value, oldVal))
    {
		Error error;
		
		if (funcPtr->dataType == DT_BOOL)
			 error = createInterpretationError("redefenition of predicate");
		else error = createInterpretationError("redefenition of function");
		
		char* oldFactStr = getFactStr(factPtr, modelPtr);
		factPtr->value = value;
		char* newFactStr = getFactStr(factPtr, modelPtr);
		
		addTextToError(&error, "\n\t");
		addTextToError(&error, oldFactStr);
		addTextToError(&error, "\n\t");
		addTextToError(&error, newFactStr);
		
		freePtr(oldFactStr);
		freePtr(newFactStr);
		addError(error, modelPtr);
	}
	return false;
}



void addParserError(char msg[], size_t lineNum, size_t columnNum, _md)
{
	Error error = createParserError(msg, modelPtr->currSrcPtr,
									lineNum, columnNum);
	addBack(modelPtr->errors, Error, error);
	
	printError(&error, modelPtr->errorStream);
}

void addInterpretationError(char msg[], _md)
{
	Error error = createInterpretationError(msg);
	addBack(modelPtr->errors, Error, error);
	
	printError(&error, modelPtr->errorStream);
}

void addInnerError(char msg[], _md)
{
	Error error = createInnerError(msg);
	addBack(modelPtr->errors, Error, error);
	
	printError(&error, modelPtr->errorStream);
}

void addError(Error error, _md)
{
	addBack(modelPtr->errors, Error, error);
	
	printError(&error, modelPtr->errorStream);
}


/* output */

#define addText(to_str, from_str, to_len_var)                          \
{                                                                      \
	size_t from_len = strlen(from_str);                                \
	                                                                   \
	(to_str) = (char*)realloc((to_str), (to_len_var) + from_len + 2);  \
	strcpy((to_str) + (to_len_var), (from_str));                       \
	(to_len_var) += from_len;                                          \
}

/*
//~ #define addText(to_str, from_str, to_len_var)                                  \
//~ {                                                                              \
	//~ size_t from_len = strlen(from_str);                                        \
	                                                                           //~ \
	//~ if (to_str != NULL)                                                        \
	//~ {                                                                          \
		//~ (to_str) = (char*)realloc((to_str), (to_len_var) + from_len + 2);      \
		//~ strcpy((to_str) + (to_len_var), (from_str));                           \
		//~ (to_len_var) += from_len;                                              \
	//~ }                                                                          \
	//~ else                                                                       \
	//~ {                                                                          \
		//~ (to_str) = 
	//~ }                                                                         \
//~ }
*/

char* getConstStr(supp con, DataTypeId typeId, _md)
{
	if (typeId < 0 || typeId >= types_m.len)
		return getDynamicStr("__NULL");
	
	DataType* typePtr = getTypePtr(typeId);
	
	if (typeId == DT_INT || typeId == DT_REAL)
	{
		#define MAX_NUM_STRING_LEN 20
		shiftSuppBack(con);
		char numStr[MAX_NUM_STRING_LEN];
		
		if (typeId == DT_INT)
			sprintf(numStr, "%ld", con.integer);
		else if (typeId == DT_REAL)
			sprintf(numStr, "%lf", con.real);
		
		numStr[MAX_NUM_STRING_LEN - 1] = '\0';
		return getDynamicStr(numStr);
	}
	else if (con.id >= typePtr->constNames.len
		|| conCmp(con, CONST_NULL))
		return getDynamicStr("__NULL");
	else if (conCmp(con, CONST_IDC))
		return getDynamicStr("__IDC");
	else
		return getDynamicStr(ptr(char*, typePtr->constNames)[con.id]);
}


char* getFuncDeclStr(Func* funcPtr, _md)
{
	char* str = getDynamicStr("");
	size_t parNum, strLen = 0;
	
	addText(str, funcPtr->name, strLen);
	addText(str, ": (", strLen);
	
	for (parNum = 0; parNum < funcPtr->parCt; ++parNum)
	{
		char* typeStr = getTypePtr(funcPtr->parTypes[parNum])->name;
		addText(str, typeStr, strLen);
		
		if (parNum < funcPtr->parCt - 1) addText(str, ", ", strLen);
	}
	
	addText(str, ") -> ", strLen);
	addText(str, getTypePtr(funcPtr->dataType)->name, strLen);
	
	return str;
}


char* getFactStr(Fact* factPtr, _md)
{
	char* str = getDynamicStr("");
	size_t strLen = 0;
    Func* funcPtr = factPtr->funcPtr;

    if (funcPtr->dataType == DT_BOOL && conCmp(factPtr->value, CONST_FALSE))
		addText(str, "!", strLen);
	
	addText(str, funcPtr->name, strLen);
	addText(str, "(", strLen);
	size_t parNum;
	
	for (parNum = 0; parNum < funcPtr->parCt; ++parNum)
	{
		char* parStr = getConstStr(factPtr->params[parNum],
									funcPtr->parTypes[parNum], modelPtr);
		addText(str, parStr, strLen);
		if (parNum < funcPtr->parCt - 1)
			addText(str, ", ", strLen);
		freePtr(parStr);
	}
	
	addText(str, ")", strLen);
	
	if (funcPtr->dataType != DT_BOOL && !conCmp(factPtr->value, CONST_IDC))
	{
		char* resStr = getConstStr(factPtr->value, funcPtr->dataType, modelPtr);
		addText(str, " = ", strLen);
		addText(str, resStr, strLen);
		freePtr(resStr);
	}
	
	addText(str, ";", strLen);
	return str;
}



char* getExprParamsStr(ExprIter iter, char dev[], Boolean inBrackets, _md)
{
	char* str = getDynamicStr("");
	size_t strLen = 0;
	
	if (inBrackets) addText(str, "(", strLen);
	
	forParams(iter)
	{
		char* paramStr = getExprStr(iter, modelPtr);
		addText(str, paramStr, strLen);
		freePtr(paramStr);
		
		if (iter.nodePtr->next != NULL)
			addText(str, dev, strLen);
	}
	
	if (inBrackets) addText(str, ")", strLen);
	
	return str;
}



//~ char ARITH_RELATIONS_TOKENS[][5] = { " < ", " > ", " <= ", " >= " };
//~ 
//~ typedef enum {
	//~ AF_ABS,		AF_MAX,		AF_MIN,		AF_SIN,		AF_COS,		AF_TAN,
	//~ AF_ASIN,	AF_ACOS,	AF_ATAN,	AF_LOG,
	//~ AF_UMINUS,	AF_PLUS,	AF_MINUS,	AF_MULT,	AF_DIV,		AF_MOD,
	//~ AF_POW
//~ } ArithmeticFunctionId;
//~ 
//~ char ARITH_FUNCTIONS_TOKENS[][5] = {
	//~ "",			"",			"",			"",			",",
	//~ " + ", " - ", " * ", " / ", " - " };


char* getExprStr(ExprIter iter, _md)
{
	char* str = getDynamicStr("");
	char separator[4] = "   ";
	size_t strLen = 0;
	ExprType type = ndType(iter);
	size_t num = ndVal(iter).id;
	
	switch (type)
	{
		case EXPR_CONST:
			return getConstStr(ndVal(iter), ndDataType(iter), modelPtr);
		case EXPR_VAR:
			return getDynamicStr(
				ptr(Variable, *iter.varVectPtr)[num].name);
		case EXPR_EQ:	return getExprParamsStr(iter, " = ", false, modelPtr);
		case EXPR_LEQ:	return getExprParamsStr(iter, " <=> ", false, modelPtr);
		case EXPR_IMP:	return getExprParamsStr(iter, " => ", false, modelPtr);
		case EXPR_AND:	return getExprParamsStr(iter, " & ", false, modelPtr);
		case EXPR_OR:	return getExprParamsStr(iter, " | ", true, modelPtr);
		case EXPR_NOT:
		{
			char* paramStr = getExprStr(getParamIter(iter), modelPtr);
			addText(str, "!", strLen);
			addText(str, paramStr, strLen);
			freePtr(paramStr);
			return str;
		}	
		break;
		default:
			if (type == EXPR_PRED)
			{
				if (num < ARITHMETIC_RELATIONS_COUNT)
				{
					separator[1] = getPredPtr(num)->name[0];
					return getExprParamsStr(iter,
						separator, false, modelPtr);
				}
			
				Pred* predPtr = getPredPtr(num);
				char* paramsStr = getExprParamsStr(iter, ", ", true, modelPtr);
				
				addText(str, predPtr->name, strLen);
				addText(str, paramsStr, strLen);
				freePtr(paramsStr);
				
				return str;
			}
			else if (type == EXPR_FUNC)
			{
				if (num == AF_UMINUS)
				{
					char* paramStr = getExprStr(getParamIter(iter), modelPtr);
					addText(str, "-", strLen);
					addText(str, paramStr, strLen);
					freePtr(paramStr);
					return str;
				}
				else if (num < ARITHMETIC_FUNCTION_COUNT
						&& num >= AF_NAMED_FUNCTION_COUNT)
				{
					separator[1] = getFuncPtr(num)->name[0];
					return getExprParamsStr(iter,
						separator, num == AF_PLUS, modelPtr);
				}
				
				Func* funcPtr = getFuncPtr(num);
				char* paramsStr = getExprParamsStr(iter, ", ", true, modelPtr);
				
				addText(str, funcPtr->name, strLen);
				addText(str, paramsStr, strLen);
				freePtr(paramsStr);
				
				return str;
			}
			else if (type == EXPR_ALL || type == EXPR_EXT)
			{
				if (type == EXPR_ALL)
					 addText(str, "All ", strLen)
				else addText(str, "Ext ", strLen);
				
				char* varStr = ptr(Variable, *iter.varVectPtr)[num].name;
				char* typeStr = getTypePtr(
					ptr(Variable, *iter.varVectPtr)[num].dataType)->name;
				char* bodyStr = getExprStr(getParamIter(iter), modelPtr);
				
				addText(str, varStr, strLen);
				addText(str, ":", strLen);
				addText(str, typeStr, strLen);
				addText(str, " ", strLen);
				addText(str, bodyStr, strLen);
				freePtr(bodyStr);
				
				return str;
			}
	}
	
	return str;
}


char* getAxiomStr(Axiom* axPtr, _md)
{
	char* str = getDynamicStr("All ");
	size_t strLen = strlen(str);
	
	size_t varNum;
		
	forVect(varNum, axPtr->vars)
	{
		char* varStr = ptr(Variable, axPtr->vars)[varNum].name;
		char* typeStr = getTypePtr(
						ptr(Variable, axPtr->vars)[varNum].dataType)->name;
		
		addText(str, varStr, strLen);
		addText(str, ":", strLen);
		addText(str, typeStr, strLen);
		
		if (varNum != axPtr->vars.len - 1) addText(str, ", ", strLen);
	}
	addText(str, "\n    ", strLen);
	
	size_t itNum;
	
	for (itNum = 0; itNum < axPtr->premCt; ++itNum)
	{
		ExprNode* nodePtr = axPtr->items[itNum];
		char* itemStr = getExprStr(getIter(&axPtr->vars, nodePtr), modelPtr);
		addText(str, itemStr, strLen);
		freePtr(itemStr);
		
		if (itNum < axPtr->premCt - 1) addText(str, " & ", strLen);
	}
	addText(str, " => ", strLen);
	
	for (itNum = axPtr->premCt; itNum < axPtr->itemCt; ++itNum)
	{
		ExprNode* nodePtr = axPtr->items[itNum];
		char* itemStr = getExprStr(getIter(&axPtr->vars, nodePtr), modelPtr);
		addText(str, itemStr, strLen);
		freePtr(itemStr);
		
		if (itNum < axPtr->itemCt - 1) addText(str, " & ", strLen);
	}
	
	return str;
}


char* getRestrStr(Restriction* restrPtr, _md)
{
	return getExprStr(getIterForRestr(restrPtr, NULL), modelPtr);
}


/* debug output */

void printAxioms(_md)
{
	if (modelPtr->debugStream == NULL) return;
	
	size_t axNum;
	//~ fprintf(modelPtr->debugStream, "Axioms:\n");
	
	forVect(axNum, axioms_m)
	{
		Axiom* axPtr = getAxPtr(axNum);
		char* axStr = getAxiomStr(axPtr, modelPtr);
		fprintf(modelPtr->debugStream, "%s\n\n", axStr);
		freePtr(axStr);
	}
}



void printDeclarations(_md)
{
	if (modelPtr->debugStream == NULL) return;
	
	size_t predNum, funcNum;
	
	//~ fprintf(modelPtr->debugStream, "Declarations:\n");
	
	for (predNum = ARITHMETIC_RELATIONS_COUNT; predNum < preds_m.len; ++predNum)
	{
		Pred* predPtr = getPredPtr(predNum);
		
		char* funcStr = getFuncDeclStr(predPtr, modelPtr);
		fprintf(modelPtr->debugStream, "%s\n", funcStr);
		freePtr(funcStr);
	}
	
	for (funcNum = ARITHMETIC_FUNCTION_COUNT; funcNum < funcs_m.len; ++funcNum)
	{
		Func* funcPtr = getFuncPtr(funcNum);
		
		char* funcStr = getFuncDeclStr(funcPtr, modelPtr);
		fprintf(modelPtr->debugStream, "%s\n", funcStr);
		freePtr(funcStr);
	}
}


void printRestrictions(_md)
{
	if (restrs_m.len == 0 || modelPtr->debugStream == NULL) return;
	
	size_t resNum;
	//~ fprintf(modelPtr->debugStream, "Restrictions:\n");
	
	forVect(resNum, restrs_m)
	{
		Restriction* restrPtr = getRestrPtr(resNum);
		char* restrStr = getExprStr(getIterForRestr(restrPtr, NULL), modelPtr);
		fprintf(modelPtr->debugStream, "%s\n\n", restrStr);
		freePtr(restrStr);
	}
}





/*	Garbage

void printDataTypes(_md)
{
	size_t typeNum;
	print(FM_BLUE, "Data types:\n");
	
	forVect(typeNum, types_m)
	{
		DataType* typePtr = getTypePtr(typeNum);
		
		if (typeNum < RESERVED_DATA_TYPE_COUNT)
			setFormat(FM_YELL);
		
		printf("%s\t", typePtr->name);
		setFormat(FM_NORM);
		printf(" - %ld constants\n", typePtr->constNames.len
									- RESERVED_CONST_COUNT);
	}
}


void printConstant(supp con, DataTypeId typeId, _md)
{
	if (typeId < 0 || typeId >= types_m.len)
	{
		printf("NULL");
		return;
	}
	
	DataType* typePtr = getTypePtr(typeId);
	
	if (typeId == DT_INT || typeId == DT_REAL)
	{
		shiftSuppBack(con);
		
		if (typeId == DT_INT)
			printf("%ld", con.integer);
		else if (typeId == DT_REAL)
			printf("%lf", con.real);
	}
	else if (con.id >= typePtr->constNames.len
		|| conCmp(con, CONST_NULL))
		printf("NULL");
	else if (conCmp(con, CONST_IDC))
		printf("IDC");
	else
	{
		printf("%s", ptr(char*, typePtr->constNames)[con.id]);
	}
}

void printFacts(_md)
{
	size_t predNum, funcNum, factNum, parNum;
	size_t factCt, parCt;
	
	print(FM_BLUE, "Facts:\n");
	print(FM_YELL, "Predicates:\n");
	
	forVect(predNum, preds_m)
	{
		Pred* predPtr = getPredPtr(predNum);
		supp* data = ptr(supp, predPtr->data);
		parCt = predPtr->parCt;
		factCt = predPtr->data.len / (parCt + 1);
		
		for (factNum = 0; factNum < factCt; ++factNum)
		{
			if (conCmp(data[parCt], CONST_FALSE))
				printf("!");
			
			printf("%s(", predPtr->name);
			
			for (parNum = 0; parNum < parCt; ++parNum)
			{
				printConstant(data[parNum], predPtr->parTypes[parNum],modelPtr);
				
				if (parNum < parCt - 1)
					printf(", ");
			}
			printf(")  ");
			
			data += (parCt + 1);
		}
		if (factCt > 0) printf("\n");
	}
	
	print(FM_YELL, "Functions:\n");
	
	forVect(funcNum, funcs_m)
	{
		Func* funcPtr = getFuncPtr(funcNum);
		supp* data = ptr(supp, funcPtr->data);
		parCt = funcPtr->parCt;
		factCt = funcPtr->data.len / (parCt + 1);
		
		for (factNum = 0; factNum < factCt; ++factNum)
		{
			printf("%s(", funcPtr->name);
			
			for (parNum = 0; parNum < parCt; ++parNum)
			{
				printConstant(data[parNum], funcPtr->parTypes[parNum],modelPtr);
				
				if (parNum < parCt - 1)
					printf(", ");
			}
			printf(") = ");
			printConstant(data[parNum], funcPtr->dataType, modelPtr);
			printf("  ");
			
			data += (parCt + 1);
		}
		if (factCt > 0) printf("\n");
	}
	
}

void printFuncValue(Func* funcPtr, supp* params, Boolean withValue, _md)
{
	supp value;
	if (withValue)
	{
		Query query = createQuery(funcPtr, params);
		value = ask(&query, modelPtr);
		
		if (funcPtr->dataType == DT_BOOL && conCmp(value, CONST_FALSE))
			printf("!");
	}
	
	printf("%s(", funcPtr->name);
	size_t parNum;
	
	for (parNum = 0; parNum < funcPtr->parCt; ++parNum)
	{
		printConstant(params[parNum], funcPtr->parTypes[parNum], modelPtr);
		
		if (parNum < funcPtr->parCt - 1)
			printf(", ");
	}
	printf(")");
	
	if (withValue && funcPtr->dataType != DT_BOOL)
	{
		printf(" = ");
		printConstant(value, funcPtr->dataType, modelPtr);
	}
}

void printExpr(ExprIter iter, _md)
{
	char* begin = "";
	char* dev = "";
	char* end = "";
	
	switch (ndType(iter))
	{
		case EXPR_CONST:
			printConstant(ndVal(iter), ndDataType(iter), modelPtr);
		break;
		case EXPR_VAR:
			printf("%s", ptr(Variable, *iter.varVectPtr)[ndVal(iter).id].name);
		break;
		case EXPR_EQ:	dev = " = ";	break;
		case EXPR_LEQ:	dev = " <=> ";	break;
		case EXPR_IMP:	dev = " => ";	break;
		case EXPR_AND:	dev = " & ";	break;
		case EXPR_OR:	dev = " | "; begin = "("; end = ")";	break;
		case EXPR_NOT:	begin = "! ";	break;
		//~ case EXPR_ALL:	begin = "All "; dev = " ";	break;
		//~ case EXPR_EXT:	begin = "Ext "; dev = " ";	break;
		default:
		{
			if (ndType(iter) == EXPR_PRED || ndType(iter) == EXPR_FUNC)
			{
				Func* funcPtr = (ndType(iter) == EXPR_PRED)
								? getPredPtr(ndVal(iter).id)
								: getFuncPtr(ndVal(iter).id);
				
				printf("%s", funcPtr->name);
				begin = "(";
				dev = ", ";
				end = ")";
			}
			else if (ndType(iter) == EXPR_ALL || ndType(iter) == EXPR_EXT)
			{
				size_t varNum = ndVal(iter).id;
				
				if (ndType(iter) == EXPR_ALL)
					 printf("All ");
				else printf("Ext ");
				
				printf("%s ", ptr(Variable, *iter.varVectPtr)[varNum].name);
			}
			else begin = "???";
		}
		break;
	}
	
	printf("%s", begin);
	
	forParams(iter)
	{
		printExpr(iter, modelPtr);
		
		if (iter.nodePtr->next != NULL)
			printf("%s", dev);
	}
	
	printf("%s", end);
}

*/

//~ /* From Expression.h */
//~ ExprIter getIter(Vector* varVectPtr, ExprNode* nodePtr)
//~ {   
    //~ ExprIter iter;
    //~ iter.varVectPtr = varVectPtr;
    //~ iter.nodePtr = nodePtr;
    //~ iter.parNum = 0;
    //~ 
    //~ return iter;
//~ }
//~ 
//~ ExprIter getIterForRestr(Restriction* restrPtr, ExprNode* nodePtr)
//~ {
	//~ if (nodePtr == NULL) nodePtr = restrPtr->root;
    //~ 
    //~ ExprIter iter;
    //~ iter.varVectPtr = &restrPtr->vars;
    //~ iter.nodePtr = nodePtr;
    //~ iter.parNum = 0;
    //~ 
    //~ return iter;
//~ }
//~ 
//~ ExprIter getParamIter(ExprIter iter)	{ into(iter); return iter; }
//~ ExprIter getNextIter(ExprIter iter)		{ step(iter); return iter; }


