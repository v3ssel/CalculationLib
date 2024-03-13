#include <cmath>
#include <gtest/gtest.h>

#include "../CalculationAlgorithm/ExpressionParser.h"
#include "../CalculationAlgorithm/Handlers/NumberHandler.h"
#include "../CalculationAlgorithm/Handlers/BracketsHandler.h"
#include "../CalculationAlgorithm/Handlers/OperatorsHandler.h"
#include "../CalculationAlgorithm/Handlers/FunctionsHandler.h"

class ExpressionParserTest : public ::testing::Test {
protected:
	void SetUp() override {
        s21::ExpressionHandler* handler = new s21::ExpressionHandler();
        s21::NumberHandler* numberHandler = new s21::NumberHandler();
        s21::BracketsHandler* bracketsHandler = new s21::BracketsHandler();
        s21::OperatorsHandler* operatorsHandler = new s21::OperatorsHandler();
        s21::FunctionsHandler* functionsHandler = new s21::FunctionsHandler();
        handler->setNext(numberHandler)->setNext(bracketsHandler)->setNext(operatorsHandler)->setNext(functionsHandler);

        m_parser = new s21::ExpressionParser(handler);
	}

	void TearDown() override {
        delete m_parser;
	}

    s21::ExpressionParser* m_parser;
};

static std::vector<s21::ExpressionToken> stackToVector(std::stack<s21::ExpressionToken>& stack) {
    std::vector<s21::ExpressionToken> result;
    while (!stack.empty()) {
        result.push_back(stack.top());
        stack.pop();
    }
    
    return result;
}

TEST_F(ExpressionParserTest, Plus) {
    auto stack = m_parser->parse("2+2");
    auto vec = stackToVector(stack);

    ASSERT_EQ(vec.size(), 5);

    EXPECT_EQ(vec[0].value, 2);
    EXPECT_EQ(vec[1].value, 0);
    EXPECT_EQ(vec[2].value, 2);
    EXPECT_EQ(vec[3].value, 0);
    EXPECT_EQ(vec[4].value, 0);

    EXPECT_EQ(vec[0].type, s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[1].type, s21::ExpressionTypes::PLUS);
    EXPECT_EQ(vec[2].type, s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[3].type, s21::ExpressionTypes::PLUS);
    EXPECT_EQ(vec[4].type, s21::ExpressionTypes::NUMBER);
    
    EXPECT_EQ(vec[0].priority, 0);
    EXPECT_EQ(vec[1].priority, 1);
    EXPECT_EQ(vec[2].priority, 0);
    EXPECT_EQ(vec[3].priority, 1);
    EXPECT_EQ(vec[4].priority, 0);

    EXPECT_EQ(vec[0].is_function, false);
    EXPECT_EQ(vec[1].is_function, false);
    EXPECT_EQ(vec[2].is_function, false);
    EXPECT_EQ(vec[3].is_function, false);
    EXPECT_EQ(vec[4].is_function, false);

    EXPECT_EQ(vec[0].is_operator, false);
    EXPECT_EQ(vec[1].is_operator, true);
    EXPECT_EQ(vec[2].is_operator, false);
    EXPECT_EQ(vec[3].is_operator, true);
    EXPECT_EQ(vec[4].is_operator, false);

    double (*fnc)(double, double) = reinterpret_cast<double (*)(double, double)>(vec[1].function);
    EXPECT_EQ(fnc(vec[0].value, vec[2].value), 4);

    fnc = reinterpret_cast<double (*)(double, double)>(vec[3].function);    
    EXPECT_EQ(fnc(vec[2].value, vec[4].value), 2);
}

TEST_F(ExpressionParserTest, SimpleOperators) {
    auto stack = m_parser->parse("2+3-4*5/6mod7^8");
    auto vec = stackToVector(stack);

    ASSERT_EQ(vec.size(), 15);

    EXPECT_EQ(vec[0].value,  2);
    EXPECT_EQ(vec[1].value,  0);
    EXPECT_EQ(vec[2].value,  3);
    EXPECT_EQ(vec[3].value,  0);
    EXPECT_EQ(vec[4].value,  4);
    EXPECT_EQ(vec[5].value,  0);
    EXPECT_EQ(vec[6].value,  5);
    EXPECT_EQ(vec[7].value,  0);
    EXPECT_EQ(vec[8].value,  6);
    EXPECT_EQ(vec[9].value,  0);
    EXPECT_EQ(vec[10].value, 7);
    EXPECT_EQ(vec[11].value, 0);
    EXPECT_EQ(vec[12].value, 8);
    EXPECT_EQ(vec[13].value, 0);
    EXPECT_EQ(vec[14].value, 0);

    EXPECT_EQ(vec[0].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[1].type,  s21::ExpressionTypes::PLUS);
    EXPECT_EQ(vec[2].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[3].type,  s21::ExpressionTypes::MINUS);
    EXPECT_EQ(vec[4].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[5].type,  s21::ExpressionTypes::MULT);
    EXPECT_EQ(vec[6].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[7].type,  s21::ExpressionTypes::DIV);
    EXPECT_EQ(vec[8].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[9].type,  s21::ExpressionTypes::MOD);
    EXPECT_EQ(vec[10].type, s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[11].type, s21::ExpressionTypes::POWER);
    EXPECT_EQ(vec[12].type, s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[13].type, s21::ExpressionTypes::PLUS);
    EXPECT_EQ(vec[14].type, s21::ExpressionTypes::NUMBER);

    EXPECT_EQ(vec[0].priority,  0);
    EXPECT_EQ(vec[1].priority,  1);
    EXPECT_EQ(vec[2].priority,  0);
    EXPECT_EQ(vec[3].priority,  1);
    EXPECT_EQ(vec[4].priority,  0);
    EXPECT_EQ(vec[5].priority,  2);
    EXPECT_EQ(vec[6].priority,  0);
    EXPECT_EQ(vec[7].priority,  2);
    EXPECT_EQ(vec[8].priority,  0);
    EXPECT_EQ(vec[9].priority,  2);
    EXPECT_EQ(vec[10].priority, 0);
    EXPECT_EQ(vec[11].priority, 3);
    EXPECT_EQ(vec[12].priority, 0);
    EXPECT_EQ(vec[13].priority, 1);
    EXPECT_EQ(vec[14].priority, 0);

    EXPECT_EQ(vec[0].is_function,  false);
    EXPECT_EQ(vec[1].is_function,  false);
    EXPECT_EQ(vec[2].is_function,  false);
    EXPECT_EQ(vec[3].is_function,  false);
    EXPECT_EQ(vec[4].is_function,  false);
    EXPECT_EQ(vec[5].is_function,  false);
    EXPECT_EQ(vec[6].is_function,  false);
    EXPECT_EQ(vec[7].is_function,  false);
    EXPECT_EQ(vec[8].is_function,  false);
    EXPECT_EQ(vec[9].is_function,  false);
    EXPECT_EQ(vec[10].is_function, false);
    EXPECT_EQ(vec[11].is_function, false);
    EXPECT_EQ(vec[12].is_function, false);
    EXPECT_EQ(vec[13].is_function, false);
    EXPECT_EQ(vec[14].is_function, false);

    EXPECT_EQ(vec[0].is_operator,  false);
    EXPECT_EQ(vec[1].is_operator,  true);
    EXPECT_EQ(vec[2].is_operator,  false);
    EXPECT_EQ(vec[3].is_operator,  true);
    EXPECT_EQ(vec[4].is_operator,  false);
    EXPECT_EQ(vec[5].is_operator,  true);
    EXPECT_EQ(vec[6].is_operator,  false);
    EXPECT_EQ(vec[7].is_operator,  true);
    EXPECT_EQ(vec[8].is_operator,  false);
    EXPECT_EQ(vec[9].is_operator,  true);
    EXPECT_EQ(vec[10].is_operator, false);
    EXPECT_EQ(vec[11].is_operator, true);
    EXPECT_EQ(vec[12].is_operator, false);
    EXPECT_EQ(vec[13].is_operator, true);
    EXPECT_EQ(vec[14].is_operator, false);

    double (*fnc)(double, double) = reinterpret_cast<double (*)(double, double)>(vec[1].function);
    EXPECT_EQ(fnc(vec[0].value, vec[2].value), 2 + 3);

    fnc = reinterpret_cast<double (*)(double, double)>(vec[3].function);    
    EXPECT_EQ(fnc(vec[2].value, vec[4].value), 3 - 4);

    fnc = reinterpret_cast<double (*)(double, double)>(vec[5].function);    
    EXPECT_EQ(fnc(vec[4].value, vec[6].value), 4 * 5);

    fnc = reinterpret_cast<double (*)(double, double)>(vec[7].function);    
    EXPECT_EQ(fnc(vec[6].value, vec[8].value), 5.0 / 6.0);

    fnc = reinterpret_cast<double (*)(double, double)>(vec[9].function);    
    EXPECT_EQ(fnc(vec[8].value, vec[10].value), 6 % 7);

    fnc = reinterpret_cast<double (*)(double, double)>(vec[11].function);    
    EXPECT_EQ(fnc(vec[10].value, vec[12].value), std::pow(7, 8));

    fnc = reinterpret_cast<double (*)(double, double)>(vec[13].function);    
    EXPECT_EQ(fnc(vec[12].value, vec[14].value), 8 + 0);
}

TEST_F(ExpressionParserTest, Functions) {
    auto stack = m_parser->parse("sqrt(sin(cos(tan(acos(asin(atan(ln(log(1)))))))))");
    auto vec = stackToVector(stack);

    ASSERT_EQ(vec.size(), 30);

    EXPECT_EQ(vec[0].value,  0);
    EXPECT_EQ(vec[1].value,  0);
    EXPECT_EQ(vec[2].value,  0);
    EXPECT_EQ(vec[3].value,  0);
    EXPECT_EQ(vec[4].value,  0);
    EXPECT_EQ(vec[5].value,  0);
    EXPECT_EQ(vec[6].value,  0);
    EXPECT_EQ(vec[7].value,  0);
    EXPECT_EQ(vec[8].value,  0);
    EXPECT_EQ(vec[9].value,  0);
    EXPECT_EQ(vec[10].value, 0);
    EXPECT_EQ(vec[11].value, 0);
    EXPECT_EQ(vec[12].value, 0);
    EXPECT_EQ(vec[13].value, 0);
    EXPECT_EQ(vec[14].value, 0);
    EXPECT_EQ(vec[15].value, 0);
    EXPECT_EQ(vec[16].value, 0);
    EXPECT_EQ(vec[17].value, 0);
    EXPECT_EQ(vec[18].value, 1);
    EXPECT_EQ(vec[19].value, 0);
    EXPECT_EQ(vec[20].value, 0);
    EXPECT_EQ(vec[21].value, 0);
    EXPECT_EQ(vec[22].value, 0);
    EXPECT_EQ(vec[23].value, 0);
    EXPECT_EQ(vec[24].value, 0);
    EXPECT_EQ(vec[25].value, 0);
    EXPECT_EQ(vec[26].value, 0);
    EXPECT_EQ(vec[27].value, 0);
    EXPECT_EQ(vec[28].value, 0);
    EXPECT_EQ(vec[29].value, 0);
    
    EXPECT_EQ(vec[0].type,  s21::ExpressionTypes::SQRT);
    EXPECT_EQ(vec[1].type,  s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[2].type,  s21::ExpressionTypes::SIN);
    EXPECT_EQ(vec[3].type,  s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[4].type,  s21::ExpressionTypes::COS);
    EXPECT_EQ(vec[5].type,  s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[6].type,  s21::ExpressionTypes::TAN);
    EXPECT_EQ(vec[7].type,  s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[8].type,  s21::ExpressionTypes::ACOS);
    EXPECT_EQ(vec[9].type,  s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[10].type, s21::ExpressionTypes::ASIN);
    EXPECT_EQ(vec[11].type, s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[12].type, s21::ExpressionTypes::ATAN);
    EXPECT_EQ(vec[13].type, s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[14].type, s21::ExpressionTypes::LN);
    EXPECT_EQ(vec[15].type, s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[16].type, s21::ExpressionTypes::LOG);
    EXPECT_EQ(vec[17].type, s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[18].type, s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[19].type, s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[20].type, s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[21].type, s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[22].type, s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[23].type, s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[24].type, s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[25].type, s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[26].type, s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[27].type, s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[28].type, s21::ExpressionTypes::PLUS);
    EXPECT_EQ(vec[29].type, s21::ExpressionTypes::NUMBER);

    EXPECT_EQ(vec[0].priority,   4);
    EXPECT_EQ(vec[1].priority,  -1);
    EXPECT_EQ(vec[2].priority,   4);
    EXPECT_EQ(vec[3].priority,  -1);
    EXPECT_EQ(vec[4].priority,   4);
    EXPECT_EQ(vec[5].priority,  -1);
    EXPECT_EQ(vec[6].priority,   4);
    EXPECT_EQ(vec[7].priority,  -1);
    EXPECT_EQ(vec[8].priority,   4);
    EXPECT_EQ(vec[9].priority,  -1);
    EXPECT_EQ(vec[10].priority,  4);
    EXPECT_EQ(vec[11].priority, -1);
    EXPECT_EQ(vec[12].priority,  4);
    EXPECT_EQ(vec[13].priority, -1);
    EXPECT_EQ(vec[14].priority,  4);
    EXPECT_EQ(vec[15].priority, -1);
    EXPECT_EQ(vec[16].priority,  4);
    EXPECT_EQ(vec[17].priority, -1);
    EXPECT_EQ(vec[18].priority,  0);
    EXPECT_EQ(vec[19].priority, -1);
    EXPECT_EQ(vec[20].priority, -1);
    EXPECT_EQ(vec[21].priority, -1);
    EXPECT_EQ(vec[22].priority, -1);
    EXPECT_EQ(vec[23].priority, -1);
    EXPECT_EQ(vec[24].priority, -1);
    EXPECT_EQ(vec[25].priority, -1);
    EXPECT_EQ(vec[26].priority, -1);
    EXPECT_EQ(vec[27].priority, -1);
    EXPECT_EQ(vec[28].priority,  1);
    EXPECT_EQ(vec[29].priority,  0);

    EXPECT_EQ(vec[0].is_function,  true);
    EXPECT_EQ(vec[1].is_function,  false);
    EXPECT_EQ(vec[2].is_function,  true);
    EXPECT_EQ(vec[3].is_function,  false);
    EXPECT_EQ(vec[4].is_function,  true);
    EXPECT_EQ(vec[5].is_function,  false);
    EXPECT_EQ(vec[6].is_function,  true);
    EXPECT_EQ(vec[7].is_function,  false);
    EXPECT_EQ(vec[8].is_function,  true);
    EXPECT_EQ(vec[9].is_function,  false);
    EXPECT_EQ(vec[10].is_function, true);
    EXPECT_EQ(vec[11].is_function, false);
    EXPECT_EQ(vec[12].is_function, true);
    EXPECT_EQ(vec[13].is_function, false);
    EXPECT_EQ(vec[14].is_function, true);
    EXPECT_EQ(vec[15].is_function, false);
    EXPECT_EQ(vec[16].is_function, true);
    EXPECT_EQ(vec[17].is_function, false);
    EXPECT_EQ(vec[18].is_function, false);
    EXPECT_EQ(vec[19].is_function, false);
    EXPECT_EQ(vec[20].is_function, false);
    EXPECT_EQ(vec[21].is_function, false);
    EXPECT_EQ(vec[22].is_function, false);
    EXPECT_EQ(vec[23].is_function, false);
    EXPECT_EQ(vec[24].is_function, false);
    EXPECT_EQ(vec[25].is_function, false);
    EXPECT_EQ(vec[26].is_function, false);
    EXPECT_EQ(vec[27].is_function, false);
    EXPECT_EQ(vec[28].is_function, false);
    EXPECT_EQ(vec[29].is_function, false);

    EXPECT_EQ(vec[0].is_operator,  false);
    EXPECT_EQ(vec[1].is_operator,  false);
    EXPECT_EQ(vec[2].is_operator,  false);
    EXPECT_EQ(vec[3].is_operator,  false);
    EXPECT_EQ(vec[4].is_operator,  false);
    EXPECT_EQ(vec[5].is_operator,  false);
    EXPECT_EQ(vec[6].is_operator,  false);
    EXPECT_EQ(vec[7].is_operator,  false);
    EXPECT_EQ(vec[8].is_operator,  false);
    EXPECT_EQ(vec[9].is_operator,  false);
    EXPECT_EQ(vec[10].is_operator, false);
    EXPECT_EQ(vec[11].is_operator, false);
    EXPECT_EQ(vec[12].is_operator, false);
    EXPECT_EQ(vec[13].is_operator, false);
    EXPECT_EQ(vec[14].is_operator, false);
    EXPECT_EQ(vec[15].is_operator, false);
    EXPECT_EQ(vec[16].is_operator, false);
    EXPECT_EQ(vec[17].is_operator, false);
    EXPECT_EQ(vec[18].is_operator, false);
    EXPECT_EQ(vec[19].is_operator, false);
    EXPECT_EQ(vec[20].is_operator, false);
    EXPECT_EQ(vec[21].is_operator, false);
    EXPECT_EQ(vec[22].is_operator, false);
    EXPECT_EQ(vec[23].is_operator, false);
    EXPECT_EQ(vec[24].is_operator, false);
    EXPECT_EQ(vec[25].is_operator, false);
    EXPECT_EQ(vec[26].is_operator, false);
    EXPECT_EQ(vec[27].is_operator, false);
    EXPECT_EQ(vec[28].is_operator, true);
    EXPECT_EQ(vec[29].is_operator, false);

    double (*fnc)(double) = reinterpret_cast<double (*)(double)>(vec[0].function);
    EXPECT_EQ(fnc(vec[18].value), std::sqrt(1));

    fnc = reinterpret_cast<double (*)(double)>(vec[2].function);    
    EXPECT_EQ(fnc(vec[18].value), std::sin(1));

    fnc = reinterpret_cast<double (*)(double)>(vec[4].function);    
    EXPECT_EQ(fnc(vec[18].value), std::cos(1));

    fnc = reinterpret_cast<double (*)(double)>(vec[6].function);    
    EXPECT_EQ(fnc(vec[18].value), std::tan(1));

    fnc = reinterpret_cast<double (*)(double)>(vec[8].function);    
    EXPECT_EQ(fnc(vec[18].value), std::acos(1));

    fnc = reinterpret_cast<double (*)(double)>(vec[10].function);    
    EXPECT_EQ(fnc(vec[18].value), std::asin(1));

    fnc = reinterpret_cast<double (*)(double)>(vec[12].function);    
    EXPECT_EQ(fnc(vec[18].value), std::atan(1));
    
    fnc = reinterpret_cast<double (*)(double)>(vec[14].function);    
    EXPECT_EQ(fnc(vec[18].value), std::log(1));

    fnc = reinterpret_cast<double (*)(double)>(vec[16].function);    
    EXPECT_EQ(fnc(vec[18].value), std::log10(1));

    double (*f)(double, double) = reinterpret_cast<double (*)(double, double)>(vec[28].function);    
    EXPECT_EQ(f(vec[18].value, vec[29].value), 1 + 0);
}

TEST_F(ExpressionParserTest, Unary) {
    auto stack = m_parser->parse("+(-2)");
    auto vec = stackToVector(stack);

    ASSERT_EQ(vec.size(), 9);

    EXPECT_EQ(vec[0].value,  0);
    EXPECT_EQ(vec[1].value,  0);
    EXPECT_EQ(vec[2].value,  0);
    EXPECT_EQ(vec[3].value,  0);
    EXPECT_EQ(vec[4].value,  0);
    EXPECT_EQ(vec[5].value,  2);
    EXPECT_EQ(vec[6].value,  0);
    EXPECT_EQ(vec[7].value,  0);
    EXPECT_EQ(vec[8].value,  0);

    EXPECT_EQ(vec[0].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[1].type,  s21::ExpressionTypes::PLUS);
    EXPECT_EQ(vec[2].type,  s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[3].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[4].type,  s21::ExpressionTypes::MINUS);
    EXPECT_EQ(vec[5].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[6].type,  s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[7].type,  s21::ExpressionTypes::PLUS);
    EXPECT_EQ(vec[8].type,  s21::ExpressionTypes::NUMBER);
    
    EXPECT_EQ(vec[0].priority,  0);
    EXPECT_EQ(vec[1].priority,  1);
    EXPECT_EQ(vec[2].priority, -1);
    EXPECT_EQ(vec[3].priority,  0);
    EXPECT_EQ(vec[4].priority,  1);
    EXPECT_EQ(vec[5].priority,  0);
    EXPECT_EQ(vec[6].priority, -1);
    EXPECT_EQ(vec[7].priority,  1);
    EXPECT_EQ(vec[8].priority,  0);

    EXPECT_EQ(vec[0].is_function,  false);
    EXPECT_EQ(vec[1].is_function,  false);
    EXPECT_EQ(vec[2].is_function,  false);
    EXPECT_EQ(vec[3].is_function,  false);
    EXPECT_EQ(vec[4].is_function,  false);
    EXPECT_EQ(vec[5].is_function,  false);
    EXPECT_EQ(vec[6].is_function,  false);
    EXPECT_EQ(vec[7].is_function,  false);
    EXPECT_EQ(vec[8].is_function,  false);

    EXPECT_EQ(vec[0].is_operator,  false);
    EXPECT_EQ(vec[1].is_operator,  true);
    EXPECT_EQ(vec[2].is_operator,  false);
    EXPECT_EQ(vec[3].is_operator,  false);
    EXPECT_EQ(vec[4].is_operator,  true);
    EXPECT_EQ(vec[5].is_operator,  false);
    EXPECT_EQ(vec[6].is_operator,  false);
    EXPECT_EQ(vec[7].is_operator,  true);
    EXPECT_EQ(vec[8].is_operator,  false);
}

TEST_F(ExpressionParserTest, SilenceMultiply) {
    auto stack = m_parser->parse("2cos(1)");
    auto vec = stackToVector(stack);

    ASSERT_EQ(vec.size(), 8);

    EXPECT_EQ(vec[0].value,  2);
    EXPECT_EQ(vec[1].value,  0);
    EXPECT_EQ(vec[2].value,  0);
    EXPECT_EQ(vec[3].value,  0);
    EXPECT_EQ(vec[4].value,  1);
    EXPECT_EQ(vec[5].value,  0);
    EXPECT_EQ(vec[6].value,  0);
    EXPECT_EQ(vec[7].value,  0);

    EXPECT_EQ(vec[0].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[1].type,  s21::ExpressionTypes::MULT);
    EXPECT_EQ(vec[2].type,  s21::ExpressionTypes::COS);
    EXPECT_EQ(vec[3].type,  s21::ExpressionTypes::OPEN_BRACKET);
    EXPECT_EQ(vec[4].type,  s21::ExpressionTypes::NUMBER);
    EXPECT_EQ(vec[5].type,  s21::ExpressionTypes::CLOSED_BRACKET);
    EXPECT_EQ(vec[6].type,  s21::ExpressionTypes::PLUS);
    EXPECT_EQ(vec[7].type,  s21::ExpressionTypes::NUMBER);
    
    EXPECT_EQ(vec[0].priority,  0);
    EXPECT_EQ(vec[1].priority,  2);
    EXPECT_EQ(vec[2].priority,  4);
    EXPECT_EQ(vec[3].priority, -1);
    EXPECT_EQ(vec[4].priority,  0);
    EXPECT_EQ(vec[5].priority, -1);
    EXPECT_EQ(vec[6].priority,  1);
    EXPECT_EQ(vec[7].priority,  0);

    EXPECT_EQ(vec[0].is_function,  false);
    EXPECT_EQ(vec[1].is_function,  false);
    EXPECT_EQ(vec[2].is_function,  true );
    EXPECT_EQ(vec[3].is_function,  false);
    EXPECT_EQ(vec[4].is_function,  false);
    EXPECT_EQ(vec[5].is_function,  false);
    EXPECT_EQ(vec[6].is_function,  false);
    EXPECT_EQ(vec[7].is_function,  false);

    EXPECT_EQ(vec[0].is_operator,  false);
    EXPECT_EQ(vec[1].is_operator,  true);
    EXPECT_EQ(vec[2].is_operator,  false);
    EXPECT_EQ(vec[3].is_operator,  false);
    EXPECT_EQ(vec[4].is_operator,  false);
    EXPECT_EQ(vec[5].is_operator,  false);
    EXPECT_EQ(vec[6].is_operator,  true);
    EXPECT_EQ(vec[7].is_operator,  false);
}

TEST_F(ExpressionParserTest, NoErrors) {
    EXPECT_NO_THROW(m_parser->parse("+2-2"));
    EXPECT_NO_THROW(m_parser->parse("+(-2)"));
}

TEST_F(ExpressionParserTest, Errors) {

    EXPECT_THROW(m_parser->parse("()sqrt(()))"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("sqrt2"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("sin"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("(3-1)())("), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("            "), std::invalid_argument);
    EXPECT_THROW(m_parser->parse(""), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("tantan"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("ln(log)"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("atak"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("acot"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("seen"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("2---+233"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("sin(1) * cos)("), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("__trash/"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("2--2**12*//4mod*31"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("2-2)"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("2...5132 - 1.24.12"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("siren"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("thanos"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("call me"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("m"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("s"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("a"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("apple"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("my man"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("xor is ^"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("2*^3"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("33^mod^33"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("11^/22/^11"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("sqrt(15)253"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("sqrt()"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("2*mod"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("cos+2"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("cos2"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("+2-"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("2mod+mod2"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("3+*5"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("sqrt(9)+7+"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("sin(45))"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("(4/2"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("log(10, 100))"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("3sin+sin3"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("log"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("sqrt+sqrt"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("tan()"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("log(10"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("1+2+3+"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("3+*5"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("(4+7)/"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("2*(6-3))"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("((8*2)-6/3) +"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("3^2+"), std::invalid_argument);
    EXPECT_THROW(m_parser->parse("--++3^-^2+"), std::invalid_argument);
}
