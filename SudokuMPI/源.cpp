#include <stdio.h>

#include "mpi.h"
#include "Sudoku.h"
#include "SudokuSolver.h"
#include "queue"


#define SEARCH_STEP 100000

int numprocs = 0;
int rank = 0;


//#define SUDOKU_RANK 16
// 1min
//const char sudokuStr[] = ".O.A.BJNL........FCPL.HDNOA.B...N.IGKCO.........DMBL....F....O......NAKGCEJ..H.LCP..BD...NGM..EOK.E......ID..F......M.PEO..L........I.AL.HCJK.O.BL.K..NCED....I.FC.D..M..KIA.LPB..JI......L.H.FGLH..P..J.M...E..E...C.DF.AO......IAF.N.K..B...JH.N...MI.DLKH..B.";
// 5min
//const char sudokuStr[] = ".O.A.BJNL........FCPL.HDNOA.B...N.IGKCO.........DMBL....F....O......NA..CEJ..H.LCP..BD...NGM..EOK.E......ID..F......M.PEO..L........I.AL.HCJK.O.BL.K..NCED....I.FC.D..M..KIA.LPB..JI......L.H.FGLH..P..J.M...E..E...C.DF.AO......IAF.N.K..B...JH.N...MI.DLKH..B.";
// 15min
//const char sudokuStr[] = "...A.BJNL........F.P..HDNOA.B...N.IGKCO.........DMBL....F....O......NA.GCEJ..H.LCP..BD...NGM..EOK.E......ID..F......M.PEO..L........I.AL.HCJK.O.BL.K..NCED....I.FC.D..M..KIA.LPB..JI......L.H.FGLH..P..J.M...E..E...C.DF.AO......IAF.N.K..B...JH.N...MI.DLKH..B.";


#define SUDOKU_RANK 25
// 5min
//const char sudokuStr[] = "...HO.UFQ......XS...L...B...CK.PBDMGYHQ.AOTRVFSIJE...DGN......A..H.C...K.VX..QFBWA.LK.R..DJEPI.MHGOCJ.I.M.HO..X...F..KL..RD.TFCB..OYANPWED.IVXRH.SLMGQ........I.LG.F..NDBQPECKJ...L.F.C.D.N.J.G.AOEIUBXH..EN..G..B.H...C.IYPOFADRIDG..HE.JQCABR..LF.STVNWYR.......W.BJ.E..C.UA.....CWUBETFQOA.D.......G.I..MD.F.AKBRYEI.XGHQMLWOJPSC.HIM..GSUXJAT.WCPFBNKVDQEO.....P..CHFUYO.DR.EI.....MBSPTE.GHVJQNDLOIYCXUARFKGL......ANTW.M...QSF.OYIPKFJQDIC.BYE..H.RTMAUGWXNVAECWIUQSPO.FKXRNHGVLBMJTDYORVNMDXF.UCGIAKBWPJHQELSBKAGYJOHMLRS...F.EDCQXVPIQHLMUB.YGFDXIAESPO..KCTRWOJVIFCNDTXP.WYQLAUKREBH.GE....QIPKW......GXT...FUAN.PXWAREUSHKFCGIYVQBDJOM.";
// 15min
//const char sudokuStr[] = "W.THO.UFQ......XS...L...B..NCK.PB.M...Q..O.R.........DGN......A..H.C...K.VX...F.W.......S.J...Y.....J.I.M.HOS.X..VF..KL..RD.T.C..J.Y..P..DUIV..HT.L.GQTYHARSX.I.....V.N.B...CK.P.W.V...RDQ..J.G..OE...X.U.E.SL....KH.T...I.PO...R..GO..E.JQC....U.F.S.VN..R.......W.BJ.E.TC.UA......WUBE.F.O.S.LPNYVJXGRIKHMDNFTAKBRYEIVXGHQMLWOJPSCUHIMYLGSUXJATRWCPFBNKVDQEOXGKJQPLVCHFUYOMDRSEIATWBNMBSPTEWGHVJQNDLOIYCXUARFKGLXUHRKJANTWVMBEDQSFCOYIPKFJQDICLBYEOPHSRTMAUGWXNVAECWIUQSPOYFKXRNHGVLBMJTDYORVNMDXFTUCGIAKBWPJHQELSBKAGYJOHMLRSTNUFWEDCQXVPIQHLMUBVYGFDXIAESPOJNKCTRWOJVIFCNDTXPMWYQLAUKREBHSGESDRCQIPKWVLJBOMGXTHYNFUANTPXWAREUSHKFCGIYVQBDJOM.";
// 28min
const char sudokuStr[] = "W.THO.UFQ......XS...L...B..NCK.PB.M...Q..O.R.........DGN......A..H.C...K.VX...F.W.......S.J...Y.....J.I.M.HOS.X..VF..KL..RD.T.C..J.Y..P..DUIV..HT.L.GQTYHARSX.I.....V.N.B...CK.P.W.V...RDQ..J.G..OE...X.U.E.SL....KH.T...I.PO...R..GO..E.JQC....U.F.S.VN..R.......W.BJ.E.TC.UA......WUBE.F.O.S.LPNYVJXGRIKHMD.FTAKBRYEI.XGHQM.WOJPSCUHIMYLGSUXJATRWCPFBNKVDQEOXGKJQPLVCHFUYOMDRSEIATWBNMBSPTEWGHVJQNDLOIYCXUARFK.LXU.RKJANTWVMBEDQSFCOYIPKFJQDICLBYEOPHSRTMAUGW.NVAECWIUQSPOYFKXRNHGVLBMJTDYORVNMDXFT.CGI.KBWPJHQELSBKAGYJOHMLRSTNUFWEDCQ.VPIQHLMUBVYGFDXIAESPOJNKCTRWOJVIFCNDTXPMWYQLAUKREBHSGESDRCQIPKWVLJBOMGXTHYNFUANTPXWAREUSHKFCGIYVQBDJOM.";
char sudokuMsg[SUDOKU_RANK * SUDOKU_RANK] = { 0 };

void serial();
void parrallel();
void master();
void slave();


int main(int argc, char* argv[])
{
	// initialize MPI
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(
		MPI_COMM_WORLD, // MPI_Comm comm,
		&rank           // int* size
	);
	MPI_Comm_size(
		MPI_COMM_WORLD, // MPI_Comm comm
		&numprocs       // int* size
	);

	MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */
	double start = MPI_Wtime();


	if (numprocs == 1) { 	// Serial
		serial();
	}
	else {		// Parallel
		parrallel();
	}

	MPI_Barrier(MPI_COMM_WORLD); /* IMPORTANT */
	double end = MPI_Wtime();

	if (rank == 0) {
		printf("Finish time: %f\n", end - start);
		fflush(stdout);
	}

	MPI_Finalize();
}


enum Tag {
	Null = 0,
	NewTask = 1,
	Solved = 2,
	Unsolved = 3,
	Terminate = 4,
};

void master() {
	// print rank number
	printf("Master Process %d of %d is running\n", rank, numprocs);
	fflush(stdout);
	std::queue<int> freeProcQue;

	double start = MPI_Wtime();

	Sudoku<SUDOKU_RANK> sudoku(sudokuStr);
	sudoku.printSudoku();
	fflush(stdout);

	// partition sudoku task
	double start2 = MPI_Wtime();
	SudokuSolver<SUDOKU_RANK> solver(sudoku);
	std::queue<std::string> queStr = solver.splitSubSum(numprocs * 10);
	double end2 = MPI_Wtime();

	printf("[master %d] Partitioned %d tasks in %f\n", rank, queStr.size(), end2 - start2);

	// assign task to slaves
	for (int i = 1; i < numprocs; i++) {
		std::string str = queStr.front();
		queStr.pop();
		printf("[master %d] Assign task to slave %d\n", rank, i);
		printf("\t> task: %s\n", str.substr(0, str.find('.')).c_str());
		fflush(stdout);

		MPI_Send(
			str.data(), // const void* buf
			SUDOKU_RANK * SUDOKU_RANK, // int count
			MPI_CHAR, // MPI_Datatype datatype
			i, // int dest
			Tag::NewTask, // int tag
			MPI_COMM_WORLD // MPI_Comm comm
		);
	}

	bool isfinished = false;
	bool isSolved = false;
	MPI_Status status;
	Tag tag = Tag::Null;
	int freeProcNum = 0;

	printf("[master %d] Enter loop\n", rank);
	while (!isfinished) {
		// receive result from slaves
		MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

		tag = (Tag)status.MPI_TAG;
		switch (tag) {
		case Tag::Solved:
			printf("[master %d] Solved!\n", rank);
			fflush(stdout);
			// receive solved result
			MPI_Recv(
				sudokuMsg, // void* buf
				SUDOKU_RANK * SUDOKU_RANK, // int count
				MPI_CHAR, // MPI_Datatype datatype
				status.MPI_SOURCE, // int source
				Tag::Solved, // int tag
				MPI_COMM_WORLD, // MPI_Comm comm
				&status // MPI_Status* status
			);
			isfinished = true;
			isSolved = true;
			break;
		case Tag::Unsolved:
			// receive unsolved result
			MPI_Recv(
				nullptr, // void* buf
				0, // int count
				MPI_CHAR, // MPI_Datatype datatype
				status.MPI_SOURCE, // int source
				Tag::Unsolved, // int tag
				MPI_COMM_WORLD, // MPI_Comm comm
				&status // MPI_Status* status
			);

			// assign new task
			if (!queStr.empty()) {
				std::string str = queStr.front();
				queStr.pop();
				printf("[master %d] Assign task to slave %d\n", rank, status.MPI_SOURCE);
				printf("\t> task: %s\n", str.substr(0, str.find('.')).c_str());
				fflush(stdout);
				MPI_Send(
					str.data(), // const void* buf
					SUDOKU_RANK * SUDOKU_RANK, // int count
					MPI_CHAR, // MPI_Datatype datatype
					status.MPI_SOURCE, // int dest
					Tag::NewTask, // int tag
					MPI_COMM_WORLD // MPI_Comm comm
				);
			}
			else {
				// no more task
				printf("[master %d] No more task for slave %d\n", rank, status.MPI_SOURCE);
				fflush(stdout);
				freeProcQue.push(status.MPI_SOURCE);
				if (freeProcQue.size() == numprocs - 1)
					isfinished = true;
			}
			break;

		}

	}

	double end = MPI_Wtime();
	Sudoku<SUDOKU_RANK> solvedSudoku(sudokuMsg);
	printf("[master %d] finish time: %f\n", rank, end - start);
	fflush(stdout);

	if (isSolved)
		solvedSudoku.printSudoku();
	else
		printf("[master %d] Failed!\n", rank);

	// teminate slaves
	for (int i = 1; i < numprocs; i++) {
		MPI_Send(
			nullptr, // const void* buf
			0, // int count
			MPI_CHAR, // MPI_Datatype datatype
			i, // int dest
			Tag::Terminate, // int tag
			MPI_COMM_WORLD // MPI_Comm comm
		);
	}

	printf("[master %d] Terminate\n", rank);
}

void slave() {
	// print rank number
	printf("Slave Process %d of %d is running\n", rank, numprocs);
	fflush(stdout);

	// receive task from master
	bool unfinished = true;
	MPI_Status status;
	Tag tag = Tag::Null;

	printf("[slave %d] Enter loop\n", rank);
	fflush(stdout);
	while (unfinished)
	{
		// receive result from slaves
		MPI_Probe(0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		tag = (Tag)status.MPI_TAG;
		switch (tag)
		{
		case NewTask:
			// receive task
			MPI_Recv(
				sudokuMsg, // void* buf
				SUDOKU_RANK * SUDOKU_RANK, // int count
				MPI_CHAR, // MPI_Datatype datatype
				0, // int source
				Tag::NewTask, // int tag
				MPI_COMM_WORLD, // MPI_Comm comm
				&status // MPI_Status* status
			);
			break;
		case Terminate:
			// receive terminate signal
			MPI_Recv(
				nullptr, // void* buf
				0, // int count
				MPI_CHAR, // MPI_Datatype datatype
				0, // int source
				Tag::Terminate, // int tag
				MPI_COMM_WORLD, // MPI_Comm comm
				&status // MPI_Status* status
			);
			printf("[slave %d] Terminate\n", rank);
			fflush(stdout);
			unfinished = false;
			continue;
			break;
		default:
			break;
		}

		// process
		Sudoku<SUDOKU_RANK> sudoku(sudokuMsg);
		sudoku.calcCadi();
		SudokuSolver<SUDOKU_RANK> solver(sudoku);
		solver.solve();


		printf("[slave %d] Finish task\n", rank);
		fflush(stdout);

		// finish task
		if (solver.isSolved()) {
			// send solved result
			MPI_Send(
				solver.getSudoku().toString().data(), // const void* buf
				SUDOKU_RANK * SUDOKU_RANK, // int count
				MPI_CHAR, // MPI_Datatype datatype
				0, // int dest
				Tag::Solved, // int tag
				MPI_COMM_WORLD // MPI_Comm comm
			);
			break;
		}
		else {
			// send unsolved result
			MPI_Send(
				nullptr, // const void* buf
				0, // int count
				MPI_CHAR, // MPI_Datatype datatype
				0, // int dest
				Tag::Unsolved, // int tag
				MPI_COMM_WORLD // MPI_Comm comm
			);
		}
	}
}

void parrallel()
{
	if (rank == 0) {
		printf("Parrallel\n");
		master();
	}
	else {
		slave();
	}

}


void serial()
{
	printf("Serial\n");
	Sudoku<SUDOKU_RANK> sudoku(sudokuStr);
	sudoku.printSudoku();

	double start = MPI_Wtime();
	sudoku.calcCadi(PreProc::CalCadi);
	double end = MPI_Wtime();
	printf("CalcCadi time: %f\n", end - start);
	// flush the output buffer
	fflush(stdout);

	SudokuSolver<SUDOKU_RANK> solver(sudoku);

	//solver.solveN();
	solver.solve();
	if (solver.isSolved()) {
		printf("Solved!\n");
		solver.getSudoku().printSudoku();
	}
	else {
		printf("Failed!\n");
	}
}