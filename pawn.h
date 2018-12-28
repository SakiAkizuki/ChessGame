#ifndef __PAWN_H__
#define __PAWN_H__
#include "piece.h"
#include <vector>

class Pawn : public Piece {

public:
  Pawn(int row, int col, char type, Board *board);
  bool legalMove(int drow, int dcol);
  std::vector<std::vector<int>> attackArea();
};

#endif
