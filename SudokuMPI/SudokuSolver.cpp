#include "SudokuSolver.h"

template <int Rank>
SudokuSolver<Rank>::SudokuSolver(Sudoku<Rank> sudoku) {
	mSudoku = sudoku;
}

template <int Rank>
SudokuSolver<Rank>::~SudokuSolver() = default;

template <int Rank>
bool SudokuSolver<Rank>::solve(PreProc preProc)
{
	mSudoku.calcCadi(preProc);
	mIsSolved = backTracking();
	return mIsSolved;
}

template <int Rank>
bool SudokuSolver<Rank>::backTracking(int index)
{

	int curIdx = index;
	// find the first unknown cell
	for (; curIdx < mTolCell; curIdx++) {
		if (!mSudoku.isCellKnown(curIdx)) {
			break;
		}
	}

	// if all cells are known, then return true
	if (curIdx == mTolCell) {
		return true;
	}

	// try all candidates
	for (int i = 1; i <= mRank; i++) {
		if (mSudoku.isCadiExist(curIdx, i)) {
			// try this candidate
			if (mSudoku.validateCell(curIdx, i)) {
				// if this candidate is valid, then try next cell
				mSudoku.setCell(curIdx, i);
				mSudoku.setCellKnown(curIdx);
				if (backTracking(curIdx + 1)) {
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

template class SudokuSolver<9>;
template class SudokuSolver<16>;
template class SudokuSolver<25>;
