#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "piece.h"
#include <vector>

class Knight : public Piece {

public:
  Knight(int row, int col, char type, Board *board);
  bool legalMove(int drow, int dcol);
  std::vector<std::vector<int>> attackArea();
};

#endif
