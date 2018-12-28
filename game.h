#ifndef _GAME_H_
#define _GAME_H_

#include "piece.h"
#include "board.h"
#include "player.h"
#include <vector>
#include "move.h"
using namespace std;
class Game{

  Board* board;
  char currentPlayer;
 public:
  Player* pW;
  Player* pB;
  void getSuggestion(int index);
  vector<Move> history;
  void removePiece_setup(vector<int> pos);
  void makeMove(vector<int> init, vector<int> end);
  void addPiece(char type,vector<int> pos);
  void removePiece(vector<int> pos);
  bool checkValid();
  int isChecked(); 
  int isWon(int playerindex);
  void addHistory(vector<int> init,vector<int> end);
  void aiMove(int index);
  void undo();
  Game(Player* pW, Player* pB,Board* board,bool setup);
  void changeboard(Board *board);
  void default_board();
    
  ~Game();
};
#endif
