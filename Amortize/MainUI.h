// generated by Fast Light User Interface Designer (fluid) version 1.0108
// Amortize v2.21

#ifndef AmortizeUI_h
#define AmortizeUI_h
#include <FL/Fl.H>
#include <FL/Fl_Text_Display.H>
#include <string>
#include <Fl/Fl_Window.H>
#include "Amortize.h"
#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Int_Input.H>
#include <stdlib.h>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Button.H>
#include <FL/fl_show_colormap.H>
#include "LoanData.h"
#include "PaymentTableUI.h"
#include <vector>

class MainUI : Fl_Window {
public:
  MainUI(const char * title);
  virtual ~MainUI() {}

  double getPrincipalAmount(void);
  double getInterestRate(void);
  LoanData::PaymentPeriod getPaymentPeriod(void);
  LoanData::LoanType getLoanType(void);
  int getNumPayments(void);
  double getFixedPayment(void);
  double getPercentPayment(void);
  double getMinimumPayment(void);
  void setText(std::string text);
  void addText(std::string text);
  char * getText(void);
  void hideSaveButton();
  void showSaveButton();
  void show(int argc, char ** argv) {Fl_Window::show(argc, argv);}
  Fl_Text_Buffer resultText ;
private:
  int handle(int event);
  Fl_Text_Display *results;
  LoanData *loan;
  vector<PaymentTableUI *> loanWindows;
  void doAmortization(void);
  static void cb_Close(Fl_Widget *, void *);
  static void cb_Amortize(Fl_Button*, void*);
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

  double principalAmount;
  double interestRate;
  LoanData::PaymentPeriod paymentPeriod;
  LoanData::LoanType loanType;
  double fixedPayment;
  double percentPayment;
  double minimumPayment;
  int numPayments;
};
#endif
