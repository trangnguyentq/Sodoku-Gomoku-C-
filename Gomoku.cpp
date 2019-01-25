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
#include <iterator>
#include <fstream>
using namespace std;

Gomoku::Gomoku(int x, int y, int winning)
{
	longest = 3;
	height = y + 2;
	width = x + 2;
	//read in the Gomoku.txt 
	ifstream inFile("Gomoku.txt");
	if (inFile.is_open())
	{
		string t;
		while (getline(inFile, t))
		{
			istringstream iss(t);
			string player;
			vector<int> xb;
			vector<int> yb;
			vector<int> xw;
			vector<int> yw;
			int xi;
			int yi;
			//contruct the board according to the file if there's info in it
			if (iss >> player&&iss >> xi&&iss >> yi)
			{
				if (player == "B"){
					xb.push_back(xi);
					yb.push_back(yi);
				}
				else if (player == "W")
				{
					xw.push_back(xi);
					yw.push_back(yi);
				}
				winningMoves = winning;
				for (unsigned int i = 0; i < (height + 1)*(width + 1); ++i) 
				{
					GameBoard.push_back(" ");
				}
				for (unsigned int j = 1; j < (width + 1); ++j) 
				{
					GameBoard[j] = to_string(j - 1);
					GameBoard[(height + 1) * j] = to_string(j - 1);
				}
				for (size_t k = 0; k < xb.size(); ++k)
				{
					GameBoard[(height + 1)*(yb[k] + 1) + (xb[k] + 1)] = "B";
				}
				for (size_t k = 0; k < xw.size(); ++k)
				{
					GameBoard[(height + 1)* (yw[k] + 1) + (xw[k] + 1)] = "W";
				}
			}
			else
			{
				//if no data, contruct the default game board

				winningMoves = winning;
				for (unsigned int i = 0; i < (height + 1)*(width + 1); ++i)
				{
					GameBoard.push_back(" ");
				}
				for (unsigned int j = 1; j < (width + 1); ++j)
				{
					GameBoard[j] = to_string(j - 1);
					GameBoard[(height + 1) * j] = to_string(j - 1);
				}

			}

		}
	}
	else
	{
		//if no Gomoku.txt file,(the game haven't ever been played), construct the default game board
		winningMoves = winning;
		for (unsigned int i = 0; i < (height + 1)*(width + 1); ++i) 
		{
			GameBoard.push_back(" ");
		}
		for (unsigned int j = 1; j < (width + 1); ++j) 
		{
			GameBoard[j] = to_string(j - 1);
			GameBoard[(height + 1) * j] = to_string(j - 1);
		}
	}
}

//define the << operator that can print out the board 
ostream &operator<<(ostream & out, const Gomoku &game) 
{
	for (int v = game.height; v >= 0; --v) 
	{
		for (unsigned int h = 0; h < (game.width + 1); ++h) 
		{
			unsigned int index = (game.width + 1) * v + h;
			out.width(game.longest);
			out << game.GameBoard[index] << setw(game.longest);
		}
		out << "\n";
	}
	return out;
}
//print out the board using << operator
void Gomoku::print() 
{
	cout << *this;
}

//checking whether the user win the gomoku game 
bool Gomoku::done() 
{
	//check whether the rows are correct
	for (unsigned int y = two; y < height; ++y) 
	{
		for (unsigned int x = two; x < width; ++x) 
		{
			int move = 1;
			int v = y;
			int h = x;
			while (GameBoard[(width + 1) * v + h].compare(" ") != 0 && GameBoard[(width + 1) * v + h].compare(GameBoard[(width + 1) * v + h + 1]) == 0 && move < winningMoves)
			{
				++move;
				++h;
			}
			if (move == winningMoves) 
			{
				return true;
			}
		}
	}

	//check whether the cols are correct
	for (unsigned int y = two; y < height; ++y) 
	{
		for (unsigned int x = two; x < width; ++x) 
		{
			int move = 1;
			int v = y;
			int h = x;
			while (GameBoard[(width + 1) * v + h].compare(" ") != 0 && GameBoard[(width + 1) * v + h].compare(GameBoard[(width + 1) * (v + 1) + h]) == 0 && move < winningMoves) 
			{
				++move;
				++v;
			}
			if (move == winningMoves) 
			{
				return true;
			}
		}
	}

	//check whether the diagonal is correct
	for (unsigned int y = two; y < height; ++y) 
	{
		for (unsigned int x = two; x < width; ++x) 
		{
			int move = 1;
			int v = y;
			int h = x;
			while (GameBoard[(width + 1)*v + h].compare(" ") != 0 && GameBoard[(width + 1)*v + h].compare(GameBoard[(width + 1)*(v + 1) + h + 1]) == 0 && move < winningMoves) 
			{
				++move;
				++h;
				++v;
			}
			if (move == winningMoves) 
			{
				return true;
			}
		}
	}
	//check whether another diagonal is correct
	for (unsigned int y = height; y > one; --y) 
	{
		for (unsigned int x = two; x < width; ++x) 
		{
			int move = 1;
			int v = y;
			int h = x;
			while (GameBoard[(width + 1)*v + h].compare(" ") != 0 && GameBoard[(width + 1)*v + h].compare(GameBoard[(width + 1)*(v - 1) + h + 1]) == 0 && move < winningMoves)
			{
				++move;
				++h;
				--v;
			}
			if (move == winningMoves) 
			{
				return true;
			}
		}
	}
	return false;

}

//check if drawn
bool Gomoku::draw() 
{
	//if done, not drawn
	if (done() == true) 
	{
		return false;
	}
	//if not completed, not drawn
	for (unsigned int v = two; v < height; ++v) 
	{
		for (unsigned int h = two; h < width; ++h) 
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
int Gomoku::prompt(unsigned int & first, unsigned int & second) 
{
	string move;
	if (getline(cin, move)) 
	{
		if (move.compare("quit") == 0) 
		{
			return quit_game;
		}
		else {
			for (size_t i = 0; i < move.length(); ++i) 
			{
				if (move[i] == ',') 
				{
					move[i] = ' ';
				}
			}
			istringstream fString(move);
			if ((fString >> first) && (fString >> second)) 
			{
				if (first < one || first > width - 2 || second < one || second > height - 2) 
				{
					cout << "Your x and y coordinate must be in the range from 1 to " << width - 2 << endl;
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
//keep prompting users for input and change turns between B and W
int Gomoku::turn() 
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
		if (GameBoard[value].compare("B") == 0) 
		{
			++Xsteps;
		}
		else if (GameBoard[value].compare("W") == 0) 
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
			cout << "Black Stone player, please enter your move: ";
		}
		else 
		{
			cout << "White Stone player, please enter your move: ";
		}

		int p = prompt(hori, vert);
		if (p == returnvalue::quit_game) 
		{
			bool valid = false;
			while (!valid)
			{
				//ask whether wanna save the game
				cout << "Do you wanna save this game? Please enter y or n" << endl;
				string answer;
				if (getline(cin, answer))
				{
					ofstream ofs("Gomoku.txt");
					if (ofs.is_open())
					{
						//if yes, save the moves of different players into corresponding vectors
						if (answer.compare("y") == 0)
						{
							for (size_t i = 0; i < bmemory.size(); ++i)
							{
								ofs << "B " << bmemory[i] << endl;
							}
							for (size_t i = 0; i < wmemory.size(); ++i)
							{
								ofs << "W " << wmemory[i] << endl;
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
				index = (vert + 1) * (width + 1) + (hori + 1);
				if (GameBoard[index].compare(" ") == 0) 
				{
					GameBoard[index] = "B";
					if (longest < GameBoard[index].length()) 
					{
						longest = GameBoard[index].length();
					}
					print();
					cout << "Black Stone: ";
					for (unsigned int v = two; v < height; ++v) 
					{
						for (unsigned int h = two; h < width; ++h) 
						{
							int index = (width + 1) * v + h;
							if (GameBoard[index].compare("B") == 0) 
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
					GameBoard[index] = "W";
					if (longest < GameBoard[index].length()) 
					{
						longest = GameBoard[index].length();
					}
					print();
					cout << "White Stone: ";
					wmemory.clear();
					for (unsigned int v = two; v < height; ++v)
					{
						for (unsigned int h = two; h < width; ++h) 
						{
							int index = (width + 1) * v + h;
							if (GameBoard[index].compare("W") == 0) 
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
					//if not valid, tell the user
					cout << "The square is occupied, please try another move." << endl;
				}

			} 
			//save the move to a memory vector
			bmemory.clear();
			wmemory.clear();
			for (unsigned int v = two; v < height; ++v)
			{
				for (unsigned int h = two; h < width; ++h)
				{
					int index = (width + 1) * v + h;
					if (GameBoard[index].compare("B") == 0)
					{
						string a = to_string(h - 1) + " " + to_string(v - 1);
						bmemory.push_back(a);
					}
					else if (GameBoard[index].compare("W") == 0)
					{
						string a = to_string(h - 1) + " " + to_string(v - 1);
						wmemory.push_back(a);
					}
				}
			}
			cout << endl;
		}

	}
	return success;
}