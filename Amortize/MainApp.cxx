#include "AmortizeUI.h"

using namespace std ;

static const char * programVersion = "Amortize V2.0";

int main(int argc, char ** argv) {

	AmortizeUI * myUI = new AmortizeUI(programVersion) ;
	myUI->show(argc, argv) ;
	myUI->setText("Results and errors will display in this space."
	    "\n\nBoth mouse and keyboard navigation are supported."
	    "\n--Enter key acts as the Amortize button"
	    "\n--Spacebar drops the pay period list"
	    "\n\nHover over the input widgets for tooltip help.");

	return Fl::run() ;
} // main()

