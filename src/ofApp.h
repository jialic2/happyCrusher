#pragma once

#include "ofMain.h"
#include "Board.h"

enum GameState {
	In_Progress, Selecting_Indices, Result, Switch, Cancel, Fall, DrawBomb
};

class ofApp : public ofBaseApp {
	int delay_counter = 18;
	int switch_counter = 20;
	bool switch_flag = false;
	int temp_x1, temp_y1, temp_x2, temp_y2;

	GameState current_state;
	GameBoard current_board;
	
	vector<int> colors = { 0xEEEEE0 , 0xff8c00 , 0x87CEEB, 0x76EE00, 0xFFFF00, 0x333333, 0x7D26CD, 0xF4CCCC, 0x080808 };
	
	public:
		void setup();
		void update();
		void draw();
		
		void drawSwitch();
		void drawCancel();
		void drawFall();
		void drawBoard();
		void drawSelection();

		void mousePressed(int x, int y, int button);
};