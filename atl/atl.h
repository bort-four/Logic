/* atl.h */

#ifndef ATL_HEADER
#define ATL_HEADER

#include <stdio.h>
#include <stddef.h>
#include "Logic.h"
#include "Model.h"


/* === types & constants === */

#define ATL_VERSION_STR "1.0 (20.06.2015)"
#define ATL_BAD_INDEX -1

typedef ssize_t 	ATL_ModelId;
typedef ssize_t 	ATL_FunctionId;
typedef DataTypeId 	ATL_DataTypeId;

typedef supp 		ATL_Constant;
typedef IntegerType	ATL_Integer;
typedef RealType	ATL_Real;

#define ATL_TRUE  CONST_TRUE
#define ATL_FALSE CONST_FALSE

typedef QueryIterator ATL_Query;
typedef Fact ATL_Fact;

static const ATL_DataTypeId ATL_DT_BOOLEAN = DT_BOOL;
static const ATL_DataTypeId ATL_DT_INTEGER = DT_INT;
static const ATL_DataTypeId ATL_DT_REAL = DT_REAL;

static const ATL_Constant ATL_IDC = {CONST_ID_IDC};

typedef enum {
	ATL_PARSER_ERR, ATL_INTERPRETATION_ERR, ATL_INNER_ERR
} ATL_ErrorType;


/* === globals === */

Vector ATL_models_g;	/* Vector of Model */


/* === macros === */

#define _atlm ATL_ModelId modelId


/* === functions === */


void ATL_init();
void ATL_free();

ATL_ModelId ATL_createModel();
void ATL_freeModel(_atlm);
void ATL_clear(_atlm);
void ATL_inputFile(char fileName[], _atlm);
void ATL_inputString(char string[], _atlm);
ATL_Query ATL_inputQuery(char string[], _atlm);

void ATL_setDebugStream(FILE* stream, _atlm);
void ATL_setErrorStream(FILE* stream, _atlm);

void ATL_run(_atlm);

Boolean ATL_queryIsValid(ATL_Query* queryPtr);
void ATL_moveQuery(ATL_Query* queryPtr);
void ATL_resetQuery(ATL_Query* queryPtr);

ATL_Query ATL_createQuery(ATL_FunctionId funcId, Boolean isPredicate,
						  ATL_Constant* params, ATL_Constant value, _atlm);
ATL_Fact ATL_createFact(ATL_FunctionId funcId, Boolean isPredicate,
						ATL_Constant* params, ATL_Constant value, _atlm);
ATL_Fact ATL_getFact(ATL_Query* queryPtr);
Boolean ATL_setFact(ATL_Fact* factPtr, _atlm);

void ATL_freeFact(ATL_Fact* factPtr);
void ATL_freeQuery(ATL_Query* queryPtr);

ATL_Integer ATL_getIntegerValue(ATL_Constant constant);
ATL_Real ATL_getRealValue(ATL_Constant constant);
char* ATL_getConstantName(ATL_Constant constant, ATL_DataTypeId typeId, _atlm);	/* for user types only */
int ATL_constCmp(ATL_Constant con1, ATL_Constant con2);

ATL_Constant ATL_getIntegerConstant(ATL_Integer value);
ATL_Constant ATL_getRealConstant(ATL_Real value);
//~ 
//~ void ATL_setIntegerValue(ATL_Constant* constPtr, ATL_Integer value);
//~ void ATL_setRealValue(ATL_Constant* constPtr, ATL_Real value);
ATL_Constant ATL_getConstantByName(const char name[], ATL_DataTypeId typeId, _atlm);

ATL_FunctionId ATL_getFuncIdByName(const char name[], _atlm);
ATL_FunctionId ATL_getPredIdByName(const char name[], _atlm);

ATL_FunctionId	ATL_getFactFunction(ATL_Fact* factPtr, _atlm);
ATL_FunctionId	ATL_getFactPredicate(ATL_Fact* factPtr, _atlm);
ATL_Constant 	ATL_getFactParam(ATL_Fact* factPtr, size_t parNum);
ATL_Constant 	ATL_getFactValue(ATL_Fact* factPtr);

char* ATL_getDataTypeName(ATL_DataTypeId dtypeId, _atlm);
ATL_DataTypeId ATL_getTypeIdByName(const char name[], _atlm);

size_t ATL_getFuncParCt(ATL_FunctionId funcId, _atlm);
ATL_DataTypeId ATL_getFuncParType(ATL_FunctionId funcId, size_t parNum, _atlm);
ATL_DataTypeId ATL_getFuncDataType(ATL_FunctionId funcId, _atlm);

size_t ATL_getPredParCt(ATL_FunctionId predId, _atlm);
ATL_DataTypeId ATL_getPredParType(ATL_FunctionId predId, size_t parNum, _atlm);

size_t ATL_getErrorCt(_atlm);
ATL_ErrorType ATL_getErrorType(size_t errNum, _atlm);

size_t ATL_getAxiomCt(_atlm);
size_t ATL_getRestrictionCt(_atlm);

/* output */
char* ATL_getAxiomStr(size_t axiomNum, _atlm);
char* ATL_getRestrictionStr(size_t restrictionNum, _atlm);
char* ATL_getFuncDefStr(ATL_FunctionId funcId, _atlm);
char* ATL_getPredDefStr(ATL_FunctionId predId, _atlm);
char* ATL_getFactStr(ATL_Fact* factPtr, _atlm);
void ATL_printError(size_t errNum, FILE* stream, _atlm);

void ATL_printDeclarations(_atlm);
void ATL_printAxioms(_atlm);
void ATL_printRestrictions(_atlm);
void ATL_printFacts(_atlm);

#endif
