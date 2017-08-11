#include "Log.h"
#include "Converter.h"
#include "TextureConverter.h"

int main()
{
    SetConsoleTitle("IV2 converter");

    lout.open();

    lout << "Conversion started." << nl << nl;

    ConverterOptions options;
    options.names.hashedFileNames = false;
    options.texturesPacking.sliceLevels = false;
    options.texturesPacking.baseLevel = 0;

    Converter::Convert("", ".wtd", "converted_txds", ".txd", TextureConverter::Convert, options);

    lout << nl << "Conversion finished.";

    lout.close();

    getchar();

    return 1;
}