/*
 * LoanData.h
 *
 *  Created on: Jan 3, 2017
 *      Author: Jack
 */
#ifndef LOANDATA_H_
#define LOANDATA_H_

#include <ctime>

/*
 * Immutable data bean for loan parameters
 */
class LoanData {
public:
  enum PaymentPeriod {InvalidPeriod = 0, BiWeeklyPeriod, SemiMonthlyPeriod,
    MonthlyPeriod, QuarterlyPeriod, SemiAnnualPeriod, AnnualPeriod} ;
  enum LoanType {InvalidLoan = 0, InstallmentLoan, RevolvingChargeLoan,
    FixedPaymentLoan, PercentPaymentLoan } ;

  LoanData(const double principalAmount, const double interestRate,
      const PaymentPeriod paymentPeriod, const LoanType loanType,
      const double fixedPayment, const double paymentPercent,
      const double minimumPayment, const int numberOfPayments,
      const time_t firstPayDate);

  virtual ~LoanData() {/* empty survey body */}

  void checkAllParameters(void);

  double principalAmount() const {
    return principalAmt;
  }
  double interestRate() const {
    return intRate;
  }
  PaymentPeriod paymentPeriod() const {
    return payPeriod;
  }
  LoanType loanType() const {
    return type;
  }
  double fixedPayment() const {
    return fixedPmt;
  }
  double paymentPercent() const {
    return paymentPct;
  }
  double minimumPayment() const {
    return minPayment;
  }
  int numberOfPayments() const {
    return numPayments;
  }
  const time_t firstPayDate() const {
    return firstPayDt;
  }

private:
  double principalAmt ;
  double intRate ;
  PaymentPeriod payPeriod;
  LoanType type;
  double fixedPmt ;
  double paymentPct ;
  double minPayment ;
  int numPayments;
  time_t firstPayDt ;

}; // LoanData class

#endif /* LOANDATA_H_ */
