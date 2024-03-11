#ifndef _UTILS_H_
#define _UTILS_H_

#include <string>

namespace s21 {
    class Utils {
    public:
        static void stringReplace(std::string& original, const std::string& from, const std::string& to);
    };
}

#endif  // _UTILS_H_