/*
 * LoanData.cpp
 *
 *  Created on: Jan 5, 2017
 *      Author: Jack
 */
#include "LoanData.h"
#include <iostream>
#include <sstream>
#include <exception>

  LoanData::LoanData(const double principalAmount, const double interestRate,
      const PaymentPeriod paymentPeriod, const LoanType loanType,
      const double fixedPayment, const double paymentPercent,
      const double minimumPayment, const int numberOfPayments,
      const time_t firstPayDate):
        principalAmt(principalAmount), intRate(interestRate),
        payPeriod(paymentPeriod), type(loanType),
        fixedPmt(fixedPayment), paymentPct(paymentPercent),
        minPayment(minimumPayment), numPayments(numberOfPayments),
        firstPayDt(firstPayDate)
  {
    checkAllParameters(); // throws if validation fails
  } // LoanData ctor

  void LoanData::checkAllParameters(void) {
    bool result = true ; // assume all is OK
    std::ostringstream buf ;
    if (principalAmount() <= 0 )  {
      result = false ;
      buf << "--The principal amount must be greater than zero, it cannot be "
        << principalAmount() << std::endl ;
    } // if principal amount is <= 0 (TRUE branch)
    if (interestRate() <= 0 ) {
      result = false ;
      buf << "--The interest rate must be greater than zero, it cannot be "
        << interestRate() << std::endl ;
    } // if interest rate is <= 0 (TRUE branch)
    if (paymentPeriod() < LoanData::BiWeeklyPeriod
        || paymentPeriod() > LoanData::AnnualPeriod ) {
      result = false ;
      buf << "--You must select a payment period\n" ;
    } // if payment period is invalid (TRUE branch)
    if (LoanData::InstallmentLoan == loanType() ) {
      if (numberOfPayments() <= 0 ) {
        result = false ;
        buf << "--An installment loan must have a number of payments greater than zero, it cannot be "
          << numberOfPayments() << std::endl ;
      } // if number of payments is <= 0 (TRUE branch)
    } // if loan type is MortgageLoan (TRUE branch)
    else if ( LoanData::RevolvingChargeLoan == loanType()) {
      result = false ;
      buf << "--You must choose a payment type\n" ;
    } // if loan type is RevolvingChargeLoan (TRUE branch)
    else if (LoanData::FixedPaymentLoan == loanType()) {
      if (fixedPayment() <= 0 ) {
        result = false ;
        buf << "--A fixed payment loan must have a fixed payment greater than zero, it cannot be "
          << fixedPayment() << std::endl ;
      } // if fixed payment is <= 0 (TRUE branch)
    } // if loan type is FixedPaymentLoan (TRUE branch)
    else if (LoanData::PercentPaymentLoan == loanType() ) {
      if (paymentPercent() <= 0 ) {
        result = false ;
        buf << "--A percent payment loan must have a percent payment greater than zero, it cannot be "
          << paymentPercent() << std::endl ;
      } // if percent payments is <= 0 (TRUE branch)
    } // if loan type is PercentPaymentLoan (TRUE branch)
    else {
      result = false ;
      buf << "--You must choose a loan type\n" ;
    } // not a recognized loan type

    if (!result) {
      throw std::invalid_argument(buf.str().c_str());
    } // if there was an error (TRUE branch)
  } // allParametersOK()
