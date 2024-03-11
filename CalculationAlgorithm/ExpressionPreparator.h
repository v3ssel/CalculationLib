#ifndef _EXPRESSIONPREPARATOR_H_
#define _EXPRESSIONPREPARATOR_H_

#include <string>

namespace s21 {
    class ExpressionPreparator {
    public:
        virtual std::string prepare(const std::string &expression, const std::string& x);

    private:
        void replaceX(std::string& str, const std::string &x);
        void replaceE(std::string& str);
    };
}

#endif  // _EXPRESSIONPREPARATOR_H_
