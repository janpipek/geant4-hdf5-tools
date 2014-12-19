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

    template<> Attribute getAttribute<hid_t>(const hid_t& hid, const string& name)
    {
        hid_t attr_id = H5Aopen(hid, name.c_str(), 0);
        if (attr_id < -1)
        {
            throw runtime_error("Attribute does not exist.");
        }
        return Attribute(attr_id);
    }

    template<> bool hasAttribute<hid_t>(const hid_t& hid, const string& name)
    {
        htri_t result = H5Aexists(hid, name.c_str());
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
}
