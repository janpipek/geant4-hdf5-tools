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
      *
      * Template: use either H5Object or hid_t.
      */
    template<typename T> bool hasAttribute(const T& obj, const std::string& name);
    template<> bool hasAttribute<hid_t>(const hid_t& hid, const std::string& name);

    /**
      * @brief HDF5 type inquiry function template + few common implementations.
      */
    template<typename T> DataType getDataType();

    template<> DataType getDataType<int>();
    template<> DataType getDataType<double>();
    template<> DataType getDataType<std::string>(); // Note: C-type string assumed

    /**
      * @brief Get attribute of an object.
      *
      * Template: use either H5Object or hid_t.
      */
    template<typename T> Attribute getAttribute(const T& obj, const std::string& name);
    template<> Attribute getAttribute<hid_t>(const hid_t& hid, const std::string& name);

    /**
      * @brief Get attribute value.
      *
      * Template: use either H5Object or hid_t.
      * If attribute is not present, throw an exception.
      */
    template<typename T, typename U> T readAttribute(const U& obj, const std::string& name);

    /**
      * @brief Get attribute value.
      *
      * Template: use either H5Object or hid_t.
      * If attribute is not present, return a default value.
      */
    template<typename T, typename U> T readAttribute(const U& obj, const std::string& name, const T& defaultValue);

    template<typename T> void addAttribute(H5Object& obj, const std::string& name, const T& value);

    /*** TEMPLATE IMPLEMENTATIONS ***/
    template<typename T> bool hasAttribute(const T& obj, const std::string& name)
    {
        return hasAttribute(obj.getId(), name);
    }

    template<typename T> Attribute getAttribute(const T& obj, const std::string& name)
    {
        return obj.openAttribute(name);
    }

    template<typename T, typename U> T readAttribute(const U& obj, const std::string& name)
    {
        DataType dataType = getDataType<T>();
        Attribute att = getAttribute(obj, name);
        T result;
        att.read(dataType, &result); // For strings, result taken as string&, for others as void*
        return result;
    }

    template<typename T, typename U> T readAttribute(const U& obj, const std::string& name, const T& defaultValue)
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

    template<typename T> void addAttribute(H5Object& obj, const std::string& name, const T& value)
    {
        DataType dataType = getDataType<T>();
        DataSpace att_space(H5S_SCALAR);
        Attribute att = obj.createAttribute(name, dataType, att_space);
        att.write(dataType, &value); // For strings, value taken as string&, for others as void*
    }
}

#endif // HDF5FUNCTIONS_HH
