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
	mIsSolved = backTracking();
	mIsFinished = true;
	return mIsFinished;
}
// don't calculate cadi automatically
// make sure that cadi is already calculated
template <int Rank>
bool SudokuSolver<Rank>::solveN(int searchNum)
{
	mIsFinished = DFSN(searchNum);
	return mIsFinished;
}

template <int Rank>
std::queue<std::string> SudokuSolver<Rank>::splitSubSum(int subNum)
{
	if (subNum == 1) {
		std::queue<std::string> queStr;
		queStr.push(mSudoku.toString());
		return queStr;
	}

	std::queue<Sudoku<Rank>> queSudoku;
	mSudoku.calcCadi(PreProc::CalCadi);
	queSudoku.push(mSudoku);

	unsigned short curIdx = 0;
	unsigned short lastIdx = 0;

	// BFS to find enough sub sudoku
	while (true) {
		Sudoku<Rank> sudoku = queSudoku.front();

		// find the first unknown cell
		for (; curIdx < mTolCell; curIdx++) {
			if (!sudoku.isCellKnown(curIdx)) {
				break;
			}
		}
		if (lastIdx != curIdx && queSudoku.size() >= subNum) {
			break;
		}

		queSudoku.pop();
		lastIdx = curIdx;

		// try all candidates
		for (num_t i = 1; i <= mRank; i++) {
			if (sudoku.isCadiExist(curIdx, i)) {
				// try this candidate
				if (sudoku.validateCell(curIdx, i)) {
					// if this candidate is valid, then try next cell
					sudoku.setCell(curIdx, i);
					sudoku.setCellKnown(curIdx);
					queSudoku.push(sudoku);
					// restore sudoku state
					sudoku.setCell(curIdx, 0);
					sudoku.setCellKnown(curIdx, false);
				}
			}
		}
	}

	std::queue<std::string> queStr;
	while (!queSudoku.empty()) {
		queStr.push(queSudoku.front().toString());
		queSudoku.pop();
	}
	return queStr;
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
		mIsSolved = true;
		mIsFinished = true;
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
template <int Rank>
bool SudokuSolver<Rank>::DFSN(int  searchNum) {
	if (mIsFinished)
		return true;
	if (mDqueSudoku.empty())
		mDqueSudoku.push_back(mSudoku);
	int curNum = 0;
	int index = 0;

	while (!mDqueSudoku.empty()) {
		Sudoku<Rank> sudoku = mDqueSudoku.back();
		mDqueSudoku.pop_back();

		// find the first unknown cell
		for (index = 0; index < mTolCell; index++) {
			if (!sudoku.isCellKnown(index)) {
				break;
			}
		}
		if (index == mTolCell) {
			mSudoku = sudoku;
			mIsFinished = true;
			mIsSolved = true;
			return true;
		}
		// try all candidates
		for (num_t i = 1; i <= mRank; i++) {
			if (sudoku.isCadiExist(index, i)) {
				// try this candidate
				if (sudoku.validateCell(index, i)) {
					// if this candidate is valid, then try next cell
					sudoku.setCell(index, i);
					sudoku.setCellKnown(index);
					mDqueSudoku.push_back(sudoku);
					curNum++;

					// restore sudoku state
					sudoku.setCell(index, 0);
					sudoku.setCellKnown(index, false);
				}
			}
		}
		if (searchNum > 0 && curNum >= searchNum) {
			return false;
		}
	}

	mIsFinished = true;
	mIsSolved = false;
	return true;

}





template class SudokuSolver<9>;
template class SudokuSolver<16>;
template class SudokuSolver<25>;
