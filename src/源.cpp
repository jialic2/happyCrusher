#include "БъЭЗ.h"
#include "stdafx.h"
#include <iostream>
using namespace std;

int main() {
	vector<vector<int>> board = {
		{ 1,2,3,4,5,6,7,8 },
	{ 8,7,6,5,4,3,2,1 },
	{ 1,2,3,4,5,6,7,8 },
	{ 8,7,6,5,4,3,2,1 },
	{ 1,2,3,4,5,6,7,8 },
	{ 8,7,6,5,4,3,2,1 },
	{ 1,2,3,4,5,6,7,8 },
	{ 8,7,6,5,4,3,2,1 } };
	int board1[8][8] = {
		{ 1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1 },
	{ 1,1,1,1,1,1,1,1 } };
	int board2[8][8] = {
		{ 1,1,2,1,1,2,1,1 },
	{ 1,1,2,1,1,2,1,1 },
	{ 3,3,1,3,3,1,3,3 },
	{ 1,1,2,1,1,2,1,1 },
	{ 3,3,1,3,3,1,3,3 },
	{ 1,1,2,1,1,2,1,1 },
	{ 3,3,1,3,3,1,3,3 },
	{ 1,1,2,1,1,2,1,1 } };
	int board3[8][8] = {
		{ 1,2,3,4,5,6,7,8 },
	{ 2,3,4,5,6,7,8,7 },
	{ 3,4,5,6,7,8,7,6 },
	{ 4,5,6,1,8,7,1,5 },
	{ 5,6,1,8,7,6,3,4 },
	{ 6,7,8,7,6,5,4,3 },
	{ 7,8,7,6,3,4,3,2 },
	{ 8,7,6,5,4,3,2,1 } };
	if (can_make_move(board)) cout << "true" << endl;
	else cout << "false" << endl;
	/*cout << can_make_move(board1) << endl;
	cout << can_make_move(board2) << endl;
	cout << can_make_move(board3) << endl;*/
	return 0;
}

bool can_make_move(vector<vector<int>> board) { // this line should be commented 
					 // judging horizontal lines
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
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
		for (int i = 0; i < 8; i++) {
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

bool cancel() {
	int board[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == 0) continue;
			if (has_bomb(i, j)) board[i][j] = Bomb;
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == Bomb) {
				for (int posi = min(0, i - 1); posi < min(8, i + 2); posi++) {
					for (int posj = min(0, j - 1); posj < min(8, j + 2); posj++) {
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

void fall() {

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

bool has_bomb(int i, int j) {
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
		for (int pos = i - 1; pos >= 0; pos--) {
			if (board[pos][j] == board[i][j]) { 
				counts[board[pos][j]]++;
				board[pos][j] = Void; 
			}
			else break;
		}
		for (int pos = i + 1; pos < 8; pos++) {
			if (board[pos][j] == board[i][j]) {
				counts[board[pos][j]]++;
				board[pos][j] = Void;
			}
			else break;
		}
	}
	if ((count_y_direction > 2)) {
		for (int pos = j - 1; pos >= 0; pos--) {
			if (board[i][pos] == board[i][j]) { 
				counts[board[i][pos]]++;
				board[i][pos] = Void; 
			}
			else break;
		}
		for (int pos = j + 1; pos < 8; pos++) {
			if (board[i][pos] == board[i][j]) {
				counts[board[i][pos]]++;
				board[i][pos] = Void;
			}
			else break;
		}
	}
	if (count_x_direction > 2 || count_y_direction > 2) {
		counts[board[i][j]]++;
		board[i][j] = Void;
	}
	return (count_x_direction > 2 && count_y_direction > 2) || count_x_direction > 4 || count_y_direction > 4;
}