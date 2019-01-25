#ifndef GomokuGame
#define GomokuGame
//GomokuGame.h: header for Gomoku
//declare Gomoku Class(public inheritance of GameBase)
#include <iostream>
#include <fstream>
#include <vector>
#include "Base.h"
#include <array>
#include <string>
#include "Header.h"
using namespace std;

class Gomoku : public GameBase {
	friend ostream &operator<<(ostream &out, const Gomoku &game);
public:
	Gomoku();
	Gomoku(Gomoku& gk);
	Gomoku(int x, int y, int winning);
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual int prompt(unsigned int & first, unsigned int & second);
	virtual void print();
	//virtual int setGame(unsigned int & x, unsigned int & y, unsigned int & winningPieces);
private:
	unsigned int height = 21;
	unsigned int width = 21;
	int winningMoves;
	vector<string> bmemory;
	vector<string> wmemory;
};

ostream &operator<<(ostream &out, const Gomoku &game);

#endif
