#ifndef TEST_SUPPORT_EASSERT
#define TEST_SUPPORT_EASSERT
#include <cstdio>
#include <stdexcept>
#include <string>

#define eassert(x) \
    { \
        if (!(x)) \
        { \
            char str[1000]; \
                sprintf( \
                        str, \
                        "Assertion failed at %s:%d (%s)", \
                        __FILE__, \
                        __LINE__, \
                        __FUNCTION__); \
                throw std::runtime_error(std::string(str)); \
        } \
    }

#endif