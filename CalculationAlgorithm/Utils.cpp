#include "Utils.h"

namespace s21 {   
void Utils::stringReplace(std::string &original, const std::string &from, const std::string &to) {
    size_t pos = std::string::npos;

    while ((pos = original.find(from)) != std::string::npos) {
        original.replace(pos, from.length(), to);
    }
}

double Utils::plus(double a, double b) {
    return a + b;
}

double Utils::minus(double a, double b) {
    return a - b;
}

double Utils::multiply(double a, double b) {
    return a * b;
}

double Utils::divide(double a, double b) {
    return a / b;
}
}
