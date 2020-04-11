#include "MainUI.h"

using namespace std ;

static const char * programVersion = "Amortize V2.2";

int main(int argc, char ** argv) {

	MainUI * myUI = new MainUI(programVersion) ;
	myUI->show(argc, argv) ;
	myUI->setText("Errors will display in this space."
	    "\n\nBoth mouse and keyboard navigation are supported."
	    "\n--Enter key acts as the Calculate button"
	    "\n--Spacebar shows the pay period list"
	    "\n\nHover over the input widgets for tooltip help.");

	return Fl::run() ;
} // main()

