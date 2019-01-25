#ifndef TicTacToe
#define TicTacToe
//TicTacToe.h: header for TicTacToe
//declare TicTacToe Class(public inheritance of GameBase)
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "Header.h"
#include "Base.h"
using namespace std;



class TicTacToeGame : public GameBase {
	friend ostream &operator<<(ostream &out, const TicTacToeGame &game);
public:
	TicTacToeGame();
	virtual bool done();
	virtual bool draw();
	virtual int turn();
	virtual int prompt(unsigned int & first, unsigned int & second);
	virtual void print();
private:
	int height = 5;
	int width = 5;
	vector<string> xmemory;
	vector<string> omemory;
};

ostream &operator<<(ostream &out, const TicTacToeGame &game);

#endif
