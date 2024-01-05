#include <stdio.h>

#include "mpi.h"
#include "Sudoku.h"
#include "SudokuSolver.h"


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	Sudoku<16> sudoku16(".O.A.BJNL........FCPL.HDNOA.B...N.IGKCO.........DMBL....F....O......NA..CEJ..H.LCP..BD...NGM..EOK.E......ID..F......M.PEO..L........I.AL.HCJK.O.BL.K..NCED....I.FC.D..M..KIA.LPB..JI......L.H.FGLH..P..J.M...E..E...C.DF.AO......IAF.N.K..B...JH.N...MI.DLKH..B.");
	sudoku16.printSudoku();
	SudokuSolver<16> solver16(sudoku16);
	double t1 = MPI_Wtime();
	solver16.solve(PreProc::CalCadi);
	double t2 = MPI_Wtime();
	if (solver16.isSolved()) {
		printf("Solved!\n");
		solver16.getSudoku().printSudoku();
	}
	else {
		printf("Failed!\n");
	}	
	printf("Time: %f\n", t2 - t1);
}