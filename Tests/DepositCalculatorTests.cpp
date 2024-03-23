#include <gtest/gtest.h>

#include "../Extensions/Deposit/DepositCalculator.h"

class DepositCalculatorTest : public ::testing::Test {
protected:
	void SetUp() override {
        m_deposit = new s21::DepositCalculator();
	}

	void TearDown() override {
        delete m_deposit;
	}

    s21::DepositCalculator* m_deposit;
};

TEST_F(DepositCalculatorTest, CapitalizeDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 20;
    params.tax_rate = 15.4;
    params.periodicity = 1;
    params.capitalization = true;

    params.count_of_replenishments = 0;

    params.rate_type = 0;
    params.rates = new double(13);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 22;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 1'425.57, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 201'425.57, 2);
}

TEST_F(DepositCalculatorTest, NoCapitalizeDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 20;
    params.tax_rate = 15.4;
    params.periodicity = 1;
    params.capitalization = false;

    params.count_of_replenishments = 0;

    params.rate_type = 0;
    params.rates = new double(13);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 22;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 1'420.8, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 200'000, 2);
}

TEST_F(DepositCalculatorTest, YearIntervalDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 412;
    params.tax_rate = 15.4;
    params.periodicity = 1;
    params.capitalization = true;

    params.count_of_replenishments = 0;

    params.rate_type = 0;
    params.rates = new double(13);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 18;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 31'539.58, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 231'539.58, 2);
}

TEST_F(DepositCalculatorTest, RateDependsOnAmountDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 400;
    params.tax_rate = 15.4;
    params.periodicity = 1;
    params.capitalization = true;

    params.count_of_replenishments = 0;

    params.rate_type = 1;
    params.rates = new double[4] { 14.8, 39.8, 20.5, 24.21 };
    params.rate_dependence_values = new double[4] { 200'000, 210'000, 230'000, 250'000 };
    params.count_of_rates = 4;

    params.term_begin_day = 18;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 57'924.87, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 257'924.87, 2);
}

TEST_F(DepositCalculatorTest, RateDependsOnTermDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 400;
    params.tax_rate = 15.4;
    params.periodicity = 1;
    params.capitalization = true;

    params.count_of_replenishments = 0;

    params.rate_type = 2;
    params.rates = new double[4] { 14.8, 39.8, 20.5, 24.21 };
    params.rate_dependence_values = new double[4] { 20, 60, 140, 172 };
    params.count_of_rates = 4;

    params.term_begin_day = 18;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 62'519.16, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 262'519.16, 2);
}

TEST_F(DepositCalculatorTest, ReplenishmentsDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 100;
    params.tax_rate = 15.4;
    params.periodicity = 1;
    params.capitalization = true;

    params.days_of_replenishments = new int[9] { 2, 10, 24, 33, 38, 39, 51, 85, 94 };
    params.amount_of_replenishments = new double[9] { 2000, -15'000, -4000, -1000, -2000, 15000, -5000, -4000, 10'000 };
    params.count_of_replenishments = 9;

    params.rate_type = 0;
    params.rates = new double(7.7);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 18;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.days_of_replenishments;
    delete params.amount_of_replenishments;
    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 4'043.72, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 200'043.72, 2);
}

TEST_F(DepositCalculatorTest, ComplexDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 200;
    params.tax_rate = 15.4;
    params.periodicity = 1;
    params.capitalization = true;

    params.days_of_replenishments = new int[9] { 2, 10, 24, 33, 38, 39, 51, 85, 94 };
    params.amount_of_replenishments = new double[9] { 2000, -15'000, -4000, -1000, -2000, 15000, -5000, -4000, 10'000 };
    params.count_of_replenishments = 9;

    params.rate_type = 2;
    params.rates = new double[4] { 14.8, 39.8, 20.5, 24.21 };
    params.rate_dependence_values = new double[4] { 20, 60, 140, 172 };
    params.count_of_rates = 4;

    params.term_begin_day = 18;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.days_of_replenishments;
    delete params.amount_of_replenishments;
    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 28'922.8, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 224'922.8, 2);
}

TEST_F(DepositCalculatorTest, WeekPeriodDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 20;
    params.tax_rate = 15.4;
    params.periodicity = 7;
    params.capitalization = true;

    params.count_of_replenishments = 0;

    params.rate_type = 0;
    params.rates = new double(13);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 22;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 1'424.12, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 201'424.12, 2);
}

TEST_F(DepositCalculatorTest, MonthPeriodDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 72;
    params.tax_rate = 15.4;
    params.periodicity = 30;
    params.capitalization = true;

    params.count_of_replenishments = 0;

    params.rate_type = 0;
    params.rates = new double(13);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 22;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 5'155.24, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 205'155.24, 2);
}

TEST_F(DepositCalculatorTest, QuarterPeriodDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 505;
    params.tax_rate = 15.4;
    params.periodicity = 365 / 4;
    params.capitalization = true;

    params.count_of_replenishments = 0;

    params.rate_type = 0;
    params.rates = new double(13);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 22;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 38'692.2, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 238'692.2, 2);
}

TEST_F(DepositCalculatorTest, YearPeriodDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 600;
    params.tax_rate = 15.4;
    params.periodicity = 365;
    params.capitalization = true;

    params.count_of_replenishments = 0;

    params.rate_type = 0;
    params.rates = new double(13);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 22;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 44'855.99, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 244'855.99, 2);
}

TEST_F(DepositCalculatorTest, EndPeriodDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 600;
    params.tax_rate = 15.4;
    params.periodicity = 600;
    params.capitalization = false;

    params.count_of_replenishments = 0;

    params.rate_type = 0;
    params.rates = new double(13);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 22;
    params.term_begin_month = 3;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 42'684.45, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 200'000, 2);
}

TEST_F(DepositCalculatorTest, TaxDeposit) {
    s21::DepositParams params;

    params.start_amount = 200'000;
    params.term_in_days = 350;
    params.tax_rate = 16;
    params.periodicity = 1;
    params.capitalization = true;

    params.count_of_replenishments = 0;

    params.rate_type = 0;
    params.rates = new double(70);
    params.rate_dependence_values = new double(0);
    params.count_of_rates = 1;

    params.term_begin_day = 1;
    params.term_begin_month = 1;
    params.term_begin_year = 2024;

    auto result = m_deposit->calculate(params);

    delete params.rates;
    delete params.rate_dependence_values;

    EXPECT_NEAR(result.income, 190'363.09, 2);
    EXPECT_NEAR(result.tax_amount, 3'947.2, 2);
    EXPECT_NEAR(result.total_amount, 390'363.09, 2);
}
