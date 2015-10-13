/* Interpretation.h */

#ifndef INTERPRETATION_HEADER
#define INTERPRETATION_HEADER

#include "Logic.h"
#include "Model.h"
#include "Expressions.h"


/* === types & constants === */

struct FTNode;

typedef struct {
	supp con;
	struct FTNode* nodePtr;
} FTParam;

struct FTNode {	/* node of fact tree */
	size_t parCt;
	FTParam* params;
	
	struct FTNode* parentPtr;
	size_t parentPos;
};

typedef struct FTNode FTNode;

typedef struct {
	FTNode* nodePtr;
	size_t pos, depth;
} FTIterator;



struct ServData
{
	size_t itNum;
	size_t varCt;
	size_t* varNums;
	FTIterator* iters;
	
	supp* currSubst;
	FTIterator currIter;

	FTNode* factTreePtr;
};

typedef struct ServData ServData;



/* macros for FTIterator */


#define FTI_moveUp(iter)                                                       \
(                                                                              \
	(iter).depth--,                                                            \
	(iter).pos = (iter).nodePtr->parentPos,                                    \
	(iter).nodePtr = (iter).nodePtr->parentPtr                                 \
)

#define FTI_moveDown(iter)                                                     \
(                                                                              \
	(iter).depth++,                                                            \
	(iter).nodePtr = (iter).nodePtr->params[(iter).pos].nodePtr,               \
	(iter).pos = 0                                                             \
)


#define FTI_isValid(iter) ((iter).nodePtr != NULL)


#define FTI_writeSubst(iter, servData, subst)                                  \
{                                                                              \
	_iter2 = (iter);                                                           \
	for (; FTI_isValid(_iter2); )                                              \
	{                                                                          \
		(subst)[(servData).varNums[_iter2.depth]]                              \
			= _iter2.nodePtr->params[_iter2.pos].con;                          \
		FTI_moveUp(_iter2);                                                    \
	}                                                                          \
}



#define FTI_inBegin(iter, servData)                                            \
{                                                                              \
	(iter).nodePtr = (servData).factTreePtr;                                   \
	(iter).depth = (iter).pos = 0;                                             \
	                                                                           \
	while (iter.depth + 1 < (servData).varCt && FTI_isValid(iter))             \
		FTI_moveDown(iter);                                                    \
}



#define FTI_moveNext(iter, servData, controlSubst)                             \
{                                                                              \
	(iter).pos++;                                                              \
	                                                                           \
	while ((iter).depth < (servData).varCt && FTI_isValid((iter)))             \
	{                                                                          \
		_value = (controlSubst)[(servData).varNums[(iter).depth]];             \
		_nodePtr = (iter).nodePtr;                                             \
		_params = _nodePtr->params;                                            \
		                                                                       \
		if (!conCmp(_value, CONST_IDC) && (iter).pos < _nodePtr->parCt         \
			&& _value.id <= _params[_nodePtr->parCt - 1].con.id)               \
			for (; _params[(iter).pos].con.id < _value.id; ++(iter).pos);      \
		                                                                       \
		if ((iter).pos == _nodePtr->parCt                                      \
			|| (!conCmp(_value, CONST_IDC)                                     \
				&& !conCmp(_value, _params[(iter).pos].con)))                  \
		{                                                                      \
			if ((iter).depth == 0) (iter).nodePtr = NULL;                      \
			else ( FTI_moveUp(iter), (iter).pos++ );                           \
		}                                                                      \
		else FTI_moveDown(iter);                                               \
	}                                                                          \
	                                                                           \
	if (FTI_isValid(iter)) FTI_moveUp(iter);                                   \
}



#define FTI_moveOn(iter, servData, controlSubst)                               \
{                                                                              \
	_iter0.nodePtr = NULL;                                                     \
	                                                                           \
	for (_iter2 = (iter); FTI_isValid(_iter2); FTI_moveUp(_iter2))             \
	{                                                                          \
		size_t varNum = (servData).varNums[_iter2.depth];                      \
		                                                                       \
		if (!conCmp((controlSubst)[varNum], CONST_IDC)                         \
			&& !conCmp(_iter2.nodePtr->params[_iter2.pos].con,                 \
						(controlSubst)[varNum]))                               \
			_iter0 = _iter2;                                                   \
	}                                                                          \
	                                                                           \
	if (FTI_isValid(_iter0))                                                   \
	{                                                                          \
		(iter) = _iter0;                                                       \
		FTI_moveNext(iter, servData, controlSubst);                            \
	}                                                                          \
}




/*
#define initItState(state, axVarCt, servData)                                  \
{                                                                              \
	(state).subst = (supp*)malloc((axVarCt) * sizeof(supp));                   \
	FTI_inBegin(state, servData, axVarCt);                                     \
}

#define freeItState(state)                                                     \
{                                                                              \
	freePtr((state).subst);                                                    \
}
*/


/* === functions === */

void prepareServData(Axiom* axPtr);
void freeServData(_md);

void work(_md);
void check(_md);




#endif /* INTERPRETATION_HEADER	*/
