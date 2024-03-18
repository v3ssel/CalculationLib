#ifndef _CREDITMONTHLYPAYMENTDIFFERENTIATED_H
#define _CREDITMONTHLYPAYMENTDIFFERENTIATED_H

#include "CreditMonthlyPayment.h"

namespace s21 {
    class CreditMonthlyPaymentDifferentiated : public CreditMonthlyPayment {
    public:
        CreditMonthlyPaymentResult calculate(double amount, double percent, int term) override;
    };
}

#endif  // _CREDITMONTHLYPAYMENTDIFFERENTIATED_H
