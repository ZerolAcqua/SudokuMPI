#pragma once

typedef unsigned char num_t;
typedef unsigned short cadi_t;

class Sudoku
{
private:
	//  #-----------------#
	//  |1 2 3|4 5 6|7 8 9|
	//  |4 5 6|7 8 9|1 2 3|
	//	|7 8 9|1 2 3|4 5 6|
	// 	|-----*-----*-----| 
	//	|2 3 4|5 6 7|8 9 1|
	//	|5 6 7|8 9 1|2 3 4|
	//	|8 9 1|2 3 4|5 6 7|
	// 	|-----*-----*-----|
	//	|3 4 5|6 7 8|9 1 2|
	//	|6 7 8|9 1 2|3 4 5|
	//	|9 1 2|3 4 5|6 7 8|
	//  #-----------------#
	//  left to right, then top to bottom
	num_t mData[81] = { 0 };    // 0 for empty
	cadi_t mCadi[81] = { 0 };			 // candidates, one cell has 9 bit for 9 numbers
	bool isKnown[81] = { 0 };
public:
	Sudoku();
	Sudoku(const char* str);
	~Sudoku() = default;

	void printSudoku();
	int rc2idx(int row, int col);

	void setCell(int index, num_t num);
	void setCell(int row, int col, num_t num);
	void setCadi(int index, cadi_t cadi);
	void setCadi(int row, int col, cadi_t cadi);
	void setCellKnown(int index, bool known = true);
	void setCellKnown(int row, int col, bool known = true);

	num_t getCell(int index);
	num_t getCell(int row, int col);
	cadi_t getCadi(int index);
	cadi_t getCadi(int row, int col);
	bool isCellKnown(int index);
	bool isCellKnown(int row, int col);

	// no validation check
	void removeCadi(int index, num_t num);
	void removeCadi(int row, int col, num_t num);
	void addCadi(int index, num_t num);
	void addCadi(int row, int col, num_t num);
	bool isCadiExist(int index, num_t num);
	bool isCadiExist(int row, int col, num_t num);

	// calculate candidates
	void calcCadi();
	bool validateCell(int index, num_t num);
	bool validateCell(int row, int col, num_t num);


};

