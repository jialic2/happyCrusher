#pragma once
#include "src\Person.h"
#include <vector>
using namespace std;

enum Element {
	Void, Fire, Water, Wood, Thunder, Shield, Power, Health
};

class GameBoard {

	Person* first_player;
	Person* second_player;
	Person* attacking_player;
	Person* defending_player;

	int x_index1 = -1, y_index1, x_index2, y_index2;

	vector<int> counts = {0, 0, 0, 0, 0, 0, 0};

	Element randomElement();
	void construct_board();
	void initialize_players();
	bool can_make_move();

public:
	
	vector<vector<Element>> board;
	GameBoard();
	bool isBigEnough(int x_index, int y_index);
	void play_one_round();
	bool receive_indices(int x_index, int y_index);

};