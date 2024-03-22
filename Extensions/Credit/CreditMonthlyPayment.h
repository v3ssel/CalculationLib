#ifndef _CREDITMONTHLYPAYMENT_H_
#define _CREDITMONTHLYPAYMENT_H_

#include "CreditMonthlyPaymentResult.h"

namespace s21 {
    class CreditMonthlyPayment {
    public:
        virtual CreditMonthlyPaymentResult calculate(double amount, double percent, int term) = 0;
        virtual ~CreditMonthlyPayment() = default;
    };
}

#endif  // _CREDITMONTHLYPAYMENT_H_
