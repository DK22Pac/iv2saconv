#pragma once
#include "ConverterOptions.h"
#include <string>

class Converter {
public:
    static bool Convert(const std::string &sourceDirectoryPath,
                        const std::string &sourceExtension,
                        const std::string &destDirectoryPath,
                        const std::string &destExtension,
                        bool(*callback)(const std::string &, const std::string &, const ConverterOptions &),
                        const ConverterOptions &options);
};