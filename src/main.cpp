#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context
	ofSetFrameRate(60);
	ofRunApp(new ofApp());
	
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	/*
	vector<vector<int>> board;
	board.push_back({ 6,7,7,1,6,5,6,7 });
	board.push_back({ 3,4,4,2,2,7,2,1 });
	board.push_back({ 6,7,7,4,2,4,6,2 });
	board.push_back({ 7,4,2,7,7,1,6,2 });
	board.push_back({ 1,5,1,5,6,4,3,6 });
	board.push_back({ 5,1,7,7,7,1,1,2 });
	board.push_back({ 2,3,7,3,2,6,2,1 });
	board.push_back({ 1,6,7,7,4,7,4,2 });
	GameBoard myBoard = GameBoard();
	myBoard.board = board;
	cout << myBoard.cancel() << endl;
	myBoard.fall();
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << myBoard.board[i][j] << " ";
		}
		cout << endl;
	}
	while (true) {

	}
	*/
}
