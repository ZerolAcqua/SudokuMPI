#include <stdio.h>
#include "Sudoku.h"


// give in one line
// 9 rank example: 003020600900305001001806400008102900700000008006708200002609500800203009005010300
// 9 rank example: 7..9...8..84.....9..381.2...3...9.....93784.....4...2...1.875..3.....84..7...4..6
// 16 rank example: .O.A.BJNL........FCPL.HDNOA.B...N.IGKCO.........DMBL....F....O......NA..CEJ..H.LCP..BD...NGM..EOK.E......ID..F......M.PEO..L........I.AL.HCJK.O.BL.K..NCED....I.FC.D..M..KIA.LPB..JI......L.H.FGLH..P..J.M...E..E...C.DF.AO......IAF.N.K..B...JH.N...MI.DLKH..B.

template <int Rank>
Sudoku<Rank>::Sudoku() = default;
template <int Rank>
Sudoku<Rank>::Sudoku(const char str[Rank * Rank])
{
	switch (mRank)
	{
	case 9:
		for (int i = 0; i < mTolCell; i++) {
			if (str[i] == '.' || str[i] == '0') {
				mData[i] = 0;
			}
			else {
				mData[i] = str[i] - '0';
				isKnown[i] = true;
			}
		}
		break;
	case 16:
	case 25:
		for (int i = 0; i < mTolCell; i++) {
			if (str[i] == '.' || str[i] == '0') {
				mData[i] = 0;
			}
			else {
				mData[i] = str[i] - 'A' + 1;
				isKnown[i] = true;
			}
		}
		break;
	default:
		throw "Rank not supported";
	}

}


template <int Rank>
void Sudoku<Rank>::printSudoku()
{
	int boardlen = mRank * 2 + 1;
	int blocklen = mBlkSize * 2 + 1;
	printf("#");
	for (int i = 0; i < boardlen - 2; i++) {
		printf("-");
	}
	printf("#\n");

	for (int i = 0; i < mRank; i++) {
		printf("|");
		for (int j = 0; j < mRank; j++) {
			if (mData[i * mRank + j] > 0) {
				switch (mRank)
				{
				case 9:
					printf("%d", mData[i * mRank + j]);
					break;
				case 16:
				case 25:
					printf("%c", mData[i * mRank + j] + 'A' - 1);
					break;
				default:
					break;
				}
			}
			else {
				printf(".");
			}
			if (j % mBlkSize == mBlkSize - 1)
				printf("|");
			else {
				printf(" ");
			}
		}
		printf("\n");
		if (i % mBlkSize == mBlkSize - 1) {
			if (i != mRank - 1) {
				printf("|");
				for (int j = 0; j < mBlkSize; j++) {
					for (int k = 0; k < blocklen - 2; k++) {
						printf("-");
					}
					if (j != mBlkSize - 1) {
						printf("*");
					}
					else {
						printf("|\n");
					}
				}
			}

		}
	}
	printf("#");
	for (int i = 0; i < boardlen - 2; i++) {
		printf("-");
	}
	printf("#\n");


}
template <int Rank>
int Sudoku<Rank>::rc2idx(int row, int col)
{
	return row * mRank + col;
}
template <int Rank>
std::string Sudoku<Rank>::toString()
{
	std::string str;
	switch (mRank)
	{
	case 9:
		for (int i = 0; i < mTolCell; i++) {
			if (mData[i] > 0) {
				str += mData[i] + '0';
			}
			else {
				str += '.';
			}
		}
		break;
	case 16:
	case 25:
		for (int i = 0; i < mTolCell; i++) {
			if (mData[i] > 0) {
				str += mData[i] + 'A' - 1;
			}
			else {
				str += '.';
			}
		}
		break;
	default:
		break;
	}
	return str;
}
template <int Rank>
int Sudoku<Rank>::unfillCellNum()
{
	int num = 0;
	for (int i = 0; i < mTolCell; i++) {
		num += !isKnown[i];
	}
	return num;
}

template <int Rank>
void Sudoku<Rank>::setCell(int index, num_t num)
{
	mData[index] = num;
}
template <int Rank>
void Sudoku<Rank>::setCell(int row, int col, num_t num)
{
	setCell(rc2idx(row, col), num);
}

template <int Rank>
void Sudoku<Rank>::setCadi(int index, cadi_t cadi)
{
	mCadi[index] = cadi;
}
template <int Rank>
void Sudoku<Rank>::setCadi(int row, int col, cadi_t cadi)
{
	setCadi(rc2idx(row, col), cadi);
}

template <int Rank>
void Sudoku<Rank>::setCellKnown(int index, bool known)
{
	isKnown[index] = known;
}
template <int Rank>
void Sudoku<Rank>::setCellKnown(int row, int col, bool known)
{
	setCellKnown(rc2idx(row, col), known);
}

template <int Rank>
num_t Sudoku<Rank>::getCell(int index)
{
	return mData[index];
}
template <int Rank>
num_t Sudoku<Rank>::getCell(int row, int col)
{
	return getCell(rc2idx(row, col));
}

template <int Rank>
cadi_t Sudoku<Rank>::getCadi(int index)
{
	return mCadi[index];
}
template <int Rank>
cadi_t Sudoku<Rank>::getCadi(int row, int col)
{
	return getCadi(rc2idx(row, col));
}

template <int Rank>
bool Sudoku<Rank>::isCellKnown(int index)
{
	return isKnown[index];
}
template <int Rank>
bool Sudoku<Rank>::isCellKnown(int row, int col)
{
	return isCellKnown(rc2idx(row, col));
}

template <int Rank>
void Sudoku<Rank>::removeCadi(int index, num_t num)
{
	mCadi[index] &= ~(1 << (num - 1));
}
template <int Rank>
void Sudoku<Rank>::removeCadi(int row, int col, num_t num)
{
	removeCadi(rc2idx(row, col), num);
}
template <int Rank>
void Sudoku<Rank>::addCadi(int index, num_t num)
{
	mCadi[index] |= (1 << (num - 1));
}
template <int Rank>
void Sudoku<Rank>::addCadi(int row, int col, num_t num)
{
	addCadi(rc2idx(row, col), num);
}

template <int Rank>
bool Sudoku<Rank>::isCadiExist(int index, num_t num)
{
	return (mCadi[index] & (1 << (num - 1))) != 0;
}
template <int Rank>
bool Sudoku<Rank>::isCadiExist(int row, int col, num_t num)
{
	return isCadiExist(rc2idx(row, col), num);
}

template <int Rank>
void Sudoku<Rank>::calcCadi(PreProc preProc)
{
	// reset all candidates
	for (int i = 0; i < mTolCell; i++)
		// set mRank bit to 1
		mCadi[i] = (1 << mRank) - 1;

	// remove candidates from known cells
	for (int i = 0; i < mTolCell; i++) {
		if (isKnown[i]) {
			setCadi(i, 0x0);
		}
	}
	switch (preProc)
	{
	case PreProc::None:
		break;
	case PreProc::CalCadi:
		// remove candidates from same row
		for (int i = 0; i < mTolCell; i++) {
			if (isKnown[i]) {
				int row = i / mRank;
				for (int j = 0; j < mRank; j++) {
					removeCadi(row, j, mData[i]);
				}
			}
		}

		// remove candidates from same col
		for (int i = 0; i < mTolCell; i++) {
			if (isKnown[i]) {
				int col = i % mRank;
				for (int j = 0; j < mRank; j++) {
					removeCadi(j, col, mData[i]);
				}
			}
		}

		// remove candidates from same block
		for (int i = 0; i < mTolCell; i++) {
			if (isKnown[i]) {
				int row = i / mRank;
				int col = i % mRank;
				int blockRow = row / mBlkSize;
				int blockCol = col / mBlkSize;
				for (int j = 0; j < mRank; j++) {
					int r = blockRow * mBlkSize + j / mBlkSize;
					int c = blockCol * mBlkSize + j % mBlkSize;
					removeCadi(r, c, mData[i]);
				}
			}
		}
		break;
	default:
		break;
	}
}

template <int Rank>
bool Sudoku<Rank>::validateCell(int index, num_t num) {
	int row = index / mRank;
	int col = index % mRank;
	int blockRow = row / mBlkSize;
	int blockCol = col / mBlkSize;

	// check row
	for (int i = 0; i < mRank; i++) {
		if (i != col && mData[row * mRank + i] == num) {
			return false;
		}
	}

	// check col
	for (int i = 0; i < mRank; i++) {
		if (i != row && mData[i * mRank + col] == num) {
			return false;
		}
	}

	// check block
	for (int i = 0; i < mRank; i++) {
		int r = blockRow * mBlkSize + i / mBlkSize;
		int c = blockCol * mBlkSize + i % mBlkSize;
		if (r != row && c != col && mData[r * mRank + c] == num) {
			return false;
		}
	}

	return true;
}

template <int Rank>
bool Sudoku<Rank>::validateCell(int row, int col, num_t num) {
	return validateCell(rc2idx(row, col), num);
}



template class Sudoku<9>;
template class Sudoku<16>;
template class Sudoku<25>;

