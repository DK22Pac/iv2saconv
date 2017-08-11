#include "Converter.h"
#include "helpers\GetRelativePath.h"
#include "Log.h"
#include "TextureConverter.h"
#include "gta_iv\Hash.h"
#include <filesystem>

using namespace std::experimental;

bool Converter::Convert(const std::string &sourceDirectoryPath,
                        const std::string &sourceExtension,
                        const std::string &destDirectoryPath,
                        const std::string &destExtension,
                        bool(*callback)(const std::string &, const std::string &, const ConverterOptions &),
                        const ConverterOptions &options)
{
    lout << "Searching for " << sourceExtension << " files ..." << nl;
    filesystem::path searchDir = sourceDirectoryPath.length() > 0 ? sourceDirectoryPath : filesystem::current_path().string();
    filesystem::path destDir = destDirectoryPath.length() > 0 ? destDirectoryPath : filesystem::current_path().string();
    for (const auto& p : filesystem::recursive_directory_iterator(searchDir)) {
        if (p.path().extension() == sourceExtension) {
            lout << "Converting " << sourceExtension << " : " << q << p.path().string() << q << nl;
            filesystem::path destPath = destDir;
            destPath /= GetRelativePath(searchDir, p.path());
            if (options.names.hashedFileNames)
                destPath.replace_filename(std::to_string(HashString(destPath.string().c_str())));
            else if (destPath.filename().string().length() > 20)
                lout << warning << "file " << q << destPath.string() << q << " has too long name (may cause problems with img)" << nl;
            destPath.replace_extension(destExtension);
            if (!filesystem::exists(destPath.parent_path()))
                filesystem::create_directories(destPath.parent_path());
            callback(p.path().string(), destPath.string(), options);
        }
    }
    return true;
}