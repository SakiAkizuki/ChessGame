#ifndef __KING_H__
#define __KING_H__
#include "piece.h"
#include <vector>

class King : public Piece {

public:
  King(int row, int col, char type, Board *board);
  bool legalMove(int drow, int dcol);
  std::vector<std::vector<int>> attackArea();
};

#endif
