#include "human.h"
Human::Human(char color):Player{color}{}
bool Human::isHuman(){
  return true;
}
vector<int> Human::getMove(Player* opponent,int checked){return {-1,-1};}
