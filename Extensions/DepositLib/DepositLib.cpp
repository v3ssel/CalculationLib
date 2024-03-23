#include <string>
#include "DepositLib.h"

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
    static void handleError(char** error_msg, const char* source) {
        std::string error_str(source);

        *error_msg = new char[error_str.length() + 1];
        std::copy(error_str.begin(), error_str.end(), *error_msg);
        (*error_msg)[error_str.length()] = '\0';
    }

    LIB_EXPORT s21::DepositResult LIB_CALLCONV CalculateDepositIncome(s21::DepositParams params, char** error_msg) {
        s21::DepositResult result{0, 0, 0};
        
        try {
            result = s21::DepositLib::Instance().calculate(params);

        } catch (std::exception& e) {
            handleError(error_msg, e.what());
        }

        return result;
    }
}

namespace s21 {
DepositLib& DepositLib::Instance() {
    static DepositLib instance;
    return instance;
}

DepositResult DepositLib::calculate(const DepositParams &params) {
    return m_deposit_->calculate(params);
}

DepositLib::DepositLib() {
    m_deposit_ = std::make_unique<DepositCalculator>();
}
}
