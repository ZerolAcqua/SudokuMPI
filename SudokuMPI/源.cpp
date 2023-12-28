#include <stdio.h>

#include "mpi.h"
#include "Sudoku.h"
#include "SudokuSolver.h"


int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	//// hard one
	//Sudoku hardSudoku("7..9...8..84.....9..381.2...3...9.....93784.....4...2...1.875..3.....84..7...4..6");
	//hardSudoku.printSudoku();
	//// easy one
	//Sudoku easySudoku(".1...849.8...7.....57.4.8..4......2....615....7......5..4.6.93.....5...1.312...5.");
	////easySudoku.printSudoku();
	//// error one
	//Sudoku errorSudoku("7..9...8..84.....9..381.2...3...9.....93784.....4...2...1.875..3.....84..7...4.16");
	//hardSudoku.printSudoku();

	//SudokuSolver solver(easySudoku);

	//Sudoku<9> sudoku9("7..9...8..84.....9..381.2...3...9.....93784.....4...2...1.875..3.....84..7...4..6");
	//sudoku9.printSudoku();
	//SudokuSolver<9> solver9(sudoku9);
	//double t1 = MPI_Wtime();
	//solver9.solve();
	//double t2 = MPI_Wtime();
	//if (solver9.isSolved()) {
	//	printf("Solved!\n");
	//	solver9.getSudoku().printSudoku();
	//}
	//else {
	//	printf("Failed!\n");
	//}
	//printf("Time: %f\n", t2 - t1);

	//Sudoku<16> sudoku16(".O.A.BJNL........FCPL.HDNOA.B...N.IGKCO.........DMBL....F....O......NA..CEJ..H.LCP..BD...NGM..EOK.E......ID..F......M.PEO..L........I.AL.HCJK.O.BL.K..NCED....I.FC.D..M..KIA.LPB..JI......L.H.FGLH..P..J.M...E..E...C.DF.AO......IAF.N.K..B...JH.N...MI.DLKH..B.");
	//sudoku16.printSudoku();
	//SudokuSolver<16> solver16(sudoku16);
	//double t1 = MPI_Wtime();
	//solver16.solve();
	//double t2 = MPI_Wtime();
	//if (solver16.isSolved()) {
	//	printf("Solved!\n");
	//	solver16.getSudoku().printSudoku();
	//}
	//else {
	//	printf("Failed!\n");
	//}	
	//printf("Time: %f\n", t2 - t1);
	
	//Sudoku<25> sudoku25("...HO.UFQ......XS...L...B...CK.PBDMGYHQ.AOTRVFSIJE...DGN......A..H.C...K.VX..QFBWA.LK.R..DJEPI.MHGOCJ.I.M.HO..X...F..KL..RD.TFCB..OYANPWED.IVXRH.SLMGQ........I.LG.F..NDBQPECKJ...L.F.C.D.N.J.G.AOEIUBXH..EN..G..B.H...C.IYPOFADRIDG..HE.JQCABR..LF.STVNWYR.......W.BJ.E..C.UA.....CWUBETFQOA.D.......G.I..MD.F.AKBRYEI.XGHQMLWOJPSC.HIM..GSUXJAT.WCPFBNKVDQEO.....P..CHFUYO.DR.EI.....MBSPTE.GHVJQNDLOIYCXUARFKGL......ANTW.M...QSF.OYIPKFJQDIC.BYE..H.RTMAUGWXNVAECWIUQSPO.FKXRNHGVLBMJTDYORVNMDXF.UCGIAKBWPJHQELSBKAGYJOHMLRS...F.EDCQXVPIQHLMUB.YGFDXIAESPO..KCTRWOJVIFCNDTXP.WYQLAUKREBH.GE....QIPKW......GXT...FUAN.PXWAREUSHKFCGIYVQBDJOM.");
	Sudoku<25> sudoku25("W.THO.UFQ......XS...L...B..NCK.PB.M...Q..O.R.........DGN......A..H.C...K.VX...F.W.......S.J...Y.....J.I.M.HOS.X..VF..KL..RD.T.C..J.Y..P..DUIV..HT.L.GQTYHARSX.I.....V.N.B...CK.P.W.V...RDQ..J.G..OE...X.U.E.SL....KH.T...I.PO...R..GO..E.JQC....U.F.S.VN..R.......W.BJ.E.TC.UA......WUBE.F.O.S.LPNYVJXGRIKHMD.FTAKBRYEI.XGHQM.WOJPSCUHIMYLGSUXJATRWCPFBNKVDQEOXGKJQPLVCHFUYOMDRSEIATWBNMBSPTEWGHVJQNDLOIYCXUARFK.LXU.RKJANTWVMBEDQSFCOYIPKFJQDICLBYEOPHSRTMAUGW.NVAECWIUQSPOYFKXRNHGVLBMJTDYORVNMDXFT.CGI.KBWPJHQELSBKAGYJOHMLRSTNUFWEDCQ.VPIQHLMUBVYGFDXIAESPOJNKCTRWOJVIFCNDTXPMWYQLAUKREBHSGESDRCQIPKWVLJBOMGXTHYNFUANTPXWAREUSHKFCGIYVQBDJOM.");
	sudoku25.printSudoku();
	SudokuSolver<25> solver25(sudoku25);
	double t1 = MPI_Wtime();
	solver25.solve();
	double t2 = MPI_Wtime();
	if (solver25.isSolved()) {
		printf("Solved!\n");
		solver25.getSudoku().printSudoku();
	}
	else {
		printf("Failed!\n");
	}
	printf("Time: %f\n", t2 - t1);






	//for (int i = 0; i < 81; i++) {
	//	if (sudoku.isCellKnown(i)) {
	//		printf("%d: %d\n", i, sudoku.getCell(i));
	//	}
	//	else {
	//		printf("%d: ", i);
	//		for(int j = 1; j <= 9; j++)
	//			if (sudoku.isCadiExist(i, j)) {
	//				printf("%d ", j);
	//			}
	//		printf("\n");
	//	}
	//}

}