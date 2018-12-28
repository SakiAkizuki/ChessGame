#include "board.h"
#include "block.h"
#include "piece.h"
#include <string>

using namespace std;


Board::Board(){
    for(int r = 0; r < 8; r++){
        vector<Block> row;
        for(int c = 0; c < 8; c++){
            Block temp{r, c};
            row.emplace_back(temp);
        }
        blocks.emplace_back(row);
    }
}

void Board::addPiece(Piece *p, vector<int> pos){
    blocks[pos[0]][pos[1]].addpiece(p);
}

void Board::removePiece(vector<int> pos){
    blocks[pos[0]][pos[1]].remove();
}
void Board::removePiece_setup(vector<int> pos){
    blocks[pos[0]][pos[1]].remove_setup();
}

void Board::makeMove(vector<int> init, vector<int> end){
    Piece *current = blocks[init[0]][init[1]].getPiece();
    blocks[init[0]][init[1]].remove();
    blocks[end[0]][end[1]].addpiece(current);
    current->changeRow(end[0]);
    current->changeCol(end[1]);
}

bool Board::checkValid() {
    int bk = 0; //number of black king
    int wk = 0;// number of white king
    //check the # of king and position of pawn
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            Piece *tempPiece = blocks[r][c].getPiece();
            char name;
            if(tempPiece != nullptr){
                name = tempPiece->getType();
            }
            if(name == 'k'){
                bk++;
                name = '1';
            }
            if(name =='K'){
                wk++;
                name = '1';
            }
            if((name == 'P' or name == 'p') and (r == 0 or r == 7)) {
                cout << "the pawn is in the bottome line or the top line" << endl;
                cout << "bk = " << bk;
                cout << "wk = " << wk << endl;
                return false;
            }
        }
    }
    if(bk == 1 and wk == 1 and !isChecked_ALL()){
        return true;
    }else{
        if(isChecked_ALL()){
            cout << "King is in checked" << endl;
        }else if( bk != 1 or wk != 1){
            cout << "there should be exactly one white king and black king!" << endl;
            cout << " bk = " << bk << " wk = " << wk << endl;
        }
        return false;
    }
}

int Board::isChecked_ALL(){
    int b = 0;
    int w = 0;
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            if(blocks[r][c].getPiece() != nullptr){
                if(isChecked(blocks[r][c].getPiece()) == 1){
                    w++;
                }else if(isChecked(blocks[r][c].getPiece()) ==2){
                    b++;
                }
            }
        }
    }
    if(b != 0 and w != 0){
        return 3; //both are in checked
    }else if(b != 0){
        return 2; //checked black
    }else if(w != 0){
        return 1; //checked white
    }else{
        return 0;
    }
}



int Board::isChecked(Piece *p) {
    vector<vector<int>> AttackArea =p->attackArea();
    //the color of piece
    char color = p->getColour();
    vector<int> position;
    char kingname = 'k';
    //Find the position of king
    if(color == 'b'){
        kingname = 'K';
    }
    //find the position of black king
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            if(blocks[r][c].get_c() == kingname){
                position =  {r,c};
            }
        }
    }
    int size = AttackArea.size();
    for(int i = 0; i < size; i++){
        if(position == AttackArea[i]){
            if(color == 'b'){
                //cout << " white is in checked by " << p->getType() << endl;
                //white is in checked
                return 1;
            }else{
                //black is in checked
                
                //cout << " black is in checked by " << p->getType() << endl;
                return 2;
            }
        }
    }
    return 0;
}



/*int  Board::IsWon() {
    int bk = 0; //number of black king
    int wk = 0;// number of white king
    // find out if the king is checked, we need to find the position of two king
    for(int r = 0; r < 8; r ++){
        for(int c = 0; c < 8; c++){
            Piece *tempPiece = blocks[r][c].getPiece();
            char name;
            if(tempPiece != nullptr){
                name = tempPiece->getType();
            }
            if(name == 'k'){
                bk++;
            }else if(name == 'K'){
                wk++;
            }
        }
    }
    if(bk == 0){
        cout << "Checkmate! White wins!" << endl;
        return 1;
    }else if(wk == 0){
        cout << "Checkmate! Black wins!" << endl;
        return 2;
    }else{
        return 0;
    }
}*/


const int width = 60;
const int gap = 2;


void Board::GraphicDisplay(Xwindow &win) {
    for(int r = 0 ; r < 8 ; r++){
        for(int c = 0; c < 8; c++){
            char temp = blocks[r][c].get_c();
            if(temp == '_'){
               	win.fillRectangle(c*(width+gap), r*(width+gap), 60, 60, 4);
            }else if(temp == ' '){
                win.fillRectangle(c*(width+gap), r*(width+gap), 60, 60, 5);
            }else{
                if((r % 2 == 0 and c % 2 == 0) or (r % 2 != 0 and c%2 != 0)){
                    win.fillRectangle(c*(width+gap), r*(width+gap), 60, 60, 5);
                }else{
                    win.fillRectangle(c*(width+gap), r*(width+gap), 60, 60, 4);
                }
            }
            //if there is a black piece on it
		string ts{temp};
            if(temp >= 'a' and temp <= 'z'){
                win.fillRectangle(c*(width+gap)+20, r*(width+gap)+20, 20, 20, 1);
                win.drawString(c*(width+gap)+28, r*(width+gap)+35, ts,9);
            }else if(temp >='A' and temp <= 'Z'){
                win.fillRectangle(c*(width+gap)+20, r*(width+gap)+20, 20, 20, 0);
                win.drawString(c*(width+gap)+28, r*(width+gap)+35, ts,9);
            }
        }
    }
}

void Board::TextDisplay() {
    for(int r = 0; r < 8 ; r++){
        string row = to_string(8 - r) + " ";
        for(int c = 0; c < 8; c++){
            char temp = blocks[r][c].get_c();
            row = row+temp;
        }
        cout << row << endl;
    }
    cout << endl;
    cout << "  abcdefgh" << endl;
}

vector<vector<Block>> Board::getBoard() {
    return blocks;
}
Board::~Board(){
    for(int r = 0; r < 8; r++){
        for(int c = 0; c < 8; c++){
            if(blocks[r][c].getPiece() != nullptr){
                delete blocks[r][c].getPiece();
            }
        }
    }
}
//helper function, find the position of the piece
//if no piece on the board, return {-1,-1}
vector<int> Board::find_p(char p_name){
    for(int i = 0; i < 8;i++){
        for(int j = 0; j < 8; j++){
            Piece *tempPiece = blocks[i][j].getPiece();
            if(tempPiece != nullptr){
                char name = tempPiece->getType();
                if(name == p_name){
                    //cout << " here is board:: find _p " << i << j << endl;
                    return {i,j};
                }
            }
        }
    }
    return {-1,-1};
}

//helper function, get the movement area of king
vector<vector<int>> Board::kingmove(int r, int c){
    char kcolour = blocks[r][c].getPiece()->getColour();
    vector<vector<int>> area;
    if ((r - 1 >= 0) and (blocks[r - 1][c].getPiece() == nullptr or blocks[r - 1][c].getPiece()->getColour() != kcolour)) {
        //cout << r-1 << c << endl;
        area.emplace_back(vector<int>{r-1,c});
    }
    if((r - 1 >= 0) and (c+1 <= 7) and (blocks[r - 1][c + 1].getPiece() == nullptr or blocks[r - 1][c + 1].getPiece()->getColour() != kcolour)) {
        //cout << r-1 << c+1 << endl;
        area.emplace_back(vector<int>{r-1, c+1});
    }
    if((c + 1 <= 7) and (blocks[r][c + 1].getPiece() == nullptr or blocks[r][c + 1].getPiece()->getColour() != kcolour)) {
        //cout << r << c+1 << endl;
        area.emplace_back(vector<int>{r, c+1});
    }
    if((c + 1 <= 7 and r + 1 <= 7) and (blocks[r + 1][c + 1].getPiece() == nullptr or blocks[r + 1][c + 1].getPiece()->getColour() != kcolour)){
        //cout << r+1 << c+1 << endl;
        area.emplace_back(vector<int>{r+1, c+1});
    }
    if((r+1 <= 7) and (blocks[r + 1][c].getPiece() == nullptr or blocks[r + 1][c].getPiece()->getColour() != kcolour)) {
        //cout << r+1 << c << endl;
        area.emplace_back(vector<int>{r+1, c});
    }
    if((r+1 <=7 and c-1 >=0) and (blocks[r + 1][c - 1].getPiece() == nullptr or blocks[r + 1][c - 1].getPiece()->getColour() != kcolour)) {
        //cout << r+1 << c-1 << endl;
        area.emplace_back(vector<int>{r+1, c-1});
    }
    if((c-1 >=0) and (blocks[r][c - 1].getPiece() == nullptr or blocks[r][c - 1].getPiece()->getColour() != kcolour)){
        //cout << r << c-1 << endl;
        area.emplace_back(vector<int>{r,c-1});
    }
    if((c-1 >= 0 and  r - 1 >=0) and (blocks[r - 1][c - 1].getPiece() == nullptr or blocks[r - 1][c - 1].getPiece()->getColour() != kcolour)) {
        //cout << r-1 << c-1 << endl;
        area.emplace_back(vector<int>{r-1,c-1});
    }
    return area;
}

vector<vector<int>> append_Vector(vector<vector<int>> range, vector<vector<int>> add){
    vector<vector<int>> temp = range;
    int size = add.size();
    for(int i =0; i < size; i++){
        temp.emplace_back(add[i]);
    }
    return temp;
}
//check king k is in check or not;
int Board::IsWon(char k){
    vector<int> K_position = find_p(k);
    vector<vector<int>> Kmovement = Board::kingmove(K_position[0], K_position[1]);
    vector<vector<int>> MAttackArea;
    vector<vector<int>> OAttackArea;
    char color = 'b';
    int checknumber = 0;
    vector<Piece *> checkpiece;
    if( k  == 'k'){
        color = 'w';
    }
    //checkmate 'k' or 'K'?
    for(int i =0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Piece *temp = blocks[i][j].getPiece();
            if(temp != nullptr and temp->getColour() == color){
                vector<vector<int>> AA = temp->attackArea();
                OAttackArea = append_Vector(OAttackArea, AA);
                for (int i = 0; i < AA.size(); i++) {
                    if (K_position == AA[i]) {
                        checknumber++;
                        checkpiece.push_back(temp);
                    }
                }
            } 
            else if(temp != nullptr and temp->getColour() != color and temp->getType() != 'k' and temp->getType() != 'K') {
                MAttackArea = append_Vector(MAttackArea, temp->attackArea());
            }
        }
    }

    if (checknumber == 0) {
        return 0;
    }
    else if (checknumber == 1) {
        vector<int> cpos = checkpiece[0]->getPos();
        if (cpos[0] == K_position[0]) {
            if (cpos[1] < K_position[1]) {
                for (int i = cpos[1] + 1; i < K_position[1]; i++) {
                    for (auto a : MAttackArea) {
                        if (a[0] == cpos[0] && a[1] == i) {
                            return 0;
                        }
                    }
                }
            } else {
                for (int i = cpos[1] - 1; i > K_position[1]; i--) {
                    for (auto a : MAttackArea) {
                        if (a[0] == cpos[0] && a[1] == i) {
                            return 0;
                        }
                    }
                }
            }
        }
        if (cpos[1] == K_position[1]) {
            if (cpos[0] < K_position[0]) {
                for (int i = cpos[0] + 1; i < K_position[0]; i++) {
                    for (auto a : MAttackArea) {
                        if (a[0] == i && a[1] == cpos[1]) {
                            return 0;
                        }
                    }
                }
            } else {
                for (int i = cpos[0] - 1; i > K_position[0]; i--) {
                    for (auto a : OAttackArea) {
                        if (a[0] == i && a[1] == cpos[1]) {
                            return 0;
                        }
                    }
                }
            }
        }
        if (cpos[0] - K_position[0] == cpos[1] - K_position[1]) {
            if (cpos[0] < K_position[0]) {
                for (int i = cpos[0] + 1, j = cpos[1] + 1; i < K_position[0]; i++, j++) {
                    for (auto a : MAttackArea) {
                        if (a[0] == i && a[1] == j) {
                            return 0;
                        }
                    }
                }
            } else {
                for (int i = cpos[0] - 1, j = cpos[1] - 1; i > K_position[0]; i--, j--) {
                    for (auto a : OAttackArea) {
                        if (a[0] == i && a[1] == j) {
                            return 0;
                        }
                    }
                }
            }
        }
        if (cpos[0] - K_position[0] == -(cpos[1] - K_position[1])) {
            if (cpos[0] < K_position[0]) {
                for (int i = cpos[0] + 1, j = cpos[1] - 1; i < K_position[0]; i++, j--) {
                    for (auto a : MAttackArea) {
                        if (a[0] == i && a[1] == j) {
                            return 0;
                        }
                    }
                }
            } else {
                for (int i = cpos[0] - 1, j = cpos[1] + 1; i > K_position[0]; i--, j++) {
                    for (auto a : MAttackArea) {
                        if (a[0] == i && a[1] == j) {
                            return 0;
                        }
                    }
                }
            }
        }

        for (auto a : MAttackArea) {
            if (cpos == a) {
                return 0;
            }
        }
        int size_m = Kmovement.size();
        vector<int> status(size_m, 0);
        //if there is a position in Kmovement is in attack area, the relative int status is 1
        int size_a = OAttackArea.size();
        int index = 0;
        for(auto m: Kmovement){
            for(auto a: OAttackArea){
                if(m == a){
                    //cout << "Kmovement" << m[0]<<m[1] << endl;
                    status[index] = 1;
                    break;
                }
            }
            index ++;
        }
        for(auto s: status){
            if(s == 0){
                return 0;
            }
        }
        if(color == 'w'){
            cout << "Checkmate! White Wins!" << endl;
            return 1;
        }else{
            cout << "Checkmate! Black Wins!" << endl;
              return 2; 
        }
    } else {
        int size_m = Kmovement.size();
        vector<int> status(size_m, 0);
        //if there is a position in Kmovement is in attack area, the relative int status is 1
        int size_a = OAttackArea.size();
        int index = 0;
        for(auto m: Kmovement){
            for(auto a: OAttackArea){
                if(m == a){
                    //cout << "Kmovement" << m[0]<<m[1] << endl;
                    status[index] = 1;
                    break;
                }
            }
            index ++;
        }
        for(auto s: status){
            if(s == 0){
                return 0;
            }
        }
        if(color == 'w'){
            cout << "Checkmate! White Wins!" << endl;
            return 1;
        }else{
            cout << "Checkmate! Black Wins!" << endl;
              return 2;
        }
    }
}
 
