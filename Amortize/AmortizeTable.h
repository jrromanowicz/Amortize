#ifndef AmortizeTable_h
#define AmortizeTable_h

#include <FL/Fl_Table.H>
#include <vector>
#include <string>
#include <stdexcept>
#include "PaymentData.h"

#define NUM_COLS 5
using namespace std;

class AmortizeTable : public Fl_Table {
public :

	AmortizeTable(int x, int y, int w, int h, const char * label = 0) ;
//	AmortizeTable(int x, int y, int w, int h) ; // GEEK!
	virtual ~AmortizeTable() { }

	void addRow(string & val) ; // append a row to the table
	void addRow(vector<string> & cells) ; // append a row to the table
	void addRow(PaymentData & payData) ; // append a row to the table
	void setData(vector<string> & data) ; // fill the table with new data
	void setData(vector<PaymentData> & data) ; // fill the table with new data

   void cell(int row, int col, string & val) ; // set the contents of a cell
   string cell(int row, int col) ; // return a cell value

	Fl_Color columnColor(int colNum) { // get column color
		return (colNum >= 0 && colNum < NUM_COLS) ? colColor[colNum] : Fl_Color(0) ;
	}
	void columnColor(int colNum, Fl_Color color) {  // set column color
		if (colNum < NUM_COLS && colNum >= 0) colColor[colNum] = color ;
	}

protected:
	void draw_cell(TableContext context, int row, int col, int x, int y,
		 int w, int h) ;

private:

	const char * header[NUM_COLS] ;
	Fl_Color colColor[NUM_COLS] ;
	vector<vector<string> > data ;
	void init( void ) ;
} ; // class AmortizeTable

#endif // ndef AmortizeTable_h

