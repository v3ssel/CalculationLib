#ifndef _CREDITMONTHLYPAYMENT_H_
#define _CREDITMONTHLYPAYMENT_H_

#include "CreditMonthlyPaymentResult.h"

namespace s21 {
    class CreditMonthlyPayment {
    public:
        virtual CreditMonthlyPaymentResult calculate(double amount, double percent, int term) = 0;
        // static CreditMonthlyPayment& Instance();

    // private:
    //     CreditMonthlyPayment();
    //     CreditMonthlyPayment(const CreditMonthlyPayment&) = delete;
    //     CreditMonthlyPayment& operator=(const CreditMonthlyPayment&) = delete;
    };
}

#endif  // _CREDITMONTHLYPAYMENT_H_
