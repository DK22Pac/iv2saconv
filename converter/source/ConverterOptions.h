#pragma once

struct ConverterOptions
{
    struct Names
    {
        bool hashedFileNames = false;
        bool hashedTextureNames = false;
        bool hashedNodeNames = false;
    } names;

    struct TexturesPacking
    {
        bool sliceLevels = false;
        unsigned int baseLevel = 0;
        bool skipNormalMaps = false;
        bool skipSpecMaps = false;
    } texturesPacking;
};