#pragma once
#include <filesystem>

inline std::experimental::filesystem::path GetRelativePath(std::experimental::filesystem::path from, std::experimental::filesystem::path to) {
    std::experimental::filesystem::path::const_iterator fromIter = from.begin();
    std::experimental::filesystem::path::const_iterator toIter = to.begin();
    while (fromIter != from.end() && toIter != to.end() && (*toIter) == (*fromIter)) {
        ++toIter;
        ++fromIter;
    }
    std::experimental::filesystem::path finalPath;
    while (fromIter != from.end()) {
        finalPath /= "..";
        ++fromIter;
    }
    while (toIter != to.end()) {
        finalPath /= *toIter;
        ++toIter;
    }
    return finalPath;
}