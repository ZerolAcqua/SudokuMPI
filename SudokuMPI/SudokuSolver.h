#pragma once
#include "Sudoku.h"
#include <queue>
#include <deque>
#include <string>

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
	std::deque<Sudoku<Rank>> mDqueSudoku;

	bool mIsFinished = false;
	bool mIsSolved = false;

public:
	SudokuSolver(Sudoku<Rank> sudoku);
	~SudokuSolver();

	bool solve(PreProc preProc = PreProc::CalCadi);
	bool solveN(int searchNum = -1);
	bool isSolved() { return mIsSolved; }
	Sudoku<Rank> getSudoku() { return mSudoku; }
	std::queue<std::string> splitSubSum(int subNum);
private:
	bool backTracking(int index = 0);
	bool DFS(int index = 0);
	bool DFSN(int searchNum);
};

