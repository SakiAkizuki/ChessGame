
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "piece.h"

class Block{
	const int x; //row number
	const int y;// col number
	
	//col is the corlor of the block, if there's no peiece on that,the color should be green
	//otherwise, the corlor is the color of the player
	//c is the character of the block (either piece symbol or -)
	char c;
public:
    Piece *p;
	Block(int x, int y,Piece *p = nullptr);
	
	//if there is a piece on the block, remove it, otherwise, do nothing
	//notice that this function is only cut the connection between block and piece
	//not remove the piece away the game(delete the piece)
    void remove();
	
	//return the pointer of the piece
	Piece* getPiece();
	
	//connect the the block to piece and change the color  
	void addpiece(Piece *p);
	
	//get the value of c
	char get_c() const;
    
    //do the same as remove but delete the piece.
    void remove_setup();
    
	//free all pieces on the blocks
	~Block(){};
    
};

#endif 
