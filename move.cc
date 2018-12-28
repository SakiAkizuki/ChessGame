#include "move.h"
#include <vector>
using namespace std;
Move::Move(vector<int> init,vector<int> end, char pc, char cpc){
  this->init=init;
  this->end=end;
  this->piece=pc;
  this->capturedPiece=cpc;
}
vector<int> Move::getInit(){
  return this->init;
}
vector<int> Move::getEnd(){
  return this->end;
}
char Move::getPiece(){
  return this->piece;
}
char Move::getCapturedPiece(){
  return this->capturedPiece;
}
Move::~Move(){}
