/*
 * PaymentTableUI.h
 *
 *  Created on: Jan 2, 2017
 *      Author: Jack
 */

#ifndef PAYMENTTABLEUI_H_
#define PAYMENTTABLEUI_H_

#include <FL/Fl_Window.H>
#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>
#include <string>
#include "AmortizeTable.h"
#include "PaymentData.h"
#include "LoanData.h"
#include <stdlib.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/fl_show_colormap.H>
#include <FL/Fl_Multiline_Output.h>

class PaymentTableUI {
public:
  PaymentTableUI(const double loanAmt, const double interestAmt,
	const char * title, vector<PaymentData>& payData);
  virtual ~PaymentTableUI();
  void hide() { window->hide(); }

private:
  Fl_Window * window;
  double loanAmount;
  double interestRate;
  double interestTotal;
  double paymentsTotal;
  AmortizeTable *amortizeTable;
  vector<PaymentData> payData ;
  Fl_Button *saveButton;
  void doSave(void);
  void cb_saveButton_i(Fl_Button*, void*);
  static void cb_saveButton(Fl_Button*, void*);
};

#endif /* PAYMENTTABLEUI_H_ */
