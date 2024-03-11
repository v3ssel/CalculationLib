#ifndef _CALCULATIONDATA_H_
#define _CALCULATIONDATA_H_

#include "ExpressionTypes.h"

namespace s21 {
struct CalculationData {
    CalculationData() {
        value = 0;
        priority = 0;
        type = ExpressionTypes::NUMBER;
        is_operator = false;
        is_function = false;
        function = nullptr;
    }

    double value;
    short priority;
    ExpressionTypes type;

    bool is_operator;
    bool is_function;
    void *function;
};
}

#endif  // _CALCULATIONDATA_H_
