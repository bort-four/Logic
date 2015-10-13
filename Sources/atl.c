/* atl.c */

#include <stddef.h>
#include <stdlib.h>
#include "Logic.h"
#include "Model.h"
#include "Interpretation.h"
#include "Parser.h"
#include "atl.h"

/* === local defenitions === */

#define getModelPtr(modelId) ( ptr(Model, ATL_models_g) + (modelId) )
#define modelPtr getModelPtr(modelId)


/* === implementation === */


void ATL_init()
{
	initVect(ATL_models_g, Model);
}

void ATL_free()
{
	size_t modlNum;
	
	forVect(modlNum, ATL_models_g)
		freeModel(ptr(Model, ATL_models_g) + modlNum);
	
	freeVect(ATL_models_g);
}


ATL_ModelId ATL_createModel()
{
	Model model;
	initModel(&model);
	
	addBack(ATL_models_g, Model, model);
	
	return ATL_models_g.len - 1;
}

void ATL_freeModel(_atlm)
{
	freeModel(modelPtr);
}


void ATL_clear(_atlm)
{
	FILE* debugStream = modelPtr->debugStream;
	FILE* errorStream = modelPtr->errorStream;
	
	freeModel(modelPtr);
	initModel(modelPtr);
	
	ATL_setDebugStream(debugStream, modelId);
	ATL_setErrorStream(errorStream, modelId);
}


void ATL_inputFile(char fileName[], _atlm)
{
	parseFile(fileName, modelPtr);
}

void ATL_inputString(char string[], _atlm)
{
	parseString(string, modelPtr);
}

ATL_Query ATL_inputQuery(char string[], _atlm)
{
	Query query = parseQuery(string, modelPtr);
	return createQueryIterator(query);
}


void ATL_setDebugStream(FILE* stream, _atlm)
{
	modelPtr->debugStream = stream;
}

void ATL_setErrorStream(FILE* stream, _atlm)
{
	modelPtr->errorStream = stream;
}

void ATL_run(_atlm)
{
	//~ if (modelPtr->errors.len == 0)
	//~ {
		work(modelPtr);
		check(modelPtr);
	//~ }
}


Boolean ATL_queryIsValid(ATL_Query* queryPtr)
{
	return qiterIsValid(queryPtr);
}

void ATL_moveQuery(ATL_Query* queryPtr)
{
	moveQIterator(queryPtr);
}

void ATL_resetQuery(ATL_Query* queryPtr)
{
	resetQIterator(queryPtr);
}


ATL_Query ATL_createQuery(ATL_FunctionId funcId, Boolean isPredicate,
						  ATL_Constant* params, ATL_Constant value, _atlm)
{
	Func* funcPtr = (isPredicate) ? getPredPtr(funcId) : getFuncPtr(funcId);
	Query query = createQuery(funcPtr, params);
	query.value = value;
	
	return createQueryIterator(query);
}

ATL_Fact ATL_createFact(ATL_FunctionId funcId, Boolean isPredicate,
						ATL_Constant* params, ATL_Constant value, _atlm)
{
	Func* funcPtr = (isPredicate) ? getPredPtr(funcId) : getFuncPtr(funcId);
	return createFact(funcPtr, params, value);
}

ATL_Fact ATL_getFact(ATL_Query* queryPtr)
{
	return getFact(queryPtr);
}


Boolean ATL_setFact(ATL_Fact* factPtr, _atlm)
{
	return setFact(factPtr, modelPtr);
}



void ATL_freeFact(ATL_Fact* factPtr)
{
	freeFact(factPtr);
}

void ATL_freeQuery(ATL_Query* queryPtr)
{
	freeQuery(&queryPtr->query);
}



ATL_Integer ATL_getIntegerValue(ATL_Constant constant)
{
	shiftSuppBack(constant);
	return constant.integer;
}

ATL_Real ATL_getRealValue(ATL_Constant constant)
{
	shiftSuppBack(constant);
	return constant.real;
}


char* ATL_getConstantName(ATL_Constant constant, ATL_DataTypeId typeId, _atlm)
{
	return getTypePtr(typeId)->name;
}


int ATL_constCmp(ATL_Constant con1, ATL_Constant con2)
{
	return (int)conCmp(con1, con2);
}


ATL_Constant ATL_getIntegerConstant(ATL_Integer value)
{
	supp con; con.integer = value;
	shiftSupp(con);
	return con;
}

ATL_Constant ATL_getRealConstant(ATL_Real value)
{
	supp con; con.real = value;
	shiftSupp(con);
	return con;
	
	//~ supp con; con.real = shiftSupp(value);
	//~ return con;
}

//~ void ATL_setIntegerValue(ATL_Constant* constPtr, ATL_Integer value)
//~ {
	//~ constPtr->integer = value;
//~ }
//~ 
//~ void ATL_setRealValue(ATL_Constant* constPtr, ATL_Real value)
//~ {
	//~ constPtr->integer = value;
//~ }

ATL_Constant ATL_getConstantByName(const char name[], ATL_DataTypeId typeId, _atlm)
{
	return getOrAddConstant(name, typeId, modelPtr);
}



ATL_FunctionId ATL_getFuncIdByName(const char name[], _atlm)
{
	return getFuncNumByName(name, modelPtr);
}

ATL_FunctionId ATL_getPredIdByName(const char name[], _atlm)
{
	return getPredNumByName(name, modelPtr);
}



ATL_FunctionId	ATL_getFactFunction(ATL_Fact* factPtr, _atlm)
{
	if (factPtr->funcPtr->dataType != DT_BOOL)
		 return factPtr->funcPtr - getFuncPtr(0);
	else return ATL_BAD_INDEX;
}

ATL_FunctionId	ATL_getFactPredicate(ATL_Fact* factPtr, _atlm)
{
	if (factPtr->funcPtr->dataType == DT_BOOL)
		 return factPtr->funcPtr - getPredPtr(0);
	else return ATL_BAD_INDEX;
}

ATL_Constant ATL_getFactParam(ATL_Fact* factPtr, size_t parNum)
{
	if (parNum >= factPtr->funcPtr->parCt) return ATL_IDC;
	return factPtr->params[parNum];
}


ATL_Constant ATL_getFactValue(ATL_Fact* factPtr)
{
	return factPtr->value;
}


char* ATL_getDataTypeName(ATL_DataTypeId dtypeId, _atlm)
{
	if (dtypeId < 0 || dtypeId >= types_m.len) return NULL;
	else return getTypePtr(dtypeId)->name;
}

ATL_DataTypeId ATL_getTypeIdByName(const char name[], _atlm)
{
	return getTypeIdByName(name, modelPtr);
}



size_t ATL_getFuncParCt(ATL_FunctionId funcId, _atlm)
{
	if (funcId >= funcs_m.len) return 0;
	return getFuncPtr(funcId)->parCt;
}

ATL_DataTypeId ATL_getFuncParType(ATL_FunctionId funcId, size_t parNum, _atlm)
{
	if (funcId >= funcs_m.len || parNum >= getFuncPtr(funcId)->parCt)
		 return ATL_BAD_INDEX;
	else return getFuncPtr(funcId)->parTypes[parNum];
}

ATL_DataTypeId ATL_getFuncDataType(ATL_FunctionId funcId, _atlm)
{
	if (funcId >= funcs_m.len) return ATL_BAD_INDEX;
	return getFuncPtr(funcId)->dataType;
}


size_t ATL_getPredParCt(ATL_FunctionId predId, _atlm)
{
	if (predId >= preds_m.len) return 0;
	return getPredPtr(predId)->parCt;
}

ATL_DataTypeId ATL_getPredParType(ATL_FunctionId predId, size_t parNum, _atlm)
{
	if (predId >= preds_m.len || parNum >= getPredPtr(predId)->parCt)
		 return ATL_BAD_INDEX;
	else return getPredPtr(predId)->parTypes[parNum];
}


size_t ATL_getErrorCt(_atlm)	{ return modelPtr->errors.len; }

ATL_ErrorType ATL_getErrorType(size_t errNum, _atlm)
{
	if (errNum >= ATL_getErrorCt(modelId))
		 return ATL_BAD_INDEX;
	else return ptr(Error, modelPtr->errors)[errNum].type;
}


size_t ATL_getAxiomCt(_atlm)		{ return axioms_m.len; }
size_t ATL_getRestrictionCt(_atlm)	{ return restrs_m.len; }


char* ATL_getAxiomStr(size_t axiomNum, _atlm)
{
	return getAxiomStr(getAxPtr(axiomNum), modelPtr);
}

char* ATL_getRestrictionStr(size_t restrictionNum, _atlm)
{
	return getRestrStr(getRestrPtr(restrictionNum), modelPtr);
}

char* ATL_getFuncDefStr(ATL_FunctionId funcId, _atlm)
{
	return getFuncDeclStr(getFuncPtr(funcId), modelPtr);
}

char* ATL_getPredDefStr(ATL_FunctionId predId, _atlm)
{
	return getFuncDeclStr(getPredPtr(predId), modelPtr);
}

char* ATL_getFactStr(ATL_Fact* factPtr, _atlm)
{
	return getFactStr(factPtr, getModelPtr(modelId));
}

void ATL_printError(size_t errNum, FILE* stream, _atlm)
{
	printError(ptr(Error, modelPtr->errors) + errNum, stream);
}


void ATL_printDeclarations(_atlm)
{
	printDeclarations(modelPtr);
}

void ATL_printAxioms(_atlm)
{
	printAxioms(modelPtr);
}

void ATL_printRestrictions(_atlm)
{
	printRestrictions(modelPtr);
}
