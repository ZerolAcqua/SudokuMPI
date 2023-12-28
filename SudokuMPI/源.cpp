#include <stdio.h>

#include "mpi.h"
#include "Sudoku.h"
#include "SudokuSolver.h"


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	// hard one
	Sudoku hardSudoku("7..9...8..84.....9..381.2...3...9.....93784.....4...2...1.875..3.....84..7...4..6");
	hardSudoku.printSudoku();
	// easy one
	Sudoku easySudoku(".1...849.8...7.....57.4.8..4......2....615....7......5..4.6.93.....5...1.312...5.");
	//easySudoku.printSudoku();
	// error one
	Sudoku errorSudoku("7..9...8..84.....9..381.2...3...9.....93784.....4...2...1.875..3.....84..7...4.16");
	hardSudoku.printSudoku();

	//SudokuSolver solver(easySudoku);
	SudokuSolver solver(hardSudoku);


	double t1 = MPI_Wtime();
	solver.solve();
	double t2 = MPI_Wtime();
	if (solver.isSolved()) {
		printf("Solved!\n");
		solver.getSudoku().printSudoku();
	}
	else {
		printf("Failed!\n");

	}
	printf("Time: %f\n", t2 - t1);
}