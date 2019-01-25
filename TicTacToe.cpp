#include "stdafx.h"
#include  "Header.h"
#include  "Base.h"
#include "GomokuGame.h"
#include "TicTacToe.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

TicTacToeGame::TicTacToeGame()
{
	longest = 1;
	height = 5;
	width = 5;
	//read in the TicTacToe.txt 
	ifstream inFile("TicTacToe.txt");
	if (inFile.is_open())
	{
		string t;
		while (getline(inFile, t))
		{
			istringstream iss(t);
			string player;
			vector<int> xo;
			vector<int> yo;
			vector<int> xx;
			vector<int> yx;
			int xi;
			int yi;
			//contruct the board according to the file if there's info in it
			if (iss >> player&&iss >> xi&&iss >> yi)
			{
				if (player == "O")
				{
					xo.push_back(xi);
					yo.push_back(yi);
				}
				else if (player == "X")
				{
					xx.push_back(xi);
					yx.push_back(yi);
				}
				for ( int i = 0; i < (height + 1)*(width + 1); ++i) 
				{
					GameBoard.push_back(" ");
				}
				for ( int j = 1; j < (width + 1); ++j) 
				{
					GameBoard[j] = to_string(j - 1);
					GameBoard[(height + 1) * j] = to_string(j - 1);
				}
				for (size_t k = 0; k < xo.size(); ++k)
				{
					GameBoard[(height + 1)*(yo[k] + 1) + (xo[k] + 1)] = "O";
				}
				for (size_t k = 0; k < xx.size(); ++k)
				{
					GameBoard[(height + 1)* (yx[k] + 1) + (xx[k] + 1)] = "X";
				}
			}
			else
			{
				//if no data, contruct the default game board
				if (player == "No")
				{
					for ( int i = 0; i < (height + 1)*(width + 1); ++i) 
					{
						GameBoard.push_back(" ");
					}
					for ( int j = 1; j < (width + 1); ++j) 
					{
						GameBoard[j] = to_string(j - 1);
						GameBoard[(height + 1) * j] = to_string(j - 1);
					}
				}
			}

		}
	}
	else
	{
		//if no TicTacToe.txt file,(the game haven't ever been played), construct the default game board
		for ( int i = 0; i < (height + 1)*(width + 1); ++i) 
		{
			GameBoard.push_back(" ");
		}
		for ( int j = 1; j < (width + 1); ++j) 
		{
			GameBoard[j] = to_string(j - 1);
			GameBoard[(height + 1) * j] = to_string(j - 1);
		}
	}
}

//define the << operator that can print out the board 
ostream &operator<<(ostream & out, const TicTacToeGame &game) 
{
	for (int v = game.height; v >= 0; --v) 
	{
		for (int h = 0; h < (game.width + 1); ++h) 
		{
			unsigned int index = (game.width + 1) * v + h;
			out << game.GameBoard[index] << " ";
		}
		out << "\n";
	}
	return out;
}

//checking whether the user win the gomoku game 
bool TicTacToeGame::done() 
{
	//check whether the cols are correct
	for (int k = two; k < height; ++k) 
	{
		int move = 1;
		int at = 2;
		while (GameBoard[(width + 1) * k + at].compare(" ") != 0 && GameBoard[(width + 1) * k + at].compare(GameBoard[(width + 1) * k + at + 1]) == 0 && move < 3) {
			move++;
			at++;
		}
		if (move == 3) 
		{
			return true;
		}
	}
	//check whether the rows are correct
	for (int j = two; j < width; ++j) 
	{
		int move = 1;
		int at = 2;
		while (GameBoard[(width + 1) * at + j].compare(" ") != 0 && GameBoard[(width + 1) * at + j].compare(GameBoard[(width + 1) * (at + 1) + j]) == 0 && move < 3) 
		{
			move++;
			at++;
		}
		if (move == 3) 
		{
			return true;
		}
	}
	//check whether the diagonal is correct
	for (int y = two; y < height; ++y) 
	{
		for (int x = two; x < width; ++x) 
		{
			int move = 1;
			int v = y;
			int h = x;
			while (GameBoard[(width + 1)*v + h].compare(" ") != 0 && GameBoard[(width + 1)*v + h].compare(GameBoard[(width + 1)*(v + 1) + h + 1]) == 0 && move < 3) 
			{
				++move;
				++h;
				++v;
			}
			if (move == 3) 
			{
				return true;
			}
		}
	}
	//check whether another diagonal is correct
	for (int y = height; y > one; --y) 
	{
		for (int x = two; x < width; ++x) 
		{
			int move = 1;
			int v = y;
			int h = x;
			while (GameBoard[(width + 1)*v + h].compare(" ") != 0 && GameBoard[(width + 1)*v + h].compare(GameBoard[(width + 1)*(v - 1) + h + 1]) == 0 && move < 3)
			{
				++move;
				++h;
				--v;
			}
			if (move == 3)
			{
				return true;
			}
		}
	}
	return false;
}
//check if drawn
bool TicTacToeGame::draw() 
{
	//if done, not drawn
	if (done() == true) 
	{
		return false;
	}
	//if not completed, not drawn
	for (int v = two; v < height; ++v) 
	{
		for (int h = two; h < width; ++h)
		{
			int index = (width + 1) * v + h;
			if (GameBoard[index].compare(" ") == 0) 
			{
				return false;
			}
		}
	}
	//otherwise, completed but no one wins, drawn
	return true;
}
//prompt users for input
int TicTacToeGame::prompt(unsigned int & first, unsigned int & second) 
{
	string move;
	if (getline(cin, move)) 
	{
		if (move.compare("quit") == 0)
		{
			return quit_game;
		}
		else
		{
			for (size_t i = 0; i < move.length(); ++i)
			{
				if (move[i] == ',') {
					move[i] = ' ';
				}
			}
			istringstream fString(move);
			if ((fString >> first) && (fString >> second))
			{
				if (first < one || first > three || second < one || second > three)
				{
					cout << "Your x and y coordinate must be in the range from 1 to " << three << endl;
					return coordinate_out_of_range;
				}
				else
				{
					return success;
				}
			}
			else 
			{
				cout << "Please input coordinate of your move following the form: x-coordinate,y-coordinate" << endl;
				return fail_to_get_coordinate;
			}

		}
	}
	else
	{
		return fail_to_getline;
	}

}

//keep prompting users for input and change turns between X and O
int TicTacToeGame::turn() 
{
	unsigned int hori;
	unsigned int vert;
	bool Xturn;
	unsigned index;
	int Osteps = 0;
	int Xsteps = 0;
	bool valid_move = false;
	for (size_t value = 0; value < GameBoard.size(); ++value) 
	{
		if (GameBoard[value].compare("X") == 0)
		{
			++Xsteps;
		}
		else if (GameBoard[value].compare("O") == 0)
		{
			++Osteps;
		}
	}
	if (Xsteps > Osteps)
	{
		Xturn = false;
	}
	else
	{
		Xturn = true;
	}

	while (!valid_move)
	{
		if (Xturn)
		{
			cout << "Player X, please enter your move: ";
		}
		else
		{
			cout << "Player O, please enter your move:  ";
		}
		int p = prompt(hori, vert);
		if (p == returnvalue::quit_game)
		{
			bool valid = false;
			while (!valid){
				//ask whether wanna save the game
				cout << "Do you wanna save this game? Please enter y or n" << endl;
				string answer;
				if (getline(cin, answer)) 
				{
					ofstream ofs("TicTacToe.txt");
					if (ofs.is_open())
					{
						//if yes, save the moves of different players into corresponding vectors
						if (answer.compare("y") == 0)
						{
							for (size_t i = 0; i < xmemory.size(); ++i)
							{
								ofs << "X " << xmemory[i] << endl;
							}
							for (size_t i = 0; i < omemory.size(); ++i)
							{
								ofs << "O " << omemory[i] << endl;
							}
							valid = true;
						}
						else if (answer.compare("n") == 0) 
						{
							//if no, write  no data into the file
							ofs << "No Data" << endl;
							valid = true;
						}
					}
					else
					{
						return fail_open_file;
					}
				}
			}
			return quit_game;
		}
		else if (p == returnvalue::success) 
		{
			if (Xturn)
			{
				//if input valid, make the move
				index = (vert + 1) * 6 + (hori + 1);
				if (GameBoard[index].compare(" ") == 0)
				{
					GameBoard[index] = "X";
					if (longest < GameBoard[index].length())
					{
						longest = GameBoard[index].length();
						cout << "longest: " << longest << endl;
					}
					for (int v = height; v >= 0; --v)
					{
						for (int h = 0; h < (width + 1); ++h)
						{
							unsigned int index = (width + 1) * v + h;
							cout << GameBoard[index] << " ";
						}
						cout << "\n";
					}
					cout << "Player X: ";
					for (int v = two; v < height; ++v)
					{
						for (int h = two; h < width; ++h)
						{
							int index = (width + 1) * v + h;
							if (GameBoard[index].compare("X") == 0) 
							{
								cout << h - 1 << ", " << v - 1 << "; ";
							}
						}
					}
					cout << endl;
					valid_move = true;
				}
				else 
				{
					//if not valid, tell the users
					cout << "The square is occupied, please try another move." << endl;
				}

			}
			else
			{
				//if input valid, make the move
				index = (vert + 1) * (height + 1) + (hori + 1);
				if (GameBoard[index].compare(" ") == 0) 
				{
					GameBoard[index] = "O";
					if (longest < GameBoard[index].length()) 
					{
						longest = GameBoard[index].length();
					}
					for (int v = height; v >= 0; --v) 
					{
						for (int h = 0; h < (width + 1); ++h) 
						{
							unsigned int index = (width + 1) * v + h;
							cout << GameBoard[index] << " ";
						}
						cout << endl;
					}
					cout << "Player O: ";
					for (int v = two; v < height; ++v) 
					{
						for (int h = two; h < width; ++h)
						{
							int index = (width + 1) * v + h;
							if (GameBoard[index].compare("O") == 0)
							{
								cout << h - 1 << ", " << v - 1 << "; ";
							}
						}
					}
					cout << endl;
					valid_move = true;
				}
				else 
				{
					//if not valid, tell the users
					cout << "The square is occupied, please try another move." << endl;
				}

			}
		}
		//save all the move to a memory vector
		for (int v = two; v < height; ++v)
		{
			for (int h = two; h < width; ++h)
			{
				int index = (width + 1) * v + h;
				if (GameBoard[index].compare("O") == 0)
				{
					string a = to_string(h - 1) + " " + to_string(v - 1);
					omemory.push_back(a);
				}
				else if (GameBoard[index].compare("X") == 0)
				{
					string a = to_string(h - 1) + " " + to_string(v - 1);
					xmemory.push_back(a);
				}
			}
		}
	}
	return success;
}

//print out the board using << operator
void TicTacToeGame::print() 
{
	cout << *this;
}
