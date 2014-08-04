#include "hdf5functions.hh"

#include <stdexcept>

#include <H5Cpp.h>
#include <H5Apublic.h>

using namespace std;

#ifndef H5_NO_NAMESPACE
    using namespace H5;
#endif

namespace g4h5
{
    bool hasAttribute(H5Object *obj, const string &name)
    {
        htri_t result = H5Aexists(obj->getId(), name.c_str());
        if (result > 0)
        {
            return true;
        }
        else if (!result)
        {
            return false;
        }
        else
        {
            throw runtime_error("Error checking for existence of attribute.");
        }
    }

    template<> DataType getDataType<int>()
    {
        return IntType(PredType::NATIVE_INT);
    }

    template<> DataType getDataType<double>()
    {
        return FloatType(PredType::NATIVE_DOUBLE);
    }

    template<> DataType getDataType<string>()
    {
        return StrType(0, H5T_VARIABLE);
    }
}
