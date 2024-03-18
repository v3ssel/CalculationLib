#ifndef _CREDITMONTHLYPAYMENTRESULT_H_
#define _CREDITMONTHLYPAYMENTRESULT_H_

#include <vector>

namespace s21 {
    struct CreditMonthlyPaymentResult {
        std::vector<double> monthly_payments;
        std::vector<double> overpayment;
        std::vector<double> total_payout;
    };
}

#endif  // _CREDITMONTHLYPAYMENTRESULT_H_
