#include "AmortizeTable.h"
#include <FL/fl_draw.H>
#include <string>
#include <sstream>

extern string ftoa(double) ;
extern string itoa(int) ;
// GEEK!
//AmortizeTable::AmortizeTable(int x, int y, int w, int h):
//		Fl_Table(x,y,w,h,"") {
//	init() ; // do common things
//} // ctor without label

AmortizeTable::AmortizeTable(int x, int y, int w, int h, const char *label) :
		Fl_Table(x,y,w,h,label) {
	init(); // do common things
} // ctor with label

void AmortizeTable::init( void ) {
	header[0] = "Payment\nNumber" ;
	header[1] = "Payment\nAmount" ;
	header[2] = "Interest\n Paid" ;
	header[3] = "Principal\n Paid" ;
	header[4] = " Balance\nRemaining" ;
	colColor[0] = colColor[1] = FL_BLACK ;
	colColor[2] = colColor[4] = FL_BLUE ;
	colColor[3] = FL_RED ;
	col_header_height(col_header_height() * 2) ;

	// Tell Fl_Table how many rows/cols of data
	rows(0);
	cols(NUM_COLS);
	col_header(1); // Enable column headers
	row_height_all(14) ;
  col_width(0, col_width(0) - 12) ;
  col_width(1, col_width(1) - 2) ;
  col_width(4, col_width(4) + 13) ;
	end(); // end of our Fl_Group

} // init()

void AmortizeTable::draw_cell(TableContext context,
		int row, int col, int x=0, int y=0, int w=0, int h=0) {
	switch ( context )  {
	   case CONTEXT_STARTPAGE:
			fl_font(FL_HELVETICA, 14);	   		// font to use for all cells
			break;

	   case CONTEXT_COL_HEADER:
			fl_push_clip(x, y, w, h); // make sure text doesn't leak outside of XYWH
			{
	  	  fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, color()); // solid 'up box'
				fl_color(FL_BLACK);
				fl_draw(header[col], x, y, w, h, FL_ALIGN_CENTER); // center text in box
			}
			fl_pop_clip();
	    	break;

	   case CONTEXT_ROW_HEADER:
//	  	  	fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, color()); // solid 'up box'
//	  	  	fl_color(FL_BLACK);
//  	  	  fl_draw(data[col], x, y, w, h, FL_ALIGN_CENTER); // center text in box
			break;

		case CONTEXT_CELL:
			fl_push_clip(x, y, w, h); // make sure text doesn't leak outside of XYWH
			{
				fl_draw_box(FL_THIN_UP_BOX, x, y, w, h, color()); // solid 'up box'
  	   	fl_color(colColor[col]) ;
				if (0 == col) { // center the payment number
		   		fl_draw(data[row][col].c_str(), x, y, w, h, FL_ALIGN_CENTER);
				}
				else { // draw text right-aligned w/2 pixel margin in other columns
		   		fl_draw(data[row][col].c_str(), x, y, w-2, h, FL_ALIGN_RIGHT);
				}
  	   	}
			fl_pop_clip();
			break;

		default:
			break;
	} // switch on context
} // draw_cell()

void AmortizeTable::cell(int row, int col, string & val) {
	if (row < (int)(data.size()))
		data[row][col] = val;
} // cell() setter

void AmortizeTable::setData(vector<string> & stringData) {
	data.clear() ;
	for (unsigned i = 0 ; i < stringData.size() ; i++) {
		addRow(stringData[i]) ;
	} // for each string in data, by i
	rows(data.size()) ;
	top_row(0) ;
} // setData()

// Adapt PaymentData fields to a new row vector
void setUpRow( vector<string> & newRow, PaymentData & payData ) {
	newRow.clear() ; // just in case
	newRow.push_back(itoa(payData.paymentNum())) ;
	newRow.push_back(ftoa(payData.totalPayment())) ;
   newRow.push_back(ftoa(payData.interest())) ;
	newRow.push_back(ftoa(payData.principal())) ;
	newRow.push_back(ftoa(payData.balance())) ;
} // setUpRow()

void AmortizeTable::setData(vector<PaymentData> & payData) {
	data.clear() ;
	vector<string> newRow ;
	for (unsigned i = 0 ; i < payData.size() ; i++) {
		setUpRow( newRow, payData[i]) ;
		data.push_back( newRow ) ;
	} // for each string in data, by i
	rows( data.size() ) ;
	top_row(0) ;
} // setData()

string AmortizeTable::cell(int row, int col) {
	if (row < (int)data.size()) return(data[row][col]);
	else return string("") ;
} // cell() getter

// val contains a whitespace-delimited set of tokens, one for each cell in a row
void AmortizeTable::addRow(string & vals) {
	char * myVals = new char[vals.length() + 1] ;
	strncpy(myVals, vals.c_str(), vals.length() ) ;
	myVals[vals.length()] = 0 ;
	const char * seperators = " \n\t" ;
	int col = 0 ;
	vector<string> val ;
	char * p = strtok(myVals, seperators) ;
	do {
		p = strtok(NULL, seperators) ;
		if (p) val.push_back(string(p)) ;
	} while (p && (col < NUM_COLS)) ;
	if (col < NUM_COLS)
		throw invalid_argument("Too few column values for AmortizeTable::setRow") ;
	data.push_back(val) ;
	rows(data.size()) ;
} // addRow() with string

void AmortizeTable::addRow(vector<string> & cells) {
	data.push_back(cells) ;
	rows(data.size()) ;
} // addRow() with string array

void AmortizeTable::addRow(PaymentData & payData) {
	vector<string> newRow ;
	setUpRow( newRow, payData ) ;
	data.push_back(newRow) ;
	rows(data.size()) ;
} // addRow() with string array


