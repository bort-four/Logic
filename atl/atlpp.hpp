// atlpp.hpp

#ifndef ATLPPP_HEADER
#define ATLPPP_HEADER

#include <string>

extern "C"
{
	#include "Model.h"
}


namespace ATL
{


typedef std::string String;

class ATL_Exception
{
public:
	ATL_Exception(const String &msg) : _msg(msg) {}
	String getMessage() const { return _msg; }
private:
	String _msg;
};


class ATL_Model;
class NamedConstant;

class ConstantBase
{
public:
	virtual ~ConstantBase();
	virtual String getDataTypeName() const = 0;
	virtual String toString(bool useDataTypeName = false) const = 0;
	
	virtual supp getSupp() const = 0;	// for internal purposes
	
	virtual bool isNamedConstant() const;
	virtual NamedConstant* toNamedConstant();
	virtual const NamedConstant* toNamedConstant() const;
	
protected:
	ConstantBase();
};


class NamedConstant : public ConstantBase
{
public:
	NamedConstant(ATL_Model* modelPtr, String name, String dataTypeName);
	NamedConstant(const NamedConstant &otherConst);
	
	String getName() const;
	
	virtual String getDataTypeName() const;
	virtual String toString(bool useDataTypeName = false) const;
	virtual supp getSupp() const;

private:
	ATL_Model* _modelPtr;
	DataTypeId _dataTypeId;
	IdType _id;
};


class ATL_Model
{
public:
	ATL_Model();
	~ATL_Model();

	Model* getNativeModelPtr();
	const Model* getNativeModelPtr() const;

private:
	Model* _nativeModelPtr;
};



}	// namespace ATL

#endif // ATLPPP_HEADER
