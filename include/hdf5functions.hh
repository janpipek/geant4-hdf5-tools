#ifndef HDF5FUNCTIONS_HH
#define HDF5FUNCTIONS_HH

/**
  * Various shortcuts for HDF5 functionality without simple C++ API.
  */

#include <string>
#include <H5Cpp.h>

namespace g4h5
{
    #ifndef H5_NO_NAMESPACE
        using H5::H5Object;
        using H5::Attribute;
        using H5::DataType;
        using H5::DataSpace;
    #endif

    /**
      * @brief Check existence of attribute using C API.
      */
    bool hasAttribute(H5Object* obj, const std::string& name);

    /**
      * @brief HDF5 type inquiry function template + few common implementations.
      */
    template<typename T> DataType getDataType();

    template<> DataType getDataType<int>();
    template<> DataType getDataType<double>();
    template<> DataType getDataType<std::string>(); // Note: C-type string assumed

    template<typename T> void addAttribute(H5Object* obj, const std::string& name, const T& value)
    {
        DataType dataType = getDataType<T>();
        DataSpace att_space(H5S_SCALAR);
        Attribute att = obj->createAttribute(name, dataType, att_space);
        att.write(dataType, &value); // For strings, value taken as string&, for others as void*
    }

    template<typename T> T readAttribute(H5Object* obj, const std::string& name)
    {
        DataType dataType = getDataType<T>();
        Attribute att = obj->openAttribute(name);
        T result;
        att.read(dataType, &result); // For strings, result taken as string&, for others as void*
        return result;
    }

    template<typename T> T readAttribute(H5Object* obj, const std::string& name, const T& defaultValue)
    {
        if (!hasAttribute(obj, name))
        {
            return defaultValue;
        }
        else
        {
            return readAttribute<T>(obj, name);
        }
    }
}

#endif // HDF5FUNCTIONS_HH
