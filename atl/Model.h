/* Model.h
 * Describes the basic data structures
 * and functions for work with them
*/

#ifndef MODEL_HEADER
#define MODEL_HEADER

#include <stddef.h>		/* for size_t 	*/
#include <stdint.h>		/* for SIZE_MAX	*/

#include "Logic.h"


/* === TYPES & CONSTANTS === */

typedef size_t 	IdType;
typedef long 	IntegerType;
typedef double 	RealType;

#define ID_CAPACITY SIZE_MAX

/* Support of model. Describes constants. */
typedef union {
	IdType id;
	IntegerType integer;
	RealType real;
} supp;

#define conCmp(con1, con2) ((con1).id == (con2).id)


/* reserved constants */
enum ReservedConstantId {CONST_ID_IDC = 0, 	CONST_ID_NULL,
						 CONST_ID_TRUE, 	CONST_ID_FALSE};

static const supp CONST_IDC   = {CONST_ID_IDC};
static const supp CONST_NULL  = {CONST_ID_NULL};
static const supp CONST_TRUE  = {CONST_ID_TRUE};
static const supp CONST_FALSE = {CONST_ID_FALSE};

/* count of service constants that must be
 * in each data type (CONST_IDC, CONST_NULL)	*/
#define RESERVED_CONST_COUNT 2

/* data types */

typedef struct {
	char* name;
	Vector constNames;	/* Vector of (char*) */
} DataType;

typedef ssize_t DataTypeId;	/* Number of datatype in model */
enum ReservedDataTypeId {DT_BOOL = 0, DT_INT, DT_REAL};
#define RESERVED_DATA_TYPE_COUNT 3

/* arithmetic functions */
typedef enum {
	AF_ABS,		AF__MAX,	AF__MIN,		AF_SIN,		AF_COS,		AF_TAN,
	AF_ASIN,	AF_ACOS,	AF_ATAN,	AF_LOG,
	AF_UMINUS,	AF_PLUS,	AF_MINUS,	AF_MULT,	AF_DIV,		AF_MOD,
	AF_POW
} ArithmeticFunctionId;

typedef enum {
	AR_LESS,	AR_MORE,	AR_LESS_EQ,	AR_MORE_EQ
} ArithmeticRelationId;

#define ARITHMETIC_FUNCTION_COUNT 17
#define AF_NAMED_FUNCTION_COUNT 10
#define ARITHMETIC_RELATIONS_COUNT 4


/* expressions */

typedef enum {
    EXPR_CONST,	EXPR_VAR, 	EXPR_FUNC, 	EXPR_PRED, 	EXPR_ALL, 	EXPR_EXT,
    EXPR_NOT,	EXPR_AND,	EXPR_OR, 	EXPR_IMP, 	EXPR_EQ,	EXPR_LEQ
} ExprType;

/* Expressions are represented a tree of ExprNode */
struct ExprNode {
	ExprType type;
	DataTypeId dataType;
	supp value;

	struct ExprNode *params, *next;
};
typedef struct ExprNode ExprNode;

typedef struct {
	char* name;
	DataTypeId dataType;
} Variable;


typedef struct {
    Vector* varVectPtr;	/* Vector of Variables */
    ExprNode* nodePtr;
    size_t parNum;
} ExprIter;


typedef size_t FactId;

/* Describes functions and predicates. */
typedef struct {
	size_t parCt;
	FactId oldFactId;	/* devide facts that were processed */
	char* name;
	DataTypeId* parTypes;	/* signature		*/
	DataTypeId dataType;	/* (parTypes)->type	*/
	Vector data;		/* vector of supp; [<params1>, val1,
											<params2>, val2, ...]	*/
	Vector waitList;    /* vector of Task* that need value of this function	*/
} Func;

typedef Func Pred;



struct ServData;	/* described in Interpretation.h */

typedef struct {
	size_t itemCt;	/* count of conjuncts in premise and result part */
	size_t premCt;	/* count of conjuncts in premise */
	size_t mainCt;	/* count of main conjuncts in premise */
	size_t actCt;	/* count of 'active' conjuncts in premise */
	Vector vars;	/* Vector of Variables */
	ExprNode** items;
	struct ServData* servData;	/* service data for each main item */
} Axiom;


/* Fact set value of function or predicate: func(params) = value */
typedef struct {
	Func* funcPtr;
	supp* params;
	supp value;
	ssize_t axiomNum;	/* debugg data */
} Fact;

/* Query value of function or predicate: func(params) - ?
 * Same as Fact, but 'value' is used for answer */
typedef Fact Query;

typedef struct {
	Query query;
	ssize_t pos;
} QueryIterator;


struct ExprResult;	/* described in Expressions.h */
typedef struct ExprResult ExprResult;

/* There must be discription */
typedef struct {
	Axiom* axPtr;
	size_t lastItNum;
	ExprResult* resultPtr;
	Vector tmpFacts;	/* Vector of Fact */
} Task;

/* restriction - arbitrary closed formula */
typedef struct {
	ExprNode* root;
	Vector vars;	/* Vector of Variables */
} Restriction;

//~ typedef enum {
    //~ NO_ERR, PARSER_ERR, INTERPRETATION_ERR, UNSORTED_ERR
//~ } ErrorType;


typedef struct {
	Vector	preds,		funcs,		axioms,		restrs,
			taskPtrs,	tmpFacts,	dataTypes;
	Vector errors;	/* Vector of Error */
	Vector sources;	/* Vector of Source - for error messages */
	Source* currSrcPtr;
	size_t totalFactCt;
	FILE *debugStream, *errorStream;
} Model;



/* === ADDITIONAL MACROS === */

#define _md 		Model* modelPtr
#define axioms_m	modelPtr->axioms
#define restrs_m	modelPtr->restrs
#define preds_m		modelPtr->preds
#define funcs_m		modelPtr->funcs
#define taskPtrs_m	modelPtr->taskPtrs
#define types_m		modelPtr->dataTypes
#define tmpFacts_m	modelPtr->tmpFacts

#define getPredPtr(num)		( ptr(Pred, preds_m)   + (num) )
#define getFuncPtr(num)		( ptr(Func, funcs_m)   + (num) )
#define getAxPtr(num)		( ptr(Axiom, axioms_m) + (num) )
#define getTaskPtr(num)		( ptr(Task*, taskPtrs_m) [num] )
#define getTypePtr(num)		( ptr(DataType, types_m) + (num) )
#define getRestrPtr(num)	( ptr(Restriction, restrs_m) + (num) )

#define shiftSupp(con)                                                 \
	{ if ((con).integer >= 0) (con).integer += RESERVED_CONST_COUNT; }

#define shiftSuppBack(con)                                             \
	{ if ((con).integer >= 0) (con).integer -= RESERVED_CONST_COUNT; }



/* === FUNCTIONS === */

/* work with structures */
DataType createDataType(const char name[]);
void freeDataType(DataType* typePtr);

ExprNode* createExprNode(ExprType type);	/* create with malloc	*/
void freeExprNode(ExprNode* nodePtr);	/* recursive free	*/

void initRestriction(Restriction* restrPtr);
void freeRestriction(Restriction* restrPtr);

Func createFunc(const char name[], size_t parCt, DataTypeId parTypes[],
												 DataTypeId dataType);
void freeFunc(Func* funcPtr);

void freeAxiom(Axiom* axiomPtr);

Fact  createFact (Func* funcPtr, supp* params, supp value);
Query createQuery(Func* funcPtr, supp* params);
void freeFact(Fact* factPtr);
void freeQuery(Query* queryPtr);

Task* createTask(Axiom* axPtr, supp* varValues);
void freeTask(Task* taskPtr);

QueryIterator createQueryIterator(Query query);
void moveQIterator(QueryIterator* qiterPtr);
void resetQIterator(QueryIterator* qiterPtr);
Boolean qiterIsValid(QueryIterator* qiterPtr);
Fact getFact(QueryIterator* qiterPtr);

/* work with model */
void initModel(_md);
void freeModel(_md);

DataTypeId addDataType(const char name[], _md);
DataTypeId getTypeIdByName(const char name[], _md);

ssize_t addFunc(Func func, _md);
ssize_t addPred(Pred pred, _md);
ssize_t getFuncNumByName(const char name[], _md);
ssize_t getPredNumByName(const char name[], _md);
Func* getFuncOrPredByName(const char name[], _md); /* returns Func or Pred pointer */

supp getOrAddConstant(const char name[], DataTypeId typeId, _md);

supp ask(Query* queryPtr, _md);
Boolean setFact(Fact* factPtr, _md);

void addParserError(char msg[], size_t lineNum, size_t columnNum, _md);
void addInterpretationError(char msg[], _md);
void addInnerError(char msg[], _md);
void addError(Error error, _md);

/* output */

char* getConstStr(supp con, DataTypeId typeId, _md);
char* getFuncDeclStr(Func* funcPtr, _md);
char* getFactStr(Fact* factPtr, _md);
char* getExprStr(ExprIter iter, _md);
char* getRestrStr(Restriction* restrPtr, _md);
char* getAxiomStr(Axiom* axPtr, _md);

/* debug output */

void printDeclarations(_md);
void printRestrictions(_md);
void printAxioms(_md);

//~ void printConstant(supp con, DataTypeId typeId, _md);
//~ void printExpr(ExprIter iter, _md);
//~ void printFuncValue(Func* funcPtr, supp* params, Boolean withValue, _md);
// ...

/* work with model */
// ...

//~ void takeError(ErrType type, char* msg, _md);
//~ void addNewFunc(Name name, int parCt, TypeId* parTypes, TypeId type, _md);
//~ TypeId getTypeNumByName_add(Name name, _md);
//~ size_t getFuncNumByName(Name name, _md);
//~ size_t getPredNumByName(Name name, _md);
//~ size_t getVarNum_add(Name name, TypeId type, Vector* varVectPtr);
//~ 
//~ supp getConstNum_add(Name name, TypeId typeId, _md);
//~ Name getConstName(supp constId, TypeId typeId);
//~ 
//~ Boolean setFact(Fact fact, _md);
//~ supp ask(Query* query, _md);
//~ void printFuncValue(char* buf, Fact fact, _md);
//~ void printNewFact(Fact fact, _md);
//~ void printError(_md);
//~ 
//~ void freeExprNode(ExprNode* node);


#endif  /* MODEL_HEADER */


/* GARBAGE */

/*Boolean addFact(Pred* pred, Fact fact, int axNum, _md);
Boolean addNot(Pred* pred, Fact fact, int axNum, _md);
//Task createTask(Axiom* ax);
void addTmpFact(int tp, int pn, Fact prs, supp val, int an, _md);

// other
//Boolean checkRestr(Expr* expr, FactMap fm, _p);
//supp getExprValue(Expr* expr, Task* task, _md);
supp getFuncValue(Func* func, Fact params);
Boolean setFuncValue(Func* func, Fact params, supp val, int axNum, _md);

Boolean canUseIn(Fact fact, Item* item);
Boolean findFact(Pred* pred, Fact fact, Boolean full);
Boolean findNot(Pred* pred, Fact fact);
*/


//~ #define SUPP_TYPE_CHAR      0
//~ #define SUPP_TYPE_SHORT     1
//~ #define SUPP_TYPE_INT       2
//~ #define SUPP_TYPE_LONG      3
//~ #define SUPP_TYPE_SIZE_T	4
//~ 
//~ #define SUPP_TYPE  SUPP_TYPE_SIZE_T
//~ 
//~ #if SUPP_TYPE == SUPP_TYPE_CHAR
    //~ typedef unsigned char supp;
    //~ static const long long MAX_SUPP_VALUE = UCHAR_MAX;
//~ #elif SUPP_TYPE == SUPP_TYPE_SHORT
    //~ typedef unsigned short supp;
    //~ static const long long MAX_SUPP_VALUE = USHORT_MAX;
//~ #elif SUPP_TYPE == SUPP_TYPE_INT
    //~ typedef unsigned int supp;
    //~ static const long long MAX_SUPP_VALUE = UINT_MAX;
//~ #elif SUPP_TYPE == SUPP_TYPE_LONG
    //~ typedef unsigned long supp;
    //~ static const long long MAX_SUPP_VALUE = ULONG_MAX;
//~ #elif SUPP_TYPE == SUPP_TYPE_SIZE_T
	//~ typedef size_t supp;
	//~ static const long long MAX_SUPP_VALUE = SIZE_MAX;
//~ #endif
