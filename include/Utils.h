#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
    void saveToFile(const std::string& data);
    std::string loadFromFile();
}

#endif