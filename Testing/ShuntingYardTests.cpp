#include <gtest/gtest.h>

#include "../CalculationAlgorithm/BaseCalculationAlgorithm.h"
#include "../CalculationAlgorithm/CalculationAlgorithm.h"

#include "../CalculationAlgorithm/Handlers/NumberHandler.h"
#include "../CalculationAlgorithm/Handlers/BracketsHandler.h"
#include "../CalculationAlgorithm/Handlers/OperatorsHandler.h"
#include "../CalculationAlgorithm/Handlers/FunctionsHandler.h"

class CalculationAlgorithmTest : public ::testing::Test {
protected:
	void SetUp() override {
        s21::ExpressionHandler* handler = new s21::ExpressionHandler();
        s21::NumberHandler* numberHandler = new s21::NumberHandler();
        s21::BracketsHandler* bracketsHandler = new s21::BracketsHandler();
        s21::OperatorsHandler* operatorsHandler = new s21::OperatorsHandler();
        s21::FunctionsHandler* functionsHandler = new s21::FunctionsHandler();
        handler->setNext(numberHandler)->setNext(bracketsHandler)->setNext(operatorsHandler)->setNext(functionsHandler);

        m_parser = new s21::ExpressionParser(handler);
        m_calculation = new s21::Calculation();
	}

	void TearDown() override {
        delete m_parser;
        delete m_calculation;
	}

    s21::ExpressionParser* m_parser;
    s21::Calculation* m_calculation;
};

TEST_F(CalculationAlgorithmTest, SumMinus1) {
    std::string exp = "-1+2+3-4+(-5)+6+7-8-9";
    
    std::stack<s21::ExpressionToken> parsed = m_parser->parse(exp);
    std::queue<s21::ExpressionToken> postfix = m_calculation->toPostfix(parsed);

    // EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, SumMinus2) {
    std::string exp = "9-(-0.30928)*3-4";

    // EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, SumFunc) {
    std::string exp = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";

    // EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, Power) {
    std::string exp = "2^2^3 * 4";

    // EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, Mod) {
    std::string exp = "(1 * (2000 / 500)) mod 3";

    // EXPECT_DOUBLE_EQ(expected, actual);
}

// TEST_F(CalculationAlgorithmTest, X) {
//     std::string exp = "2x(2x+1) + 4";
//     x = 3.15, ans = 49.989999999999995
// }
