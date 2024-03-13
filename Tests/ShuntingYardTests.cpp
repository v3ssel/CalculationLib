#include <gtest/gtest.h>

#include "../CalculationAlgorithm/BaseCalculationAlgorithm.h"
#include "../CalculationAlgorithm/CalculationAlgorithm.h"

#include "../CalculationAlgorithm/Handlers/NumberHandler.h"
#include "../CalculationAlgorithm/Handlers/BracketsHandler.h"
#include "../CalculationAlgorithm/Handlers/OperatorsHandler.h"
#include "../CalculationAlgorithm/Handlers/FunctionsHandler.h"

class ShuntingYardTest : public ::testing::Test {
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

static std::vector<s21::ExpressionToken> queueToVector(std::queue<s21::ExpressionToken> queue) {
    std::vector<s21::ExpressionToken> result;
    while (!queue.empty()) {
        result.push_back(queue.front());
        queue.pop();
    }

    return result;
}

TEST_F(ShuntingYardTest, SumMinus1) {
    std::string exp = "-1+2+3-4+(-5)+6+7-8-9";
    // 01-2+3+4-05-+6+7+8-9-0+
    
    std::stack<s21::ExpressionToken> parsed = m_parser->parse(exp);
    std::queue<s21::ExpressionToken> postfix = m_calculation->toPostfix(parsed);
    auto vec = queueToVector(postfix);

    ASSERT_EQ(vec.size(), 23);

    EXPECT_DOUBLE_EQ(vec[0].value,  0);
    EXPECT_DOUBLE_EQ(vec[1].value,  1);
    EXPECT_EQ       (vec[2].type,   s21::ExpressionTypes::MINUS);
    EXPECT_DOUBLE_EQ(vec[3].value,  2);
    EXPECT_EQ       (vec[4].type,   s21::ExpressionTypes::PLUS);
    EXPECT_DOUBLE_EQ(vec[5].value,  3);
    EXPECT_EQ       (vec[6].type,   s21::ExpressionTypes::PLUS);
    EXPECT_DOUBLE_EQ(vec[7].value,  4);
    EXPECT_EQ       (vec[8].type,   s21::ExpressionTypes::MINUS);
    EXPECT_DOUBLE_EQ(vec[9].value,  0);
    EXPECT_DOUBLE_EQ(vec[10].value, 5);
    EXPECT_EQ       (vec[11].type,  s21::ExpressionTypes::MINUS);
    EXPECT_EQ       (vec[12].type,  s21::ExpressionTypes::PLUS);
    EXPECT_DOUBLE_EQ(vec[13].value, 6);
    EXPECT_EQ       (vec[14].type,  s21::ExpressionTypes::PLUS);
    EXPECT_DOUBLE_EQ(vec[15].value, 7);
    EXPECT_EQ       (vec[16].type,  s21::ExpressionTypes::PLUS);
    EXPECT_DOUBLE_EQ(vec[17].value, 8);
    EXPECT_EQ       (vec[18].type,  s21::ExpressionTypes::MINUS);
    EXPECT_DOUBLE_EQ(vec[19].value, 9);
    EXPECT_EQ       (vec[20].type,  s21::ExpressionTypes::MINUS);
    EXPECT_DOUBLE_EQ(vec[21].value, 0);
    EXPECT_EQ       (vec[22].type,  s21::ExpressionTypes::PLUS);
}

TEST_F(ShuntingYardTest, SumMinus2) {
    std::string exp = "9-(-0.30928)*3-4";
    // 9 0 0.30928 - 3 * - 4 - 0 +

    std::stack<s21::ExpressionToken> parsed = m_parser->parse(exp);
    std::queue<s21::ExpressionToken> postfix = m_calculation->toPostfix(parsed);
    auto vec = queueToVector(postfix);

    ASSERT_EQ(vec.size(), 11);

    EXPECT_DOUBLE_EQ(vec[0].value,  9);
    EXPECT_DOUBLE_EQ(vec[1].value,  0);
    EXPECT_DOUBLE_EQ(vec[2].value,  0.30928);
    EXPECT_EQ       (vec[3].type,   s21::ExpressionTypes::MINUS);
    EXPECT_DOUBLE_EQ(vec[4].value,  3);
    EXPECT_EQ       (vec[5].type,   s21::ExpressionTypes::MULT);
    EXPECT_EQ       (vec[6].type,   s21::ExpressionTypes::MINUS);
    EXPECT_DOUBLE_EQ(vec[7].value,  4);
    EXPECT_EQ       (vec[8].type,   s21::ExpressionTypes::MINUS);
    EXPECT_DOUBLE_EQ(vec[9].value,  0);
    EXPECT_EQ       (vec[10].type,  s21::ExpressionTypes::PLUS);
}

TEST_F(ShuntingYardTest, SumFunc) {
    std::string exp = "(132+sin(asin(sqrt(ln(log(228.11)))))-4*5^6*(123))";
    // 132 228.11 log ln sqrt asin sin + 4 5 6 ^ * 123 * - 0 +

    std::stack<s21::ExpressionToken> parsed = m_parser->parse(exp);
    std::queue<s21::ExpressionToken> postfix = m_calculation->toPostfix(parsed);
    auto vec = queueToVector(postfix);

    ASSERT_EQ(vec.size(), 18);

    EXPECT_DOUBLE_EQ(vec[0].value,  132);
    EXPECT_DOUBLE_EQ(vec[1].value,  228.11);
    EXPECT_EQ       (vec[2].type,   s21::ExpressionTypes::LOG);
    EXPECT_EQ       (vec[3].type,   s21::ExpressionTypes::LN);
    EXPECT_EQ       (vec[4].type,   s21::ExpressionTypes::SQRT);
    EXPECT_EQ       (vec[5].type,   s21::ExpressionTypes::ASIN);
    EXPECT_EQ       (vec[6].type,   s21::ExpressionTypes::SIN);
    EXPECT_EQ       (vec[7].type,   s21::ExpressionTypes::PLUS);
    EXPECT_DOUBLE_EQ(vec[8].value,  4);
    EXPECT_DOUBLE_EQ(vec[9].value,  5);
    EXPECT_DOUBLE_EQ(vec[10].value, 6);
    EXPECT_EQ       (vec[11].type,  s21::ExpressionTypes::POWER);
    EXPECT_EQ       (vec[12].type,  s21::ExpressionTypes::MULT);
    EXPECT_DOUBLE_EQ(vec[13].value, 123);
    EXPECT_EQ       (vec[14].type,  s21::ExpressionTypes::MULT);
    EXPECT_EQ       (vec[15].type,  s21::ExpressionTypes::MINUS);
    EXPECT_DOUBLE_EQ(vec[16].value, 0);
    EXPECT_EQ       (vec[17].type,  s21::ExpressionTypes::PLUS);
}

TEST_F(ShuntingYardTest, Power) {
    std::string exp = "2^2^3*4";
    // 2 2 3 ^ ^ 4 * 0 +

    std::stack<s21::ExpressionToken> parsed = m_parser->parse(exp);
    std::queue<s21::ExpressionToken> postfix = m_calculation->toPostfix(parsed);
    auto vec = queueToVector(postfix);

    ASSERT_EQ(vec.size(), 9);

    EXPECT_DOUBLE_EQ(vec[0].value,  2);
    EXPECT_DOUBLE_EQ(vec[1].value,  2);
    EXPECT_DOUBLE_EQ(vec[2].value,  3);
    EXPECT_EQ       (vec[3].type,   s21::ExpressionTypes::POWER);
    EXPECT_EQ       (vec[4].type,   s21::ExpressionTypes::POWER);
    EXPECT_DOUBLE_EQ(vec[5].value,  4);
    EXPECT_EQ       (vec[6].type,   s21::ExpressionTypes::MULT);
    EXPECT_DOUBLE_EQ(vec[7].value,  0);
    EXPECT_EQ       (vec[8].type,   s21::ExpressionTypes::PLUS);
}

TEST_F(ShuntingYardTest, Mod) {
    std::string exp = "(1*(2000/500))mod3";
    // 1 2000 500 / * 3 mod 0 +

    std::stack<s21::ExpressionToken> parsed = m_parser->parse(exp);
    std::queue<s21::ExpressionToken> postfix = m_calculation->toPostfix(parsed);
    auto vec = queueToVector(postfix);

    ASSERT_EQ(vec.size(), 9);

    EXPECT_DOUBLE_EQ(vec[0].value,  1);
    EXPECT_DOUBLE_EQ(vec[1].value,  2000);
    EXPECT_DOUBLE_EQ(vec[2].value,  500);
    EXPECT_EQ       (vec[3].type,   s21::ExpressionTypes::DIV);
    EXPECT_EQ       (vec[4].type,   s21::ExpressionTypes::MULT);
    EXPECT_DOUBLE_EQ(vec[5].value,  3);
    EXPECT_EQ       (vec[6].type,   s21::ExpressionTypes::MOD);
    EXPECT_DOUBLE_EQ(vec[7].value,  0);
    EXPECT_EQ       (vec[8].type,   s21::ExpressionTypes::PLUS);
}
