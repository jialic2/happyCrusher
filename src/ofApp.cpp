#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	current_board = GameBoard();
	current_state = Selecting_Indices;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (current_state == In_Progress) {
		bool hasCancelledSth = true;
		while (hasCancelledSth) {
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
		//TO-DO: ¶¯»­Ð§¹û
		while (!current_board.can_make_move()) {
			current_board.construct_board();
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
				switch_counter = 20;
				current_board.switch_blocks();
			}
		}
		else {
			if (switch_counter > 0) {
				switch_counter--;
			}
			else {
				switch_flag = false;
				switch_counter = 20;
				current_state = In_Progress;
			}
		}
	}
	else if (current_state == Result) {
		//display result
		current_board.display_result();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	drawBoard();
	if (current_state == Selecting_Indices) {
		drawSelection();
	}
	else if (current_state == Switch) {
		drawSwitch();
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
			cout << "mouse_pressed" << endl;
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
			int width = 3 * (20 - switch_counter);
			int up = 260 + temp_x1 * 60;
			ofSetHexColor(0xffffff);
			ofDrawRectangle(left, up, width, 60);
			left += 60 + 60 - width;
			ofDrawRectangle(left, up, width, 60);
		}
		else {
			int left = min(temp_y1, temp_y2) * 60 + 260;
			int width = 3 * switch_counter;
			int up = 260 + temp_x1 * 60;
			ofSetHexColor(0xffffff);
			ofDrawRectangle(left, up, width, 60);
			left += 60 + 60 - width;
			ofDrawRectangle(left, up, width, 60);
		}
	}
	else {
		if (!switch_flag) {
			int up = min(temp_x1, temp_x2) * 60 + 260;
			int height = 3 * (20 - switch_counter);
			int left = 260 + temp_y1 * 60;
			ofSetHexColor(0xffffff);
			ofDrawRectangle(left, up, 60, height);
			up += 60 + 60 - height;
			ofDrawRectangle(left, up, 60, height);
		}
		else {
			int up = min(temp_x1, temp_x2) * 60 + 260;
			int height = 3 * switch_counter;
			int left = 260 + temp_y1 * 60;
			ofSetHexColor(0xffffff);
			ofDrawRectangle(left, up, 60, height);
			up += 60 + 60 - height;
			ofDrawRectangle(left, up, 60, height);
		}
	}
}
void ofApp::drawCancel() {

}
void ofApp::drawFall() {

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