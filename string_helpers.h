#ifndef STRING_HELPERS_H
#define STRING_HELPERS_H

#endif // STRING_HELPERS_H

#pragma once

#include <sstream>

template <typename T>
T FromString(const std::string& str) {
    std::stringstream ss;
    ss << str;
    T value;
    ss >> value;
    return value;
}

template <typename T>
std::string ToString(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

