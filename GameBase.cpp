#include "stdafx.h"
#include  "Header.h"
#include "GomokuGame.h"
#include "Base.h"
#include "TicTacToe.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "SudokuGame.h"
using namespace std;


shared_ptr<GameBase> GameBase::sptr = nullptr;
//check whether the pointer is null
shared_ptr<GameBase> GameBase::instance()
{
	if (sptr != nullptr)
	{
		return sptr;
	}
	else
	{
		throw error1;
	}

}

//check user input, either give usage message or return different game pointers for play method
void GameBase::check(int i, char *b[])
{
	if (sptr == nullptr)
	{
		if (i == two && strcmp(b[input_name], "TicTacToe") == 0)
		{
			TicTacToeGame *t = new TicTacToeGame;
			sptr = shared_ptr<GameBase>(t);
		}
		else if (i == two && strcmp(b[input_name], "Gomoku") == 0)
		{
			Gomoku *g = new Gomoku(nineteen, nineteen, five);
			sptr = shared_ptr<GameBase>(g);
		}
		else if (i == two && strcmp(b[input_name], "Sudoku") == 0)
		{
			Sudoku *s = new Sudoku();
			sptr = shared_ptr<GameBase>(s);
		}
		else if (i == four && strcmp(b[input_name], "Gomoku") == 0)
		{
			string di = b[dimension];
			string win = b[winning];
			istringstream ss(di);
			istringstream ss2(win);
			int x;
			int winningPieces;
			if (ss >> x && ss2 >> winningPieces)
			{
				int y = x;
				if (x >= 3 && y >= 3 && winningPieces >= 3 && x >= winningPieces)
				{
					Gomoku *g = new Gomoku(x, y, winningPieces);
					sptr = shared_ptr<GameBase>(g);
				}
				else
				{
					cout << "x,y dimensions and winnigMoves have to be larger or equal to 3. In addtion, x,y dimensions have to be larger or equal to winningMoves." << endl;
					throw error2;
				}
			}
			else
			{
				cout << "usage: " << " Lab3.exe Gomoku dimension winningMoves, eg: Lab3.exe Gomoku 3 3" << endl;
				throw error2;
			}
		}
		else if (i == three && strcmp(b[input_name], "Gomoku") == 0) 
		{
			string di = b[dimension];
			istringstream ss(di);
			int x;
			if (ss >> x)
			{
				int y = x;
				if (x >= five && y >= five)
				{
					Gomoku *g = new Gomoku(x, y, five);
					sptr = shared_ptr<GameBase>(g);
				}
				else
				{
					cout << "x,y dimensions have to be larger or equal to 5" << endl;
					throw error2;
				}
			}
			else
			{
				cout << "usage: " << " Lab3.exe Gomoku dimension, eg: Lab3.exe Gomoku 5" << endl;
				throw error2;
			}
		}
	}
	else {
		throw error2;
	}
}

//play the game using turn(), check results using done() and draw()
int GameBase::play(char *c[]) 
{
	print();
	int this_turn = turn();
	bool dn = done();
	bool dr = draw();
	unsigned int t = 1;
	while (dn != true && dr != true && this_turn != returnvalue::quit_game) 
	{
		this_turn = turn();
		dn = done();
		dr = draw();
		++t;

	}
	//if done, print out different messages according to different game
	if (dn == true) 
	{
		won = true;
		if (strcmp(c[input_name], "Sudoku") == 0)
		{
			remove("Sudoku.txt");
			cout << "Congratulations! You won!" << endl;
		}
		else if (t % 2 == 0)
		{
			if (strcmp(c[input_name], "TicTacToe") == 0) 
			{
				remove("TicTacToe.txt");
				cout << "Player O won." << endl;
			}
			else if (strcmp(c[input_name], "Gomoku") == 0) 
			{
				remove("Gomoku.txt");
				cout << "White Stone won" << endl;
			}
		}
		else {
			if (strcmp(c[input_name], "TicTacToe") == 0) 
			{
				remove("TicTacToe.txt");
				cout << "Player X won." << endl;
			}
			else if (strcmp(c[input_name], "Gomoku") == 0) 
			{
				remove("Gomoku.txt");
				cout << "Black Stone won" << endl;
			}
		}
		return success;

	}
	// if drawn,  print out different messages according to different game
	if (dr == true)
	{
		cout << t << " turns were played and no winning moves remain." << endl;
		return game_draw;
	}
	//if users quit,  print out number of turns
	if (this_turn == returnvalue::quit_game)
	{
		cout << t - 1 << " turns were played. User has quit the game. " << endl;
		return quit_game;
	}
	return success;
}
