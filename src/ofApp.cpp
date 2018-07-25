#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	current_board = GameBoard();
	current_state = Selecting_Indices;
}

//--------------------------------------------------------------
void ofApp::update(){
	if (current_state == In_Progress) {
		while ()
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

}



//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (!(x < 260 || x >= 740 || y < 260 || y >= 740)) {
		int x_index = (x - 260) / 60;
		int y_index = (y - 260) / 60;
		bool has_selected_both = current_board.receive_indices(x_index, y_index);
		if (has_selected_both) {
			current_state = In_Progress;
		}
	}
}
