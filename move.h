#include <vector>
using namespace std;
class Move{
  vector<int> init;
  vector<int> end;
  char piece;
  char capturedPiece;
 public:
  vector<int> getInit();
  vector<int> getEnd();
  char getPiece();
  char getCapturedPiece();
  Move(vector<int> init, vector<int> end, char pc, char cpc);
  ~Move();
};
