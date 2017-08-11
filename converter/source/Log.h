#pragma once
#include <iostream>
#include <string>
#include <fstream>

enum log_options {
    n,       // new line
    nl = n,  // new line
    q,       // quote
    note,    // NOTE
    warning, // WARNING
    error    // ERROR
};

class log_output {
    std::ofstream *file = nullptr;
public:
    inline void close() {
        if (file) {
            delete file;
            file = nullptr;
        }
    }

    inline void open() {
        file = new std::ofstream("log.txt");
    }

    inline void restart() {
        close();
        open();
    }

    template <typename T>
    inline log_output &put(T const &value) {
        std::cout << value;
        if (file)
            *file << value;
        return *this;
    }

    template <typename T>
    inline log_output &operator<<(T const &value) {
        return put(value);
    }

    inline log_output &operator<<(log_options option) {
        switch (option) {
        case n:
            put("\n"); break;
        case q:
            put("\""); break;
        case note:
            put("  NOTE: "); break;
        case warning:
            put("  WARNING: "); break;
        case error:
            put("  ERROR: "); break;
        }
        return *this;
    }
};

extern log_output lout;