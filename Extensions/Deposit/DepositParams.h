#ifndef _DEPOSITPARAMS_H_
#define _DEPOSITPARAMS_H_

namespace s21 {
    struct DepositParams {
        double start_amount;
        int term_in_days;
        int term_begin_day;
        int term_begin_month;
        int term_begin_year;
        double tax_rate;
        int periodicity;
        bool capitalization;

        int* days_of_replenishments;
        double* amount_of_replenishments;
        int count_of_replenishments;

        int rate_type;
        double* rates;
        double* rate_dependence_values;
        int count_of_rates;
    };
}

#endif  // _DEPOSITPARAMS_H_
