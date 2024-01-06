#include <stdio.h>

#include "mpi.h"
#include "Sudoku.h"
#include "SudokuSolver.h"

int numprocs = 0;
char sudokuStr[] = ".O.A.BJNL........FCPL.HDNOA.B...N.IGKCO.........DMBL....F....O......NA..CEJ..H.LCP..BD...NGM..EOK.E......ID..F......M.PEO..L........I.AL.HCJK.O.BL.K..NCED....I.FC.D..M..KIA.LPB..JI......L.H.FGLH..P..J.M...E..E...C.DF.AO......IAF.N.K..B...JH.N...MI.DLKH..B.";

void serial();
void parrallel();
void master();
void slave();


int main(int argc, char* argv[])
{
	// initialize MPI
	MPI_Init(&argc, &argv);

	MPI_Comm_size(
		MPI_COMM_WORLD, // MPI_Comm comm
		&numprocs       // int* size
	);

	if (numprocs == 1) { 	// Serial
		serial();
	}
	else {		// Parallel
		parrallel();
	}

	MPI_Finalize();
}



void master()
{

}

void slave()
{

}

void parrallel()
{
	int rank = 0; // rank number
	MPI_Comm_rank(
		MPI_COMM_WORLD, // MPI_Comm comm,
		&rank           // int* size
	);

	// print rank number
	printf("%d of %d is running\n", rank, numprocs);

	if (rank == 0) {
		master();
	}
	else {
		slave();
	}
}


void serial()
{
	Sudoku<16> sudoku16(sudokuStr);
	sudoku16.printSudoku();
	// flush the output buffer
	fflush(stdout);

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