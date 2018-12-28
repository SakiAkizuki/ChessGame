#include "king.h"
#include "board.h"
#include <cstdlib>
#include <vector>
using namespace std;

King::King(int row, int col, char type ,Board *board) : Piece(row, col, type, board) {}

bool King::legalMove(int drow, int dcol) {
  int row = getRow();
  int col = getCol();
  Piece *dest = board->getBoard()[drow][dcol].getPiece();
  if ((drow >= 0) && (drow <= 7) && (dcol >= 0) && (dcol <= 7) && !((drow == row) && (dcol == col))) {
    if ((dest == nullptr) || (dest->getColour() != getColour())) {
      if ((abs(drow - row) <= 1) && (abs(dcol - col) <= 1)) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}

vector<vector<int>> King::attackArea() {
  int row = getRow();
  int col = getCol();
  vector<vector<int>> retval;
  for (int i = row - 1; i <= row + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      if ((i == row) && (j == col)) {
        continue;
      }
      else if (!((i >= 0) && (i <= 7) && (j >= 0) && (j <= 7))) {
        continue;
      } else {
        vector<int> tmp = {i, j};
        retval.push_back(tmp);
      }
    }
  }
  return retval;
}
