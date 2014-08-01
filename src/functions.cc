#include "functions.hh"

#include <H5Cpp.h>


using namespace std;

#ifndef H5_NO_NAMESPACE
    using namespace H5;
#endif

namespace g4h5
{
    void addStringAttribute(H5Object* obj, const std::string& name, const std::string& value)
    {
        StrType str_type(0, H5T_VARIABLE);
        DataSpace att_space(H5S_SCALAR);
        Attribute att = obj->createAttribute(name, str_type, att_space);
        att.write(str_type, value);
    }

    void addDoubleAttribute(H5Object* obj, const std::string& name, double value)
    {
        FloatType int_type(PredType::NATIVE_DOUBLE);
        DataSpace att_space(H5S_SCALAR);
        Attribute att = obj->createAttribute(name, int_type, att_space);
        att.write( int_type, &value);
    }

    void addIntegerAttribute(H5Object* obj, const std::string& name, int value)
    {
        IntType int_type(PredType::NATIVE_INT);
        DataSpace att_space(H5S_SCALAR);
        Attribute att = obj->createAttribute(name, int_type, att_space);
        att.write( int_type, &value);
    }
}
