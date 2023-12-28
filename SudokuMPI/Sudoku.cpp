#include <stdio.h>
#include "Sudoku.h"




Sudoku::Sudoku() = default;

// give in one line
// example: 003020600900305001001806400008102900700000008006708200002609500800203009005010300
// example: 7..9...8..84.....9..381.2...3...9.....93784.....4...2...1.875..3.....84..7...4..6
Sudoku::Sudoku(const char* str)
{
	for (int i = 0; i < 81; i++) {
		if (str[i] == '.' || str[i] == '0') {
			mData[i] = 0;
		}
		else {
			mData[i] = str[i] - '0';
			isKnown[i] = true;
		}
	}
}

void Sudoku::printSudoku()
{
	printf("#-----------------#\n");
	for (int i = 0; i < 9; i++) {
		printf("|");
		for (int j = 0; j < 9; j++) {
			if (mData[i * 9 + j] > 0) {
				printf("%d", mData[i * 9 + j]);
			}
			else {
				printf(".");
			}
			if (j % 3 == 2)
				printf("|");
			else {
				printf(" ");
			}
		}
		printf("\n");
		if (i == 2 || i == 5) {
			printf("|-----*-----*-----|\n");
		}
	}
	printf("#-----------------#\n");
}
int Sudoku::rc2idx(int row, int col)
{
	return row * 9 + col;
}

void Sudoku::setCell(int index, num_t num)
{
	mData[index] = num;
}
void Sudoku::setCell(int row, int col, num_t num)
{
	setCell(rc2idx(row, col), num);
}
void Sudoku::setCadi(int index, cadi_t cadi)
{
	mCadi[index] = cadi;
}
void Sudoku::setCadi(int row, int col, cadi_t cadi)
{
	setCadi(rc2idx(row, col), cadi);
}
void Sudoku::setCellKnown(int index, bool known)
{
	isKnown[index] = known;
}
void Sudoku::setCellKnown(int row, int col, bool known)
{
	setCellKnown(rc2idx(row, col), known);
}

num_t Sudoku::getCell(int index)
{
	return mData[index];
}
num_t Sudoku::getCell(int row, int col)
{
	return getCell(rc2idx(row, col));
}
cadi_t Sudoku::getCadi(int index)
{
	return mCadi[index];
}
cadi_t Sudoku::getCadi(int row, int col)
{
	return getCadi(rc2idx(row, col));
}
bool Sudoku::isCellKnown(int index)
{
	return isKnown[index];
}
bool Sudoku::isCellKnown(int row, int col)
{
	return isCellKnown(rc2idx(row, col));
}

void Sudoku::removeCadi(int index, num_t num)
{
	mCadi[index] &= ~(1 << (num - 1));
}
void Sudoku::removeCadi(int row, int col, num_t num)
{
	removeCadi(rc2idx(row, col), num);
}
void Sudoku::addCadi(int index, num_t num)
{
	mCadi[index] |= (1 << (num - 1));
}
void Sudoku::addCadi(int row, int col, num_t num)
{
	addCadi(rc2idx(row, col), num);
}
bool Sudoku::isCadiExist(int index, num_t num)
{
	return (mCadi[index] & (1 << (num - 1))) != 0;
}
bool Sudoku::isCadiExist(int row, int col, num_t num)
{
	return isCadiExist(rc2idx(row, col), num);
}

void Sudoku::calcCadi()
{
	// reset all candidates
	for (int i = 0; i < 81; i++)
		mCadi[i] = 0x1ff;

	// remove candidates from known cells
	for (int i = 0; i < 81; i++) {
		if (isKnown[i]) {
			setCadi(i, 0x0);
		}
	}

	// remove candidates from same row
	for (int i = 0; i < 81; i++) {
		if (isKnown[i]) {
			int row = i / 9;
			for (int j = 0; j < 9; j++) {
				removeCadi(row, j, mData[i]);
			}
		}
	}

	// remove candidates from same col
	for (int i = 0; i < 81; i++) {
		if (isKnown[i]) {
			int col = i % 9;
			for (int j = 0; j < 9; j++) {
				removeCadi(j, col, mData[i]);
			}
		}
	}

	// remove candidates from same block
	for (int i = 0; i < 81; i++) {
		if (isKnown[i]) {
			int row = i / 9;
			int col = i % 9;
			int blockRow = row / 3;
			int blockCol = col / 3;
			for (int j = 0; j < 9; j++) {
				int r = blockRow * 3 + j / 3;
				int c = blockCol * 3 + j % 3;
				removeCadi(r, c, mData[i]);
			}
		}
	}
}

bool Sudoku::validateCell(int index, num_t num) {
	int row = index / 9;
	int col = index % 9;
	int blockRow = row / 3;
	int blockCol = col / 3;

	// check row
	for (int i = 0; i < 9; i++) {
		if (i != col && mData[row * 9 + i] == num) {
			return false;
		}
	}

	// check col
	for (int i = 0; i < 9; i++) {
		if (i != row && mData[i * 9 + col] == num) {
			return false;
		}
	}

	// check block
	for (int i = 0; i < 9; i++) {
		int r = blockRow * 3 + i / 3;
		int c = blockCol * 3 + i % 3;
		if (r != row && c != col && mData[r * 9 + c] == num) {
			return false;
		}
	}

	return true;
}
bool Sudoku::validateCell(int row, int col, num_t num){
	return validateCell(rc2idx(row, col), num);
}
