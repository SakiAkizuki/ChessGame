#ifndef __PIECE_H__
#define __PIECE_H__
#include <vector>
using namespace std;
class Board;
class Piece {
  int row;
  int col;
  char type;

public:
  Board *board;
  Piece(int row, int col, char , Board *board);
  vector<int> getPos();
  int getRow();
  int getCol();
  char getType();
  char getColour();
  void changeRow(int r);
  void changeCol(int c);
  virtual bool legalMove(int drow, int dcol) = 0;
  virtual std::vector<std::vector<int>> attackArea() = 0;
  virtual ~Piece();
};

#endif
