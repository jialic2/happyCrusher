#pragma once
#include "Person.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
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

	int damage = 0;

	vector<int> counts = {0, 0, 0, 0, 0, 0, 0, 0};

	int randomElement();
	void initialize_players();
	bool has_bomb(int x_index, int y_index);
	void cancel_helper(int x_index, int y_index);

public:

	int x_index1 = -1, y_index1, x_index2 = -1, y_index2;
	bool is_horizontal_ajacent = false;

	bool cancel();
	void fall();

	vector<vector<int>> board;
	vector<vector<int>> draw_board;
	vector<int> toBe;
	vector<int> pos;

	GameBoard();
	void construct_board();
	void construct_draw_board();
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
	bool trigger_cancelation();
	void construct_helper_vectors();
	vector<bool> fall_one_block();
	void return_hps();
};