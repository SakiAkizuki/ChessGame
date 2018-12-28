
#ifndef _BOARD_H_
#define _BOARD_H_
#include "block.h"
#include <vector>
#include "window.h"
#include <string>

class Piece;

class Board{
	std::vector<std::vector<Block>> blocks;
public:
	Board();
	void makeMove(std::vector<int> init, std::vector<int> end);

	//add piece to board,if there is a piece on that board remove it and add type
	//after adding the board will display
	void addPiece(Piece *p, std::vector<int> pos);
	void removePiece(std::vector<int> pos);
    
    //do the same as remove Piece but delete the piece
    void removePiece_setup(std::vector<int> pos);
    
	//check the current board is valid!
	bool checkValid();
    
    //return 1 if white is in check,
    //return 2 if black is in checked
    //return 0 if no one is in checked
	int isChecked(Piece *p);

	//return 0 if no winner yet
	//return 1 if white wins
	//return 2 if black wins
	int IsWon(char k);

	//print the whole board
	void GraphicDisplay(Xwindow &win);
    
	//print the whole board(text)
	void TextDisplay();
    
    //check the whole board is in checked or not
    int isChecked_ALL();
    
	std::vector<std::vector<Block>> getBoard();
    
    std::vector<int> find_p(char p_name);
    
	~Board();

    std::vector<std::vector<int>> kingmove(int r, int c);
};




#endif
