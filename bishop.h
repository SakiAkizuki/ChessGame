#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "piece.h"
#include <vector>

class Bishop : public Piece {

public:
  Bishop(int row, int col, char type, Board *board);
  bool legalMove(int drow, int dcol);
  std::vector<std::vector<int>> attackArea();
};

#endif
