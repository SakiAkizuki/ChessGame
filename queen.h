#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "piece.h"
#include <vector>

class Queen : public Piece {

public:
  Queen(int row, int col, char type, Board *board);
  bool legalMove(int drow, int dcol);
  std::vector<std::vector<int>> attackArea();
};

#endif
