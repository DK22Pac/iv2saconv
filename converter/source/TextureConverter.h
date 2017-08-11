#pragma once
#include "ConverterOptions.h"
#include "gta_iv\formats\rage\grcTexturePC.h"
#include "gta_iv\formats\rage\pgDictionary.h"
#include "dffapi\Txd.h"

class TextureConverter {
public:
    static bool Convert(const std::string &sourceFilePath, const std::string &destFilePath, ConverterOptions const &options);
    static void SetTextureName(char *outputTxdTextureName, char const *wtdTextureName);
    static void WtdToTxd(rage::pgDictionary<rage::grcTexturePC> *wtd, gtaRwTexDictionary *txd);
    static void WtdToTxd(rage::pgDictionary<rage::grcTexturePC> *wtd, gtaRwTexDictionary *txd, unsigned int startLevel);
};