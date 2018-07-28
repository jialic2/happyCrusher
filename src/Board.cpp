#include "Board.h";
#include <cstdlib>

int GameBoard::randomElement() {
	int num = rand() % 7 + 1;
	return num;
}

GameBoard::GameBoard() {
	construct_board();
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
	cout << x_index << " " << y_index << endl;
	if (x_index1 == -1) {
		x_index1 = x_index;
		y_index1 = y_index;
		return false;
	}
	else {
		if (((x_index == x_index1 - 1 || x_index == x_index1 + 1) && y_index == y_index1)
			|| (y_index == y_index1 - 1 || y_index == y_index1 + 1) && x_index == x_index1) {
			//two blocks are ajacent
			x_index2 = x_index;
			y_index2 = y_index;
			return true;
		}
		else {
			x_index1 = x_index;
			y_index1 = y_index;
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
			if (has_bomb(i, j)) board[i][j] = Bomb;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == 8) {
				for (int posi = max(0, i - 1); posi < min(8, i + 2); posi++) {
					for (int posj = max(0, j - 1); posj < min(8, j + 2); posj++) {
						if (board[posi][posj] == Void) continue;
						counts[board[posi][posj]]++;
						board[posi][posj] = Void;
					}
				}
			}
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
	return (count_x_direction > 2 && count_y_direction > 2) || count_x_direction > 4 || count_y_direction > 4;
}

void GameBoard::fall() {
	/*for (int j = 0; j < 8; j++) {
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
	}*/
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
}

void GameBoard::update_damage() {
	int temp_damage = 0;
	for (int i : counts) {
		temp_damage += i * 5;
		temp_damage += i >= 5 ? 50 : 0;
	}
	temp_damage -= counts[Health] * 5;
	temp_damage -= counts[Power] * 5;
	attacking_player->setHp(attacking_player->getHp() + counts[Health] * 5);
	attacking_player->setMp(attacking_player->getMp() + counts[Power]);
	while (attacking_player->getMp() >= 10) {
		attacking_player->setMp(attacking_player->getMp() - 10);
		temp_damage += 100;
	}
	damage = temp_damage;
}

bool GameBoard::either_is_dead() {
	if (defending_player->hasShield) {
		
		if (attacking_player->getHp() <= damage) {
			loser = attacking_player;
			return true;
		}
		return false;
	}
	else {
		if (defending_player->getHp() <= damage) {
			loser = defending_player;
			return true;
		}
		return false;
	}
}

void GameBoard::make_damage() {
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
	cout << "loser is " << (loser == first_player) ? "first player" : "second player";
	cout << endl;
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
}