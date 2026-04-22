#include "Utils.h"
#include <fstream>

namespace Utils {

void saveToFile(const std::string& data) {
    std::ofstream file("data.txt");
    file << data;
}

std::string loadFromFile() {
    std::ifstream file("data.txt");
    std::string data, line;

    while (getline(file, line)) {
        data += line;
    }

    return data;
}

}