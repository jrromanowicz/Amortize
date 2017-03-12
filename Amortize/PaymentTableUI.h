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
  PaymentTableUI(const LoanData& loan, const char * title,
      vector<PaymentData>& payData);
  virtual ~PaymentTableUI();
  Fl_Group *colorButtons;

private:
  Fl_Window * window;
  double interestTotal;
  double paymentsTotal;
  AmortizeTable *amortizeTable;
  const LoanData& loan;
  vector<PaymentData> payData ;
  Fl_Button *saveButton;
  Fl_Multiline_Output *totals;
  void doSave(void);
  void cb_saveButton_i(Fl_Button*, void*);
  static void cb_saveButton(Fl_Button*, void*);
  Fl_Button *Col1Color;
  void cb_Col1Color_i(Fl_Button*, void*);
  static void cb_Col1Color(Fl_Button*, void*);
  Fl_Button *Col2Color;
  void cb_Col2Color_i(Fl_Button*, void*);
  static void cb_Col2Color(Fl_Button*, void*);
  Fl_Button *Col3Color;
  void cb_Col3Color_i(Fl_Button*, void*);
  static void cb_Col3Color(Fl_Button*, void*);
  Fl_Button *Col4Color;
  void cb_Col4Color_i(Fl_Button*, void*);
  static void cb_Col4Color(Fl_Button*, void*);
};

#endif /* PAYMENTTABLEUI_H_ */
