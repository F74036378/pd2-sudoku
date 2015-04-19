#include<iostream>
#include<vector>
#include<cstdio>
#include<string>


#ifndef Sudoku_h
#define Sudoku_h

class Sudoku{
	private:
		int theAnswer;
		int sudoku[144];
		bool canModify[144];
		int sp1,sp2;
	public:
		bool isCorrect(int *sudoku , int pos ,int val);
		bool check();
		void ReadIn();
		bool Solve();
		void GiveQuestion();
		
};

#endif
