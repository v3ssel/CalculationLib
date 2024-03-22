#ifndef _DEPOSITCALCULATOR_H_
#define _DEPOSITCALCULATOR_H_

#include <ctime>
#include "DepositResult.h"
#include "DepositParams.h"

namespace s21 {
    class DepositCalculator {
    public:
        virtual ~DepositCalculator() = default;

        virtual DepositResult calculate(const DepositParams& params, std::tm term_begin);
    
    private:
        int getYearDays(std::tm term_begin, int& next_year_day_number);
    };
}

#endif  // _DEPOSITCALCULATOR_H_
