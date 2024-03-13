#include <gtest/gtest.h>

#include "../CalculationAlgorithm/CalculationAlgorithmWithXWrapper.h"

#include "../CalculationAlgorithm/CalculationAlgorithm.h"

#include "../CalculationAlgorithm/ExpressionPreparator.h"
#include "../CalculationAlgorithm/Handlers/NumberHandler.h"
#include "../CalculationAlgorithm/Handlers/BracketsHandler.h"
#include "../CalculationAlgorithm/Handlers/OperatorsHandler.h"
#include "../CalculationAlgorithm/Handlers/FunctionsHandler.h"

class CalculationAlgorithmWithXWrapperTest : public ::testing::Test {
protected:
	void SetUp() override {
        s21::ExpressionHandler* handler = new s21::ExpressionHandler();
        s21::NumberHandler* numberHandler = new s21::NumberHandler();
        s21::BracketsHandler* bracketsHandler = new s21::BracketsHandler();
        s21::OperatorsHandler* operatorsHandler = new s21::OperatorsHandler();
        s21::FunctionsHandler* functionsHandler = new s21::FunctionsHandler();
        handler->setNext(numberHandler)->setNext(bracketsHandler)->setNext(operatorsHandler)->setNext(functionsHandler);

        s21::ExpressionParser* parser = new s21::ExpressionParser(handler);
        s21::Calculation* calculation = new s21::Calculation();

        s21::ExpressionPreparator* preparator = new s21::ExpressionPreparator();
        s21::CalculationAlgorithm* algorithm = new s21::CalculationAlgorithm(parser, calculation);

        m_xalgorithm = new s21::CalculationAlgorithmWithXWrapper(algorithm, preparator);
	}

	void TearDown() override {
        delete m_xalgorithm;
	}

    s21::CalculationAlgorithmWithXWrapper* m_xalgorithm;
};

TEST_F(CalculationAlgorithmWithXWrapperTest, SilentMultiplyWithX) {
    std::string exp = "2x(2x+1) + 4";
    
    double expected = 49.989999999999995;
    double actual = m_xalgorithm->calculate(exp, "3.15");

    EXPECT_DOUBLE_EQ(expected, actual);
}
