/*
 * PaymentTableUI.cpp
 *
 *  Created on: Jan 2, 2017
 *      Author: Jack
 */

#include "PaymentTableUI.h"
#include <FL/Fl_File_Chooser.h>
#include <FL/Fl_ask.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>

extern string ftoa(double);

PaymentTableUI::PaymentTableUI(const LoanData& loan_, const char * title,
    vector<PaymentData> & payData) :
    Fl_Window(425, 606, title), loan(loan_), payData(payData) {
  { totals = new Fl_Multiline_Output(2, 2, 429, 54);
    totals->box(FL_NO_BOX);
  } // Fl_Multiline_output * totals
  { amortizeTable = new AmortizeTable(2, 80, 420, 490);
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
  { colorButtons = new Fl_Group(85, 58, 320, 20);
    { Col1Color = new Fl_Button(87, 59, 50, 18, "Color...");
      Col1Color->tooltip("Choose a text color for this column");
      Col1Color->callback((Fl_Callback*)cb_Col1Color);
    } // Fl_Button* Col1Color
    { Col2Color = new Fl_Button(165, 59, 50, 18, "Color...");
      Col2Color->tooltip("Choose a text color for this column");
      Col2Color->callback((Fl_Callback*)cb_Col2Color);
    } // Fl_Button* Col2Color
    { Col3Color = new Fl_Button(243, 59, 50, 18, "Color...");
      Col3Color->tooltip("Choose a text color for this column");
      Col3Color->callback((Fl_Callback*)cb_Col3Color);
    } // Fl_Button* Col3Color
    { Col4Color = new Fl_Button(326, 59, 50, 18, "Color...");
      Col4Color->tooltip("Choose a text color for this column");
      Col4Color->callback((Fl_Callback*)cb_Col4Color);
    } // Fl_Button* Col4Color
    colorButtons->end();
  } // Fl_Group* colorButtons
  { saveButton = new Fl_Button(165, 574, 94, 25, "Save to CSV");
    saveButton->tooltip("Save amortization as a file you can open in a spreadsheet");
    saveButton->color(fl_rgb_color(0, 128, 255));
//    saveButton->color(fl_lighter(FL_BLUE));
    saveButton->callback((Fl_Callback*)cb_saveButton, (void*)(this));
  } // Fl_Button* saveButton

  end();

  interestTotal = 0. ;
  for (unsigned int i = 0 ; i < payData.size() ; i++ ) {
    interestTotal += payData[i].interest() ;
  } // for each payment record by i
  paymentsTotal = interestTotal + loan.principalAmount() ;
  char total[100];
  sprintf(total, "There are %d payments\nTotal Interest: %.2f\nTotal Payments: %.2f",
      payData.size(), interestTotal, paymentsTotal);
  totals->value(total);
  show();
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
  if (NULL != saveDlg.value()) {ofstream outStr(saveDlg.value(),ios::out);
    if (!outStr ) {
      fl_alert("Can't write to %s, data was not saved.", saveDlg.value());
      return ;
    } // if can't open file for output (TRUE branch)

    outStr << "Loan Amount,$" << ftoa(loan.principalAmount()) << endl ;
    outStr << "Interest Rate," << loan.interestRate() << "%" << endl ;
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
        << ",$" << data.cell(i, 1)
        << ",$" << data.cell(i, 2)
        << ",$" << data.cell(i, 3)
        << ",$" << data.cell(i, 4)
        << endl ;
       } // for each row in the data by i
      fl_message("Saved amortization to:\n%s", saveDlg.value());
    outStr.close() ;
    } // if user chose a file (TRUE branch)
} // doSave()


void PaymentTableUI::cb_Col1Color_i(Fl_Button*, void*) {
  Fl_Color colColor = fl_show_colormap(amortizeTable->columnColor(1)) ;
amortizeTable->columnColor(1, colColor) ;
amortizeTable->redraw() ;
}
void PaymentTableUI::cb_Col1Color(Fl_Button* o, void* v) {
  ((PaymentTableUI*)(o->parent()->parent()->user_data()))->cb_Col1Color_i(o,v);
}

void PaymentTableUI::cb_Col2Color_i(Fl_Button*, void*) {
  Fl_Color colColor = fl_show_colormap(amortizeTable->columnColor(2)) ;
amortizeTable->columnColor(2, colColor) ;
amortizeTable->redraw() ;
}
void PaymentTableUI::cb_Col2Color(Fl_Button* o, void* v) {
  ((PaymentTableUI*)(o->parent()->parent()->user_data()))->cb_Col2Color_i(o,v);
}

void PaymentTableUI::cb_Col3Color_i(Fl_Button*, void*) {
  Fl_Color colColor = fl_show_colormap(amortizeTable->columnColor(3)) ;
amortizeTable->columnColor(3, colColor) ;
amortizeTable->redraw() ;
}
void PaymentTableUI::cb_Col3Color(Fl_Button* o, void* v) {
  ((PaymentTableUI*)(o->parent()->parent()->user_data()))->cb_Col3Color_i(o,v);
}

void PaymentTableUI::cb_Col4Color_i(Fl_Button*, void*) {
  Fl_Color colColor = fl_show_colormap(amortizeTable->columnColor(4)) ;
amortizeTable->columnColor(4, colColor) ;
amortizeTable->redraw() ;
}
void PaymentTableUI::cb_Col4Color(Fl_Button* o, void* v) {
  ((PaymentTableUI*)(o->parent()->parent()->user_data()))->cb_Col4Color_i(o,v);
}
void PaymentTableUI::cb_saveButton_i(Fl_Button*, void* v) {
  ((PaymentTableUI *)v)->doSave() ;
}
void PaymentTableUI::cb_saveButton(Fl_Button* o, void* v) {
  ((PaymentTableUI*)(o->parent()->user_data()))->cb_saveButton_i(o,v);
}

