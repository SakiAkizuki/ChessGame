#ifndef HUMAN_H_
#define HUMAN_H_
#include "player.h"
class Human:public Player{
 public:
  Human(char color);
  bool isHuman() override;
  vector<int> getMove(Player* opponent,int checked)override;
  ~Human(){};
};
#endif
