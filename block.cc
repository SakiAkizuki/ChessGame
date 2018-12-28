#include <string>
#include <iostream>
#include "block.h"
using namespace std;
Block::Block(int x, int y, Piece *p): x{x},y{y},p{p} {
    c = '_';
    //if row are even, then even col is ' ', odd col is '_'
    if(x % 2 == 0){
        if(y % 2 == 0){
            c = ' ';
        }
    }else{
        if(y % 2 != 0){
            c = ' ';
        }
    }
}

void Block::remove(){
	if(p != nullptr){
		p  = nullptr;
		c = '_';
        if(x % 2 == 0){
            if(y % 2 == 0){
                c = ' ';
            }
        }else{
            if(y % 2 != 0){
                c = ' ';
            }
        }
    }
}
void Block::remove_setup(){
    if(p != nullptr){
        delete p;
        p  = nullptr;
        c = '_';
        if(x % 2 == 0){
            if(y % 2 == 0){
                c = ' ';
            }
        }else{
            if(y % 2 != 0){
                c = ' ';
            }
        }
    }
}
Piece* Block::getPiece(){
	return p;
}

void Block::addpiece(Piece *p){
	if(this->p == nullptr){
		this->p = p;
		c = p->getType();
	}else{
		//cout<< this->p->getType() << " is captured" << endl;
		delete this->p;
		this->p = p;
		c = p->getType();
	}
}
char Block::get_c() const{
	return c;
}



