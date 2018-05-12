# Fast-Sudoku-Solver-Cpp
The lazy approach that solves every 9x9 sudoku cannot be used in 25x25 sudoku.
This solver tuckles the problem of high brunching factor by playing always in the most constraint box.
Infrastructure to find also the most constraint value is implemented (Box_Structures : Column, Row, Container) but not used.
The 25x25 given sudoku is solved in less than 2 seconds. Of course the programm can become a lot faster.
