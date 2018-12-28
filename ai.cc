#include "ai.h"
#include <vector>
#include <stdlib.h>
#include "piece.h"
#include "board.h"
#include "block.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "pawn.h"
using namespace std;
AI::AI(char color, int lvl,Board *board):Player{color},level{lvl},board{board}{}
bool AI::isHuman(){
  return 0;
}
AI::AI( Player *other, Board *b):Player(other->wb){
    king = other->king;
    level = 2;
    board = b;
    pieces = other->pieces;
}




vector<int> AI::getMove(Player* opponent,int checked){
  srand(time(NULL));

  if(this->level==1){
    while(1){
      int n1=rand()%this->pieces.size();
      Piece* p=this->pieces[n1];
      vector<int> posI=p->getPos();
      vector<int> posE;
      if(p->getType()=='p'){
        posE={posI[0]+rand()%2,posI[1]};
      }else if(p->getType()=='P'){
        posE={posI[0]-rand()%2,posI[1]};
      }else{
        int n2=rand()%p->attackArea().size();
        posE=p->attackArea()[n2];
      }
      vector<int> move;
      if(p->legalMove(posE[0],posE[1])){
        move.push_back(posI[0]);
        move.push_back(posI[1]);
        move.push_back(posE[0]);
        move.push_back(posE[1]);
        return move;
      }
    }
  }else if(this->level==2){
    for(int i=0;i<this->pieces.size();i++){
      Piece* p=this->pieces[i];
      for(int j=0;j<p->attackArea().size();j++){
        vector<int> pos=p->attackArea()[j];
        int posX=pos[0];
        int posY=pos[1];
        if(this->board->getBoard()[posX][posY].getPiece()!=nullptr&&(p->legalMove(posX,posY))){
          vector<int> move;
          move.push_back(p->getPos()[0]);
  	  move.push_back(p->getPos()[1]);
	  move.push_back(posX);
 	  move.push_back(posY); 
          return move;
        }
      }
    }
    for(int i=0;i<this->pieces.size();i++){
      Piece* p=this->pieces[i];
      //cout<<p->getType()<<endl;
      for(int j=0;j<p->attackArea().size();j++){
        vector<int> pos=p->attackArea()[j];
        int posX=pos[0];
        int posY=pos[1];
    	Piece* n;
        if(this->board->getBoard()[posX][posY].getPiece()!=nullptr){
	  Piece* temp=this->board->getBoard()[posX][posY].getPiece();
        }else{
          if(p->getType()=='r'){
            n=new Rook(posX,posY,'r',board);
          }
          else if(p->getType()=='n'){
            n=new Knight(posX,posY,'n',board);
          }
          else if(p->getType()=='b'){
            n=new Bishop(posX,posY,'b',board);
          }
          else if(p->getType()=='q'){
            n=new Queen(posX,posY,'q',board);
          }
          else if(p->getType()=='k'){
            n=new King(posX,posY,'k',board);
          }
         else if(p->getType()=='p'){
           n=new Pawn(posX,posY,'p',board);
         }
         else if(p->getType()=='R') {
           n=new Rook(posX,posY,'R',board);
         }
         else if(p->getType()=='N'){
           n=new Knight(posX,posY,'N',board);
         }
         else if(p->getType()=='B'){
           n=new Bishop(posX,posY,'B',board);
         }
         else if(p->getType()=='Q'){
           n=new Queen(posX,posY,'Q',board);
         }
         else if(p->getType()=='K'){
           n=new King(posX,posY,'K',board);
         }
         else if(p->getType()=='P'){
           n=new Pawn(posX,posY,'P',board);
        }
        //this->board->getBoard()[posX][posY].p=n;
	int x,y;
	for(int i=0;i<opponent->pieces.size();i++){
	  if(opponent->pieces[i]->getType()=='k'||opponent->pieces[i]->getType()=='K'){
	    x=opponent->pieces[i]->getRow();
	    y=opponent->pieces[i]->getCol();
	  }
	}
   
	if(n->legalMove(x,y)){
          vector<int> move;
          move.push_back(p->getPos()[0]);
  	  move.push_back(p->getPos()[1]);
	  move.push_back(posX);
 	  move.push_back(posY); 
          return move;
 	}    
      }
    }
  }

    while(1){
      int n1=rand()%this->pieces.size();
      Piece* p=this->pieces[n1];
      vector<int> posI=p->getPos();
      vector<int> posE;
      if(p->getType()=='p'){
        posE={posI[0]+rand()%2,posI[1]};
      }else if(p->getType()=='P'){
        posE={posI[0]-rand()%2,posI[1]};
      }else{
        int n2=rand()%p->attackArea().size();
        posE=p->attackArea()[n2];
      }
      vector<int> move;
      if(p->legalMove(posE[0],posE[1])){
        move.push_back(posI[0]);
        move.push_back(posI[1]);
        move.push_back(posE[0]);
        move.push_back(posE[1]);
        return move;
      }
    }
  }else if (this->level==3){
    for(int i=0;i<this->pieces.size();i++){
      Piece* p=this->pieces[i];
      for(int j=0;j<p->attackArea().size();j++){
        vector<int> pos=p->attackArea()[j];
        int posX=pos[0];
        int posY=pos[1];
        if(this->board->getBoard()[posX][posY].getPiece()!=nullptr&&(p->legalMove(posX,posY))){
          vector<int> move;
          move.push_back(p->getPos()[0]);
  	  move.push_back(p->getPos()[1]);
	  move.push_back(posX);
 	  move.push_back(posY); 
          return move;
        }
      }
    }
    for(int i=0;i<this->pieces.size();i++){
      Piece* p=this->pieces[i];
      //cout<<p->getType()<<endl;
      for(int j=0;j<p->attackArea().size();j++){
	//cout<<"11111"<<endl;
        vector<int> pos=p->attackArea()[j];
        int posX=pos[0];
        int posY=pos[1];
    	Piece* n;
        if(this->board->getBoard()[posX][posY].getPiece()!=nullptr){
	  Piece* temp=this->board->getBoard()[posX][posY].getPiece();
        }else{
	  //cout<<"222222"<<endl;
          if(p->getType()=='r'){
            n=new Rook(posX,posY,'r',board);
            //cout<<"333333"<<endl;
          }
          else if(p->getType()=='n'){
            n=new Knight(posX,posY,'n',board);
          }
          else if(p->getType()=='b'){
            n=new Bishop(posX,posY,'b',board);
          }
          else if(p->getType()=='q'){
            n=new Queen(posX,posY,'q',board);
          }
          else if(p->getType()=='k'){
            n=new King(posX,posY,'k',board);
          }
         else if(p->getType()=='p'){
           n=new Pawn(posX,posY,'p',board);
         }
         else if(p->getType()=='R') {
           n=new Rook(posX,posY,'R',board);
         }
         else if(p->getType()=='N'){
           n=new Knight(posX,posY,'N',board);
         }
         else if(p->getType()=='B'){
           n=new Bishop(posX,posY,'B',board);
         }
         else if(p->getType()=='Q'){
           n=new Queen(posX,posY,'Q',board);
         }
         else if(p->getType()=='K'){
           n=new King(posX,posY,'K',board);
         }
         else if(p->getType()=='P'){
           n=new Pawn(posX,posY,'P',board);
        }
        //this->board->getBoard()[posX][posY].p=n;
	int x,y;
	for(int i=0;i<opponent->pieces.size();i++){
	  if(opponent->pieces[i]->getType()=='k'||opponent->pieces[i]->getType()=='K'){
	    x=opponent->pieces[i]->getRow();
	    y=opponent->pieces[i]->getCol();
	  }
	}
   
	if(n->legalMove(x,y)){
          vector<int> move;
          move.push_back(p->getPos()[0]);
  	  move.push_back(p->getPos()[1]);
	  move.push_back(posX);
 	  move.push_back(posY); 
          return move;
 	}    
      }
    }
  }

    while(1){
      int n1=rand()%this->pieces.size();
      Piece* p=this->pieces[n1];
      vector<int> posI=p->getPos();
      vector<int> posE;
      if(p->getType()=='p'){
        posE={posI[0]+rand()%2,posI[1]};
      }else if(p->getType()=='P'){
        posE={posI[0]-rand()%2,posI[1]};
      }else{
        int n2=rand()%p->attackArea().size();
        posE=p->attackArea()[n2];
      }
      if(p->legalMove(posE[0],posE[1])){
        for(int i=0;i<opponent->pieces.size();i++){

          if((opponent->pieces[i]!=nullptr)&&!opponent->pieces[i]->legalMove(p->getPos()[0],p->getPos()[1])){
            vector<int> move;
            move.push_back(posI[0]);
            move.push_back(posI[1]);
            move.push_back(posE[0]);
            move.push_back(posE[1]);
            return move;
          }


        }
      }
    }
  }else if (this->level=4){
    if(checked==1){
      for(int i=0;i<this->pieces.size();i++){
	if(pieces[i]->getType()=='k'||pieces[i]->getType()=='K'){
	  for(int j=0;j<pieces[i]->attackArea().size();j++){
	    int x=pieces[i]->attackArea()[j][0];
	    int y=pieces[i]->attackArea()[j][1];
	    if(pieces[i]->legalMove(x,y)){
  	      vector<int> move;
              move.push_back(pieces[i]->getPos()[0]);
              move.push_back(pieces[i]->getPos()[1]);
              move.push_back(x);
              move.push_back(y);
              return move;
            }
	  }
	}
     }
   }
	    for(int i=0;i<this->pieces.size();i++){
      Piece* p=this->pieces[i];
      for(int j=0;j<p->attackArea().size();j++){
        vector<int> pos=p->attackArea()[j];
        int posX=pos[0];
        int posY=pos[1];
        if(this->board->getBoard()[posX][posY].getPiece()!=nullptr&&(p->legalMove(posX,posY))){
          vector<int> move;
          move.push_back(p->getPos()[0]);
  	  move.push_back(p->getPos()[1]);
	  move.push_back(posX);
 	  move.push_back(posY); 
          return move;
        }
      }
    }
    for(int i=0;i<this->pieces.size();i++){
      Piece* p=this->pieces[i];
      //cout<<p->getType()<<endl;
      for(int j=0;j<p->attackArea().size();j++){
	//cout<<"11111"<<endl;
        vector<int> pos=p->attackArea()[j];
        int posX=pos[0];
        int posY=pos[1];
    	Piece* n;
        if(this->board->getBoard()[posX][posY].getPiece()!=nullptr){
	  Piece* temp=this->board->getBoard()[posX][posY].getPiece();
        }else{
	  //cout<<"222222"<<endl;
          if(p->getType()=='r'){
            n=new Rook(posX,posY,'r',board);
            //cout<<"333333"<<endl;
          }
          else if(p->getType()=='n'){
            n=new Knight(posX,posY,'n',board);
          }
          else if(p->getType()=='b'){
            n=new Bishop(posX,posY,'b',board);
          }
          else if(p->getType()=='q'){
            n=new Queen(posX,posY,'q',board);
          }
          else if(p->getType()=='k'){
            n=new King(posX,posY,'k',board);
          }
         else if(p->getType()=='p'){
           n=new Pawn(posX,posY,'p',board);
         }
         else if(p->getType()=='R') {
           n=new Rook(posX,posY,'R',board);
         }
         else if(p->getType()=='N'){
           n=new Knight(posX,posY,'N',board);
         }
         else if(p->getType()=='B'){
           n=new Bishop(posX,posY,'B',board);
         }
         else if(p->getType()=='Q'){
           n=new Queen(posX,posY,'Q',board);
         }
         else if(p->getType()=='K'){
           n=new King(posX,posY,'K',board);
         }
         else if(p->getType()=='P'){
           n=new Pawn(posX,posY,'P',board);
        }
        //this->board->getBoard()[posX][posY].p=n;
	int x,y;
	for(int i=0;i<opponent->pieces.size();i++){
	  if(opponent->pieces[i]->getType()=='k'||opponent->pieces[i]->getType()=='K'){
	    x=opponent->pieces[i]->getRow();
	    y=opponent->pieces[i]->getCol();
	  }
	}
   
	if(n->legalMove(x,y)){
          vector<int> move;
          move.push_back(p->getPos()[0]);
  	  move.push_back(p->getPos()[1]);
	  move.push_back(posX);
 	  move.push_back(posY); 
          return move;
 	}    
      }
    }
  }

    while(1){
      int n1=rand()%this->pieces.size();
      Piece* p=this->pieces[n1];
      vector<int> posI=p->getPos();
      vector<int> posE;
      if(p->getType()=='p'){
        posE={posI[0]+rand()%2,posI[1]};
      }else if(p->getType()=='P'){
        posE={posI[0]-rand()%2,posI[1]};
      }else{
        int n2=rand()%p->attackArea().size();
        posE=p->attackArea()[n2];
      }
      if(p->legalMove(posE[0],posE[1])){
        for(int i=0;i<opponent->pieces.size();i++){

          if((opponent->pieces[i]!=nullptr)&&!opponent->pieces[i]->legalMove(p->getPos()[0],p->getPos()[1])){
            vector<int> move;
            move.push_back(posI[0]);
            move.push_back(posI[1]);
            move.push_back(posE[0]);
            move.push_back(posE[1]);
            return move;
          }


        }
      }
    }

    }
  }


