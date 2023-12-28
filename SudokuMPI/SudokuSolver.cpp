#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(Sudoku sudoku) {
	mSudoku = sudoku;
}

SudokuSolver::~SudokuSolver() = default;

bool SudokuSolver::solve()
{
	mSudoku.calcCadi();
	mIsSolved = backTracking();
	return mIsSolved;
}

bool SudokuSolver::backTracking(int index)
{

	int curIdx = index;
	// find the first unknown cell
	for (; curIdx < 81; curIdx++) {
		if (!mSudoku.isCellKnown(curIdx)) {
			break;
		}
	}
	
	// if all cells are known, then return true
	if (curIdx == 81) {
		return true;
	}

	// try all candidates
	for (int i = 1; i <= 9; i++) {
		if (mSudoku.isCadiExist(curIdx, i)) {
			// try this candidate
			if (mSudoku.validateCell(curIdx, i)) {
				// if this candidate is valid, then try next cell
				mSudoku.setCell(curIdx, i);
				mSudoku.setCellKnown(curIdx);
				if (backTracking(curIdx+1)) {
					return true;
				}
				// if this candidate is invalid, then try next candidate
				mSudoku.setCell(curIdx, 0);
				mSudoku.setCellKnown(curIdx, false);
			}
		}
	}

	return false;
}
