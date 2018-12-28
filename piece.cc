#include "piece.h"
using namespace std;

Piece::Piece(int row, int col, char type, Board *board) : row{row}, col{col}, type{type}, board{board} {}
vector<int> Piece::getPos(){
  return {row,col};
}

int Piece::getRow() {
  return row;
}

int Piece::getCol() {
  return col;
}

char Piece::getType() {
  return type;
}

char Piece::getColour() {
  if ((type >= 'a') && (type <= 'z')) {
    return 'b';
  } else {
    return 'w';
  }
}

void Piece::changeRow(int r) {
  row = r;
}

void Piece::changeCol(int c) {
  col = c;
}

Piece::~Piece() {}
