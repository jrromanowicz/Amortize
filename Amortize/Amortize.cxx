#include "Amortize.h"
#include <sstream>
#include <cmath>
#include <string.h>
#include <cstdio>
#include <FL/fl_ask.h>
#include <locale>

string ftoa(double value) {
  ostringstream buf ;
  buf.setf(ios::fixed) ;
  buf.precision(2) ;
  buf << value ;
  return buf.str() ;
}

string itoa(int value) {
  ostringstream buf ;
  buf << value ;
  return buf.str() ;
}

Amortize::Amortize(LoanData& loan_) : loan(loan_)
{
  switch (loan.paymentPeriod()) {
    case LoanData::BiWeeklyPeriod: pmtsPerYear = 26 ; break ;
    case LoanData::SemiMonthlyPeriod: pmtsPerYear = 24 ; break ;
    case LoanData::MonthlyPeriod: pmtsPerYear = 12 ; break ;
    case LoanData::QuarterlyPeriod: pmtsPerYear = 4 ; break ;
    case LoanData::SemiAnnualPeriod: pmtsPerYear = 2 ; break ;
    case LoanData::AnnualPeriod: pmtsPerYear = 1 ; break ;
    default: throw domain_error("Invalid payment period") ;
  } // switch on payment period
  loan.checkAllParameters(); // will throw exception if any parameter is invalid

  // got good parameters, create the amortization data
  switch (loan.loanType()) {
    case LoanData::InstallmentLoan:
      amortizeInstallmentLoan() ;
      break ;
    case LoanData::FixedPaymentLoan:
      amortizeFixedPayment() ;
      break ;
    case LoanData::PercentPaymentLoan:
      amortizePercentPayment() ;
      break ;
    default:
      throw domain_error("Unknown loan type") ;
      break ;
  } // switch on loan type
} // ctor

#include <cmath>
PaymentData * Amortize::makePayment(double balance, double intRate,
    double payment, int pymtNum) {
	double interest = balance * intRate ; // interest paid
	interest = round(interest * 100.) / 100.; // round to nearest penny
	double principal = payment - interest ; // principal paid
	if (principal <= 0) {
	  const char * msg = "The payment amount (%.2f) must be greater\nthan the first period interest (%.2f)";
	  fl_alert(msg, payment, interest);
	  throw logic_error("Fixed payment is too small");
	} // if principal paid is not positive (TRUE branch)
	if (principal > balance) { // recalc if payment's bigger than what's owed
		payment = balance + interest ;
		principal = payment - interest ;
		balance = 0 ;
	} // if overpaid (TRUE branch)
	else balance -= principal ;
	if (balance < 1.00) {   // avoid an extra payment for small amt
	  payment += balance;
	  principal += balance;
	  balance = 0 ;
	}

	return new PaymentData(principal, interest, balance, pymtNum, NULL) ;
} // makePayment()

void Amortize::amortizeFixedPayment() {
  if (interestRate() && pmtsPerYear && principalAmount() && fixedPayment()) {
    double bal = principalAmount() ;
    double rate = (interestRate() / pmtsPerYear) / 100 ;
    int pymtNum = 0 ;

    while (bal > 0) {
      PaymentData * pd = makePayment( bal, rate, fixedPayment(), ++pymtNum ) ;
      payData.push_back( *pd ) ;
      bal = pd->balance() ;
    }  // while there's a balance left
  } // if all needed values are set (TRUE branch)
} // amortizeFixedPayment()

void Amortize::amortizePercentPayment() {
  if (interestRate() && pmtsPerYear && principalAmount() && paymentPercent() && minimumPayment()) {
    double bal = principalAmount() ;
    double rate = (interestRate() / pmtsPerYear) / 100 ;
    int pymtNum = 0 ;

    while (bal > 0 ) {
      double payment = max(bal * paymentPercent() / 100, minimumPayment()) ;
      payment = round(payment * 100.) / 100.; // round to nearest penny
      PaymentData * pd = makePayment( bal, rate, payment, ++pymtNum ) ;
      payData.push_back( *pd ) ;
      bal = pd->balance() ;
	  }  // while there's a balance left
  } // if all needed values are set (TRUE branch)
} // amortizePercentPayment()

void Amortize::amortizeInstallmentLoan() {
	if (interestRate() && pmtsPerYear && principalAmount() && numberOfPayments()) {
		double payment = round(calcInstallmentPayment() * 100.) / 100. ; // round to nearest penny
	  double bal = principalAmount() ;
	  double rate = (interestRate() / pmtsPerYear) / 100 ;
		int pymtNum = 0 ;

		while (bal > 0 ) {
			PaymentData * pd = makePayment( bal, rate, payment, ++pymtNum ) ;
			payData.push_back( *pd ) ;
			bal = pd->balance() ;
	  	} // while there's a balance left
	} // if all fields have values (TRUE branch)
} // amortizeInstallmentLoan()

double Amortize::calcInstallmentPayment() {
  if (interestRate() && pmtsPerYear && principalAmount() && numberOfPayments()) {
		double rate = (interestRate() / pmtsPerYear) / 100 ;
		return principalAmount() * (rate / (1. - pow(1. + rate, - numberOfPayments()))) ;
	}  // if all the needed values are defined (TRUE branch)
	else return 0 ; // not ready to rumble
} // calcInstallmentPayment()


