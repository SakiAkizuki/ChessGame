#include "pawn.h"
#include "board.h"
#include <cstdlib>
#include <vector>
using namespace std;

Pawn::Pawn(int row, int col, char type, Board *board) : Piece(row, col, type, board) {}

bool Pawn::legalMove(int drow, int dcol) {
  int row = getRow();
  int col = getCol();
  Piece *dest = board->getBoard()[drow][dcol].getPiece();
  if ((drow >= 0) && (drow <= 7) && (dcol >= 0) && (dcol <= 7) && !((drow == row) && (dcol == col))) {
    if (dest == nullptr) {
      if (col == dcol) {
        if (getType() == 'p') {
          if (drow - row == 1) {
            return true;
          }
          else if ((row == 1) && (drow - row == 2) && (board->getBoard()[row + 1][col].getPiece() == nullptr)) {
            return true;
          } else {
          return false;
          }
        } else {
          if (row - drow == 1) {
            return true;
          }
          else if ((row == 6) && (row - drow == 2) && (board->getBoard()[row - 1][col].getPiece() == nullptr)) {
            return true;
          } else {
            return false;
          }
        }
      } else {
        return false;
      }
    } else if (dest->getColour() != getColour()) {
      if (abs(col - dcol) == 1) {
        if(getType() == 'p') {
          if (drow - row == 1) {
            return true;
          } else {
            return false;
          }
        } else {
          if (row - drow == 1) {
            return true;
          } else {
            return false;
          }
        }
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

vector<vector<int>> Pawn::attackArea() {
  int row = getRow();
  int col = getCol();
  vector<vector<int>> retval;
  if (getType() == 'p') {
    vector<int> v1 = {row + 1, col + 1};
    vector<int> v2 = {row + 1, col - 1};
    if ((v1[0] >= 0) && (v1[0] <= 7) && (v1[1] >= 0) && (v1[1] <= 7)) {
      retval.push_back(v1);
    }
    if ((v2[0] >= 0) && (v2[0] <= 7) && (v2[1] >= 0) && (v2[1] <= 7)) { 
    retval.push_back(v2);
    }
  } else {
    vector<int> v1 = {row - 1, col + 1};
    vector<int> v2 = {row - 1, col - 1};
    if ((v1[0] >= 0) && (v1[0] <= 7) && (v1[1] >= 0) && (v1[1] <= 7)) {
      retval.push_back(v1);
    }
    if ((v2[0] >= 0) && (v2[0] <= 7) && (v2[1] >= 0) && (v2[1] <= 7)) { 
    retval.push_back(v2);
    }
  }
  return retval;
}
