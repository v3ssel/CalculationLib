#ifndef _CREDITMONTHLYPAYMENTANNUITY_H
#define _CREDITMONTHLYPAYMENTANNUITY_H

#include "CreditMonthlyPayment.h"

namespace s21 {
    class CreditMonthlyPaymentAnnuity : public CreditMonthlyPayment {
    public:
        CreditMonthlyPaymentResult calculate(double amount, double percent, int term) override;
    };
}

#endif  // _CREDITMONTHLYPAYMENTANNUITY_H
