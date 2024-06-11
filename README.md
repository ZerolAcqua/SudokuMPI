# SudokuMPI

MPI (Message Passing Interface) employed Microsoft MPI. You can run it following [How to compile and run a simple MS-MPI program | Microsoft Learn](https://learn.microsoft.com/zh-cn/archive/blogs/windowshpc/how-to-compile-and-run-a-simple-ms-mpi-program). You can also use other MPI implementations, such as OpenMPI.

The test data was sourced from the test suite of the [Parallelized Giant Sudoku Solver](https://clairewangyuyue.github.io/CS205_G1.github.io/) project. 

```shell
# serial version
mpiexec -n 1 SudokuMPI.exe 
# parallel version
mpiexec -n 16 SudokuMPI.exe 

```