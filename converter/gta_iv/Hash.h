#pragma once

//
// 'compile-time' hashing
//

template <unsigned int N, unsigned int I>
struct FnvHash
{
    __forceinline static unsigned int Hash(const char(&str)[N])
    {
        return (FnvHash<N, I - 1>::Hash(str) ^ str[I - 1]) * 16777619u;
    }
};

template <unsigned int N>
struct FnvHash<N, 1>
{
    __forceinline static unsigned int Hash(const char(&str)[N])
    {
        return (2166136261u ^ str[0]) * 16777619u;
    }
};

class StringHash
{
private:
    unsigned int m_hash;

public:
    template <unsigned int N>
    __forceinline StringHash(const char(&str)[N])
        : m_hash(FnvHash<N, N>::Hash(str))
    {
    }

    __forceinline operator unsigned int() const
    {
        return m_hash;
    }
};

// hash string, don't lowercase
inline constexpr uint32_t HashRageString(const char* string)
{
    uint32_t hash = 0;

    for (; *string; ++string)
    {
        hash += *string;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

inline constexpr char ToLower(const char c)
{
    return (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;
}

// hash string, lowercase
inline constexpr uint32_t HashString(const char* string)
{
    uint32_t hash = 0;

    for (; *string; ++string)
    {
        hash += ToLower(*string);
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}