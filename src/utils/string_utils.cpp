#ifndef UTIL_STRING_UTILS_CPP
#define UTIL_STRING_UTILS_CPP

#include<string>
#include <algorithm>
#include <cctype>

std::string to_lower(const std::string s) {
    std::string lowered = s;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return lowered;
}

#endif