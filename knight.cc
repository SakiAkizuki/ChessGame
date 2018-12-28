#include "knight.h"
#include "board.h"
#include <cstdlib>
#include <vector>
using namespace std;

Knight::Knight(int row, int col, char type, Board *board) : Piece(row, col, type, board) {}

bool Knight::legalMove(int drow, int dcol) {
  int row = getRow();
  int col = getCol();
  Piece *dest = board->getBoard()[drow][dcol].getPiece();
  if ((drow >= 0) && (drow <= 7) && (dcol >= 0) && (dcol <= 7) && !((drow == row) && (dcol == col))) {
    if ((dest == nullptr) || (dest->getColour() != getColour())) {
      if (((abs(drow - row) == 1) && (abs(dcol - col) == 2)) || ((abs(drow - row) == 2) && (abs(dcol - col) == 1))) {
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

vector<vector<int>> Knight::attackArea() {
  int row = getRow();
  int col = getCol();
  vector<int> v1 = {row - 1, col - 2};
  vector<int> v2 = {row - 1, col + 2};
  vector<int> v3 = {row + 1, col - 2};
  vector<int> v4 = {row + 1, col + 2};
  vector<int> v5 = {row - 2, col - 1};
  vector<int> v6 = {row - 2, col + 1};
  vector<int> v7 = {row + 2, col - 1};
  vector<int> v8 = {row + 2, col + 1};
  vector<vector<int>> tmp = {v1, v2, v3, v4, v5, v6, v7, v8};
  vector<vector<int>> retval;
  for (int i = 0; i < 7; i++) {
    if ((tmp[i][0] >= 0) && (tmp[i][0] <= 7) && (tmp[i][1] >= 0) && (tmp[i][1] <= 7)) {
      //cout<<tmp[i][0]<<tmp[i][1]<<endl;
      retval.push_back(tmp[i]);
    }
  }
  return retval;
}
