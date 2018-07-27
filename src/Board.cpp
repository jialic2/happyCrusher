#include "Board.h";
#include <cstdlib>


Element GameBoard::randomElement() {
	int num = rand() % 7 + 1;
	return (Element) num;
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
	vector<Element> current;
	for (int i = 0; i < 8; i++) {
		current.push_back(Void);
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
}

bool GameBoard::can_make_move() { // this line should be commented 
									   // judging horizontal lines
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 7; j++) {
			Element temp = board[i][j];
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
			Element temp = board[i][j];
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

void GameBoard::play_one_round() {
	attacking_player->hasShield = false;
	//To-Do: check if can make a valid move
	while (!can_make_move()) {
		construct_board();
	}
	//To-Do: if not, construct board
	int x_index1, x_index2, y_index1, y_index2;
	//indices selected by the player

	//if the defending player has a shield, ·´µ¯£¡£¡£¡£¡£¡

	//check if move is valid
	//if not, deduct some points of hp
	//else, keep canceling
	//generate new elements from top
	//increment counts along

	//check if either player is dead

	//after that, reset counts
}

void fall() {
	for (int j = 0; j < 8; j++) {
		for (int i = 7; i > 0; i--) {
			if (board[i][j] == Void) {
				for (int k = i - 1; k >= 0; k--) {
					board[k + 1][j] = board[k][j];
					board[k][j] = Void;
				}
			}
		}
	}
}

void GameBoard::generate_elements() {
	vector<vector<bool>> temp;
	for (int i = 0; i < 8; i++) {
		vector<int> vec;
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