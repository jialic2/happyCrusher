#include "Board.h";
#include <cstdlib>

int GameBoard::randomElement() {
	int num = rand() % 7 + 1;
	return num;
}

GameBoard::GameBoard() {
	construct_board();
	construct_draw_board();
	initialize_players();
}

void GameBoard::initialize_players() {
	first_player = new Person();
	second_player = new Person();
	if (rand() % 2 == 0) {
		attacking_player = first_player;
		defending_player = second_player;
	}
	else {
		attacking_player = second_player;
		defending_player = first_player;
	}
}

void GameBoard::construct_board() {
	vector<int> current;
	for (int i = 0; i < 8; i++) {
		current.push_back(0);
	}
	for (int i = 0; i < 8; i++) {
		board.push_back(current);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = randomElement();
			while (isBigEnough(i, j)) {
				board[i][j] = randomElement();
			}
		}
	}
}

void GameBoard::construct_draw_board() {
	vector<int> current;
	for (int i = 0; i < 8; i++) {
		current.push_back(0);
	}
	for (int i = 0; i < 8; i++) {
		draw_board.push_back(current);
	}
}

bool GameBoard::isBigEnough(int x_index, int y_index) {
	int count_x_direction = 0;
	int count_y_direction = 0;
	for (int x1 = x_index; x1 < x_index + 3; x1++) {
		if (x1 < 8 && x1 >= 0) {
			if (board[x1][y_index] == board[x_index][y_index]) {
				count_x_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	for (int x1 = x_index - 1; x1 > x_index - 3; x1--) {
		if (x1 < 8 && x1 >= 0) {
			if (board[x1][y_index] == board[x_index][y_index]) {
				count_x_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	for (int y1 = y_index; y1 < y_index + 3; y1++) {
		if (y1 < 8 && y1 >= 0) {
			if (board[x_index][y1] == board[x_index][y_index]) {
				count_y_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	for (int y1 = y_index - 1; y1 > y_index - 3; y1--) {
		if (y1 < 8 && y1 >= 0) {
			if (board[x_index][y1] == board[x_index][y_index]) {
				count_y_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	return count_x_direction > 2 || count_y_direction > 2;
}

bool GameBoard::can_make_move() { // this line should be commented 
									   // judging horizontal lines
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			int temp = board[i][j];
			if (board[i][j + 1] == temp) {
				if (j > 1) {
					if (i > 0 && board[i - 1][j - 1] == temp) return true;
					if (i < 7 && board[i + 1][j - 1] == temp) return true;
					if (j - 3 >= 0 && board[i][j - 2] == temp) return true;
				}
				if (j < 6) {
					if (i > 0 && board[i - 1][j + 2] == temp) return true;
					if (i < 7 && board[i + 1][j + 2] == temp) return true;
					if (j + 3 < 8 && board[i][j + 3] == temp) return true;
				}
			}
			if (j < 6 && board[i][j + 2] == temp) {
				if (i > 0 && board[i - 1][j + 1] == temp) return true;
				if (i < 7 && board[i + 1][j + 1] == temp) return true;
			}
		}
	}
	// judging vertical lines 
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i < 7; i++) {
			//TO-DO: change type back to element
			int temp = board[i][j];
			if (board[i + 1][j] == temp) {
				if (i > 1) {
					if (j > 0 && board[i - 1][j - 1] == temp) return true;
					if (j < 7 && board[i - 1][j + 1] == temp) return true;
					if (i - 3 >= 0 && board[i - 2][j] == temp) return true;
				}
				if (i < 6) {
					if (j > 0 && board[i + 2][j - 1] == temp) return true;
					if (j < 7 && board[i + 2][j + 1] == temp) return true;
					if (i + 3 < 8 && board[i + 3][j] == temp) return true;
				}
			}
			if (i < 6 && board[i + 2][j] == temp) {
				if (j > 0 && board[i + 1][j - 1] == temp) return true;
				if (j < 7 && board[i + 1][j + 1] == temp) return true;
			}
		}
	}
	return false;
}

bool GameBoard::receive_indices(int x_index, int y_index) {
	if (x_index1 == -1) {
		x_index1 = x_index;
		y_index1 = y_index;
		return false;
	}
	else {
		if (((x_index == x_index1 - 1 || x_index == x_index1 + 1) && y_index == y_index1)
			|| (y_index == y_index1 - 1 || y_index == y_index1 + 1) && x_index == x_index1) {
			draw_board = board;
			int temp = board[x_index1][y_index1];
			board[x_index1][y_index1] = board[x_index][y_index];
			board[x_index][y_index] = temp;
			if (isBigEnough(x_index1, y_index1) || isBigEnough(x_index, y_index)) {
				x_index2 = x_index;
				y_index2 = y_index;
				is_horizontal_ajacent = x_index1 == x_index2;
				board = draw_board;
				return true;
			}
			else {
				x_index1 = x_index;
				y_index1 = y_index;
				board = draw_board;
				return false;
			}
		}
		else {
			x_index1 = x_index;
			y_index1 = y_index;
			x_index2 = -1;
			return false;
		}
	}
}

void GameBoard::switch_players() {
	attacking_player = attacking_player == first_player ? second_player : first_player;
	defending_player = defending_player == first_player ? second_player : first_player;
}

bool GameBoard::cancel() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == Void) continue;
			if (has_bomb(i, j)) { 
				counts[board[i][j]]++;
				board[i][j] = Bomb;
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == Void) continue;
			cancel_helper(i, j);
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == Void) return true;
		}
	}
	return false;
}

bool GameBoard::has_bomb(int x_index, int y_index) {
	int count_x_direction = 0;
	int count_y_direction = 0;
	for (int x1 = x_index; x1 < x_index + 3; x1++) {
		if (x1 < 8 && x1 >= 0) {
			if (board[x1][y_index] == board[x_index][y_index]) {
				count_x_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	for (int x1 = x_index - 1; x1 > x_index - 3; x1--) {
		if (x1 < 8 && x1 >= 0) {
			if (board[x1][y_index] == board[x_index][y_index]) {
				count_x_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	for (int y1 = y_index; y1 < y_index + 3; y1++) {
		if (y1 < 8 && y1 >= 0) {
			if (board[x_index][y1] == board[x_index][y_index]) {
				count_y_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	for (int y1 = y_index - 1; y1 > y_index - 3; y1--) {
		if (y1 < 8 && y1 >= 0) {
			if (board[x_index][y1] == board[x_index][y_index]) {
				count_y_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	/*if (count_x_direction > 2) {
	for (int pos = x_index - 1; pos >= 0; pos--) {
	if (board[pos][y_index] == board[x_index][y_index]) {
	counts[board[pos][y_index]]++;
	board[pos][y_index] = Void;
	}
	else break;
	}
	for (int pos = x_index + 1; pos < 8; pos++) {
	if (board[pos][y_index] == board[x_index][y_index]) {
	counts[board[pos][y_index]]++;
	board[pos][y_index] = Void;
	}
	else break;
	}
	}
	if ((count_y_direction > 2)) {
	for (int pos = y_index - 1; pos >= 0; pos--) {
	if (board[x_index][pos] == board[x_index][y_index]) {
	counts[board[x_index][pos]]++;
	board[x_index][pos] = Void;
	}
	else break;
	}
	for (int pos = y_index + 1; pos < 8; pos++) {
	if (board[x_index][pos] == board[x_index][y_index]) {
	counts[board[x_index][pos]]++;
	board[x_index][pos] = Void;
	}
	else break;
	}
	}*/
	/*if (count_x_direction > 2 || count_y_direction > 2) {
	counts[board[x_index][y_index]]++;
	board[x_index][y_index] = Void;
	}*/
	if ((count_x_direction > 2 && count_y_direction > 2) || count_x_direction > 4 || count_y_direction > 4) {
		if (count_x_direction > 2) {
			for (int pos = x_index - 1; pos >= 0; pos--) {
				if (board[pos][y_index] == board[x_index][y_index]) {
					counts[board[pos][y_index]]++;
					board[pos][y_index] = Void;
				}
				else break;
			}
			for (int pos = x_index + 1; pos < 8; pos++) {
				if (board[pos][y_index] == board[x_index][y_index]) {
					counts[board[pos][y_index]]++;
					board[pos][y_index] = Void;
				}
				else break;
			}
		}
		if (count_y_direction > 2) {
			for (int pos = y_index - 1; pos >= 0; pos--) {
				if (board[x_index][pos] == board[x_index][y_index]) {
					counts[board[x_index][pos]]++;
					board[x_index][pos] = Void;
				}
				else break;
			}
			for (int pos = y_index + 1; pos < 8; pos++) {
				if (board[x_index][pos] == board[x_index][y_index]) {
					counts[board[x_index][pos]]++;
					board[x_index][pos] = Void;
				}
				else break;
			}
		}
	}
	return (count_x_direction > 2 && count_y_direction > 2) || count_x_direction > 4 || count_y_direction > 4;
}

void GameBoard::fall() {
	/*
	for (int j = 0; j < 8; j++) {
	int numVoid = 0;
	for (int i = 7; i >= 0; i--) {
	if (board[i][j] == Void) numVoid++;
	}
	for (int i = 7; i > 0; i--) {
	if (numVoid == 0) break;
	if (board[i][j] == Void) {
	numVoid--;
	for (int k = i - 1; k >= 0; k--) {
	board[k + 1][j] = board[k][j];
	board[k][j] = Void;
	}
	if (board[i][j] == Void) i++;
	}
	}
	}
	*/
	
	vector<int> toBe(8,0);
	vector<int> pos(8,7);
	//list<int> toBeHelper[8];
	for (int j = 0; j < 8; j++) {
		for (int i = 7; i >= 0; i--) {
			if (board[i][j] == Void) {
				toBe[j]++;
				//toBeHelper[j].push_back(i);
			}
		}
	}
	int max = 0;
	for (int i : toBe) max = (i > max) ? i : max;
	while (max > 0) {
		max--;
		for (int j = 0; j < 8; j++) {
			if (toBe[j] == 0) continue;
			else {
				toBe[j]--;
				while (pos[j] > 0) {
					if (board[pos[j]][j] == Void) {
						for (int k = pos[j] - 1; k >= 0; k--) {
							board[k + 1][j] = board[k][j];
							board[k][j] = Void;
						}
						if (board[pos[j]][j] != Void) pos[j]--;
						break;
					}
					pos[j]--;
				}
			}
		}

	}
	
}

void GameBoard::construct_helper_vectors() {
	toBe = vector<int>(8, 0);
	pos = vector<int>(8, 7);
	for (int j = 0; j < 8; j++) {
		for (int i = 7; i >= 0; i--) {
			if (board[i][j] == Void) {
				toBe[j]++;
				//toBeHelper[j].push_back(i);
			}
		}
	}
}

vector<bool> GameBoard::fall_one_block() {
	vector<bool> result(8, false);
	for (int j = 0; j < 8; j++) {
		if (toBe[j] == 0) continue;
		else {
			toBe[j]--;
			result[j] = true;
			while (pos[j] > 0) {
				if (board[pos[j]][j] == Void) {
					for (int k = pos[j] - 1; k >= 0; k--) {
						board[k + 1][j] = board[k][j];
						board[k][j] = Void;
					}
					break;
				}
				pos[j]--;
			}
		}
	}
	return result;
}

void GameBoard::update_damage() {
	int temp_damage = 0;
	for (int i : counts) {
		temp_damage += i * 5;
		temp_damage += i >= 5 ? 50 : 0;
	}
	temp_damage -= counts[Health] * 5;
	temp_damage -= counts[Power] * 5;
	temp_damage -= counts[Shield] * 5;
	if (counts[Shield] > 0) {
		attacking_player->hasShield = true;
	}
	
	damage = temp_damage;
}

bool GameBoard::either_is_dead() {
	if (first_player->getHp() <= 0) {
		loser = first_player;
	}
	if (second_player->getHp() <= 0) {
		loser = second_player;
	}
	return first_player->getHp() <= 0 || second_player->getHp() <= 0;
}

void GameBoard::make_damage() {
	attacking_player->setHp(attacking_player->getHp() + counts[Health] * 5);
	attacking_player->setMp(attacking_player->getMp() + counts[Power]);
	while (attacking_player->getMp() >= 10) {
		attacking_player->setMp(attacking_player->getMp() - 10);
		damage += 100;
	}
	if (defending_player->hasShield) {
		attacking_player->setHp(attacking_player->getHp() - damage);
	}
	else {
		defending_player->setHp(defending_player->getHp() - damage);
	}
	defending_player->hasShield = false;
	counts = { 0,0,0,0,0,0,0,0 };
}

void GameBoard::display_result() {
	loser->setHp(0);
	cout << "loser is " << ((loser == first_player) ? "first player" : "second player") << endl;
}

void GameBoard::generate_elements() {
	vector<vector<bool>> temp;
	for (int i = 0; i < 8; i++) {
		vector<bool> vec;
		for (int j = 0; j < 8; j++) {
			vec.push_back(false);
		}
		temp.push_back(vec);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == Void) {
				board[i][j] = randomElement();
				temp[i][j] = true;
			}
		}
	}
}

void GameBoard::switch_blocks() {
	int temp = board[x_index1][y_index1];
	board[x_index1][y_index1] = board[x_index2][y_index2];
	board[x_index2][y_index2] = temp;
	x_index1 = -1;
	x_index2 = -1;
}

void GameBoard::cancel_helper(int x_index, int y_index) {
	int count_x_direction = 0;
	int count_y_direction = 0;
	for (int x1 = x_index; x1 < x_index + 3; x1++) {
		if (x1 < 8 && x1 >= 0) {
			if (board[x1][y_index] == board[x_index][y_index]) {
				count_x_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	for (int x1 = x_index - 1; x1 > x_index - 3; x1--) {
		if (x1 < 8 && x1 >= 0) {
			if (board[x1][y_index] == board[x_index][y_index]) {
				count_x_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	for (int y1 = y_index; y1 < y_index + 3; y1++) {
		if (y1 < 8 && y1 >= 0) {
			if (board[x_index][y1] == board[x_index][y_index]) {
				count_y_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	for (int y1 = y_index - 1; y1 > y_index - 3; y1--) {
		if (y1 < 8 && y1 >= 0) {
			if (board[x_index][y1] == board[x_index][y_index]) {
				count_y_direction++;
			}
			else {
				break;
			}
		}
		else {
			break;
		}
	}
	if (count_x_direction > 2) {
		for (int pos = x_index - 1; pos >= 0; pos--) {
			if (board[pos][y_index] == board[x_index][y_index]) {
				counts[board[pos][y_index]]++;
				board[pos][y_index] = Void;
			}
			else break;
		}
		for (int pos = x_index + 1; pos < 8; pos++) {
			if (board[pos][y_index] == board[x_index][y_index]) {
				counts[board[pos][y_index]]++;
				board[pos][y_index] = Void;
			}
			else break;
		}
	}
	if ((count_y_direction > 2)) {
		for (int pos = y_index - 1; pos >= 0; pos--) {
			if (board[x_index][pos] == board[x_index][y_index]) {
				counts[board[x_index][pos]]++;
				board[x_index][pos] = Void;
			}
			else break;
		}
		for (int pos = y_index + 1; pos < 8; pos++) {
			if (board[x_index][pos] == board[x_index][y_index]) {
				counts[board[x_index][pos]]++;
				board[x_index][pos] = Void;
			}
			else break;
		}
	}
	if (count_x_direction > 2 || count_y_direction > 2) {
		counts[board[x_index][y_index]]++;
		board[x_index][y_index] = Void;
	}
}

bool GameBoard::trigger_cancelation() {
	bool result = false;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == Bomb) {
				result = true;
				for (int posi = max(0, i - 1); posi <= min(7, i + 1); posi++) {
					for (int posj = max(0, j - 1); posj <= min(7, j + 1); posj++) {
						if (board[posi][posj] == Void) continue;
						if (board[posi][posj] != Bomb) counts[board[posi][posj]]++;
						board[posi][posj] = Void;
					}
				}
			}
		}
	}
	return result;
}

void GameBoard::return_hps() {
	cout << first_player->getHp() << " " << second_player->getHp() << endl;
}

vector<int> GameBoard::return_hps_mps_shields() {
	vector<int> output;
	output.push_back(first_player->getHp());
	output.push_back(first_player->getMp());
	output.push_back(second_player->getHp());
	output.push_back(second_player->getMp());
	output.push_back(first_player->hasShield);
	output.push_back(second_player->hasShield);
	return output;
}