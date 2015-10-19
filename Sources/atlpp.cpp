// atlpp.cpp

#include "atlpp.hpp"
//~ #include "Model.h"

namespace ATL
{

//// ConstantBase

ConstantBase::ConstantBase() {}
ConstantBase::~ConstantBase() {}

bool ConstantBase::isNamedConstant() const { return false; }

NamedConstant* ConstantBase::toNamedConstant()
{
	throw ATL_Exception("ConstantBase::toNamedConstant(): "
						"cant't cast to NamedConst");
}

const NamedConstant* ConstantBase::toNamedConstant() const
{
	throw ATL_Exception("ConstantBase::toNamedConstant(): "
						"cant't cast to NamedConst");
}



//// NamedConstant

NamedConstant::NamedConstant(ATL_Model* modelPtr,
							String name, String dataTypeName)
	: _modelPtr(modelPtr)
{
	if (_modelPtr == NULL)
		throw ATL_Exception("NamedConstant(): invalid model pointer");
	
	Model* nativeModelPtr = modelPtr->getNativeModelPtr();
	_dataTypeId = getTypeIdByName(dataTypeName.c_str(), nativeModelPtr);
	
	if (_dataTypeId == BAD_INDEX)
		_dataTypeId = addDataType(dataTypeName.c_str(), nativeModelPtr);
	
	if (_dataTypeId == BAD_INDEX)
		throw ATL_Exception("NamedConstant(): can't find "
							"or add datatype");
	
	_id = getOrAddConstant(name.c_str(), _dataTypeId, nativeModelPtr).id;
	
	//~ if (_id == BAD_INDEX)
		//~ throw ATL_Exception("NamedConstant(): can't find "
							//~ "or add named constant");
}


NamedConstant::NamedConstant(const NamedConstant &otherConst)
	: _modelPtr(otherConst._modelPtr), _dataTypeId(otherConst._dataTypeId)
	, _id(otherConst._id)
{}


String NamedConstant::getName() const
{
	supp con; con.id = _id;
	char* namePtr = getConstStr(con, _dataTypeId,
								_modelPtr->getNativeModelPtr());
	String name(namePtr);
	delete namePtr;
	return name; 
}


String NamedConstant::getDataTypeName() const
{
	Model* modelPtr = _modelPtr->getNativeModelPtr();
	return String(getTypePtr(_dataTypeId)->name);
}


String NamedConstant::toString(bool useDataTypeName) const
{
	return getName() + " : " + getDataTypeName();
}


supp NamedConstant::getSupp() const
{
	supp con; con.id = _id;
	return con;
}



//// NamedConstant

ATL_Model::ATL_Model()
{
	_nativeModelPtr = new Model;
	initModel(_nativeModelPtr);
}


ATL_Model::~ATL_Model()
{
	freeModel(_nativeModelPtr);
	delete _nativeModelPtr;
}


Model* ATL_Model::getNativeModelPtr()
{
	return _nativeModelPtr;
}


const Model* ATL_Model::getNativeModelPtr() const
{
	return _nativeModelPtr;
}


} // namespace ATL
