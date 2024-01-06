#pragma once
#include "Sudoku.h"
#include <deque>

struct CellNum {
	unsigned short index;
	num_t num;
};	

template <int Rank>
class SudokuSolver
{
private:
	unsigned char mRank = Rank;
	unsigned char mBlkSize = int(round(sqrt(Rank)));
	unsigned short mTolCell = Rank * Rank;
	Sudoku<Rank> mSudoku;

	bool mIsSolved = false;
public:
	SudokuSolver(Sudoku<Rank> sudoku);
	~SudokuSolver();

	bool solve(PreProc preProc = PreProc.CalCadi);
	bool isSolved() { return mIsSolved; }
	Sudoku<Rank> getSudoku() { return mSudoku; }
private:
	bool backTracking(int index = 0);
	bool DFS(int index = 0);
};

