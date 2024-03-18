#include <cmath>
#include "CreditMonthlyPaymentAnnuity.h"

namespace s21 {
    CreditMonthlyPaymentResult CreditMonthlyPaymentAnnuity::calculate(double amount, double percent, int term) {
        CreditMonthlyPaymentResult result;
        result.monthly_payments.resize(term);
        result.overpayment.resize(term);
        result.total_payout.resize(term);
        
        percent = percent / 100.0 / 12.0;
        double annuity = amount * (percent / (1 - std::pow((double)(1 + percent), (double)(-term))));
        annuity = std::round((double)(annuity * 100)) / 100.0;

        for (int i = 0; i < term; i++) {
            result.monthly_payments[i] = annuity;
            result.total_payout[i] = result.monthly_payments[i] * (i + 1);
            result.overpayment[i] = result.total_payout[i] - amount / term * (i + 1);
        }

        return result;
    }
}
