#include "queen.h"
#include "board.h"
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

Queen::Queen(int row, int col, char type, Board *board) : Piece(row, col, type, board) {}

bool Queen::legalMove(int drow, int dcol) {
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
      } else if ((row - drow) == (col - dcol)) {
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

vector<vector<int>> Queen::attackArea() {
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
