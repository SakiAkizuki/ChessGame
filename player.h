#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include "piece.h"
#include "king.h"
class Piece;
class Player{
  
  //char type;
 public:
    char wb; //
    King* king;
    std::vector<Piece*> pieces;
    void removePiece(std::vector<int>);
    Player(char color);
    virtual bool isHuman()=0;    
    virtual vector<int> getMove(Player* opponent,int checked)=0;
    virtual ~Player() =0;
};
#endif


