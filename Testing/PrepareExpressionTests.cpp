#include <gtest/gtest.h>
#include "../CalculationAlgorithm/CalculationModel.h"

TEST(PrepareExpression, Dots) {
    s21::CalculationModel model("12.4532 - 13,23 * 12,3 + 1.2");
    model.prepareExpression("");

    EXPECT_EQ(model.getExpression(), "12.4532-13.23*12.3+1.2");
}

TEST(PrepareExpression, E) {
    s21::CalculationModel model("12.4e10 - 13e-2 * 12e+4");
    model.prepareExpression("");

    EXPECT_EQ(model.getExpression(), "12.4*10^10-13/10^2*12*10^4");
}

TEST(PrepareExpression, X) {
    s21::CalculationModel model("SIN(x) + x * 1ex + 2x * XeX");
    model.prepareExpression("ACOS(10)");

    EXPECT_EQ(model.getExpression(), "sin(acos(10))+acos(10)*1*10^acos(10)+2*acos(10)*acos(10)*10^acos(10)");
}

TEST(PrepareExpression, Combine) {
    s21::CalculationModel model("SIN(x) * (1e2 + 21 - 1,324e-4) ^ (4e+2 * x)");
    model.prepareExpression("acos(12) + cos(3)");

    EXPECT_EQ(model.getExpression(), "sin(acos(12)+cos(3))*(1*10^2+21-1.324/10^4)^(4*10^2*acos(12)+cos(3))");
}

TEST(PrepareExpression, XwithX) {
    s21::CalculationModel model("SIN(x) + x * 1ex + 2x * XeX");
    EXPECT_THROW(model.prepareExpression("ACOS(x)"), std::invalid_argument);
}
