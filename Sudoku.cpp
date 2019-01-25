#include "stdafx.h"
#include  "Header.h"
#include  "Base.h"
#include "GomokuGame.h"
#include "TicTacToe.h"
#include "SudokuGame.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

Sudoku::Sudoku()
{
	longest = 1;
	height = 19;
	width = 19;
	//contrusct an empty game board with the correct format
	for (int i = 0; i < (height + 1)*(width + 1); ++i) 
	{
		GameBoard.push_back(" ");
	}
	GameBoard[0] = "#";
	for (int j = 1; j < (height + 1); ++j) 
	{
		if (j == one || j == seven || j == thirteen || j == nineteen) 
		{
			for (int t = 0; t < (width + 1); ++t) 
			{
				GameBoard[j *(width + 1) + t] = "=";
			}
		}
		else if (j % 2 == 1) 
		{
			for (int t = 0; t < (height + 1); ++t) 
			{
				GameBoard[j *(width + 1) + t] = "-";
			}
		}
		else 
		{
			GameBoard[j *(width + 1)] = to_string(j / 2 - 1);
		}
	}
	for (int j = 1; j < (width + 1); ++j) 
	{
		if (j == one || j == seven || j == thirteen || j == nineteen) 
		{
			for (int t = 0; t < (height + 1); ++t) 
			{
				GameBoard[t *(width + 1) + j] = "||";
			}
		}
		else if (j % 2 == 1) 
		{
			for (int t = 0; t < (height + 1); ++t) 
			{
				GameBoard[t *(width + 1) + j] = "|";
			}
		}
		else 
		{
			GameBoard[j] = to_string(j / 2 - 1);
		}
	}
	//fill in the numbers according to the sudoku.txt file 
	ifstream inFile("sudoku0.txt");
	int line = 0;
	int ind = 0;
	if (inFile.is_open())
	{
		string t;
		while (getline(inFile, t))
		{
			istringstream iss(t);
			unsigned int move;
			while (iss >> move)
			{
				Original.push_back(to_string(move));
				if (move != zero) 
				{
					unsigned int index = ((line + 1) * 2)*(width + 1) + ((ind + 1) * 2);
					GameBoard[index] = to_string(move);
				}
				if (ind >= eight) 
				{
					ind = 0;
				}
				else 
				{
					++ind;
				}
			}
			++line;
		}
	}
	//if user chose to save the game last time, fill in the number according to Sudoku.txt
	ifstream saveFile("Sudoku.txt");
	if (saveFile.is_open()) 
	{
		string m;
		while (getline(saveFile, m))
		{
			if (m != "No Data") 
			{
				istringstream iss(m);
				unsigned int x;
				unsigned int y;
				unsigned int tileVal;
				if (iss >> y && iss >> x && iss >> tileVal)
				{
					unsigned int index = ((y + 1) * 2)*(width + 1) + ((x + 1) * 2);
					GameBoard[index] = to_string(tileVal);
				}
			}
		}
	}
}

//define the << operator that can print out the board 
ostream &operator<<(ostream & out, const Sudoku &game) 
{
	for (int v = game.height; v >= 0; --v) 
	{
		for (int h = 0; h < (game.width + 1); ++h) 
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
void Sudoku::print() 
{
	cout << *this;
}
//checking whether the user win the sudoku game 
bool Sudoku::done() 
{
	vector<bool> brow;
	vector<bool> bcol;
	vector<bool> bsquare;
	bool squareWrong = false;
	bool rowWrong = false;
	bool colWrong = false;
	//checking if the cols are correct
	for (int i = 1; i < (width + 1); ++i) 
	{
		if (i % 2 == 0) {
			vector<string> col;
			for (int j = 1; j < (height + 1); ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					col.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
			sort(col.begin(), col.end());
			auto it1 = adjacent_find(col.begin(), col.end());
			if (it1 == col.end()) 
			{
				bcol.push_back(true);
			}
			else 
			{
				bcol.push_back(false);
			}
		}
	}


	//check whether the rows are correct
	for (int i = 1; i < (height + 1); ++i) 
	{
		if (i % 2 == 0) 
		{
			vector<string> row;
			for (int j = 1; j < (width + 1); ++j) 
			{
				if (j % 2 == 0 && GameBoard[i*(width + 1) + j] != " ") 
				{
					row.push_back(GameBoard[i*(width + 1) + j]);
				}
			}
			sort(row.begin(), row.end());
			auto it2 = adjacent_find(row.begin(), row.end());
			if (it2 == row.end()) 
			{
				brow.push_back(true);
			}
			else 
			{
				brow.push_back(false);
			}
		}
	}
	//check whether square1 is correct
	vector<string> square1;
	for (int i = 1; i < seven; ++i) 
	{
		if (i % 2 == 0) 
		{
			for (int j = 1; j < seven; ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					square1.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
		}
	}
	sort(square1.begin(), square1.end());
	auto it3 = adjacent_find(square1.begin(), square1.end());
	if (it3 == square1.end()) 
	{
		bsquare.push_back(true);
	}
	else 
	{
		bsquare.push_back(false);
	}
	//check whether square2 is correct
	vector<string> square2;
	for (int i = seven; i < thirteen; ++i) 
	{
		if (i % 2 == 0) 
		{
			for (int j = seven; j < thirteen; ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					square2.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
		}
	}
	sort(square2.begin(), square2.end());
	auto it4 = adjacent_find(square2.begin(), square2.end());
	if (it4 == square2.end()) 
	{
		bsquare.push_back(true);
	}
	else 
	{
		bsquare.push_back(false);
	}
	//check whether square3 is correct
	vector<string> square3;
	for (int i = thirteen; i < nineteen; ++i) 
	{
		if (i % 2 == 0) 
		{
			for (int j = thirteen; j < nineteen; ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					square3.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
		}
	}
	sort(square3.begin(), square3.end());
	auto it5 = adjacent_find(square3.begin(), square3.end());
	if (it5 == square3.end()) 
	{
		bsquare.push_back(true);
	}
	else 
	{
		bsquare.push_back(false);
	}
	//check whether square4 is correct
	vector<string> square4;
	for (int i = thirteen; i < nineteen; ++i) 
	{
		if (i % 2 == 0) 
		{
			for (int j = 1; j < seven; ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					square4.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
		}
	}
	sort(square4.begin(), square4.end());
	auto it6 = adjacent_find(square4.begin(), square4.end());
	if (it6 == square4.end()) 
	{
		bsquare.push_back(true);
	}
	else 
	{
		bsquare.push_back(false);
	}
	//check whether square5 is correct
	vector<string> square5;
	for (int i = thirteen; i < nineteen; ++i) 
	{
		if (i % 2 == 0) 
		{
			for (int j = seven; j < thirteen; ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					square5.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
		}
	}
	sort(square5.begin(), square5.end());
	auto it7 = adjacent_find(square5.begin(), square5.end());
	if (it7 == square5.end()) 
	{
		bsquare.push_back(true);
	}
	else 
	{
		bsquare.push_back(false);
	}
	//check whether square6 is correct
	vector<string> square6;
	for (int i = 1; i < seven; ++i) 
	{
		if (i % 2 == 0) 
		{
			for (int j = seven; j < thirteen; ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					square6.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
		}
	}
	sort(square6.begin(), square6.end());
	auto it8 = adjacent_find(square6.begin(), square6.end());
	if (it8 == square6.end()) 
	{
		bsquare.push_back(true);
	}
	else 
	{
		bsquare.push_back(false);
	}
	//check whether square7 is correct
	vector<string> square7;
	for (int i = 1; i < seven; ++i) 
	{
		if (i % 2 == 0) 
		{
			for (int j = thirteen; j < nineteen; ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					square7.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
		}
	}
	sort(square7.begin(), square7.end());
	auto it9 = adjacent_find(square7.begin(), square7.end());
	if (it9 == square7.end()) 
	{
		bsquare.push_back(true);
	}
	else 
	{
		bsquare.push_back(false);
	}
	//check whether square8 is correct
	vector<string> square8;
	for (int i = seven; i < thirteen; ++i) 
	{
		if (i % 2 == 0) 
		{
			for (int j = thirteen; j < nineteen; ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					square8.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
		}
	}
	sort(square8.begin(), square8.end());
	auto it10 = adjacent_find(square8.begin(), square8.end());
	if (it10 == square8.end()) 
	{
		bsquare.push_back(true);
	}
	else 
	{
		bsquare.push_back(false);
	}
	//check whether square9 is correct
	vector<string> square9;
	for (int i = seven; i < thirteen; ++i) 
	{
		if (i % 2 == 0) 
		{
			for (int j = 1; j < seven; ++j) 
			{
				if (j % 2 == 0 && GameBoard[j*(width + 1) + i] != " ") 
				{
					square9.push_back(GameBoard[j*(width + 1) + i]);
				}
			}
		}
	}
	sort(square9.begin(), square9.end());
	auto it11 = adjacent_find(square9.begin(), square9.end());
	if (it11 == square9.end()) 
	{
		bsquare.push_back(true);
	}
	else 
	{
		bsquare.push_back(false);
	}
	for (int i = 0; i < (height + 1)*(width + 1); ++i)
	{
		if (GameBoard[i] == " ")
		{
			return false;
		}
	}
	for (unsigned int t = 0; t < bsquare.size(); ++t) 
	{
		if (bsquare[t] == false) 
		{
			cout << "The GameBoard is full but you didn't win the game because some of your tile values are wrong. Please keep playing or type 'quit' to quit the game" << endl;
			return false;
		}
	}
	for (unsigned int i = 0; i < brow.size(); ++i) 
	{
		if (brow[i] == false)
		{

			cout << "The GameBoard is full but you didn't win the game because some of your tile values are wrong. Please keep playing or type 'quit' to quit the game" << endl;
			return false;
		}
	}
	for (unsigned int j = 0; j < bcol.size(); ++j) 
	{
		if (bcol[j] == false) 
		{
			cout << "The GameBoard is full but you didn't win the game because some of your tile values are wrong. Please keep playing or type 'quit' to quit the game" << endl;
			return false;
		}
	}
	return true;
}


//check if drawn, not eligible for sudoku game so always return false
bool Sudoku::draw() 
{
	return false;
}
//prompting users for input
int Sudoku::prompt(unsigned int & first, unsigned int & second, unsigned int & third) 
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
			if ((fString >> first) && (fString >> second) && (fString >> third)) 
			{
				if (first < zero || first > eight || second < zero || second > eight || third>nine || third<one) 
				{
					cout << "Your x and y coordinate must be in the range from 1 to " << eight << " and your tile value should be in the range between 1 and 9" << endl;
					return coordinate_out_of_range;
				}
				else 
				{
					return success;
				}
			}
			else 
			{
				cout << "Please input coordinate of your move following the form: x-coordinate,y-coordinate,tile value" << endl;
				return fail_to_get_coordinate;
			}

		}
	}
	else 
	{
		return fail_to_getline;
	}

}

//keep prompting users for input 
int Sudoku::turn() 
{
	unsigned int hori;
	unsigned int vert;
	unsigned int tile;
	unsigned index;
	int Xsteps = 0;
	bool valid_move = false;

	while (!valid_move) 
	{
		cout << "Please enter your move: ";
		int p = prompt(hori, vert, tile);
		if (p == returnvalue::quit_game) 
		{
			bool valid = false;
			while (!valid)
			{
				//asking users whether he/she wanna save the game
				cout << "Do you wanna save this game? Please enter y or n" << endl;
				string answer;
				if (getline(cin, answer)) 
				{
					//if the user want to save the game, save the moves in Sudoku.txt(see readme for format)
					ofstream ofs("Sudoku.txt");
					if (ofs.is_open()){
						if (answer.compare("y") == 0) 
						{
							for (size_t i = 0; i < memory.size(); ++i)
							{
								ofs << memory[i] << endl;
							}
							valid = true;
						}
						else if (answer.compare("n") == 0) 
						{
							//if not saving the game, write no data in the file
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
			index = ((vert + 1) * 2)*(width + 1) + ((hori + 1) * 2);
			if (Original[vert*nine + hori] == "0")
			{
				GameBoard[index] = to_string(tile);
				//save the moves to the memory vector

				ifstream saveFile("Sudoku.txt");
				if (saveFile.is_open())
				{
					string m;
					while (getline(saveFile, m))
					{
						if (m != "No Data")
						{
							istringstream iss(m);
							unsigned int x;
							unsigned int y;
							unsigned int tileVal;
							if (iss >> y && iss >> x && iss >> tileVal)
							{
								string b = to_string(y) + " " + to_string(x) + " " + to_string(tileVal);
								memory.push_back(b);
								
							}
						}
					}
				}
				string a = to_string(vert) + " " + to_string(hori) + " " + to_string(tile);
				memory.push_back(a);




				/*for (int v = two; v < height; ++v)
				{
				for (int h = two; h < width; ++h)
				{
				int index = ((v + 1) * 2)*(width + 1) + ((h + 1) * 2);
				string that = GameBoard[index];
				if (isdigit(that[zero]) && Original[vert*nine + hori] == "0")
				{
				//cout << h - 1 << ", " << v - 1 << "; ";
				string a = to_string(vert) + " " + to_string(hori) + " " + to_string(tile);
				memory.push_back(a);
				}

				}
				}*/
				if (longest < GameBoard[index].length())
				{
					longest = GameBoard[index].length();
					cout << "longest: " << longest << endl;
				}
				print();
				valid_move = true;
			}
			else 
			{
				//avoid user to change the original tiles
				cout << "You cannot change the original tile." << endl;
			}
		}
		return success;
	}
	return success;
}

