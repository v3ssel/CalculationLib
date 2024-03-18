#include <gtest/gtest.h>

#include "../Extensions/Credit/CreditMonthlyPaymentAnnuity.h"
#include "../Extensions/Credit/CreditMonthlyPaymentDifferentiated.h"

class CreditMonthlyPaymentTest : public ::testing::Test {
protected:
	void SetUp() override {
        m_annuity = new s21::CreditMonthlyPaymentAnnuity();
        m_differ = new s21::CreditMonthlyPaymentDifferentiated();
	}

	void TearDown() override {
        delete m_annuity;
        delete m_differ;
	}

    s21::CreditMonthlyPayment* m_annuity;
    s21::CreditMonthlyPayment* m_differ;
};

TEST_F(CreditMonthlyPaymentTest, Annuity) {
    double amount = 1500000;
    double percent = 22.3;
    int term = 33;

    auto result = m_annuity->calculate(amount, percent, term);

    EXPECT_FLOAT_EQ(result.monthly_payments[0],      61215.94);
    EXPECT_FLOAT_EQ(result.overpayment[term - 1],   520126.02);
    EXPECT_FLOAT_EQ(result.total_payout[term - 1], 2020126.02);
}


TEST_F(CreditMonthlyPaymentTest, Differ) {
    double amount = 1000000;
    double percent = 9.4;
    int term = 21;

    auto result = m_differ->calculate(amount, percent, term);

    EXPECT_FLOAT_EQ(result.monthly_payments[0],        55452.38);
    EXPECT_FLOAT_EQ(result.monthly_payments[term - 1], 47992.06);
    EXPECT_FLOAT_EQ(result.overpayment[term - 1],      86166.67);
    EXPECT_FLOAT_EQ(result.total_payout[term - 1],   1086166.67);
}
