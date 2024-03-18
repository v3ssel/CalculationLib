#include "CreditMonthlyPaymentDifferentiated.h"

namespace s21 {
CreditMonthlyPaymentResult CreditMonthlyPaymentDifferentiated::calculate(double amount, double percent, int term) {
    CreditMonthlyPaymentResult result;
    result.monthly_payments.resize(term);
    result.overpayment.resize(term);
    result.total_payout.resize(term);

    percent = percent / 100.0 / 12.0;
    double clear_monthly = amount / (double)term;
    double save_sum = amount;

    for (int i = 0; i < term; i++) {
        result.monthly_payments[i] = clear_monthly + amount * percent;
        
        if (!i)
            result.total_payout[i] = result.monthly_payments[i];
        else
            result.total_payout[i] = result.total_payout[i - 1] + result.monthly_payments[i];
            
        result.overpayment[i] = result.total_payout[i] - save_sum / term * (i + 1);
        amount -= clear_monthly;
    }
    
    return result;
}
}
