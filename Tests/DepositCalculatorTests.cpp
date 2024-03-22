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

TEST_F(DepositCalculatorTest, BasicDeposit) {
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

    std::tm term_begin;
    term_begin.tm_year = 2024 - 1900;
    term_begin.tm_mon = 3 - 1;
    term_begin.tm_mday = 22;
    term_begin.tm_hour = 0;
    term_begin.tm_min = 0;
    term_begin.tm_sec = 0;

    auto result = m_deposit->calculate(params, term_begin);

    EXPECT_NEAR(result.income, 1'425.57, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 201'425.57, 2);
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

    std::tm term_begin;
    term_begin.tm_year = 2024 - 1900;
    term_begin.tm_mon = 3 - 1;
    term_begin.tm_mday = 18;
    term_begin.tm_hour = 0;
    term_begin.tm_min = 0;
    term_begin.tm_sec = 0;

    auto result = m_deposit->calculate(params, term_begin);

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

    std::tm term_begin;
    term_begin.tm_year = 2024 - 1900;
    term_begin.tm_mon = 3 - 1;
    term_begin.tm_mday = 18;
    term_begin.tm_hour = 0;
    term_begin.tm_min = 0;
    term_begin.tm_sec = 0;


    auto result = m_deposit->calculate(params, term_begin);

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

    std::tm term_begin;
    term_begin.tm_year = 2024 - 1900;
    term_begin.tm_mon = 3 - 1;
    term_begin.tm_mday = 18;
    term_begin.tm_hour = 0;
    term_begin.tm_min = 0;
    term_begin.tm_sec = 0;


    auto result = m_deposit->calculate(params, term_begin);

    EXPECT_NEAR(result.income, 62'519.16, 2);
    EXPECT_NEAR(result.tax_amount, 0, 2);
    EXPECT_NEAR(result.total_amount, 262'519.16, 2);
}
