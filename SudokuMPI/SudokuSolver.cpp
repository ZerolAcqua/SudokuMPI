#include "SudokuSolver.h"
#include <deque>

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
	//mIsSolved = backTracking();
	mIsSolved = DFS();
	return mIsSolved;
}

template <int Rank>
bool SudokuSolver<Rank>::backTracking(int index)
{

	unsigned short curIdx = index;
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
	for (num_t i = 1; i <= mRank; i++) {
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

template <int Rank>
bool SudokuSolver<Rank>::DFS(int index)
{
	std::deque<CellNum> dqueCellnum;
	unsigned short curIdx = index;
	bool needRestore = false;
	bool isKnownTmp[Rank * Rank] = { false };
	for (unsigned short i = 0; i < mTolCell; i++) {
		isKnownTmp[i] = mSudoku.isKnown[i];
	}

	// find the first unknown cell
	for (; curIdx < mTolCell; curIdx++) {
		if (!isKnownTmp[curIdx]) {
			// push back all candidates
			for (num_t i = 1; i <= mRank; i++) {
				if (mSudoku.isCadiExist(curIdx, i)) {
					dqueCellnum.push_back({ curIdx, i });
				}
			}
			break;
		}
	}

	// if all cells are known, then return true
	if (curIdx == mTolCell) {
		return true;
	}

	// process tasks in stack
	while (!dqueCellnum.empty()) {
		CellNum cellnum = dqueCellnum.back();
		dqueCellnum.pop_back();
		// restore known and num between curIdx and maxIdx
		if (needRestore) {
			for (unsigned short i = cellnum.index; i <= curIdx; i++) {
				if (!mSudoku.isCellKnown(i)) {
					isKnownTmp[i] = false;
					mSudoku.setCell(i, 0);
				}

			}
			needRestore = false;
			curIdx = cellnum.index;
		}

		// try this candidate
		if (mSudoku.validateCell(cellnum.index, cellnum.num)) {
			// if this candidate is valid, push back all candidates in next unknown cell
			mSudoku.setCell(cellnum.index, cellnum.num);
			isKnownTmp[cellnum.index] = true;
			for (curIdx = cellnum.index + 1; curIdx < mTolCell; curIdx++) {
				if (!isKnownTmp[curIdx]) {
					for (num_t i = 1; i <= mRank; i++) {
						if (mSudoku.isCadiExist(curIdx, i)) {
							dqueCellnum.push_back({ curIdx, i });
						}
					}
					break;
				}
			}
			if (curIdx == mTolCell) {
				return true;
			}
		}
		else {
			// if this candidate is invalid, then restore sudoku state
			needRestore = true;
			curIdx = cellnum.index;
		}
	}
	return false;
}

template class SudokuSolver<9>;
template class SudokuSolver<16>;
template class SudokuSolver<25>;
