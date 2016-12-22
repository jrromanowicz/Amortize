#ifndef Amortize_h
#define Amortize_h

#include "PaymentData.h"
#include <string>
#include <stdexcept>
#include <vector>

using namespace std ;

class Amortize {

public:

Amortize(void) {
  intRate = principalAmt = fixedPmt = paymentPct = minPayment = payments
      = pmtsPerYear = 0;
  firstPaymentDate();
  resultText = "";
};
virtual ~Amortize() {}

void amortizeFixedPayment(vector<PaymentData> &payments) ;
void amortizePercentPayment(vector<PaymentData> &payments) ;
void amortizeInstallmentLoan(vector<PaymentData> &payments) ;

void interestRate(float intRate) throw (out_of_range) ;
void principalAmount(float principalAmt) throw (out_of_range) ;
void numPayments(int payments) throw (out_of_range) ;
void fixedPayment(float fixedPmt) throw (out_of_range) ;
void paymentPercent(float paymentPct) throw (out_of_range) ;
void minimumPayment(float minPayment) throw (out_of_range) ;
void paymentsPerYear(int pmtsPerYear) throw (out_of_range) ;
void firstPaymentDate(struct tm * firstPayDate) ;

double interestRate(void) {return intRate ; }
double principalAmount(void) {return principalAmt ; }
int   numPayments(void) {return payments ; }
double fixedPayment(void) {return fixedPmt ; }
double paymentPercent(void) {return paymentPct ; }
double minimumPayment(void) {return minPayment ; }
int   paymentsPerYear(void) {return pmtsPerYear ; }
struct tm * firstPaymentDate(void) {return & firstPayDate ; }

private:

double intRate ;
double principalAmt ;
int    payments ;
double fixedPmt ;
double paymentPct ;
double minPayment ;
int    pmtsPerYear ;
struct tm firstPayDate ;
string resultText ;

PaymentData * makePayment(double bal, double intRate, double payment,
    int pymtNum) throw (out_of_range) ;
double calcInstallmentPayment(void) ;

} ; // class Amortize

#endif  // ifndef Amortize_h

