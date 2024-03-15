#include <vector>
#include "CalculationLib.h"

#include "../CalculationAlgorithm/CalculationAlgorithm.h"
#include "../CalculationAlgorithm/Handlers/NumberHandler.h"
#include "../CalculationAlgorithm/Handlers/BracketsHandler.h"
#include "../CalculationAlgorithm/Handlers/OperatorsHandler.h"
#include "../CalculationAlgorithm/Handlers/FunctionsHandler.h"

extern "C" {
    __declspec(dllexport) double __cdecl calculate(const char* expression, const char* x) {
        return s21::CalculationLib::Instance().calculate(expression, x);
    }

    __declspec(dllexport) void __cdecl calculate_range(int start, int end, const char* expression, int *size, double**data) {
        std::vector<double> result = s21::CalculationLib::Instance().calculate_range(start, end, expression);

        *size = result.size();
        *data = new double[result.size()];
        std::copy(result.begin(), result.end(), *data);
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

std::vector<double> CalculationLib::calculate_range(int start, int end, std::string expression) {
    std::vector<double> result;
    for (int i = start; i <= end; i++) {
        result.push_back(m_algorithm_wrapper_->calculate(expression, std::to_string(i)));
    }

    return result;
}
}
