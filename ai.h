#ifndef _AI_H_
#define _AI_H_
#include "player.h"
#include "board.h"
//#include "piece.h"

class AI:public Player{
  int level;
  Board* board;
 public:
  AI(char color,int lvl,Board* board);
  bool isHuman() override;
  ~AI(){};
  vector<int> getMove(Player* opponent,int checked)override;
    //copy ctor
   AI( Player *other, Board *b);
};

#endif
