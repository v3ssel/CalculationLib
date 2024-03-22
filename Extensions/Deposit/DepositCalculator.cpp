#include <iostream>

#include <cmath>
#include "DepositCalculator.h"

namespace s21 {
DepositResult DepositCalculator::calculate(const DepositParams &params, std::tm term_begin) {
    DepositResult result;
    result.income = 0;
    result.tax_amount = 0;
    result.total_amount = params.start_amount;
    
    int next_year_day_number = 0;
    double year_days = getYearDays(term_begin, next_year_day_number); 

    long current_repl = 0;
    long current_rate_index = 0;
    double current_rate_value = 0;
    int actual_term = params.rate_type == 2 ? params.term_in_days - 1 : params.term_in_days;

    for (long day = 1; day <= actual_term; day++) {
        if (current_repl < params.count_of_replenishments && day == params.days_of_replenishments[current_repl]) {
            result.total_amount += params.amount_of_replenishments[current_repl];
            current_repl++;
        }
        
        if (current_rate_index < params.count_of_rates &&
            ((params.rate_type == 2 && day == params.rate_dependence_values[current_rate_index]) ||
             (params.rate_type != 2 && result.total_amount >= params.rate_dependence_values[current_rate_index]))) {
            current_rate_value = params.rates[current_rate_index];
            current_rate_index++;
        }

        if (day == next_year_day_number || (params.rate_type == 2 && day == next_year_day_number - 1)) {
            year_days = getYearDays(term_begin, next_year_day_number);
        }

        double inc = std::round((result.total_amount / 100.0 * current_rate_value / year_days) * 100) / 100;
        result.income += inc; 
        // std::cout << "INCOME IN DAY " << day << " = " << inc << " = " << result.income << std::endl;

        if (params.capitalization && day % params.periodicity == 0) {
            result.total_amount += result.income;
            result.income = 0;
        }

        if (day == actual_term && actual_term % params.periodicity != 0) {
            result.total_amount += result.total_amount / 100.0 * current_rate_value / year_days * (actual_term % params.periodicity);
        }
    }

    if (params.capitalization) {
        double full_amount = params.start_amount;
        for (int i = 0; i < params.count_of_replenishments; i++) {
            full_amount += params.amount_of_replenishments[i];
        }

        result.income = result.total_amount - full_amount;
    }

    double no_taxes = 1e6 * params.tax_rate / 100.0;

    if (params.tax_rate != 0 && result.income > no_taxes)
        result.tax_amount = (result.income - no_taxes) * 13.0 / 100.0;
        
    return result;
}

int DepositCalculator::getYearDays(std::tm term_begin, int& next_year_day_number) {
    std::time_t t = std::mktime(&term_begin);
    std::tm* time = std::localtime(&t);

    time->tm_mday += next_year_day_number;
    std::mktime(time);

    int current_year = time->tm_year + 1900;

    int ydays = (current_year % 400 == 0 || current_year % 100 != 0) && (current_year % 4 == 0) ? 366 : 365;
    next_year_day_number = ydays - time->tm_yday;

    return ydays;
}
}