#ifndef _CREDITLIB_H_
#define _CREDITLIB_H_

#include <memory>

#include "../Credit/CreditMonthlyPayment.h"

namespace s21 {
    class CreditLib {
    public:
        static CreditLib& Instance();

        CreditMonthlyPaymentResult calculateAnnuity(double amount, double percent, int term);    
        CreditMonthlyPaymentResult calculateDifferentiated(double amount, double percent, int term);    
    private:
        CreditLib();
        CreditLib(CreditLib const&) = delete;
        CreditLib& operator=(CreditLib const&) = delete;

        std::unique_ptr<CreditMonthlyPayment> m_annuity_;
        std::unique_ptr<CreditMonthlyPayment> m_differ_;
    };
}

#endif  // _CREDITLIB_H_
