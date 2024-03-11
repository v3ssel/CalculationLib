#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

namespace s21 {
    class Utils {
    public:
        static void stringReplace(std::string& original, const std::string& from, const std::string& to);

        static double plus(double a, double b);
        static double minus(double a, double b);
        static double multiply(double a, double b);
        static double divide(double a, double b);
    };
}

#endif  // _UTILS_H_