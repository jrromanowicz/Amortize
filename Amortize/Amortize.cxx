#include "Amortize.h"
#include <sstream>
#include <cmath>
#include <string.h>

string ftoa(double _value) {
	ostringstream buf ;
	buf.setf(ios::fixed) ;
	buf.precision(2) ;
	buf << _value ;
	return buf.str() ;
}

string itoa(int _value) {
	ostringstream buf ;
	buf << _value ;
	return buf.str() ;
}

void Amortize::principalAmount(float _value) throw (out_of_range) {
	if (_value > 0) {
		principalAmt = _value ;
	}
	else {
		principalAmt = 0. ;
		throw out_of_range(string("Principal must be positive, not ") + ftoa(_value)) ;
	}
} // principal()

void Amortize::interestRate(float _value) throw (out_of_range) {
	if (_value > 0) {
		intRate = _value ;
	}
	else {
		intRate = 0. ;
		throw out_of_range(string("Interest rate must be positive, not ") + ftoa(_value)) ;
	}
} // interestRate()

void Amortize::numPayments(int _value) throw (out_of_range) {
	if (_value > 0) {
		payments = _value ;
	}
	else {
		payments = 0 ;
		throw out_of_range(string("Payments must be positive, not ") + itoa(_value)) ;
	}
} // numPayments()

void Amortize::fixedPayment(float _value) throw (out_of_range) {
	if (_value > 0) {
		fixedPmt = _value ;
	}
	else {
		fixedPmt = 0. ;
		throw out_of_range(string("Fixed payment must be positive, not ") + ftoa(_value)) ;
	}
} // fixedPayment()

void Amortize::paymentPercent(float _value) throw (out_of_range) {
	if (_value > 0 && _value < 100) {
		paymentPct = _value ;
	}
	else {
		paymentPct = 0. ;
		throw out_of_range(string("Payment percent must be positive and less than 100, not ")
		                  + ftoa(_value)) ;
	}
} // paymentPercent()

void Amortize::minimumPayment(float _value) throw (out_of_range) {
	if (_value > 0) {
		minPayment = _value ;
	}
	else {
		minPayment = 0. ;
		throw out_of_range(string("Minimum payment must be positive, not ") + ftoa(_value)) ;
	}
} // minimumPayment()

void Amortize::paymentsPerYear(int _value) throw (out_of_range) {
	if (_value > 0 ) {
		pmtsPerYear = _value ;
	}
	else {
		pmtsPerYear = 0 ;
		throw out_of_range(string("Payments per year must be positive, not ") + itoa(_value)) ;
	}
} // paymentsPerYear()

void Amortize::firstPaymentDate(struct tm * _value = 0) {
	if (_value ) {
		memcpy(&firstPayDate, _value, sizeof(firstPayDate)) ;
	}
	else {
		time_t now = time(NULL) ;
		memcpy(&firstPayDate, localtime(&now), sizeof(firstPayDate)) ;
	}
} // firstPaymentDate()

PaymentData * Amortize::makePayment(double balance, double intRate, double payment,
                             int pymtNum) throw (out_of_range) {
	double interest = balance * intRate ; // interest paid
	double principal = payment - interest ; // principal paid
	if (principal <= 0) {
	  throw out_of_range(string("The payment amount (" + ftoa(payment) + ") "
	      "must be greater than the first period interest (" + ftoa(interest) + ")"));
	} // if principal paid is not positive (TRUE branch)
	if (principal > balance) { // recalc if payment's bigger than what's owed
		payment = balance + interest ;
		principal = payment - interest ;
		balance = 0 ;
	} // if overpaid (TRUE branch)
	else balance -= principal ;
	if (balance < .01) balance = 0 ;  // avoid an extra payment
	return new PaymentData(principal, interest, balance, pymtNum, NULL) ;
} // makePayment()

void Amortize::amortizeFixedPayment(vector<PaymentData> & data) {
	double bal = principalAmt ;
	double rate = (intRate / pmtsPerYear) / 100 ;
	int pymtNum = 0 ;

	while (bal > 0) {
		PaymentData * pd = makePayment( bal, rate, fixedPayment(), ++pymtNum ) ;
		data.push_back( *pd ) ;
		bal = pd->balance() ;
	}  // while there's a balance left
} // amortizeFixedPayment()

void Amortize::amortizePercentPayment(vector<PaymentData> & data) {
	double bal = principalAmt ;
	double rate = (intRate / pmtsPerYear) / 100 ;
	int pymtNum = 0 ;

	while (bal > 0 ) {
		double payment = max(bal * paymentPct / 100, minPayment) ;
		PaymentData * pd = makePayment( bal, rate, payment, ++pymtNum ) ;
		data.push_back( *pd ) ;
		bal = pd->balance() ;
	  }  // while there's a balance left
} // amortizePercentPayment()

void Amortize::amortizeInstallmentLoan(vector<PaymentData> & data) {
	if (intRate && pmtsPerYear && principalAmt && payments) {
		double payment = calcInstallmentPayment() ;
		double bal = principalAmt ;
		double rate = (intRate / pmtsPerYear) / 100 ;
		int pymtNum = 0 ;

		while (bal > 0 ) {
			PaymentData * pd = makePayment( bal, rate, payment, ++pymtNum ) ;
			data.push_back( *pd ) ;
			bal = pd->balance() ;
	  	} // while there's a balance left
	} // if all fields have values (TRUE branch)
} // amortizeInstallmentLoan()

double Amortize::calcInstallmentPayment() {
	if (intRate && pmtsPerYear && principalAmt && payments) {
		double rate = (intRate / pmtsPerYear) / 100 ;
		return principalAmt * (rate / (1 - pow(1. + rate, - payments))) ;
	}  // if all the needed values are defined (TRUE branch)
	else return 0 ; // not ready to rumble
} // calcInstallmentPayment()


