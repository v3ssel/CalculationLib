#include <string>

#include "CreditLib.h"
#include "../Credit/CreditMonthlyPaymentAnnuity.h"
#include "../Credit/CreditMonthlyPaymentDifferentiated.h"

#if defined(__WIN32__) || defined(__APPLE__)
    #define LIB_EXPORT __declspec(dllexport)
    #define LIB_CALLCONV __cdecl
#elif defined(__GNUC__) 
    #define LIB_EXPORT __attribute__((visibility("default")))
    #define LIB_CALLCONV
#else 
    #define LIB_EXPORT
    #define LIB_CALLCONV
    #pragma warning Unknown dynamic link import/export semantics.
#endif

extern "C" {
    void copyVector(double** dest, std::vector<double>& src) {
        *dest = new double[src.size()];
        std::copy(src.begin(), src.end(), *dest);
    }

    void handleError(char** error_msg, const char* source) {
        std::string error_str(source);

        *error_msg = new char[error_str.length() + 1];
        std::copy(error_str.begin(), error_str.end(), *error_msg);
        (*error_msg)[error_str.length()] = '\0';
    }

    LIB_EXPORT void LIB_CALLCONV CalculateAnnuity(double amount, double percent, int term, 
                                                        double** res_monthly_payment,
                                                        double** res_overpayment,
                                                        double** res_totalpayout, char** error_msg) {
        try {
            auto result = s21::CreditLib::Instance().calculateAnnuity(amount, percent, term);

            copyVector(res_monthly_payment, result.monthly_payments);
            copyVector(res_overpayment, result.overpayment);
            copyVector(res_totalpayout, result.total_payout);
        } catch (std::exception& e) {
            handleError(error_msg, e.what());
        }
    }

    LIB_EXPORT void LIB_CALLCONV CalculateDifferentiated(double amount, double percent, int term,
                                                               double** res_monthly_payment,
                                                               double** res_overpayment,
                                                               double** res_totalpayout, char** error_msg) {
        try {
            auto result = s21::CreditLib::Instance().calculateDifferentiated(amount, percent, term);

            copyVector(res_monthly_payment, result.monthly_payments);
            copyVector(res_overpayment, result.overpayment);
            copyVector(res_totalpayout, result.total_payout);
        } catch (std::exception& e) {
            handleError(error_msg, e.what());
        }
    }
}

namespace s21 {
CreditLib &CreditLib::Instance() {
    static CreditLib instance;
    return instance;
}

CreditMonthlyPaymentResult CreditLib::calculateAnnuity(double amount, double percent, int term) {
    return m_annuity_->calculate(amount, percent, term);
}

CreditMonthlyPaymentResult CreditLib::calculateDifferentiated(double amount, double percent, int term) {
    return m_differ_->calculate(amount, percent, term);
}

CreditLib::CreditLib() {
    m_annuity_ = std::make_unique<CreditMonthlyPaymentAnnuity>();
    m_differ_ = std::make_unique<CreditMonthlyPaymentDifferentiated>();
}
}
