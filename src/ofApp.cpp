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
			current_board.generate_elements();
			//cancel
			//deduct health at the same time, check if either player is dead
			if (current_board.either_is_dead()) { //if one player is dead
				current_state = Result;
			}
		}
		//display end of round: damage, shield,...
		current_board.make_damage();
		current_state = Selecting_Indices;
		current_board.switch_players();
		//switch players
		//if cannot make a move, contruct a new board
		//TO-DO: ¶¯»­Ð§¹û
		while (!current_board.can_make_move()) {
			current_board.construct_board();
		}
	}
	else if (current_state == Result) {
		//display result
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			int left = 260 + j * 60;
			int up = 260 + i * 60;
			ofSetHexColor(colors[current_board.board[i][j]]);
			ofDrawRectangle(left, up, 60, 60);
		}
	}
	//draw board
	//draw players + info
	//draw bomb
	//draw cancellation
}



//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (!(x < 260 || x >= 740 || y < 260 || y >= 740)) {
		cout << "mouse_pressed" << endl;
		int x_index = (x - 260) / 60;
		int y_index = (y - 260) / 60;
		bool has_selected_both = current_board.receive_indices(y_index, x_index);
		if (has_selected_both) {
			current_state = In_Progress;
			current_board.switch_blocks();
		}
	}
}

