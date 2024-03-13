#ifndef _CALCULATIONLIB_H_
#define _CALCULATIONLIB_H_

#include "../CalculationAlgorithm/CalculationAlgorithmWithXWrapper.h"

namespace s21 {
    class CalculationLib {
    public:
        double calculate(std::string expression, std::string x);
        double calculate_range(int start, int end, std::string expression);
    };
}

#endif // _CALCULATIONLIB_H_
