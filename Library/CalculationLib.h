#ifndef _CALCULATIONLIB_H_
#define _CALCULATIONLIB_H_

#include "../CalculationAlgorithm/CalculationAlgorithmWithXWrapper.h"

namespace s21 {
    class CalculationLib {
    public:
        static CalculationLib& Instance();

        double calculate(std::string expression, std::string x);
        std::vector<double> calculate_range(int start, int end, std::string expression);
    
    private:
        CalculationLib();
        CalculationLib(CalculationLib const&) = delete;
        CalculationLib& operator=(CalculationLib const&) = delete;


        std::unique_ptr<CalculationAlgorithmWithXWrapper> m_algorithm_wrapper_;
    };
}

#endif // _CALCULATIONLIB_H_
