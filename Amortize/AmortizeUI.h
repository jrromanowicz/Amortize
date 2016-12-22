// generated by Fast Light User Interface Designer (fluid) version 1.0108

#ifndef AmortizeUI_h
#define AmortizeUI_h
#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>
#include <string>
#include <Fl/Fl_Window.H>
#include "AmortizeTable.h"
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Int_Input.H>
#include <stdlib.h>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Button.H>
#include <FL/fl_show_colormap.H>

class AmortizeUI : Fl_Window {
public:
  enum PaymentPeriod {InvalidPeriod = 0, BiWeeklyPeriod, SemiMonthlyPeriod,
    MonthlyPeriod, QuarterlyPeriod, SemiAnnualPeriod, AnnualPeriod} ;
  enum LoanType {InvalidLoan = 0, InstallmentLoan, RevolvingChargeLoan,
    FixedPaymentLoan, PercentPaymentLoan } ;
  AmortizeUI(void (*doAmortize)(AmortizeUI *), void(*saveFunc)(AmortizeUI *),
      const char * title);

private:
  int handle(int event);
  Fl_Text_Display *results;
  AmortizeTable *amortizeTable;
  void cb_Principal_i(Fl_Float_Input*, void*);
  static void cb_Principal(Fl_Float_Input*, void*);
  void cb_Interest_i(Fl_Float_Input*, void*);
  static void cb_Interest(Fl_Float_Input*, void*);
  Fl_Menu_Button *menuButton;
  void cb_menuButton_i(Fl_Menu_Button*, void*);
  static void cb_menuButton(Fl_Menu_Button*, void*);
  static Fl_Menu_Item menu_menuButton[];
  void cb_Installment_i(Fl_Round_Button*, void*);
  static void cb_Installment(Fl_Round_Button*, void*);
  void cb_Revolving_i(Fl_Round_Button*, void*);
  static void cb_Revolving(Fl_Round_Button*, void*);
  Fl_Group *installmentGroup;
  void cb_Number_i(Fl_Int_Input*, void*);
  static void cb_Number(Fl_Int_Input*, void*);
  Fl_Group *revolveGroup;
  void cb_Fixed_i(Fl_Round_Button*, void*);
  static void cb_Fixed(Fl_Round_Button*, void*);
  void cb_Percentage_i(Fl_Round_Button*, void*);
  static void cb_Percentage(Fl_Round_Button*, void*);
  Fl_Float_Input *fixedPay;
  void cb_fixedPay_i(Fl_Float_Input*, void*);
  static void cb_fixedPay(Fl_Float_Input*, void*);
  Fl_Float_Input *pctPayment;
  void cb_pctPayment_i(Fl_Float_Input*, void*);
  static void cb_pctPayment(Fl_Float_Input*, void*);
  Fl_Float_Input *minPayment;
  void cb_minPayment_i(Fl_Float_Input*, void*);
  static void cb_minPayment(Fl_Float_Input*, void*);
  void cb_Amortize_i(Fl_Button*, void*);
  static void cb_Amortize(Fl_Button*, void*);
public:
  Fl_Button *saveButton;
private:
  void cb_saveButton_i(Fl_Button*, void*);
  static void cb_saveButton(Fl_Button*, void*);
public:
  Fl_Group *colorButtons;
private:
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
public:
  double getPrincipalAmount(void);
  double getInterestRate(void);
  AmortizeUI::PaymentPeriod getPaymentPeriod(void);
  AmortizeUI::LoanType getLoanType(void);
  int getNumPayments(void);
  double getFixedPayment(void);
  double getPercentPayment(void);
  double getMinimumPayment(void);
  void setText(std::string text);
  void addText(std::string text);
  char * getText(void);
  AmortizeTable * getPaymentTable(void);
  void hideSaveButton();
  void showSaveButton();
  void show(int argc, char ** argv) {Fl_Window::show(argc, argv);}
  Fl_Text_Buffer resultText ;
private:
  double principalAmount;
  double interestRate;
  PaymentPeriod paymentPeriod;
  LoanType loanType;
  double fixedPayment;
  double percentPayment;
  double minimumPayment;
  int numPayments;
  void (*doAmortization)(AmortizeUI *) ;
  void (*doSave)(AmortizeUI *);
};
#endif
