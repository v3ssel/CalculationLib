#include <gtest/gtest.h>
#include "../CalculationAlgorithm/ExpressionPreparator.h"

TEST(ExpressionPreparatorTests, Dots) {
    s21::ExpressionPreparator preparator;

    std::string expected = "12.4532-13.23*12.3+1.2";
    std::string actual = preparator.prepare("12.4532 - 13,23 * 12,3 + 1.2", "");

    EXPECT_EQ(actual, expected);
}

TEST(ExpressionPreparatorTests, E) {
    s21::ExpressionPreparator preparator;
    
    std::string expected = "12.4*10^10-13/10^2*12*10^4";
    std::string actual = preparator.prepare("12.4e10 - 13e-2 * 12e+4", "");

    EXPECT_EQ(actual, expected);
}

TEST(ExpressionPreparatorTests, X) {
    s21::ExpressionPreparator preparator;

    std::string expected = "sin(acos(10))+acos(10)*1*10^acos(10)+2*acos(10)*acos(10)*10^acos(10)";
    std::string actual = preparator.prepare("SIN(x) + x * 1ex + 2x * XeX", "ACOS(10)");

    EXPECT_EQ(actual, expected);
}

TEST(ExpressionPreparatorTests, Combine) {
    s21::ExpressionPreparator preparator;
    
    std::string expected = "sin(acos(12)+cos(3))*(1*10^2+21-1.324/10^4)^(4*10^2*acos(12)+cos(3))";
    std::string actual = preparator.prepare("SIN(x) * (1e2 + 21 - 1,324e-4) ^ (4e+2 * x)", "acos(12) + cos(3)");

    EXPECT_EQ(actual, expected);
}

TEST(ExpressionPreparatorTests, XwithX) {
    s21::ExpressionPreparator preparator;
    EXPECT_THROW(preparator.prepare("SIN(x) + x * 1ex + 2x * XeX", "ACOS(x)"), std::invalid_argument);
}
