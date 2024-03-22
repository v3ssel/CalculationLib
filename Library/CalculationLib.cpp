#include <vector>
#include "CalculationLib.h"

#include "../CalculationAlgorithm/CalculationAlgorithm.h"
#include "../CalculationAlgorithm/Handlers/NumberHandler.h"
#include "../CalculationAlgorithm/Handlers/BracketsHandler.h"
#include "../CalculationAlgorithm/Handlers/OperatorsHandler.h"
#include "../CalculationAlgorithm/Handlers/FunctionsHandler.h"

#if defined(__WIN32__) || defined(__APPLE__)
    #define LIB_EXPORT __declspec(dllexport)
    #define LIB_CALLCONV __cdecl
#elif defined(__GNUC__) 
    #define LIB_EXPORT __attribute__((visibility("default")))
    #define LIB_CALLCONV __attribute__((cdecl))
#else 
    #define LIB_EXPORT
    #define LIB_CALLCONV
    #pragma warning Unknown dynamic link import/export semantics.
#endif

extern "C" {
    void handleError(char** error_msg, const char* source) {
        std::string error_str(source);

        *error_msg = new char[error_str.length() + 1];
        std::copy(error_str.begin(), error_str.end(), *error_msg);
        (*error_msg)[error_str.length()] = '\0';
    }

    LIB_EXPORT double LIB_CALLCONV Calculate(const char* expression, const char* x, char** error_msg) {
        try {
            return s21::CalculationLib::Instance().calculate(expression, x);
            
        } catch (std::exception& e) {
            handleError(error_msg, e.what());
        }
        
        return 1;
    }

    LIB_EXPORT void LIB_CALLCONV CalculateRange(int start, int end, const char* expression, int *size, double** data, char** error_msg) {
        try {
            std::vector<double> result = s21::CalculationLib::Instance().calculateRange(start, end, expression);

            *size = result.size();
            *data = new double[result.size()];
            std::copy(result.begin(), result.end(), *data);

        } catch (std::exception& e) {
            handleError(error_msg, e.what());
        }
    }
}

namespace s21 {
CalculationLib& CalculationLib::Instance() {
    static CalculationLib instance;
    return instance;
}

CalculationLib::CalculationLib() {
    ExpressionHandler* handler = new ExpressionHandler();
    NumberHandler* numberHandler = new NumberHandler();
    BracketsHandler* bracketsHandler = new BracketsHandler();
    OperatorsHandler* operatorsHandler = new OperatorsHandler();
    FunctionsHandler* functionsHandler = new FunctionsHandler();
    handler->setNext(numberHandler)->setNext(bracketsHandler)->setNext(operatorsHandler)->setNext(functionsHandler);

    ExpressionParser* parser = new ExpressionParser(handler);
    Calculation* calculation = new Calculation();

    ExpressionPreparator* preparator = new ExpressionPreparator();
    CalculationAlgorithm* algorithm = new CalculationAlgorithm(parser, calculation);

    m_algorithm_wrapper_ = std::make_unique<CalculationAlgorithmWithXWrapper>(algorithm, preparator); 
}

double CalculationLib::calculate(std::string expression, std::string x) {
    return m_algorithm_wrapper_->calculate(expression, x);
}

std::vector<double> CalculationLib::calculateRange(int start, int end, std::string expression) {
    std::vector<double> result;
    for (int i = start; i <= end; i++) {
        result.push_back(m_algorithm_wrapper_->calculate(expression, std::to_string(i)));
    }

    return result;
}
}
