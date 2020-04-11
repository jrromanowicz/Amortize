/*
 * PaymentTableUI.cpp
 *
 *  Created on: Jan 2, 2017
 *      Author: Jack
 */

#include "PaymentTableUI.h"
#include <FL/Fl_File_Chooser.h>
#include <FL/Fl_ask.h>
#include <FL/fl_draw.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <locale>
#include <exception>

extern string ftoa(double);

PaymentTableUI::PaymentTableUI(const double loanAmt, double intRate,
	const char * title, vector<PaymentData> & payData)
	: loanAmount(loanAmt), interestRate(intRate), payData(payData) {
  window = new Fl_Window(425, 600, title);
  window->user_data((void*)(this));
  interestTotal = 0. ;
  for (unsigned int i = 0 ; i < payData.size() ; i++ ) {
	  interestTotal += payData[i].interest() ;
  } // for each payment record by i
  paymentsTotal = interestTotal + loanAmt ;
  int lineh = 14;
  fl_font(FL_HELVETICA, lineh);
  int colw = window->w()/3; // third of window width
  int h, w ;
  char buf[20];
  const char * msg1 = "Number of Payments:";
  w = 0;
  fl_measure(msg1, w, h);
  {Fl_Box * b = new Fl_Box(colw - w, 2, w, lineh, msg1 );
  	  b->copy_label(msg1);
  	  b->align(FL_ALIGN_INSIDE|FL_ALIGN_RIGHT);
  }
  sprintf(buf, "%d", payData.size());
  w = 0; // for fl_measure()
  fl_measure(buf, w, h);
  {Fl_Box * b = new Fl_Box(colw, 2, w, lineh, buf);
	  b->copy_label(buf);
	  b->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT );
  }
  const char * msg2 = "Total of Payments:";
  w = 0;
  fl_measure(msg2, w, h);
  {Fl_Box * b = new Fl_Box(colw - w, 2 + lineh, w, lineh, msg2);
	  b->copy_label(msg2);
  	  b->align(FL_ALIGN_INSIDE|FL_ALIGN_RIGHT);
  }
  sprintf(buf, "%.2f", paymentsTotal);
  w = 0;
  fl_measure(buf, w, h);
  {Fl_Box * b = new Fl_Box(colw, 2 + lineh, w, lineh, buf);
  	  b->copy_label(buf);
  	  b->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT );
  }
  const char * msg3 = "Total Interest Paid:";
  w = 0;
  fl_measure(msg3, w, h);
  {Fl_Box * b = new Fl_Box(colw - w, 2 + lineh * 2, w, lineh, msg3);
	  b->copy_label(msg3);
  	  b->align(FL_ALIGN_INSIDE|FL_ALIGN_RIGHT);
  }
  sprintf(buf, "%.2f", interestTotal);
  w = 0;
  fl_measure(buf, w, h);
  {Fl_Box * b = new Fl_Box(colw, 2 + lineh * 2,  w, lineh, buf);
  	  b->copy_label(buf);
	  b->align(FL_ALIGN_INSIDE|FL_ALIGN_LEFT );
  }
  { amortizeTable = new AmortizeTable(2, 80, window->w() -5, window->h() - 80);
    amortizeTable->box(FL_NO_BOX);
    amortizeTable->color(FL_BACKGROUND_COLOR);
    amortizeTable->selection_color(FL_BACKGROUND_COLOR);
    amortizeTable->labeltype(FL_NORMAL_LABEL);
    amortizeTable->labelfont(0);
    amortizeTable->labelsize(14);
    amortizeTable->labelcolor(FL_FOREGROUND_COLOR);
    amortizeTable->align(FL_ALIGN_TOP);
    amortizeTable->when(FL_WHEN_RELEASE);
    amortizeTable->setData(payData);
    amortizeTable->end();
  } // AmortizeTable* amortizeTable
  { saveButton = new Fl_Button(165, 54, 94, 20, "Save to CSV");
  	saveButton->color(FL_DARK3);
    saveButton->tooltip("Save amortization as a file you can open in a spreadsheet");
    saveButton->callback((Fl_Callback*)cb_saveButton, (void*)(this));
  } // Fl_Button* saveButton

  window->end();
  window->show();
} // PaymentTableUI ctor

PaymentTableUI::~PaymentTableUI() {
  // nothing to do here
}

void PaymentTableUI::doSave(void) {
  Fl_File_Chooser saveDlg(".", "*", Fl_File_Chooser::CREATE, "Save Amortization to CSV");
  saveDlg.preview(0);
  saveDlg.ok_label("Save");
  saveDlg.show();
  while (saveDlg.shown()) Fl::wait();
  saveDlg.hide();
  if (NULL != saveDlg.value()) {
	ofstream outStr(saveDlg.value(),ios::out);
    if (!outStr ) {
      fl_alert("Can't write to %s, data was not saved.", saveDlg.value());
      return ;
    } // if can't open file for output (TRUE branch)
#include <clocale>
char * name = setlocale(LC_ALL, "");
fl_message("locale: %s", name);
//name = setlocale(LC_MONETARY, "");
//fl_message("locale: %s", name);
    try {
    std::locale loc = locale(name);
    fl_message("locale: %s", loc.name().c_str());
    outStr.imbue(loc);
    } catch ( exception & ex) {
    	fl_message("locale fail: %s", ex.what());
    }

    outStr << "Loan Amount,$" << ftoa(loanAmount) << endl ;
    outStr << "Interest Rate," << ftoa(interestRate) << "%" << endl ;
    outStr << "Number of Payments," << payData.size() << endl;
    outStr << "Total Interest Paid,$" << ftoa(interestTotal) << endl;
    outStr << "Total of Payments,$" << ftoa(paymentsTotal) << endl;
    outStr << "" << endl ;
    outStr << "Payment Number, Payment Amount, Interest Paid,"
      << "Principal Paid, Balance Remaining" << endl ;

    AmortizeTable & data = *amortizeTable ;  // for brevity
    for (int i = 0 ; i < data.rows() ; i++ ) {
      // output each column value in the row, separated by commas
      outStr << data.cell(i, 0)
 		  << "," << std::put_money(data.cell(i, 1))
      	  << "," << std::put_money(data.cell(i, 2))
      	  << "," << std::put_money(data.cell(i, 3))
      	  << "," << std::put_money(data.cell(i, 4))
                << ",$" << data.cell(i, 2)
                << ",$" << data.cell(i, 3)
                << ",$" << data.cell(i, 4)
/*		        << ",$" << data.cell(i, 1)
		        << ",$" << data.cell(i, 2)
		        << ",$" << data.cell(i, 3)
		        << ",$" << data.cell(i, 4) */
        << endl ;
       } // for each row in the data by i
      fl_message("Saved amortization to:\n%s", saveDlg.value());
    outStr.close() ;
    } // if user chose a file (TRUE branch)
} // doSave()

void PaymentTableUI::cb_saveButton_i(Fl_Button*, void* v) {
  ((PaymentTableUI *)v)->doSave() ;
}
void PaymentTableUI::cb_saveButton(Fl_Button* o, void* v) {
  ((PaymentTableUI*)(o->parent()->user_data()))->cb_saveButton_i(o,v);
}

