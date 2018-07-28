#pragma once
#include "Person.h"
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

enum Element {
	Void, Fire, Water, Wood, Thunder, Shield, Power, Health, Bomb
};

class GameBoard {

	Person* first_player;
	Person* second_player;
	Person* attacking_player;
	Person* defending_player;
	Person* loser;

	int x_index1 = -1, y_index1, x_index2, y_index2;
	int damage = 0;

	vector<int> counts = {0, 0, 0, 0, 0, 0, 0, 0};

	int randomElement();
	void initialize_players();
	bool has_bomb(int x_index, int y_index);

public:

	bool cancel();
	void fall();
	vector<vector<int>> board;
	GameBoard();
	void construct_board();
	bool isBigEnough(int x_index, int y_index);
	bool receive_indices(int x_index, int y_index);
	void switch_players();
	bool can_make_move();
	void update_damage();
	void make_damage();
	bool either_is_dead();
	void generate_elements();
	void display_result();
	void switch_blocks();
};