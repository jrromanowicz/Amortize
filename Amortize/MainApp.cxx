#include "AmortizeUI.h"
#include "Amortize.h"
#include <FL\Fl_File_Chooser.H>

using namespace std ;

#include <fstream>
#include <sstream>
#include <iomanip>

static const char * programVersion = "Amortize V1.0";

bool allParametersOK(AmortizeUI & ui) {
	bool result = true ; // assume all is OK
	ostringstream buf ;
	if ( ui.getPrincipalAmount() <= 0 )  {
		result = false ;
		buf << "The principal amount must be greater than zero, it cannot be "
			<< ui.getPrincipalAmount() << endl ;
	} // if principal amount is <= 0 (TRUE branch)
	if (ui.getInterestRate() <= 0 ) {
		result = false ;
		buf << "The interest rate must be greater than zero, it cannot be "
			<< ui.getInterestRate() << endl ;
	} // if interest rate is <= 0 (TRUE branch)
	if (ui.getPaymentPeriod() < AmortizeUI::BiWeeklyPeriod
			|| ui.getPaymentPeriod() > AmortizeUI::AnnualPeriod ) {
		result = false ;
		buf << "You must select a payment period\n" ;
	} // if payment period is invalid (TRUE branch)
	if (AmortizeUI::InstallmentLoan == ui.getLoanType() ) {
		if (ui.getNumPayments() <= 0 ) {
			result = false ;
			buf << "An installment loan must have a number of payments greater than zero, it cannot be "
				<< ui.getNumPayments() << endl ;
		} // if number of payments is <= 0 (TRUE branch)
	} // if loan type is MortgageLoan (TRUE branch)
	else if ( AmortizeUI::RevolvingChargeLoan == ui.getLoanType() ) {
		result = false ;
		buf << "You must choose a payment type\n" ;
	} // if loan type is RevolvingChargeLoan (TRUE branch)
	else if (AmortizeUI::FixedPaymentLoan == ui.getLoanType() ) {
		if (ui.getFixedPayment() <= 0 ) {
			result = false ;
			buf << "A fixed payment loan must have a fixed payment greater than zero, it cannot be "
				<< ui.getFixedPayment() << endl ;
		} // if fixed payment is <= 0 (TRUE branch)
	} // if loan type is FixedPaymentLoan (TRUE branch)
	else if (AmortizeUI::PercentPaymentLoan == ui.getLoanType() ) {
		if (ui.getPercentPayment() <= 0 ) {
			result = false ;
			buf << "A percent payment loan must have a percent payment greater than zero, it cannot be "
				<< ui.getPercentPayment() << endl ;
		} // if percent payments is <= 0 (TRUE branch)
	} // if loan type is PercentPaymentLoan (TRUE branch)
	else {
		result = false ;
		buf << "You must choose a loan type\n" ;
	} // not a recognized loan type

	if (result) {
		buf << "All parameters are valid\n" ;
	}

	ui.addText(buf.str().c_str() ) ;

	return result ;
} // allParametersOK()

extern string itoa(int) ;
extern string ftoa(double) ;

Fl_File_Chooser * saveDlg = NULL ;
void doSave(AmortizeUI * amortizeUI) {
	AmortizeUI & ui = *amortizeUI ;
	if (!saveDlg) {
		saveDlg = new Fl_File_Chooser(".", "*",
			Fl_File_Chooser::CREATE,"Save Amortization to CSV") ;
		saveDlg->preview( 0 ) ; // no preview
		saveDlg->ok_label("Save") ;
	}  // if save dialog needs creating (TRUE branch)

	saveDlg->show() ;

	while (saveDlg->shown() ) Fl::wait() ; // block while user decides

	saveDlg->hide() ;

	if (NULL != saveDlg->value() ) { // chose some file?
		ofstream outStr(saveDlg->value(), ios::out) ;
		if (!outStr ) {
			ui.setText( string("Can't write to ") +
				saveDlg->value() + ", data was not saved.") ;
			return ;
		} // if can't open file (TRUE branch)

		outStr << "Loan Amount," << ui.getPrincipalAmount() << endl ;
		outStr << "Interest Rate," << ui.getInterestRate() << "%" << endl ;
		outStr << "" << endl ;
   	outStr << "Payment Number, Payment Amount, Interest Paid,"
			<< "Principal Paid, Balance Remaining" << endl ;

  	   AmortizeTable & data = *(ui.getPaymentTable()) ;
		for (int i = 0 ; i < data.rows() ; i++ ) {
			// output each column value in the row, separated by commas
			outStr << data.cell(i, 0)
				<< ", " << data.cell(i, 1)
				<< ", " << data.cell(i, 2)
				<< ", " << data.cell(i, 3)
				<< ", " << data.cell(i, 4)
	 	   	<< endl ;
  	   } // for each row in the data by i
    	ui.setText( string("Saved amortization to:\n") + saveDlg->value() ) ;
		outStr.close() ;
	  } // if user chose a file (TRUE branch)
} // doSave()

void doAmortization(AmortizeUI * amortizeUI) {
	AmortizeUI & ui = *amortizeUI ;
	ui.setText("") ;
	ui.hideSaveButton() ;
	ui.getPaymentTable()->hide() ;
	time_t timeNow ;
	struct tm startDate ;
	time(&timeNow) ;
	memcpy(&startDate, localtime(&timeNow), sizeof(startDate)) ;
	try {
		if (allParametersOK(ui)) {
			ui.addText("Doing amortization...\n") ;
			Amortize *amortize = new Amortize() ;
			Amortize & loan = *amortize ;
			loan.principalAmount(ui.getPrincipalAmount()) ;
		  loan.interestRate(ui.getInterestRate()) ;
			loan.firstPaymentDate(&startDate) ;
		  int numPeriods = 0 ; // default to invalid

			switch (ui.getPaymentPeriod()) {
				case AmortizeUI::BiWeeklyPeriod: numPeriods = 26 ; break ;
				case AmortizeUI::SemiMonthlyPeriod: numPeriods = 24 ; break ;
				case AmortizeUI::MonthlyPeriod: numPeriods = 12 ; break ;
				case AmortizeUI::QuarterlyPeriod: numPeriods = 4 ; break ;
				case AmortizeUI::SemiAnnualPeriod: numPeriods = 2 ; break ;
				case AmortizeUI::AnnualPeriod: numPeriods = 1 ; break ;
				default: throw domain_error("Invalid payment period") ;
			} // switch on payment period
		   loan.paymentsPerYear(numPeriods) ;

			vector<PaymentData> payData ;
			switch (ui.getLoanType()) {
				case AmortizeUI::InstallmentLoan:
					loan.numPayments(ui.getNumPayments()) ;
  	   		loan.amortizeInstallmentLoan(payData) ;
					break ;
				case AmortizeUI::FixedPaymentLoan:
					loan.fixedPayment(ui.getFixedPayment()) ;
		    	loan.amortizeFixedPayment(payData) ;
		    	break ;
				case AmortizeUI::PercentPaymentLoan:
					loan.paymentPercent(ui.getPercentPayment()) ;
  		 	  loan.minimumPayment(ui.getMinimumPayment()) ;
	  	  	loan.amortizePercentPayment(payData) ;
	  	  	break ;
				default:
					throw domain_error("Unknown loan type") ;
					break ;
			} // switch on loan type
			ui.addText("Amortization done!\n") ;
			int size = payData.size() ;
			ostringstream buf ;
			buf << endl << "There are " << size << " payments" << endl ;
			double intTotal = 0. ;
			for (int i = 0 ; i < size ; i++ ) {
				intTotal += payData[i].interest() ;
			} // for each payment record by i
			double payTotal = intTotal + loan.principalAmount() ;
	  	  	buf << "Total Interest: " << ftoa(intTotal) << endl ;
			buf << "Total Payments: " << ftoa(payTotal) << endl ;
			ui.addText(buf.str().c_str() ) ;

      ui.getPaymentTable()->setData(payData) ; // GEEK!!
      ui.getPaymentTable()->show() ;  // GEEK!!
			ui.showSaveButton() ;
			ui.colorButtons->show() ;  //GEEK!!
  	   } // if all parameters are OK (TRUE branch)
		else { // some parameter(s) not OK
			ui.addText("Amortization was not done\n") ;
		} // if all parameters are OK (FALSE branch)
	} // try block
	catch(exception& e) {
		ui.addText(e.what()) ;
    ui.addText("\nAmortization was not done\n") ;
	} // catch exception
} // doAmortization()


int main(int argc, char ** argv) {

	AmortizeUI * myUI = new AmortizeUI(doAmortization, doSave, programVersion) ;  // GEEK!!  GEEK!!
	myUI->show(argc, argv) ;
	myUI->setText("Results and errors will display in this space."
	    "\n\nBoth mouse and keyboard navigation are supported."
	    "\n--Enter key acts as the Amortize button"
	    "\n--Spacebar drops the pay period list"
	    "\n\nHover over input widgets for tooltip help.");

	return Fl::run() ;
} // main()

