#include "rook.h"
#include "board.h"
#include <vector>
#include <algorithm>
using namespace std;

Rook::Rook(int row, int col, char type, Board *board) : Piece(row, col, type, board) {}

bool Rook::legalMove(int drow, int dcol) {
  int row = getRow();
  int col = getCol();
  Piece *dest = board->getBoard()[drow][dcol].getPiece();
  if ((drow >= 0) && (drow <= 7) && (dcol >= 0) && (dcol <= 7) && !((drow == row) && (dcol == col))) {
    if ((dest == nullptr) || (dest->getColour() != getColour())) {
      if (drow == row) {
        int i = min(col, dcol) + 1;
        int j = max(col, dcol);
        while (i < j) {
          if (board->getBoard()[row][i].getPiece() != nullptr) break;
          i++;
        }
        return i == j;
      } else if (dcol == col) {
        int i = min(row, drow) + 1;
        int j = max(row, drow);
        while (i < j) {
          if (board->getBoard()[i][col].getPiece() != nullptr) break;
          i++;
        }
        return i == j;
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

vector<vector<int>> Rook::attackArea() {
  int row = getRow();
  int col = getCol();
  vector<vector<int>> retval;
  for (int i = row + 1; i <= 7; i++) {
    vector<int> tmp = {i, col};
    retval.push_back(tmp);
    if (board->getBoard()[i][col].getPiece() != nullptr) break;
  }
  for (int i = row - 1; i >= 0; i--) {
    vector<int> tmp = {i, col};
    retval.push_back(tmp);
    if (board->getBoard()[i][col].getPiece() != nullptr) break;
  }
  for (int i = col + 1; i <= 7; i++) {
    vector<int> tmp = {row, i};
    retval.push_back(tmp);
    if (board->getBoard()[row][i].getPiece() != nullptr) break;
  }
  for (int i = col - 1; i >= 0; i--) {
    vector<int> tmp = {row, i};
    retval.push_back(tmp);
    if (board->getBoard()[row][i].getPiece() != nullptr) break;
  }
  return retval;
}
