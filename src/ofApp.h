#pragma once

#include "ofMain.h"
#include "Board.h"

enum GameState {
	In_Progress, Selecting_Indices, Result
};

class ofApp : public ofBaseApp {
	GameState current_state;
	GameBoard current_board;
	
	vector<int> colors = { 0xEEEEE0 , 0xff8c00 , 0x87CEEB, 0x76EE00, 0xFFFF00, 0xCD8500, 0x7D26CD, 0xEE0000, 0x080808 };
	
	public:
		void setup();
		void update();
		void draw();
		
		void mousePressed(int x, int y, int button);
};
