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

        s21::ExpressionPreparator* preparator = new s21::ExpressionPreparator();
        s21::ExpressionParser* parser = new s21::ExpressionParser(handler);
        s21::Calculation* calculation = new s21::Calculation();

        m_algorithm = new s21::CalculationAlgorithm(preparator, parser, calculation);
	}

	void TearDown() override {
        delete m_algorithm;
	}

    s21::BaseCalculationAlgorithm* m_algorithm;
};

TEST_F(CalculationAlgorithmTest, SumMinus1) {
    std::string exp = "-1+2+3-4+(-5)+6+7-8-9";

    double expected = -9;
    double actual = m_algorithm->calculate(exp);

    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, SumMinus2) {
    std::string exp = "9-(-0.30928)*3-4";

    double expected = 5.92784;
    double actual = m_algorithm->calculate(exp);

    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, SumFunc) {
    std::string exp = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";

    double expected = -7687367.0737845786;
    double actual = m_algorithm->calculate(exp);

    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, MultByBracket) {
    std::string exp = "2cos(1) + 3sin(2) - 4tan(1) + 2acos(0.32) - 3asin(0.2) + 4atan(2) - 4ln(10) + 7log(99) / 4 * 10";

    double expected = 29.606796314880558;
    double actual = m_algorithm->calculate(exp);

    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, Long) {
    std::string exp = "15/(7-(1+1))*3-(2+(1+1))*15/(7-(200+1))*3-(2+(1+1))*(15/"
                      "(7-(1+1))*3-(2+(1+1))+15/(7-(1+1))*3-(2+(1+1)))";

    double expected = -30.072164948453608;
    double actual = m_algorithm->calculate(exp);

    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, Functions) {
    std::string exp = "sin(1)+cos(1)+asin(1)+acos(1)+atan(1)+tan(1)+sqrt(16)+ln(10)+log(10)";

    double expected = 12.597960598517329;
    double actual = m_algorithm->calculate(exp);

    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, Power) {
    std::string exp = "2^2^3 * 4";

    double expected = 1024;
    double actual = m_algorithm->calculate(exp);

    EXPECT_DOUBLE_EQ(expected, actual);
}

TEST_F(CalculationAlgorithmTest, Mod) {
    std::string exp = "((2 * 5437 mod 521 * 224 mod (3 + 2)) * 2000 / 500) mod 3";

    double expected = 1;
    double actual = m_algorithm->calculate(exp);

    EXPECT_DOUBLE_EQ(expected, actual);
}

// TEST_F(CalculationAlgorithmTest, X) {
//     std::string exp = "2x(2x+1) + 4";
//     x = 3.15, ans = 49.989999999999995
// }
