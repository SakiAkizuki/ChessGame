#include "bishop.h"
#include "board.h"
#include <vector>
#include <algorithm>
using namespace std;

Bishop::Bishop(int row, int col, char type, Board *board) : Piece(row, col, type, board) {}

bool Bishop::legalMove(int drow, int dcol) {
  int row = getRow();
  int col = getCol();
  Piece *dest = board->getBoard()[drow][dcol].getPiece();
  if ((drow >= 0) && (drow <= 7) && (dcol >= 0) && (dcol <= 7) && !((drow == row) && (dcol == col))) {
    if ((dest == nullptr) || (dest->getColour() != getColour())) {
      if ((row - drow) == (col - dcol)) {
        int i = min(row,drow) + 1;
        int j = min(col,dcol) + 1;
        int k = max(row,drow);
        int l = max(col,dcol);
        while (i < k) {
          if (board->getBoard()[i][j].getPiece() != nullptr) break;
          i++;
          j++;
        }
        return ((i == k) && (j == l));
      } 
      else if ((row - drow) == -(col - dcol)) {
        int i = min(row,drow) + 1;
        int j = max(col,dcol) - 1;
        int k = max(row,drow);
        int l = min(col,dcol);
        while (i < k) {
          if (board->getBoard()[i][j].getPiece() != nullptr) break;
          i++;
          j--;
        }
        return ((i == k) && (j == l));
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

vector<vector<int>> Bishop::attackArea() {
  int row = getRow();
  int col = getCol();
  vector<vector<int>> retval;
  for (int i = row + 1, j = col + 1; ((i <= 7) && (j <= 7)); i++, j++) {
    vector<int> tmp = {i, j};
    retval.push_back(tmp);
    if (board->getBoard()[i][j].getPiece() != nullptr) break;
  }
  for (int i = row + 1, j = col - 1; ((i <= 7) && (j >= 0)); i++, j--) {
    vector<int> tmp = {i, j};
    retval.push_back(tmp);
    if (board->getBoard()[i][j].getPiece() != nullptr) break;
  }
  for (int i = row - 1, j = col + 1; ((i >= 0) && (j <= 7)); i--, j++) {
    vector<int> tmp = {i, j};
    retval.push_back(tmp);
    if (board->getBoard()[i][j].getPiece() != nullptr) break;
  }
  for (int i = row - 1, j = col - 1; ((i >= 0) && (j >= 0)); i--, j--) {
    vector<int> tmp = {i, j};
    retval.push_back(tmp);
    if (board->getBoard()[i][j].getPiece() != nullptr) break;
  }
  return retval;
}
