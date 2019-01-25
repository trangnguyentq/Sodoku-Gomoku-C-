#ifndef Base
#define Base
//Base.h: header for GameBase
//declare GameBase Class
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <memory>
using namespace std;

class GameBase {
public:
	static void check(int i, char* b[]);
	void checkgame(char* b[]);
	int play(char *c[]);
	virtual void print() = 0;
	virtual bool done() = 0;
	virtual bool draw() = 0;
	virtual int turn() = 0;
	static shared_ptr<GameBase> instance();
protected:
	int width;
	int height;
	vector <string> GameBoard;
	unsigned int longest;
	static shared_ptr<GameBase> sptr;
	bool won;




};

#endif
