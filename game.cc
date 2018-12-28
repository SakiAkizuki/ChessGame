#include "game.h"
#include "bishop.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include <vector>
using namespace std;
Game::Game(Player* pW, Player* pB,Board* board,bool setup){
  this->pW=pW;
  this->pB=pB;
  this->board=board;
  this->currentPlayer='w';
  if(setup==0){
    Rook* r1=new Rook(0,0,'r',board);
    Knight* n1=new Knight(0,1,'n',board);
    Bishop* b1=new Bishop(0,2,'b',board);
    Queen* q1=new Queen(0,3,'q',board);
    King* k1=new King(0,4,'k',board);
    Bishop* b2=new Bishop(0,5,'b',board);
    Knight* n2=new Knight(0,6,'n',board);
    Rook* r2=new Rook(0,7,'r',board);

    Rook* r3=new Rook(7,0,'R',board); 
    Knight* n3=new Knight(7,1,'N',board);
    Bishop* b3=new Bishop(7,2,'B',board);
    Queen* q2=new Queen(7,3,'Q',board);
    King* k2=new King(7,4,'K',board);
    Bishop* b4=new Bishop(7,5,'B',board);
    Knight* n4=new Knight(7,6,'N',board);
    Rook* r4=new Rook(7,7,'R',board);

    this->board->addPiece(r1,{0,0});
    this->board->addPiece(n1,{0,1});
    this->board->addPiece(b1,{0,2});
    this->board->addPiece(q1,{0,3});
    this->board->addPiece(k1,{0,4});
    this->board->addPiece(b2,{0,5});
    this->board->addPiece(n2,{0,6});
    this->board->addPiece(r2,{0,7});
    
    this->board->addPiece(r3,{7,0});
    this->board->addPiece(n3,{7,1});
    this->board->addPiece(b3,{7,2});
    this->board->addPiece(q2,{7,3});
    this->board->addPiece(k2,{7,4});
    this->board->addPiece(b4,{7,5});
    this->board->addPiece(n4,{7,6});
    this->board->addPiece(r4,{7,7});


    pB->pieces.push_back(r1);
    pB->pieces.push_back(n1);
    pB->pieces.push_back(b1);
    pB->pieces.push_back(q1);
    pB->pieces.push_back(k1);
    pB->pieces.push_back(b2);
    pB->pieces.push_back(n2);
    pB->pieces.push_back(r2);
    pB->king=k1;
    pW->pieces.push_back(r3);
    pW->pieces.push_back(n3);
    pW->pieces.push_back(b3);
    pW->pieces.push_back(q2);
    pW->pieces.push_back(k2);
    pW->pieces.push_back(b4);
    pW->pieces.push_back(n4);
    pW->pieces.push_back(r4);
    pB->king=k2;
    for(int i=0;i<8;i++){
      Pawn* p=new Pawn(6,i,'P',board);
      this->board->addPiece(p,{6,i});
      pW->pieces.push_back(p);
    }

    for(int i=0;i<8;i++){
      Pawn* p=new Pawn(1,i,'p',board);
      this->board->addPiece(p,{1,i});
      pB->pieces.push_back(p);
    }
  }else{
  }
  
}
Game::~Game(){
  delete this->pW;
  delete this->pB;
  delete this->board;
}
void Game::getSuggestion(int index){
    if (index==0){
        vector<int> temp=this->pW->getMove(this->pB,0);
    }else{
        vector<int> temp=this->pB->getMove(this->pW,0);
    }
}
void Game::aiMove(int index){

  if (index==0){
    vector<int> temp;
    if(Game::isChecked()==1){
      temp=this->pW->getMove(this->pB,1);
    }else{
      temp=this->pW->getMove(this->pB,0);
    }
    vector<int> init={temp[0],temp[1]};
    vector<int> end={temp[2],temp[3]};
    Game::makeMove(init,end);
  }else{
    vector<int> temp;
    if(Game::isChecked()==2){
      temp=this->pB->getMove(this->pW,1);
    }else{
      temp=this->pB->getMove(this->pW,0);
    }
    vector<int> init={temp[0],temp[1]};
    vector<int> end={temp[2],temp[3]};
    Game::makeMove(init,end);
  }
}
void Game::makeMove(vector<int> init,vector<int> end){
  //char pc=this->board->getBoard()[init[0]][init[1]].getPiece()->getType();
  //char cpc=this->board->getBoard()[end[0]][end[1]].getPiece()->getType();

  Game::addHistory(init,end);

  if (this->board->getBoard()[end[0]][end[1]].getPiece()!=nullptr){
    if(this->board->getBoard()[end[0]][end[1]].getPiece()->getColour()=='w'){
      pW->removePiece(end);
    }else if(this->board->getBoard()[end[0]][end[1]].getPiece()->getColour()=='b'){
      pB->removePiece(end);
    }
  }

  this->board->makeMove(init,end);

}

void Game::addPiece(char type,vector<int> pos){
    if(type=='r'){
      Rook* r=new Rook(pos[0],pos[1],'r',board);
      this->board->addPiece(r,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pB->removePiece(pos);
      }
      this->pB->pieces.push_back(r);

    }
    else if(type=='n'){
      Knight* n=new Knight(pos[0],pos[1],'n',board);
      this->board->addPiece(n,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pB->removePiece(pos);
      }
      this->pB->pieces.push_back(n);

    }
     else if(type=='b'){
      Bishop* b=new Bishop(pos[0],pos[1],'b',board);
      this->board->addPiece(b,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pB->removePiece(pos);
      }
      this->pB->pieces.push_back(b);

    }
     else if(type=='q'){
      Queen* q=new Queen(pos[0],pos[1],'q',board);
      this->board->addPiece(q,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pB->removePiece(pos);
      }
      this->pB->pieces.push_back(q);

    }
     else if(type=='k'){
      King* k=new King(pos[0],pos[1],'k',board);
      this->board->addPiece(k,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pB->removePiece(pos);
      }
      this->pB->pieces.push_back(k);
      this->pB->king=k;

    }
     else if(type=='p'){
      Pawn* p=new Pawn(pos[0],pos[1],'p',board);
      this->board->addPiece(p,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pW->removePiece(pos);
      }
      this->pB->pieces.push_back(p);

    }
     else if(type=='R') {
      Rook* r2=new Rook(pos[0],pos[1],'R',board);
      this->board->addPiece(r2,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pW->removePiece(pos);
      }
      this->pW->pieces.push_back(r2);

    }
     else if(type=='N'){
      Knight* n2=new Knight(pos[0],pos[1],'N',board);
      this->board->addPiece(n2,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pW->removePiece(pos);
      }
      this->pW->pieces.push_back(n2);

    }
     else if(type=='B'){
      Bishop* b2=new Bishop(pos[0],pos[1],'B',board);
      this->board->addPiece(b2,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pW->removePiece(pos);
      }
      this->pW->pieces.push_back(b2);

    }
     else if(type=='Q'){
      Queen* q2=new Queen(pos[0],pos[1],'Q',board);
      this->board->addPiece(q2,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pW->removePiece(pos);
      }
      this->pW->pieces.push_back(q2);

    }
     else if(type=='K'){
      King* k2=new King(pos[0],pos[1],'K',board);
      this->board->addPiece(k2,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pW->removePiece(pos);
      }
      this->pW->pieces.push_back(k2);
      this->pB->king=k2;

    }
     else if(type=='P'){
      Pawn* p2=new Pawn(pos[0],pos[1],'P',board);
      this->board->addPiece(p2,pos);
      if(board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
	pW->removePiece(pos);
      }
      this->pW->pieces.push_back(p2);

    }
    
 
  
}
void Game::removePiece(vector<int> pos){
  if(this->board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
    if(this->board->getBoard()[pos[0]][pos[1]].getPiece()->getColour()=='w'){
      pW->removePiece(pos);
    }else if(this->board->getBoard()[pos[0]][pos[1]].getPiece()->getColour()=='b'){
      pB->removePiece(pos);
    }
  }
  this->board->removePiece(pos);
}
/*void Game::setTurn(char type){
  this->currentPlayer=type;
}
*/
bool Game::checkValid(){
  return this->board->checkValid();
}
int Game::isChecked(){
  return this->board->isChecked_ALL();
}
int Game::isWon(int playerindex){
    if(playerindex  == 1){
        return this->board->IsWon('k');
    }else{
        return this->board->IsWon('K');
    }
}

void Game::addHistory(vector<int> init, vector<int> end){
  //cout<<init[0]<<init[1]<<end[0]<<end[1]<<endl;
  char c1=this->board->getBoard()[init[0]][init[1]].getPiece()->getType();
  char c2;
  if(this->board->getBoard()[end[0]][end[1]].getPiece()!=nullptr){
    c2=this->board->getBoard()[end[0]][end[1]].getPiece()->getType();
  }
  Move m(init,end,c1,c2);
  this->history.push_back(m);
}

void Game::removePiece_setup(vector<int> pos){
    if(this->board->getBoard()[pos[0]][pos[1]].getPiece()!=nullptr){
        if(this->board->getBoard()[pos[0]][pos[1]].getPiece()->getColour()=='w'){
            pW->removePiece(pos);
        }else if(this->board->getBoard()[pos[0]][pos[1]].getPiece()->getColour()=='b'){
            pB->removePiece(pos);
        }
    }
    this->board->removePiece_setup(pos);
}


void Game::changeboard(Board *board){
    this->board = board;
}
void Game::default_board(){
    this->currentPlayer='w';
    Rook* r1=new Rook(0,0,'r',board);
    Knight* n1=new Knight(0,1,'n',board);
    Bishop* b1=new Bishop(0,2,'b',board);
    Queen* q1=new Queen(0,3,'q',board);
    King* k1=new King(0,4,'k',board);
    Bishop* b2=new Bishop(0,5,'b',board);
    Knight* n2=new Knight(0,6,'n',board);
    Rook* r2=new Rook(0,7,'r',board);
    
    Rook* r3=new Rook(7,0,'R',board);
    Knight* n3=new Knight(7,1,'N',board);
    Bishop* b3=new Bishop(7,2,'B',board);
    Queen* q2=new Queen(7,3,'Q',board);
    King* k2=new King(7,4,'K',board);
    Bishop* b4=new Bishop(7,5,'B',board);
    Knight* n4=new Knight(7,6,'N',board);
    Rook* r4=new Rook(7,7,'R',board);
    
    this->board->addPiece(r1,{0,0});
    this->board->addPiece(n1,{0,1});
    this->board->addPiece(b1,{0,2});
    this->board->addPiece(q1,{0,3});
    this->board->addPiece(k1,{0,4});
    this->board->addPiece(b2,{0,5});
    this->board->addPiece(n2,{0,6});
    this->board->addPiece(r2,{0,7});
    
    this->board->addPiece(r3,{7,0});
    this->board->addPiece(n3,{7,1});
    this->board->addPiece(b3,{7,2});
    this->board->addPiece(q2,{7,3});
    this->board->addPiece(k2,{7,4});
    this->board->addPiece(b4,{7,5});
    this->board->addPiece(n4,{7,6});
    this->board->addPiece(r4,{7,7});
    
    
    pB->pieces.push_back(r1);
    pB->pieces.push_back(n1);
    pB->pieces.push_back(b1);
    pB->pieces.push_back(q1);
    pB->pieces.push_back(k1);
    pB->pieces.push_back(b2);
    pB->pieces.push_back(n2);
    pB->pieces.push_back(r2);
    
    pW->pieces.push_back(r3);
    pW->pieces.push_back(n3);
    pW->pieces.push_back(b3);
    pW->pieces.push_back(q2);
    pW->pieces.push_back(k2);
    pW->pieces.push_back(b4);
    pW->pieces.push_back(n4);
    pW->pieces.push_back(r4);
    
    for(int i=0;i<8;i++){
        Pawn* p=new Pawn(6,i,'P',board);
        this->board->addPiece(p,{6,i});
        pW->pieces.push_back(p);
    }
    
    for(int i=0;i<8;i++){
        Pawn* p=new Pawn(1,i,'p',board);
        this->board->addPiece(p,{1,i});
        pB->pieces.push_back(p);
    }
    
    
}

void Game::undo() {
  if (history.size() == 0) {
    cout << "No past movement" << endl;
  } else {
    Move lm = history.back();
    history.pop_back();
    vector<int> init = lm.getEnd();
    vector<int> end = lm.getInit();
    char piece = lm.getCapturedPiece();
    board->makeMove(init, end);
    if (piece != ' ') {
      Game::addPiece(piece, init);
    } 
  }
}

