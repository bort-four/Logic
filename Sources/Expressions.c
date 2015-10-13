/* Expressions.c - implements addition functions for
 * work with expressions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Logic.h"
#include "Model.h"
#include "Expressions.h"


/* === local declarations === */

#define getNum(con, dataType)                                                  \
(                                                                              \
	((dataType) == DT_REAL) ? (con).real : (con).integer                       \
)

#define setNum(con, dataType, number)                                          \
{                                                                              \
	if ((dataType) == DT_REAL)                                                 \
		 (con).real = (RealType)(number);                                      \
	else (con).integer = (IntegerType)(number);                                \
}


const char EXPR_NAMES[][10] = {	/* for debugg output */
	"const",	"var",		"func",		"pred",		"All",		"Ext",
	"!",		"&",		"|",		"=>",		"=",		"=="
};

supp makeExprCalcStep(ExprResult* resultPtr, _md);
supp makeQuanCalcStep(ExprResult* resultPtr, _md);
supp makeArithmeticCalc(ExprIter iter, supp* params);
supp makeArithmeticCheck(ExprIter iter, supp* params);


/* === Implementation === */


supp getExprValue(ExprIter iter, ExprResult* resultPtr, _md)
{
	//~ resultPtr->rootIter = resultPtr->currIter = iter;
	resultPtr->currIter = iter;
	//~ resultPtr->resultType = RES_VALID;
	supp value = makeExprCalcStep(resultPtr, modelPtr);
	
	if (resultPtr->mode == MD_NORMAL)
	{
		ExprValue exprValue;
		
		if (conCmp(value, CONST_IDC))
		{
			ExprIter paramIter = getParamIter(resultPtr->stopIter);
			
			forIter(paramIter)
			{
				exprValue.value = resultPtr->stopParams[paramIter.parNum];
				exprValue.nodePtr = paramIter.nodePtr;
				addBack(resultPtr->valueCache, ExprValue, exprValue);
			}
		}
		else
		{
			exprValue.value = value;
			exprValue.nodePtr = iter.nodePtr;
			addBack(resultPtr->valueCache, ExprValue, exprValue);
		}
	}
	
	return value;
}


supp makeExprCalcStep(ExprResult* resultPtr, _md)
{
	//~ printf("\n");	/* debug output */
	ExprIter iter = resultPtr->currIter;
	
	/* debugg output */
	//~ size_t spNum;
	//~ for (spNum = 0; spNum < resultPtr->layer; ++spNum) printf("  ");
	//~ setFormat(FM_YELL);
	//~ printf("%s ", EXPR_NAMES[ndType(iter)]);
	//~ setFormat(FM_NORM);
	/* ============= */

	/* search in valueCache	*/
	size_t valNum;
	
	forVect (valNum, resultPtr->valueCache)
	{
		ExprValue* valuePtr = ptr(ExprValue, resultPtr->valueCache) + valNum;
		
		if (valuePtr->nodePtr == iter.nodePtr)
		{
			resultPtr->value = valuePtr->value;
			delFrom(resultPtr->valueCache, ExprValue, valNum);
			valNum--;

			/* debug output */
			//~ printConstant(resultPtr->value, ndDataType(iter), modelPtr);
			//~ printf(" [from cache]");
			/* ============ */

			return resultPtr->value;
		}
	}

	/* if expression is a quantifier	*/
	if (ndType(iter) == EXPR_ALL || ndType(iter) == EXPR_EXT)
		return makeQuanCalcStep(resultPtr, modelPtr);

	/* initialization	*/
	ExprType exprType = ndType(iter);
	size_t saveParamCt = 0;
	Boolean paramsFlag = true;
	ExprIter paramIter = getParamIter(iter);
	forIter(paramIter);
	size_t parCt = paramIter.parNum;
	
	/* allocate memory for parametrs	*/
	supp* params = (supp*)malloc(parCt * sizeof(supp));

	/* calculation parameters	*/
	//~ supp stopValue = { RESERVED_CONST_COUNT };
	supp stopValue1 = CONST_NULL;
	supp stopValue2 = CONST_NULL;

	//~ if (exprType == EXPR_AND || exprType == EXPR_IMP)
		//~ stopValue = CONST_FALSE;
	//~ else if (exprType == EXPR_OR)
		//~ stopValue = CONST_TRUE;

	if (exprType == EXPR_AND || exprType == EXPR_IMP)
	{
		stopValue1 = CONST_FALSE;
		stopValue2 = CONST_IDC;
	}
	else if (exprType == EXPR_OR)	 	stopValue1 = CONST_TRUE;
	if (resultPtr->mode == MD_NORMAL)	stopValue2 = CONST_IDC;

	paramIter = getParamIter(iter);
	resultPtr->value = CONST_IDC;
	
	forIterIf(paramIter, paramsFlag)	/* recursion */
	{
		resultPtr->currIter = paramIter;
		resultPtr->layer++;
		params[saveParamCt] = makeExprCalcStep(resultPtr, modelPtr);
		resultPtr->layer--;
		
		if (	conCmp(resultPtr->value, CONST_NULL)
			|| 	conCmp(resultPtr->value, stopValue1)
			||	conCmp(resultPtr->value, stopValue2))
			paramsFlag = false;
		else
			saveParamCt++;
	}


	/* if can't calculate expression */
	if (conCmp(resultPtr->value, CONST_NULL))
	{
		//~ printf("\n");	/* debug output */
		freePtr(params);
		return CONST_NULL;
	}
	
	if (conCmp(resultPtr->value, CONST_IDC) && resultPtr->mode == MD_NORMAL
		&& iter.nodePtr->params != NULL)
	{
		/* save calculated parametrs in resultPtr->valueCache */
		paramIter = getParamIter(iter);

		forIterIf(paramIter, paramIter.parNum < saveParamCt)
		{
			ExprValue exprValue;
			exprValue.nodePtr = paramIter.nodePtr;
			exprValue.value = params[paramIter.parNum];
			addBack(resultPtr->valueCache, ExprValue, exprValue);
		}
		
		//~ printf("\n");	/* debug output */
		freePtr(params);
		return CONST_IDC;
	}

	/* calculation	*/
	switch (exprType)
	{
		case EXPR_CONST: resultPtr->value = ndVal(iter); break;
		case EXPR_VAR:
			resultPtr->value = resultPtr->varValues[ndVal(iter).id]; break;
		case EXPR_NOT:	/* !	*/
			resultPtr->value = (conCmp(params[0], CONST_TRUE))
								? CONST_FALSE : CONST_TRUE;
			break;
		case EXPR_IMP:	/* =>	*/
			resultPtr->value =
				(!conCmp(params[0], CONST_TRUE) || conCmp(params[1],CONST_TRUE))
				? CONST_TRUE : CONST_FALSE;
			break;
		case EXPR_EQ:	/* =	*/
			if (conCmp(params[0], CONST_IDC) || conCmp(params[1], CONST_IDC))
				 resultPtr->value = CONST_FALSE;
			else resultPtr->value = (conCmp(params[0], params[1]))
									? CONST_TRUE : CONST_FALSE;
			break;
		case EXPR_LEQ:	/* ==	*/
			if (conCmp(params[0], CONST_IDC) || conCmp(params[1], CONST_IDC))
				 resultPtr->value = CONST_FALSE;
			else resultPtr->value = (conCmp(params[0], params[1]))
									? CONST_TRUE : CONST_FALSE;
			break;
		case EXPR_AND:	/* &	*/
			resultPtr->value = (paramsFlag) ? CONST_TRUE : CONST_FALSE;
			break;
		case EXPR_OR:	/* |	*/
			resultPtr->value = (paramsFlag) ? CONST_FALSE : CONST_TRUE;
			break;
		default:	/* predicate or function	*/
			if (exprType == EXPR_PRED || exprType == EXPR_FUNC)
			{
				if (exprType == EXPR_FUNC
					&& ndVal(iter).id < ARITHMETIC_FUNCTION_COUNT)
					resultPtr->value = makeArithmeticCalc(iter, params);
				else
				if (exprType == EXPR_PRED
					&& ndVal(iter).id < ARITHMETIC_RELATIONS_COUNT)
					resultPtr->value = makeArithmeticCheck(iter, params);
				else
				{
					resultPtr->reqCt++;
					Func* funcPtr = (exprType == EXPR_PRED)
									? getPredPtr(ndVal(iter).id)
									: getFuncPtr(ndVal(iter).id);
					Query query = createQuery(funcPtr, params);
					resultPtr->value = ask(&query, modelPtr);
					freeQuery(&query);
		
					/* in case of fail remember this node and params	*/
					if (conCmp(resultPtr->value, CONST_IDC)
						&& resultPtr->mode == MD_NORMAL)
					{
						resultPtr->stopIter = iter;
						resultPtr->stopParams = params;
						params = NULL;
					}
				}
			}
			else
				printf("Inner error: unknown type of expression.\n");
			
			break;
	}

	/* debugg output */
	//~ if (iter.nodePtr->params == NULL)
	//~ {
		//~ setFormat(FM_BLUE);
		//~ printConstant(resultPtr->value, ndDataType(iter), modelPtr);
		//~ setFormat(FM_NORM);
	//~ }
	/* ============= */
	
	freePtr(params);
	return resultPtr->value;
}


supp makeArithmeticCalc(ExprIter iter, supp* params)
{
	supp result;
	DataTypeId dtype1, dtype2;
	supp param1, param2;
	
	dtype1 = iter.nodePtr->params->dataType;
	param1 = params[0];
	shiftSuppBack(param1);
	
	if (iter.nodePtr->params->next != NULL)
	{
		dtype2 = iter.nodePtr->params->next->dataType;
		param2 = params[1];
		shiftSuppBack(param2);
	}
	
	switch ((ArithmeticFunctionId)ndVal(iter).id)
	{
		case AF_ABS:
			setNum(result, ndDataType(iter), _ABS(getNum(param1, dtype1)));
			break;
		case AF__MAX:
			setNum(result, ndDataType(iter),
					  _MAX(getNum(param1, dtype1), getNum(param2, dtype2)));
			break;
		case AF__MIN:
			setNum(result, ndDataType(iter),
					  _MIN(getNum(param1, dtype1), getNum(param2, dtype2)));
			break;
		
		case AF_SIN:
			setNum(result, ndDataType(iter), sin(getNum(param1, dtype1)));
			break;
		case AF_COS:
			setNum(result, ndDataType(iter), cos(getNum(param1, dtype1)));
			break;
		case AF_TAN:
			setNum(result, ndDataType(iter), tan(getNum(param1, dtype1)));
			break;
		case AF_ASIN:
			setNum(result, ndDataType(iter), sin(getNum(param1, dtype1)));
			break;
		case AF_ACOS:
			setNum(result, ndDataType(iter), cos(getNum(param1, dtype1)));
			break;
		case AF_ATAN:
			setNum(result, ndDataType(iter), tan(getNum(param1, dtype1)));
			break;
		case AF_LOG:
			setNum(result, ndDataType(iter), log(getNum(param1, dtype1)));
			break;
		
		case AF_UMINUS:
			setNum(result, ndDataType(iter), -getNum(param1, dtype1));
			break;
		case AF_PLUS:
			setNum(result, ndDataType(iter),
					  getNum(param1, dtype1) + getNum(param2, dtype2));
			break;
		case AF_MINUS:
			setNum(result, ndDataType(iter),
					  getNum(param1, dtype1) - getNum(param2, dtype2));
			break;
		case AF_MULT:
			setNum(result, ndDataType(iter),
					  getNum(param1, dtype1) * getNum(param2, dtype2));
			break;
		case AF_DIV:
			setNum(result, ndDataType(iter),
					  getNum(param1, dtype1) / getNum(param2, dtype2));
			break;
		case AF_MOD:
			setNum(result, ndDataType(iter),
					  (int)getNum(param1, dtype1) % (int)getNum(param2, dtype2));
			break;
		case AF_POW:
			setNum(result, ndDataType(iter),
					  pow(getNum(param1, dtype1), getNum(param2, dtype2)));
			break;
	}
	
	shiftSupp(result);
	return result;
}

//~ typedef enum {
	//~ AF_ABS,		AF_MAX,		AF_MIN,		AF_SIN,		AF_COS,		AF_TAN,
	//~ AF_ASIN,	AF_ACOS,	AF_ATAN,	AF_LN,
	//~ AF_UMINUS,	AF_PLUS,	AF_MINUS,	AF_MULT,	AF_DIV,		AF_MOD,
	//~ AF_POW
//~ } ArithmeticFunctionId;


supp makeArithmeticCheck(ExprIter iter, supp* params)
{
	supp result;
	DataTypeId dtype1, dtype2;
	supp param1, param2;
	
	dtype1 = iter.nodePtr->params->dataType;
	param1 = params[0];
	shiftSuppBack(param1);
	
	if (iter.nodePtr->params->next != NULL)
	{
		dtype2 = iter.nodePtr->params->next->dataType;
		param2 = params[1];
		shiftSuppBack(param2);
	}
	
	switch ((ArithmeticRelationId)ndVal(iter).id)
	{
		case AR_LESS:
			result = (getNum(param1, dtype1) < getNum(param2, dtype2))
					? CONST_TRUE : CONST_FALSE;
			break;
		case AR_MORE:
			result = (getNum(param1, dtype1) > getNum(param2, dtype2))
					? CONST_TRUE : CONST_FALSE;
			break;
		case AR_LESS_EQ:
			result = (getNum(param1, dtype1) <= getNum(param2, dtype2))
					? CONST_TRUE : CONST_FALSE;
			break;
		case AR_MORE_EQ:
			result = (getNum(param1, dtype1) >= getNum(param2, dtype2))
					? CONST_TRUE : CONST_FALSE;
			break;
	}
	
	return result;
}


supp makeQuanCalcStep(ExprResult* resultPtr, _md)
{
	//~ printf("\n");	/* debug output */
	ExprIter iter = resultPtr->currIter;
	
	size_t varNum = ndVal(iter).id;
	ExprIter bodyIter = getParamIter(iter);

	/* debugg output */
	//~ size_t spNum;
	//~ for (spNum = 0; spNum < resultPtr->layer; ++spNum) printf("  ");
	//~ printf("var%ld = ", varNum); print(FM_BLUE, "NULL");
	/* ============= */
	
	resultPtr->varValues[varNum] = CONST_NULL;
	resultPtr->currIter = bodyIter;
	resultPtr->layer++;
	makeExprCalcStep(resultPtr, modelPtr);
	resultPtr->layer--;

	if (!conCmp(resultPtr->value, CONST_NULL))
	{
		//~ resultPtr->layer--;
		return resultPtr->value = (conCmp(resultPtr->value, CONST_TRUE))
									? CONST_TRUE : CONST_FALSE;
	}

	DataTypeId typeId = ptr(Variable, *iter.varVectPtr)[varNum].dataType;
	DataType* dataTypePtr = getTypePtr(typeId);
	size_t constCt = dataTypePtr->constNames.len;
	supp value = {RESERVED_CONST_COUNT};
	Boolean flag = true;

	for (; value.id < constCt && flag; value.id++)
	{
		/* debugg output */
		//~ printf("\n");	/* debug output */
		//~ for (spNum = 0; spNum < resultPtr->layer; ++spNum) printf("  ");
		//~ printf("var%ld = ", varNum);
		//~ setFormat(FM_BLUE);
		//~ printConstant(value, typeId, modelPtr);
		//~ setFormat(FM_NORM);
		/* ============= */

		resultPtr->varValues[varNum] = value;
		resultPtr->currIter = bodyIter;
		resultPtr->layer++;
		makeExprCalcStep(resultPtr, modelPtr);
		resultPtr->layer--;

		if (conCmp(resultPtr->value, CONST_NULL))
			return /*resultPtr->layer--,*/ CONST_NULL;

		if (	(ndType(iter) == EXPR_ALL
					&& !conCmp(resultPtr->value, CONST_TRUE))
			|| 	(ndType(iter) == EXPR_EXT
					&& conCmp(resultPtr->value, CONST_TRUE)))
		flag = false;
	}

	if (ndType(iter) == EXPR_ALL)
		 resultPtr->value = (flag) ? CONST_TRUE : CONST_FALSE;
	else resultPtr->value = (flag) ? CONST_FALSE : CONST_TRUE;

	if (conCmp(resultPtr->value, CONST_TRUE))
		resultPtr->varValues[varNum] = CONST_IDC;

	//~ resultPtr->layer--;
	return resultPtr->value;
}



/* work with structures */

ExprResult* createExprResult(supp* varValues, size_t varCt, CalcMode mode)
{
	ExprResult* resultPtr = (ExprResult*)malloc(sizeof(ExprResult));
	resultPtr->varValues = NULL;
	
	if (varCt > 0)
	{
		resultPtr->varValues = (supp*)malloc(varCt * sizeof(supp));
		if (varValues != NULL)
			memcpy(resultPtr->varValues, varValues, varCt * sizeof(supp));
	}
	resultPtr->currIter.nodePtr = resultPtr->stopIter.nodePtr = NULL;
	resultPtr->value = CONST_NULL;
	resultPtr->mode = mode;
	resultPtr->stopParams = NULL;
	initVect(resultPtr->valueCache, ExprValue);
	resultPtr->layer = resultPtr->reqCt = 0;
	
	return resultPtr;
}

void freeExprResult(ExprResult* resultPtr)
{
	freePtr(resultPtr->varValues);
	freePtr(resultPtr->stopParams);
	freeVect(resultPtr->valueCache);
	freePtr(resultPtr);
}

/* work with iterators */

ExprIter getIter(Vector* varVectPtr, ExprNode* nodePtr)
{   
    ExprIter iter;
    iter.varVectPtr = varVectPtr;
    iter.nodePtr = nodePtr;
    iter.parNum = 0;
    
    return iter;
}

ExprIter getIterForRestr(Restriction* restrPtr, ExprNode* nodePtr)
{
	if (nodePtr == NULL) nodePtr = restrPtr->root;
    
    ExprIter iter;
    iter.varVectPtr = &restrPtr->vars;
    iter.nodePtr = nodePtr;
    iter.parNum = 0;
    
    return iter;
}

ExprIter getParamIter(ExprIter iter)	{ into(iter); return iter; }
ExprIter getNextIter(ExprIter iter)		{ step(iter); return iter; }
