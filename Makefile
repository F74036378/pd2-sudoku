sudoku: Sudoku.o solve.cpp give_question.cpp
	g++ -o give_question Sudoku.o give_question.cpp
	g++ -o solve Sudoku.o solve.cpp
Sudoku.o: Sudoku.h Sudoku.cpp
	g++ -c Sudoku.cpp
