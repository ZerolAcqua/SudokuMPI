#pragma once
#include "Sudoku.h"

class SudokuSolver
{
private:
	Sudoku mSudoku;
	bool mIsSolved = false;
public:
	SudokuSolver(Sudoku sudoku);
	~SudokuSolver();
	bool solve();
	bool isSolved() { return mIsSolved; }
	Sudoku getSudoku() { return mSudoku; }
private:
	bool backTracking(int index = 0);

};

