#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	current_board = GameBoard();
	current_state = Selecting_Indices;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (current_state == Cancel) {
		cancel_counter--;
		if (cancel_counter == 0) {
			current_state = Fall;
			current_board.construct_helper_vectors();
			current_board.draw_board = current_board.board;
			columns = current_board.fall_one_block();
			cancel_counter = 15;
		}
	}
	else if (current_state == Refresh) {
		refresh_counter--;
		if (refresh_counter == 0) {
			current_state = Selecting_Indices;
			refresh_counter = 15;
		}
	}
	else if (current_state == Generate) {
		generate_counter--;
		if (generate_counter == 0) {
			current_board.draw_board = current_board.board;
			generate_counter = 15;
			current_state = In_Progress;
		}
	}
	else if (current_state == Fall) {
		// current_board.fall();
		fall_counter--;
		if (fall_counter == 0) {
			bool fall_is_done = true;
			for (int i = 0; i < 8; i++) {
				if (columns[i] == true) {
					fall_is_done = false;
					break;
				}
			}
			if (fall_is_done) {
				current_board.draw_board = current_board.board;
				current_board.generate_elements();
				current_board.update_damage();
				current_state = Generate;
				fall_counter = 15;
				return;
			}
			fall_counter = 15;
			current_board.draw_board = current_board.board;
			columns = current_board.fall_one_block();
		}
	}
	else if (current_state == In_Progress) {
		current_board.draw_board = current_board.board;
		bool has_cancelled_sth = current_board.trigger_cancelation();
		has_cancelled_sth = has_cancelled_sth || current_board.cancel();
		if (has_cancelled_sth) {
			current_state = Cancel;
			return;
		}
		/*
		bool hasCancelledSth = true;
		while (hasCancelledSth) {
			current_board.draw_board = current_board.board;
			hasCancelledSth = current_board.cancel();
			current_board.fall();
			// bomb
			if (current_board.trigger_cancelation()) {
				current_board.fall();
			}
			current_board.generate_elements();
			current_board.update_damage();
			//cancel
			//deduct health at the same time, check if either player is dead
		}
		*/
		//display end of round: damage, shield,...
		current_board.make_damage();
		if (current_board.either_is_dead()) { //if one player is dead
			current_state = Result;
			current_board.return_hps();
			return;
		}
		current_state = Selecting_Indices;
		current_board.return_hps();
		current_board.switch_players();
		//switch players
		//if cannot make a move, contruct a new board
		//TO-DO: ����Ч��
		while (!current_board.can_make_move()) {
			current_state = Refresh;
			current_board.construct_board();
			current_board.draw_board = current_board.board;
		}
	}
	else if (current_state == Selecting_Indices) {
		if (current_board.x_index1 != -1 && current_board.x_index2 != -1) {
			delay_counter--;
			if (delay_counter == 0) {
				current_state = Switch;
				temp_x1 = current_board.x_index1;
				temp_x2 = current_board.x_index2;
				temp_y1 = current_board.y_index1;
				temp_y2 = current_board.y_index2;
				delay_counter = 3;
			}
		}
	}
	else if (current_state == Switch) {
		if (!switch_flag) {
			if (switch_counter > 0) {
				switch_counter--;
			}
			else {
				switch_flag = true;
				switch_counter = 15;
				current_board.switch_blocks();
			}
		}
		else {
			if (switch_counter > 0) {
				switch_counter--;
			}
			else {
				switch_flag = false;
				switch_counter = 15;
				current_state = In_Progress;
			}
		}
	}
	else if (current_state == Result) {
		//display result
		current_board.display_result();
		cin.get();
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	vector<int> properties = current_board.return_hps_mps_shields();
	string message = "HP: " + std::to_string(properties[0]);
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(message, 100, 260);
	message = "MP: " + std::to_string(properties[1]);
	ofDrawBitmapString(message, 100, 300);
	message = "HasShield: " + std::to_string(properties[4] == 1);
	ofDrawBitmapString(message, 100, 340);
	message = "HP: " + std::to_string(properties[2]);
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(message, 810, 260);
	message = "MP: " + std::to_string(properties[3]);
	ofDrawBitmapString(message, 810, 300);
	message = "HasShield: " + std::to_string(properties[5]);
	ofDrawBitmapString(message, 810, 340);
	drawBoard();
	if (current_state == Selecting_Indices) {
		drawSelection();
	}
	else if (current_state == Switch) {
		drawSwitch();
	}
	else if (current_state == Cancel) {
		drawCancel();
	}
	else if (current_state == Fall) {
		drawFall();
	}
	else if (current_state == Generate) {
		drawGenerate();
	}
	else if (current_state == Refresh) {
		drawRefresh();
	}
	//draw board
	//draw players + info
	//draw bomb
	//draw cancellation
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (current_state == Selecting_Indices) {
		if (!(x < 260 || x >= 740 || y < 260 || y >= 740)) {
			if (current_board.x_index1 != -1 && current_board.x_index2 != -1) {
				return;
			}
			int x_index = (x - 260) / 60;
			int y_index = (y - 260) / 60;
			current_board.receive_indices(y_index, x_index);
		}
	}
}

void ofApp::drawSelection() {
	if (current_board.x_index1 == -1) {
		return;
	}
	int left = 260 + current_board.y_index1 * 60;
	int up = 260 + current_board.x_index1 * 60;
	ofSetHexColor(0x000000);
	ofDrawRectangle(left, up, 60, 60);
	ofSetHexColor(colors[current_board.board[current_board.x_index1][current_board.y_index1]]);
	ofDrawRectangle(left + 5, up + 5, 50, 50);
	if (current_board.x_index2 == -1) {
		return;
	}
	left = 260 + current_board.y_index2 * 60;
	up = 260 + current_board.x_index2 * 60;
	ofSetHexColor(0x000000);
	ofDrawRectangle(left, up, 60, 60);
	ofSetHexColor(colors[current_board.board[current_board.x_index2][current_board.y_index2]]);
	ofDrawRectangle(left + 5, up + 5, 50, 50);
}

void ofApp::drawSwitch() {
	if (current_board.is_horizontal_ajacent) {
		if (!switch_flag) {
			int left = min(temp_y1, temp_y2) * 60 + 260;
			int width = 4 * (15 - switch_counter);
			int up = 260 + temp_x1 * 60;
			ofSetHexColor(0xEEEEE0);
			ofDrawRectangle(left, up, width, 60);
			left += 60 + 60 - width;
			ofDrawRectangle(left, up, width, 60);
		}
		else {
			int left = min(temp_y1, temp_y2) * 60 + 260;
			int width = 4 * switch_counter;
			int up = 260 + temp_x1 * 60;
			ofSetHexColor(0xEEEEE0);
			ofDrawRectangle(left, up, width, 60);
			left += 60 + 60 - width;
			ofDrawRectangle(left, up, width, 60);
		}
	}
	else {
		if (!switch_flag) {
			int up = min(temp_x1, temp_x2) * 60 + 260;
			int height = 4 * (15 - switch_counter);
			int left = 260 + temp_y1 * 60;
			ofSetHexColor(0xEEEEE0);
			ofDrawRectangle(left, up, 60, height);
			up += 60 + 60 - height;
			ofDrawRectangle(left, up, 60, height);
		}
		else {
			int up = min(temp_x1, temp_x2) * 60 + 260;
			int height = 4 * switch_counter;
			int left = 260 + temp_y1 * 60;
			ofSetHexColor(0xEEEEE0);
			ofDrawRectangle(left, up, 60, height);
			up += 60 + 60 - height;
			ofDrawRectangle(left, up, 60, height);
		}
	}
}

void ofApp::drawCancel() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (current_board.board[i][j] == Void) {
				ofSetHexColor(colors[current_board.draw_board[i][j]]);
				ofDrawRectangle(260 + j * 60 + 30 - 2 * cancel_counter,
					260 + i * 60 + 30 - 2 * cancel_counter,
					4 * cancel_counter,
					4 * cancel_counter);
			}
		}
	}
}

void ofApp::drawFall() {
	for (int i = 0; i < 8; i++) {
		if (columns[i] == true) {
			ofSetHexColor(colors[Void]);
			ofDrawRectangle(260 + i * 60, 260, 60, current_board.pos[i] * 60 + 60);
			for (int j = 0, n = current_board.pos[i]; j < n; j++) {
				ofSetHexColor(colors[current_board.draw_board[j][i]]);
				ofDrawRectangle(260 + i * 60, 260 + j * 60 + 60 - 4 * fall_counter, 60, 60);
			}
		}
	}
}

void ofApp::drawGenerate() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (current_board.draw_board[i][j] == Void) {
				ofSetHexColor(colors[Void]);
				ofDrawRectangle(260 + j * 60, 260 + i * 60, 60, 60);
				ofSetHexColor(colors[current_board.board[i][j]]);
				ofDrawRectangle(260 + j * 60 + 2 * generate_counter,
					260 + i * 60 + 2 * generate_counter,
					4 * (15 - generate_counter),
					4 * (15 - generate_counter));
			}
		}
	}
}

void ofApp::drawRefresh() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int left = 260 + j * 60;
			int up = 260 + i * 60;
			ofSetHexColor(colors[Void]);
			ofDrawRectangle(left, up, 60, 60);
			ofSetHexColor(colors[current_board.board[i][j]]);
			ofDrawRectangle(left + 2 * refresh_counter, up + 2 * refresh_counter, 
				60 - 4 * refresh_counter, 60 - 4 * refresh_counter);
		}
	}
}

void ofApp::drawBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int left = 260 + j * 60;
			int up = 260 + i * 60;
			ofSetHexColor(colors[current_board.board[i][j]]);
			ofDrawRectangle(left, up, 60, 60);
		}
	}
}