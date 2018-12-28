#include "player.h"
#include <vector>
class Piece;
using namespace std;
Player::Player(char color):wb{color},king{nullptr}{}
Player::~Player(){
  pieces.clear();
}
void Player::removePiece(vector<int> pos){
    int sizeofpiece = pieces.size();
  for(int i=0;i< sizeofpiece;i++){
    if(pieces[i]->getPos()==pos){
      pieces.erase(pieces.begin()+i);
    }
  }
}
