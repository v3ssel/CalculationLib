#include "Utils.h"

namespace s21 {   
void Utils::stringReplace(std::string &original, const std::string &from, const std::string &to) {
    size_t pos = std::string::npos;

    while ((pos = original.find(from)) != std::string::npos) {
        original.replace(pos, from.length(), to);
    }
}
}