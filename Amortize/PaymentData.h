#ifndef PaymentData_h
#define PaymentData_h

#include <ctime>
#include <string>
#include <string.h>

using namespace std ;

/*
 * Immutable data bean for information about one payment on a loan
 */
class PaymentData {

	struct tm	payDate ;
	int  	paymentNumber ;
	double 	interestPaid ;
	double 	principalPaid ;
	double 	balanceLeft ;

public :
	double principal( void ) { return principalPaid ; }
	double interest( void ) { return interestPaid ; }
	double balance( void ) { return balanceLeft ; }
	int paymentNum( void ) { return paymentNumber ; }
	double totalPayment( void ) { return interestPaid + principalPaid ; }
	string * paymentDate( void ) {
		char date[11] ;
		strftime( date, 10, "%m/%d/%Y", &payDate ) ;
		return new string(date) ;
	} // paymentDate() as string

	PaymentData(double principal, double interest, double balance, int pmtNum,
			struct tm * date): paymentNumber(pmtNum), interestPaid(interest),
			   principalPaid(principal), balanceLeft(balance)  {
		if (NULL != date) memcpy(&payDate, date, sizeof(payDate)) ;
	} // ctor

} ; // PaymentData

#endif // ndef PaymentData_h

