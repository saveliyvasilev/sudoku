# sudoku
Solver for 9x9 sudokus in C++.

A brute-force algorithm that branches on the cell which has the least number of inferred options.

The input is a matrix given by standard input, where the empty cell is represented with 0.

## Execution example

```
$ make
$ ./main < hard.in
Loaded sudoku:

4 0 0 0 0 0 8 0 5
0 3 0 0 0 0 0 0 0
0 0 0 7 0 0 0 0 0
0 2 0 0 0 0 0 6 0
0 0 0 0 8 0 4 0 0
0 0 0 0 1 0 0 0 0
0 0 0 6 0 3 0 7 0
5 0 0 2 0 0 0 0 0
1 0 4 0 0 0 0 0 0

Used 482 attempts.
Solved sudoku:

4 1 7 3 6 9 8 2 5
6 3 2 1 5 8 9 4 7
9 5 8 7 2 4 3 1 6
8 2 5 4 3 7 1 6 9
7 9 1 5 8 6 4 3 2
3 4 6 9 1 2 7 5 8
2 8 9 6 4 3 5 7 1
5 7 3 2 9 1 6 8 4
1 6 4 8 7 5 2 9 3

Time elapsed 0.030215s

===

To generate a PDF with sudous using this code run:

```bash
./main --pdf 15 1.01
pdflatex output.tex
```
