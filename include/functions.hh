#ifndef FUNCTIONS_HH
#define FUNCTIONS_HH

#include <H5Cpp.h>

namespace g4h5
{
    #ifndef H5_NO_NAMESPACE
        using H5::H5Object;
    #endif

    void addStringAttribute(H5Object* obj, const std::string& name, const std::string& value);

    void addDoubleAttribute(H5Object* obj, const std::string& name, double value);

    void addIntegerAttribute(H5Object* obj, const std::string& name, int value);
}

#endif // FUNCTIONS_HH
