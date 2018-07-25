#pragma once

#include "ofMain.h"
#include "Board.h"

enum GameState {
	In_Progress, Selecting_Indices, Result
};

class ofApp : public ofBaseApp{
	GameState current_state;
	GameBoard current_board;

	public:
		void setup();
		void update();
		void draw();
		
		void mousePressed(int x, int y, int button);
};
