#ifndef Amortize_h
#define Amortize_h

#include "PaymentData.h"
#include "LoanData.h"
#include <string>
#include <stdexcept>
#include <vector>

using namespace std ;

/*
 * An class to calculate an amortization schedule and display it
 * in a grid in it's own window.
 */
class Amortize {

public:

Amortize(LoanData& loan);
virtual ~Amortize() { }

double interestRate(void) const {return loan.interestRate() ; }
double principalAmount(void) const {return loan.principalAmount() ; }
int    numberOfPayments(void) const {return loan.numberOfPayments() ; }
double fixedPayment(void) const {return loan.fixedPayment() ; }
double paymentPercent(void) const {return loan.paymentPercent() ; }
double minimumPayment(void) const {return loan.minimumPayment() ; }
int    paymentsPerYear(void) const {return pmtsPerYear ; }
time_t firstPaymentDate(void) const {return loan.firstPayDate() ; }
vector<PaymentData> &paymentData() {return payData;}

private:

LoanData& loan;
int pmtsPerYear;
vector<PaymentData> payData;

PaymentData* makePayment(double bal, double intRate, double payment, int pymtNum);
double calcInstallmentPayment(void) ;
void amortizeFixedPayment() ;
void amortizePercentPayment() ;
void amortizeInstallmentLoan() ;


} ; // class Amortize

#endif  // ifndef Amortize_h

