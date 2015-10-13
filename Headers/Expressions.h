/* Expressions.h */

#ifndef EXPRESSIONS_HEADER
#define EXPRESSIONS_HEADER

#include <stddef.h>		/* for size_t 	*/
#include "Model.h"


/* types & constants */

typedef enum {MD_NORMAL, MD_NO_SAVE} CalcMode;
//~ typedef enum {RES_VALID, RES_IDC, RES_NULL} ResultType;

typedef struct {
	ExprNode* nodePtr;
	supp value;
} ExprValue;

/* ExprResult contains service data for calculation of expressions 	*/
struct ExprResult {
	/* input params */
	supp *varValues;
	CalcMode mode;		/* mode of getExprValue function				*/
	ExprIter currIter;
	
	/* output params */
	//~ ResultType resultType;
	supp value;
	ExprIter stopIter;
	supp* stopParams;	/* parametrs of node in currIter in case of stop */
	Vector valueCache;	/* vector of ExprValue. Saves known values for stop. */
	size_t layer, reqCt;	/* debugg data	*/
};



/* macros for ExprIter */

#define initIter(iter, _varVectPtr, _nodePtr)                                  \
(                                                                              \
	(iter).varVectPtr = (_varVectPtr),                                         \
	(iter).nodePtr = (_nodePtr),                                               \
	(iter).parNum = 0                                                          \
)

#define into(iter) ((iter).nodePtr = (iter).nodePtr->params, (iter).parNum = 0)
#define step(iter) ((iter).nodePtr = (iter).nodePtr->next,   (iter).parNum++)

#define ndType(iter) 		( (iter).nodePtr->type )
#define ndDataType(iter)	( (iter).nodePtr->dataType )
#define ndVal(iter)  		( (iter).nodePtr->value )

#define isValid(iter) 	( (iter).nodePtr != NULL )

#define forIter(iter) 	for (		   ; isValid(iter); step(iter))
#define forParams(iter) for (into(iter); isValid(iter); step(iter))

#define forIterIf(iter, cond) 	for (; isValid(iter) && (cond); step(iter))
#define forParamsIf(iter, cond)                                                \
	for (into(iter); isValid(iter) && (cond); step(iter))



/* functions declarations */

ExprIter getIter(Vector* varVectPtr, ExprNode* nodePtr);
ExprIter getIterForRestr(Restriction* restrPtr, ExprNode* nodePtr);
ExprIter getParamIter(ExprIter iter);
ExprIter getNextIter(ExprIter iter);


//~ void inputExpr(FILE* fin, ExprIter iter, TypeId expType, _md);
//~ void printExpr(ExprIter iter, _md);
//~ void getWord(FILE* fin, Name* name);
//~ ExprNode* createNewExprNode();

ExprResult* createExprResult(supp* varValues, size_t varCt, CalcMode mode);
void freeExprResult(ExprResult* resultPtr);

supp getExprValue(ExprIter iter, ExprResult* resultPtr, _md);
//~ supp getQuanValue(ExprResult* resultPtr, _md);

//~ void transformExpr(Expr* expr);



#endif // EXPRESSIONS_HEADER
