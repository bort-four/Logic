/* Interpretation.c	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Logic.h"
#include "Model.h"
#include "Expressions.h"
#include "Interpretation.h"


/* === local declarations === */

/* types & constants */

typedef enum {MD_POSITIVE, MD_NEGATIVE} WorkMode;

/* functions */

Boolean canUseFactIn(FactId factId, ExprIter iter, _md);
void workWithFact(Axiom* axPtr, size_t itNumOrigin, FactId factId, _md);
void getResult(Axiom* axPtr, supp* subst, _md);
void makeTask(Task* taskPtr, WorkMode mode, _md);
Fact makeFact(Axiom* axPtr, size_t itNum, ExprResult* resultPtr, _md);
void checkUndefinedValues(_md);

/* work with fact tree */
size_t addFactToTree(ServData* servPtr, supp* subst, FactId factId,
															size_t varCt);
FTNode* createFTNode(FTNode* parentNodePtr);
void freeFTNode(FTNode* nodePtr);
void printFactTree(Axiom* axPtr, ServData* servPtr, FTNode* nodePtr,
													size_t layer, _md);

/* debug output */
void printSubst(supp* subst, Vector* varVectPtr, _md);


/* === Implementation === */


void work(_md)
{	
	size_t predNum, factId, axNum, itNum;
	Boolean needWork = true;
	
	if (modelPtr->debugStream != NULL)
		fprintf(modelPtr->debugStream, "Interpretation started...\n");
	
	size_t oldFactCt = modelPtr->totalFactCt;

	while (needWork)
	{
		needWork = false;

		/* processing new facts	*/
		forVect(predNum, preds_m)    /* in predicats	*/
		{
			Pred* predPtr = getPredPtr(predNum);
			size_t parCt = predPtr->parCt;
			size_t oldFactId = predPtr->data.len;
			
			if (predPtr->data.len > predPtr->oldFactId) needWork = true;
			
			//~ printf("predicate %s\n", predPtr->name);

			forVect(axNum, axioms_m) /* in axioms	*/
			{
				Axiom* axPtr = getAxPtr(axNum);
				
				//~ printf("axiom %ld\n", axNum);

				for (itNum = 0; itNum < axPtr->mainCt; ++itNum)	/* in items	*/
				{
					ExprIter iter = getIter(&axPtr->vars, axPtr->items[itNum]);
					
					//~ printf("item %ld\n", itNum);
					
					if (ndVal(iter).id == predNum)
					{
						factId = predPtr->oldFactId;
						supp* factPtr = ptr(supp, predPtr->data) + factId;
						
						for (; factId < oldFactId; factId += parCt + 1)
						{
							if (	conCmp(factPtr[parCt], CONST_TRUE)
								&&	canUseFactIn(factId, iter, modelPtr))
							{
								//~ printf("-> axiom %ld, item %ld\n",
										//~ axNum, itNum);
								workWithFact(axPtr, itNum, factId, modelPtr);
							}
							
							factPtr += parCt + 1;
							
						} /* in facts */
					}	/* if item uses current predicate */
				}	/* in items */
			}	/* in axioms */
			
			predPtr->oldFactId = oldFactId;
		}	/* in predicates */
	
		/* processing active tasks	*/
		size_t taskNum;
		needWork |= (taskPtrs_m.len > 0);

		forVect(taskNum, taskPtrs_m)
			makeTask(getTaskPtr(taskNum), MD_POSITIVE, modelPtr);
		taskPtrs_m.len = 0;

		/* negative mode	*/
		if (!needWork)
		{
			/* loking for tasks which need a predicate value
			for negative conjunct (negative item)	*/

			forVect(predNum, preds_m)    /* in predicats	*/
			{
				Pred* predPtr = getPredPtr(predNum);
				
				forVect(taskNum, predPtr->waitList)
				{
					Task* taskPtr = ptr(Task*, predPtr->waitList)[taskNum];

					if (taskPtr->axPtr->items[taskPtr->lastItNum]->type
						== EXPR_NOT)
					{
						makeTask(taskPtr, MD_NEGATIVE, modelPtr);

						delFrom(predPtr->waitList, Task*, taskNum);
						taskNum--;
					}
				}	/* in tasks	*/
			}	/* in predicates	*/

			needWork |= (tmpFacts_m.len > 0);

			/* realize temp facts	*/
			size_t factNum;
			
			forVect(factNum, tmpFacts_m)
			{
				Fact* tmpFactPtr = ptr(Fact, tmpFacts_m) + factNum; 
				setFact(tmpFactPtr, modelPtr);
			}
			tmpFacts_m.len = 0;

		} /* negative mode	*/
	
	}	/* main loop */
	
	/* debug output */
	//~ forVect(axNum, axioms_m)
	//~ {
		//~ Axiom* axPtr = getAxPtr(axNum);
		//~ printf("=== Fact tree for axiom %ld ===\n", axNum);
		//~ 
		//~ for (itNum = 0; itNum < axPtr->mainCt; ++itNum)
		//~ {
			//~ printf("Item %ld: ", itNum);
			//~ ServData* sdPtr = axPtr->servData + itNum;
			//~ size_t varNum;
			//~ 
			//~ for (varNum = 0; varNum < sdPtr->varCt; ++varNum)
				//~ printf("%ld ", sdPtr->varNums[varNum]);
			//~ printf("\n");
			//~ 
			//~ printFactTree(axPtr, sdPtr, sdPtr->factTreePtr, 0, modelPtr);
		//~ }
		//~ printf("==========\n");
	//~ }
	
	checkUndefinedValues(modelPtr);
	
	if (modelPtr->debugStream != NULL)
	{
		fprintf(modelPtr->debugStream, "New fact count: ");
		fprintf(modelPtr->debugStream, "%u\n",
				modelPtr->totalFactCt - oldFactCt);
	}
	//~ freeServData(modelPtr);
}


void checkUndefinedValues(_md)
{
	size_t predNum, funcNum, taskNum;
	
	forVect(predNum, preds_m)
	{
		Pred* predPtr = getPredPtr(predNum);
		
		forVect(taskNum, predPtr->waitList)
		{
            Task* taskPtr = ptr(Task*, predPtr->waitList)[taskNum];
			Fact fact = createFact(predPtr, taskPtr->resultPtr->stopParams,
									CONST_IDC);
			Error error = createInterpretationError(
							"undefined value of predicate\n    ");
			addTextToError(&error, getFactStr(&fact, modelPtr));
			addError(error, modelPtr);
		}
	}
	
	forVect(funcNum, funcs_m)
	{
		Func* funcPtr = getFuncPtr(funcNum);
		
		forVect(taskNum, funcPtr->waitList)
		{
            Task* taskPtr = ptr(Task*, funcPtr->waitList)[taskNum];
			Fact fact = createFact(funcPtr, taskPtr->resultPtr->stopParams,
									CONST_IDC);
			Error error = createInterpretationError(
							"undefined value of function\n    ");
			addTextToError(&error, getFactStr(&fact, modelPtr));
			addError(error, modelPtr);
		}
	}
}



void makeTask(Task* taskPtr, WorkMode mode, _md)
{
	ExprResult* resultPtr = taskPtr->resultPtr;
	Axiom* axPtr = taskPtr->axPtr;
	size_t axNum = axPtr - getAxPtr(0);
	size_t itNum = taskPtr->lastItNum;
	
	/* debugg output */
	//~ printf("task for axiom %ld  ", axNum + 1);
	//~ printSubst(taskPtr->resultPtr->varValues, &axPtr->vars, modelPtr);
	//~ printf(" itNum = %ld, mode = %d\n", itNum, mode);
	/* ============= */
	
	/* check dependences in premise	*/
	resultPtr->stopIter.nodePtr = NULL;
	
	for (; itNum < axPtr->premCt && !isValid(resultPtr->stopIter); ++itNum)
	{
		/* try to calculate item value */
		ExprIter iter = getIter(&axPtr->vars, axPtr->items[itNum]);
		getExprValue(iter, resultPtr, modelPtr);
		//~ printf("\n");	/* debugg output */
		
		/* if there is negative node, ignore indefinite predicate
		 * in negative items */
		if (conCmp(resultPtr->value, CONST_IDC) && mode == MD_NEGATIVE
			&& ndType(iter) == EXPR_NOT
			&& ndType(resultPtr->stopIter) == EXPR_PRED)
			resultPtr->stopIter.nodePtr = NULL;
		
		/* if some item in premise is false, remove task */
		if (conCmp(resultPtr->value, CONST_FALSE))
			return freeTask(taskPtr);
		
		/* remove old saved values in valueCache */
		//~ if (!isValid(resultPtr->stopIter)) resultPtr->valueCache.len = 0;
	}
	
	/* check dependences in result part	*/
	for (; itNum < axPtr->itemCt && !isValid(resultPtr->stopIter); ++itNum)
	{
		ExprIter iter = getIter(&axPtr->vars, axPtr->items[itNum]);
		ExprIter paramIter = getParamIter(iter);
		
		if (ndType(iter) == EXPR_EQ)
		{
			/* check value node */
			ExprIter valueIter = getNextIter(paramIter);
			paramIter = getParamIter(paramIter);
			
			//~ resultPtr->currIter = valueIter;
			getExprValue(valueIter, resultPtr, modelPtr);
			//~ printf("\n");	/* debugg output */
		}
		
		/* check params */
		forIterIf(paramIter, !isValid(resultPtr->stopIter))
		{
			//~ resultPtr->currIter = paramIter;
			getExprValue(paramIter, resultPtr, modelPtr);
			//~ printf("\n");	/* debugg output */
		}
	}
	
	/* if can't calculate some value, add task in wait list
	 * of needed function or predicate */
	if (isValid(resultPtr->stopIter))
	{
		Func* funcPtr = (ndType(resultPtr->stopIter) == EXPR_PRED)
						? getPredPtr(ndVal(resultPtr->stopIter).id)
						: getFuncPtr(ndVal(resultPtr->stopIter).id);
		
		taskPtr->lastItNum = itNum - 1;
		addBack(funcPtr->waitList, Task*, taskPtr);
		
		/* debugg output */
		//~ printf("    added to wait list of function %s\n", funcPtr->name);
		/* ============= */
		
		return;
	}
	
	/* make negative facts in negative mode */
	if (mode == MD_NEGATIVE)
	{
		for (itNum = axPtr->mainCt; itNum < axPtr->premCt; ++itNum)
			if (axPtr->items[itNum]->type == EXPR_NOT)
			{
				Fact tmpFact = makeFact(axPtr, itNum, resultPtr, modelPtr);
				tmpFact.axiomNum = axNum;
				addBack(tmpFacts_m, Fact, tmpFact);
			}
	}
	
	/* generate new facts */
	for (itNum = axPtr->premCt; itNum < axPtr->itemCt; ++itNum)
	{
		Fact fact = makeFact(axPtr, itNum, resultPtr, modelPtr);
		
		if (mode == MD_NEGATIVE)
		{
			fact.axiomNum = axNum;
			addBack(tmpFacts_m, Fact, fact);
		}
		else
		{
			setFact(&fact, modelPtr);
			freeFact(&fact);
		}
	}
	
	freeTask(taskPtr);
}


Fact makeFact(Axiom* axPtr, size_t itNum, ExprResult* resultPtr, _md)
{
	ExprIter iter = getIter(&axPtr->vars, axPtr->items[itNum]);
	supp value, *params;
	
	if (ndType(iter) == EXPR_PRED)
	{
		value = CONST_TRUE;
	}
	else if (ndType(iter) == EXPR_NOT)
	{
		value = CONST_FALSE;
		into(iter);
	}
	else if (ndType(iter) == EXPR_EQ)
	{
		into(iter);
		//~ resultPtr->currIter = getNextIter(iter);
		value = getExprValue(getNextIter(iter), resultPtr, modelPtr);
		//~ printf("\n");	/* debugg output */
	}
	
	ExprIter paramIter = getParamIter(iter);
	forIter(paramIter);
	params = (supp*)malloc(paramIter.parNum * sizeof(supp));
	
	paramIter = getParamIter(iter);
	forIter(paramIter)
	{
		//~ resultPtr->currIter = paramIter;
		params[paramIter.parNum] = getExprValue(paramIter, resultPtr, modelPtr);
		//~ printf("\n");	/* debugg output */
	}
	
	Func* funcPtr = (ndType(iter) == EXPR_PRED) ? getPredPtr(ndVal(iter).id)
												: getFuncPtr(ndVal(iter).id);
	
	Fact fact = createFact(funcPtr, params, value);
	fact.axiomNum = axPtr - getAxPtr(0);
	freePtr(params);
	return fact;
}



void workWithFact(Axiom* axPtr, size_t itNumOrigin, FactId factId, _md)
{
	ExprIter iter = getIter(&axPtr->vars, axPtr->items[itNumOrigin]);
	supp* factPtr = ptr(supp, getPredPtr(ndVal(iter).id)->data) + factId;
	
	/* debug output */
	//~ Pred* predPtr = getPredPtr(ndVal(iter).id);
	//~ Fact fact = createFact(predPtr, factPtr, CONST_TRUE);
	//~ char* factStr = getFactStr(&fact, modelPtr);
	//~ printf("%s -> [%ld, %ld]\n", factStr, axPtr - getAxPtr(0) + 1, itNumOrigin);
	//~ freePtr(factStr);
	/* ================= */
	
	size_t varNum;
	const size_t varCt = axPtr->vars.len;
	
	/* write initial substitution - fact in context of axiom */
	ServData* servPtrOrigin = axPtr->servData + itNumOrigin;
	
	for (varNum = 0; varNum < varCt; ++varNum)
		servPtrOrigin->currSubst[varNum] = CONST_IDC;
	
	forParams(iter)
		if (ndType(iter) == EXPR_VAR)
			servPtrOrigin->currSubst[ndVal(iter).id] = factPtr[iter.parNum];
	
	/* add new fact into fact tree */
	size_t posOrigin =
		addFactToTree(servPtrOrigin, servPtrOrigin->currSubst, factId, varCt);
	
	/* debug output */
	//~ printf("=== %ld ===\n", servPtrOrigin->iters[0].depth);
	//~ printf("    [");
	//~ FTIterator ftIter = servPtrOrigin->iters[0]; 
	//~ for (; isValid(ftIter); )
	//~ {
		//~ printf("%ld ", ftIter.pos);
		//~ FTI_moveUp(ftIter);
	//~ }
	//~ printf("]  ");
	//~ printSubst(servPtrOrigin->currSubst, &axPtr->vars, modelPtr);
	//~ printf("\n");
	//~ printf("==========\n");
	//~ size_t itNum0;
	//~ for (itNum0 = 0; itNum0 < axPtr->mainCt; ++itNum0)
	//~ {
		//~ printFactTree(axPtr, axPtr->servData + itNum0, axPtr->servData[itNum0].factTreePtr, 0, modelPtr);
		//~ printf("------\n");
	//~ }
	//~ printf("==========\n");
	/* ================= */
	
	/* variables for macros */
	supp _value;
	FTNode* _nodePtr;
	FTParam* _params;
	FTIterator _iter2, _iter0;
	
	/* other inner variables */
	supp *lastSubst, *resultSubst = (supp*)malloc(varCt * sizeof(supp));
	ServData* servPtr, *nextServPtr;
	FTIterator* iterPtr;
	Boolean flag;
	ssize_t itNum = 0, itNum2;
	Boolean swapItems = servPtrOrigin->varCt > 0;
	ssize_t newItNum = (swapItems) ? 0 : itNumOrigin;
	
	if (swapItems)
		_SWAP(axPtr->servData[itNumOrigin], axPtr->servData[0], ServData);
	
	/* main loop */
	while (itNum >= 0)
	{
		if (itNum == axPtr->actCt)
		{
			axPtr->servData[newItNum].currIter.pos = posOrigin;
			
			for (flag = true, itNum2 = axPtr->actCt;
					itNum2 < axPtr->mainCt && flag; ++itNum2)
				flag = FTI_isValid(axPtr->servData[itNum2].currIter);
			
			itNum2 = (flag) ? 0 : -1;
			
			while (itNum2 >= 0)
			{
				if (itNum2 == axPtr->mainCt)
				{
					Task* taskPtr = createTask(axPtr, resultSubst);
					addBack(taskPtrs_m, Task*, taskPtr);
					itNum2--;
					
					/* debug output */
					//~ printf("    result = ");
					//~ printSubst(resultSubst, &axPtr->vars, modelPtr);
					//~ printf("\n");
					/* ============ */
				}
				else if (axPtr->servData[itNum2].currIter.pos
						== axPtr->servData[itNum2].currIter.nodePtr->parCt)
				{
					itNum2--;
				}
				else
				{
					servPtr = axPtr->servData + itNum2;
					iterPtr = &(servPtr->currIter);
					
					FactId factId
						= (FactId)iterPtr->nodePtr->params[iterPtr->pos].con.id;

					ExprIter iter;
					initIter(iter, &axPtr->vars, axPtr->items[servPtr->itNum]);
					Pred* predPtr = getPredPtr(ndVal(iter).id);
					supp* factPtr = ptr(supp, predPtr->data) + factId;
					
					forParams (iter)	/* write result substitution */
						if (ndType(iter) == EXPR_VAR)
							resultSubst[ndVal(iter).id] = factPtr[iter.parNum];
						
					if (itNum2 == newItNum)
						 iterPtr->pos = iterPtr->nodePtr->parCt;
					else iterPtr->pos++;

					itNum2++;
					
					if (itNum2 < axPtr->mainCt)
					{
						if (itNum2 == newItNum)
							 axPtr->servData[itNum2].currIter.pos = posOrigin;
						else axPtr->servData[itNum2].currIter.pos = 0;
					}
				}
			}
			
			itNum = axPtr->actCt - 1;
		}
		else if (!FTI_isValid(axPtr->servData[itNum].iters[itNum]))
		{
			itNum--;
		}
		else
		{
			servPtr = axPtr->servData + itNum;
			iterPtr = servPtr->iters + itNum;

			servPtr->currIter = *iterPtr;
			FTI_moveDown(servPtr->currIter);

			if (servPtr->itNum != itNumOrigin)
			{
				lastSubst = (itNum == 0) ? axPtr->servData[0].currSubst
										 : axPtr->servData[itNum - 1].currSubst;
				
				/* write current subst */
				for (varNum = 0; varNum < varCt; ++varNum)
					servPtr->currSubst[varNum] = lastSubst[varNum];
				
				FTI_writeSubst(*iterPtr, *servPtr, servPtr->currSubst);
				
				/* move iterator next */
				FTI_moveNext(*iterPtr, *servPtr, lastSubst);
			}
			else iterPtr->nodePtr = NULL;
			
			// debug output
			//~ printf("    ");
			//~ printSubst(servPtr->currSubst, &axPtr->vars, modelPtr);
			//~ printf("\n");
			// ============
			
			/* update next items */
			flag = true;
			
			for (itNum2 = itNum + 1; itNum2 < axPtr->actCt && flag; ++itNum2)
			{
				nextServPtr = axPtr->servData + itNum2;

				if ((flag = nextServPtr->factTreePtr != NULL))
				{
					nextServPtr->iters[itNum + 1] = nextServPtr->iters[itNum];
					
					FTI_moveOn(nextServPtr->iters[itNum + 1], *nextServPtr,
								servPtr->currSubst);
					
					flag = FTI_isValid(nextServPtr->iters[itNum + 1]);
				}
			}
			
			if (flag) itNum++;
		}
	}
	
	/* restore structure */
	FTI_inBegin(axPtr->servData[0].iters[0], axPtr->servData[0]);
	axPtr->servData[0].currIter = axPtr->servData[0].iters[0];
	
	if (swapItems)
		_SWAP(axPtr->servData[itNumOrigin], axPtr->servData[0], ServData);
	
	freePtr(resultSubst);
}




void check(_md)
{
	if (modelPtr->debugStream != NULL)
		fprintf(modelPtr->debugStream, "Check started...\n");
	
	size_t restrNum;
	
	forVect(restrNum, restrs_m)
	{
		Restriction* restrPtr = getRestrPtr(restrNum);
		ExprIter rootIter = getIter(&restrPtr->vars, restrPtr->root);
		ExprResult* resultPtr
			= createExprResult(NULL, restrPtr->vars.len, MD_NO_SAVE);
		
		getExprValue(rootIter, resultPtr, modelPtr);
		
		if (!conCmp(resultPtr->value, CONST_TRUE))
		{
			Error error
				= createInterpretationError("restriction check failed\n\t");
			char* restrStr = getRestrStr(restrPtr, modelPtr);
			addTextToError(&error, restrStr);
			freePtr(restrStr);
			
			addError(error, modelPtr);
		}
		
		freeExprResult(resultPtr);
	}
	
	if (modelPtr->debugStream != NULL)
		fprintf(modelPtr->debugStream, "Check finished.\n");
}


Boolean canUseFactIn(FactId factId, ExprIter iter, _md)
{
	supp* factPtr = ptr(supp, getPredPtr(ndVal(iter).id)->data) + factId;
	
	forParams(iter)
		if (ndType(iter) == EXPR_VAR)	/* check for selfcrossing */
		{
			ExprIter iter2 = iter; step(iter2);

			forIter(iter2)
				if (	ndType(iter2) == EXPR_VAR
					&&	ndVal(iter).id == ndVal(iter2).id
					&&	!conCmp(factPtr[iter.parNum], factPtr[iter2.parNum]))
					return false;
		}
		else if (!conCmp(ndVal(iter), factPtr[iter.parNum]))
			return false;	/* check for constant equality */
	
	return true;
}



size_t addFactToTree(ServData* servPtr, supp* subst, FactId factId,
															size_t varCt)
{
	if (servPtr->factTreePtr == NULL)
		servPtr->factTreePtr = createFTNode(NULL);
	
	FTNode* nodePtr = servPtr->factTreePtr;
	size_t layer;
	
	for (layer = 0; layer < servPtr->varCt; ++layer)
	{
		FTParam* params = nodePtr->params;
		supp value = subst[servPtr->varNums[layer]];
		/* value shouldn't be IDC or so one */
		
		/* find value in array of node */
		size_t conNum;
		
		for (conNum = 0; conNum < nodePtr->parCt
						&& params[conNum].con.id < value.id; ++conNum);
		
		if (conNum < nodePtr->parCt && conCmp(params[conNum].con, value))
		{
			/* if found do nothing */
		}
		else /* if not found extand array and add new value saving order */
		{
			nodePtr->parCt++;
			FTParam* newParams
				= (FTParam*)malloc(nodePtr->parCt * sizeof(FTParam));
			size_t conNum2;
			
			for (conNum2 = 0; conNum2 < conNum; ++conNum2)
				newParams[conNum2] = params[conNum2];
			
			for (conNum2 = conNum + 1; conNum2 < nodePtr->parCt; ++conNum2)
				newParams[conNum2] = params[conNum2 - 1];
			
			//~ _SWAP(newParams, params, FTParam*);
			freePtr(params);
			nodePtr->params = params = newParams;
			
			params[conNum].con = value;
			params[conNum].nodePtr = createFTNode(nodePtr);
			params[conNum].nodePtr->parentPtr = nodePtr;
			params[conNum].nodePtr->parentPos = conNum;
			
			/* update parentPos property in next params */
			for (conNum2 = conNum + 1; conNum2 < nodePtr->parCt; ++conNum2)
				params[conNum2].nodePtr->parentPos++;
		}
		
		nodePtr = params[conNum].nodePtr;
	}
	
	/* now nodePtr points to layer of fact identificators */
	nodePtr->parCt++;
	nodePtr->params = (FTParam*)realloc(nodePtr->params,
										nodePtr->parCt * sizeof(FTParam));
	
	nodePtr->params[nodePtr->parCt - 1].con.id = factId;
	nodePtr->params[nodePtr->parCt - 1].nodePtr = NULL;
	
	/* initialize iterator	*/
	servPtr->iters[0].nodePtr = nodePtr;
	servPtr->iters[0].depth = layer;
	//~ servPtr->iters[0].pos = nodePtr->parCt - 1;
	FTI_moveUp(servPtr->iters[0]);
	
	servPtr->currIter.pos = 0;
	servPtr->currIter.depth = 0;
	servPtr->currIter.nodePtr = servPtr->factTreePtr;
	
	return nodePtr->parCt - 1;
}


void prepareServData(Axiom* axPtr)
{
	if (axPtr->servData != NULL) return;
	
	size_t itNum;
	
	//~ forVect(axNum, axioms_m) 	/* in axioms	*/
	//~ {
	
	//~ Axiom* axPtr = getAxPtr(axNum);
	axPtr->servData = (ServData*)malloc(axPtr->mainCt * sizeof(ServData));
	
	/* get counts of using for each variable	*/
	size_t* useCounts = (size_t*)calloc(axPtr->vars.len, sizeof(size_t));
	
	for (itNum = 0; itNum < axPtr->mainCt; ++itNum)
	{
		ExprIter iter = getIter(&axPtr->vars, axPtr->items[itNum]);
		
		forParams(iter)
			if (ndType(iter) == EXPR_VAR) useCounts[ndVal(iter).id]++;
	}
	
	/* create service data */
	
	for (itNum = 0; itNum < axPtr->mainCt; ++itNum)
	{
		//~ ServData* sdPtr = axPtr->servData + itNum;
		ServData servData;
		//~ servData.itNum = itNum;
		servData.varCt = 0;
		servData.varNums = NULL;
		servData.factTreePtr = NULL;
		servData.currIter.nodePtr = NULL;
		servData.currSubst = (supp*)malloc(axPtr->vars.len * sizeof(supp));
		
		ExprIter iter = getIter(&axPtr->vars, axPtr->items[itNum]);
		//~ size_t itNumBegin = 0, itNumEnd = axPtr->mainCt - 1;
		
		/* write array of active vars for each main item	*/
		forParams(iter)
			if (ndType(iter) == EXPR_VAR && useCounts[ndVal(iter).id] > 1)
			{
				/* check for unique */
				size_t varNum;
				
				for (varNum = 0; varNum < servData.varCt
						&& servData.varNums[varNum] != ndVal(iter).id;
						++varNum);
				
				if (varNum == servData.varCt)
				{
					servData.varCt++;
					servData.varNums = realloc(servData.varNums,
										servData.varCt * sizeof(size_t));
					servData.varNums[varNum] = ndVal(iter).id;
				}
			}
		
		/* create iterators */
		servData.iters
			= (FTIterator*) malloc(axPtr->mainCt * sizeof(FTIterator));
		
		size_t itNum2;
		for (itNum2 = 0; itNum2 < axPtr->mainCt; ++itNum2)
			servData.iters[itNum2].nodePtr = NULL;

		axPtr->servData[itNum] = servData;

		if (servData.varCt > 0)
		{
			/* if item is active, move it in begin part */
			size_t itNum2 = itNum;
			axPtr->actCt++;
			
			while ((ssize_t)itNum2 - 1 >= 0
					&& axPtr->servData[itNum2 - 1].varCt == 0)
			{
				_SWAP(axPtr->items[itNum2],
					 axPtr->items[itNum2 - 1], ExprNode*);
				_SWAP(axPtr->servData[itNum2],
					 axPtr->servData[itNum2 - 1], ServData);
				itNum2--;
			}
		}
		
		
	} /* in items */
	
	for (itNum = 0; itNum < axPtr->mainCt; ++itNum)
		axPtr->servData[itNum].itNum = itNum;
	
	freePtr(useCounts);
	//~ }
}


void freeServData(_md)
{
	size_t axNum, itNum;
	
	forVect(axNum, axioms_m)
	{
		Axiom* axPtr = getAxPtr(axNum);
		
		for (itNum = 0; itNum < axPtr->mainCt; ++itNum)
		{
			ServData* sdPtr = axPtr->servData + itNum;
			freePtr(sdPtr->varNums);
			freePtr(sdPtr->currSubst);
			freeFTNode(sdPtr->factTreePtr);
		}
		
		freePtr(axPtr->servData);
	}
}


FTNode* createFTNode(FTNode* parentNodePtr)
{
	FTNode* nodePtr = (FTNode*)malloc(sizeof(FTNode));
	nodePtr->parCt = 0;
	nodePtr->parentPos = 0;
	nodePtr->params = NULL;
	nodePtr->parentPtr = parentNodePtr;
	
	return nodePtr;
}

void freeFTNode(FTNode* nodePtr)
{
	if (nodePtr == NULL) return;
	
	size_t conNum;
	for (conNum = 0; conNum < nodePtr->parCt; ++conNum)
		freeFTNode(nodePtr->params[conNum].nodePtr);
	freePtr(nodePtr);
}


void printFactTree(Axiom* axPtr, ServData* servPtr, FTNode* nodePtr,
													size_t layer, _md)
{
	if (nodePtr == NULL) return;
	
	size_t conNum;
	Variable* varPtr = NULL;
	if (layer < servPtr->varCt)
		varPtr = ptr(Variable, axPtr->vars) + servPtr->varNums[layer];
	
	for (conNum = 0; conNum < nodePtr->parCt; ++conNum)
	{
		size_t spNum;
		for (spNum = 0; spNum < layer; ++spNum) printf("  ");
		
		if (layer == servPtr->varCt)
		{
			printf("factId = %u, parentPos = %u\n",
					nodePtr->params[conNum].con.id,
					nodePtr->parentPos);
		}
		else
		{
			printf("%s = ", varPtr->name);
			char* constStr = getConstStr(nodePtr->params[conNum].con,
								varPtr->dataType, modelPtr);
			printf("%s", constStr); freePtr(constStr);
			printf(", parentPos = %u\n", nodePtr->parentPos);
			
			printFactTree(axPtr, servPtr, nodePtr->params[conNum].nodePtr,
				layer + 1, modelPtr);
		}
	}
}




void printSubst(supp* subst, Vector* varVectPtr, _md)
{
	printf("{");
	size_t varNum, varCt = varVectPtr->len;
	
	for (varNum = 0; varNum < varCt; ++varNum)
		if (conCmp(subst[varNum], CONST_IDC))
			 printf("_ ");
		else
		{
			char* constStr = getConstStr(subst[varNum],
								ptr(Variable, *varVectPtr)[varNum].dataType,
								modelPtr);
			printf("%s", constStr);
			freePtr(constStr);
			printf(" ");
		}
	printf("}");
}


/* === Garbage === */

//~ void work(_md)
//~ {
    //~ int predNum, factNum, axNum, itNum;
    //~ Boolean needWork = true;
    //~ //WorkMode mode = MD_NORMAL;
    //~ print(FM_BLUE, "Work started...\n");
//~ 
    //~ while (needWork)
    //~ {
        //~ needWork = false;
//~ 
        //~ // processing new facts
        //~ forVec(predNum, preds_m)    // in predicats
        //~ {
            //~ Pred* pred = getPredPtr(predNum);
            //~ int factEnd = pred->map.len;
//~ 
            //~ forVec(axNum, axioms_m) // in axioms
            //~ {
                //~ Axiom* ax = getAxPtr(axNum);
//~ 
                //~ forRange(itNum, 0, ax->actCt)   // in items
                    //~ if (ax->items[itNum]->num == predNum)
                        //~ forRange(factNum, pred->oldFactCt, factEnd) // in facts
                        //~ {
                            //~ Point pt = ptr(Point, pred->map)[factNum];
//~ 
                            //~ if (pt.val == CON_TRUE && canUse(ax, itNum, pt.par))
                            //~ {
                                //~ workWithFact(ax, itNum, pt.par, model);
                                //~ /*print(FM_YELL, "Fact ");
                                //~ printFuncValue(pred, pt.par, pt.val, model);
                                //~ printf("\n");*/
                            //~ }
                        //~ } // facts
            //~ } // axioms
            //~ pred->oldFactCt = factEnd;
        //~ } // predicates
//~ 
        //~ // processing active tasks
        //~ int taskNum;
        //~ needWork |= (tasks_m.len > 0);
//~ 
        //~ forVec(taskNum, tasks_m)
            //~ makeTask(getTaskPtr(taskNum), MD_NORMAL, model);
        //~ tasks_m.len = 0;
//~ 
        //~ // negative mode
        //~ if (!needWork)
        //~ {
            //~ // loking for tasks which need a predicate value
            //~ // for negative conjunct (negative item)
//~ 
            //~ forVec(predNum, preds_m)    // in predicats
            //~ {
                //~ Pred* pred = getPredPtr(predNum);
                //~ int taskNum;
//~ 
                //~ for (taskNum = 0; taskNum < pred->waitList.len; taskNum++)
                //~ {
                    //~ Task* task = ptr(Task, pred->waitList) + taskNum;
//~ 
                    //~ if (task->ax->items[task->itNum]->type == EXPR_NOT)
                        //~ //&& task->result.stopNode == stopItemNode->params)
                    //~ {
                        //~ //ExprValue answer = {task->result.stopNode, CON_FALSE};
                        //~ //addBack(task->result.valCache, ExprValue, answer);
                        //~ makeTask(task, MD_NEGATIVE, model);
//~ 
                        //~ delFrom(pred->waitList, Task, taskNum);
                        //~ taskNum--;
                    //~ }
                //~ } // tasks
            //~ } // predicates
//~ 
            //~ needWork |= (tmpFacts_m.len != 0);
//~ 
            //~ // realize temp facts
            //~ forVec(factNum, tmpFacts_m)
            //~ {
                //~ TmpFact* tmp = ptr(TmpFact, tmpFacts_m) + factNum;
                //~ Boolean res =
                        //~ setFuncValue(tmp->func, tmp->params, tmp->value, model);
//~ 
                //~ // ///// debug outout
                //~ if (res)
                //~ {
                    //~ print(FM_YELL, "Axiom");
                    //~ printf(" %d => ", tmp->axNum);
                    //~ printFuncValue(tmp->func, tmp->params, tmp->value, model);
                    //~ printf("\n");
                //~ }
                //~ // /////
            //~ }
            //~ tmpFacts_m.len = 0;
//~ 
        //~ } // negative mode
//~ 
    //~ } // haveNewFacts
//~ }

