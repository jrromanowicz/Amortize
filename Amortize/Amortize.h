#ifndef Amortize_h
#define Amortize_h

#include "PaymentData.h"
#include "LoanData.h"
#include "PaymentTableUI.h"
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

double interestRate(void) {return loan.interestRate() ; }
double principalAmount(void) {return loan.principalAmount() ; }
int    numberOfPayments(void) {return loan.numberOfPayments() ; }
double fixedPayment(void) {return loan.fixedPayment() ; }
double paymentPercent(void) {return loan.paymentPercent() ; }
double minimumPayment(void) {return loan.minimumPayment() ; }
int    paymentsPerYear(void) {return pmtsPerYear ; }
time_t firstPaymentDate(void) {return loan.firstPayDate() ; }
Fl_Window* paymentUI(void) {return (Fl_Window *)myUI;}

private:

LoanData& loan;
int pmtsPerYear;
PaymentTableUI * myUI;
char title[100];

PaymentData* makePayment(double bal, double intRate, double payment, int pymtNum);
double calcInstallmentPayment(void) ;
void amortizeFixedPayment(vector<PaymentData> &payments) ;
void amortizePercentPayment(vector<PaymentData> &payments) ;
void amortizeInstallmentLoan(vector<PaymentData> &payments) ;


} ; // class Amortize

#endif  // ifndef Amortize_h

