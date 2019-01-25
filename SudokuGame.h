#ifndef SudokuGame
#define SudokuGame
//SudokuGame.h: header for Sudoku
//declare Sudoku Class(public inheritance of GameBase)
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "Header.h"
#include "Base.h"
using namespace std;



class Sudoku : public GameBase {
	friend ostream &operator<<(ostream &out, const Sudoku &game);
public:
	Sudoku();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual int prompt(unsigned int & first, unsigned int & second, unsigned int & third);
	virtual void print();
private:
	int height = 9;
	int width = 9;
	vector<string> Original;
	vector<string> memory;
};

ostream &operator<<(ostream &out, const Sudoku &game);

#endif
