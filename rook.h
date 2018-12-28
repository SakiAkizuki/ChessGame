#ifndef __ROOK_H__
#define __ROOK_H__
#include "piece.h"
#include <vector>

class Rook : public Piece {

public:
  Rook(int row, int col, char type, Board *board);
  bool legalMove(int drow, int dcol);
  std::vector<std::vector<int>> attackArea();
};

#endif
