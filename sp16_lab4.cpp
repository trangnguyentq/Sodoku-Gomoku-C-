// Lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include  "Header.h"
#include "GomokuGame.h"
#include "Base.h"
#include "TicTacToe.h"
#include "SudokuGame.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

int usage_mess(string message) {
	cout << "usage: " << message << " TicTacToe/Gomoku/Sudoku" << endl;
	return no_input_file;
}

int main(int argc, char* argv[])
{
	try {

		GameBase::check(argc, argv);
		shared_ptr<GameBase> p = GameBase::instance();
		return p->play(argv);
	}
	catch (exception_self i) {
		if (i == error1) {
			usage_mess(argv[program_name]);
			return no_input_file;
		}
		else if (i == error2) {
			cout << "error2 detected " << endl;
			return error2_detected;
		}
	}
	catch (std::bad_alloc &ba) {
		std::cerr << "bad_alloc caught: " << ba.what() << endl;
		return bad_allocate;
	}
	catch (...) {
		return error2;
	}

}



