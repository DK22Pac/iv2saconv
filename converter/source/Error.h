#pragma once
#include <Windows.h>
#include <stdio.h>

template <typename... ArgTypes> bool Error(char *format, ArgTypes... Args) {
    char text[512];
    sprintf_s(text, format, Args...);
    MessageBoxA(NULL, text, "IV2 converter", 0);
    return false;
}

template <typename... ArgTypes> bool Error(wchar_t *format, ArgTypes... Args) {
    wchar_t text[512];
    swprintf_s(text, format, Args...);
    MessageBoxW(NULL, text, L"IV2 converter", 0);
    return false;
}