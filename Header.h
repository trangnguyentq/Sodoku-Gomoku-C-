#ifndef Header
#define Header
//Header.h: store enum and declare usage message
#include <iostream>
#include <vector>
#include <array>
#include <string>
using namespace std;


enum game { None, TicTacToe, GomokuGame };
enum index { program_name, input_name, dimension, winning };
enum returnvalue {
	success, failure, fail_open_file, no_input_file, fail_to_get_coordinate, fail_to_getline, coordinate_out_of_range, quit_game,
	X_success, Y_success, square_occupied, game_draw, bad_allocate, user_set_game_fail, error1_detected, error2_detected
};
enum board {
	zero, one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen, seventeen, eighteen, nineteen, twenty, twentyone
};

enum exception_self {
	error0, error1, error2, error3
};


int usage_mess(string message);




#endif
