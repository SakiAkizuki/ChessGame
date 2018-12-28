#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include "ai.h"
#include "human.h"
#include "player.h"
#include "block.h"
#include "board.h"
#include "piece.h"
#include "game.h"
using namespace std;



//change abcdefgh to 12345678
int change_char(char c){
    int ic;
    if(c > '8'){
        ic = c - 'a';
    }else{
        ic = 7 - ( c - '1' );
    }
    //cout << ic << " " ; //Test command
    return ic;
}

vector<int> transfer(string s){
    if(s.length() != 2){
        return {-1,-1};
    }
    int i = change_char(s[1]);//row
    int k = change_char(s[0]); //col
    vector<int> temp{i, k};
    if(i < 0 or i > 7 or k < 0 or k > 7){
        return {-1,-1};
    }
//    cout << "transfer " << temp[0] << temp[1] << endl;
    return temp;
}


int main(){
    string command;
    string inval = "invalid input, please try again";
    vector<char>player{'W', 'B', 'G', 'Y'};
    vector<int> wrong{-1,-1};
    //pls is the player ptr list
    int WhiteScore = 0;
    int BlackScore = 0;
    bool setupBoard=0;
    vector<Player*> pls;
    Xwindow window;
    Board *gameboard = new Board{};
    Game *game=nullptr;
    //empty game
    
    
    
    int playerindex = 0;
    //if playerindex = 0, that means it's black'trun, if = 1, that means it's white'turn
    
    int current_run = 0;
    //current_run = 0 means the game is not start yet; = 1 otherwise;
    //if the game is not set yet, current_run = 2;
    
    while(cin >> command){
        if(command == "game"){
            pls.clear();
            if(game != nullptr){
                delete game;
                game  = nullptr;
                gameboard = new Board{};
            }
            string temp;
            for(int i = 0; i < 2; i++){
                cout << "Please Entre the type of " << player[i] << endl;
                cin >> temp;
                //cin will call until the correct type is set
                while(temp != "computer[1]" and temp != "computer[2]" and temp != "computer[3]" and temp != "computer[4]" and temp != "human"){
                    cout << "please enter right player type" << endl;
                    cin >> temp;
                }
                
                if(temp == "human"){
                    Human *p = new Human{player[i]};
                    pls.push_back(p);
                }else if(temp == "computer[1]"){
                    //lvl 1 AI
                    AI *p = new AI(player[i], 1, gameboard);
                    pls.emplace_back(p);
                }else if(temp == "computer[2]"){
                    //lvl 2 AI
                    AI *p = new AI(player[i], 2, gameboard);
                    pls.emplace_back(p);
                }else if(temp == "computer[3]"){
                    AI *p = new AI(player[i], 3, gameboard);
                    pls.emplace_back(p);
                    //Lvl 3 AI
                }else if(temp == "computer[4]"){
                    //Lvl 4 AI
                    AI *p = new AI(player[i], 4, gameboard);
                    pls.emplace_back(p);
                }
            }
            if(game != nullptr) {
                setupBoard=0;
                delete game;
            }
          
            game = new Game{pls[0], pls[1], gameboard,setupBoard};
            gameboard->GraphicDisplay(window);
            gameboard->TextDisplay();
            //create the game we needed*/
            
        }else if(command == "resign"){
            
            if(playerindex == 1){
                cout << "Black resigns, The Winner is White-player" << endl;
                WhiteScore++;
            }else{
                cout << "White resigns, The Winner is Black-player" << endl;
                BlackScore++;
            }
            if(game != nullptr){
                setupBoard=0;
                delete gameboard;
                pls[0]->pieces.clear();
                pls[1]->pieces.clear();
                gameboard = new Board{};
                game->changeboard(gameboard);
                game->default_board();
            }
            playerindex = 0;
            cout << "Good Game and Have A Nice Day XD" << endl;
            cout << "To start a new game please type game, otherwise press Ctrl+D to end the game!"<<endl;
            string continuue;
            current_run = 0;
            while(cin >> continuue and continuue != "game"){}
            //gameboard->GraphicDisplay(window);
            gameboard->TextDisplay();
            
        }else if (command == "undo") {
            game->undo();
            playerindex = (playerindex + 1) % 2;
            gameboard->GraphicDisplay(window);
            gameboard->TextDisplay();

        }else if (command == "move"){
            vector<int> init;
            vector<int> end;
            int valid_move = 0; // 0 means it's valid
            //if the player is a human
            if((pls[playerindex]->isHuman())){
                AI temp{pls[playerindex], gameboard};
                vector<int> Suggestion = temp.getMove(pls[(playerindex + 1)%2], 0);
                char sugget3 = Suggestion[3] + 'a';
                char sugget1 = Suggestion[1] + 'a';
                cout << "Suggestion Move " <<  sugget1 << (8 - Suggestion[0]) << " " << sugget3 << (8 - Suggestion[2])  << endl;
                string position;
                cin >> position;
                init = transfer(position);
                cin >> position;
                end = transfer(position);
                if(init != wrong and end !=wrong){
                    //game->move function here, to determine which player is moving, use player_index.
                    //check if the movement is legal
                    Piece *temp = gameboard->getBoard()[init[0]][init[1]].getPiece();
                    if(temp != nullptr){
                        bool condition1= temp->legalMove(end[0], end[1]); //legal move
                        bool condition2= false;
                        if(temp->getColour() == 'w' and playerindex == 0){
                            condition2 = true;
                        }
                        if(temp->getColour() == 'b' and playerindex  == 1){
                            condition2 = true;
                        }
                        if(condition2 and condition1){
                            game->makeMove(init, end);
                            playerindex = (playerindex + 1) % 2;
                            current_run = 1;
                            if (temp->getType() == 'p' and end[0] == 7) {
                                char promote;
                                cin >> promote;
                                if (islower(promote)) {
                                    game->addPiece(promote, end);
                                }
                            }
                            if (temp->getType() == 'P' and end[0] == 0) {
                                char promote;
                                cin >> promote;
                                if (isupper(promote)) {
                                    game->addPiece(promote, end);
                                }
                            }
                        }
                        else if (condition2 and temp->getType() == 'p' and init[0] == 4 and end[0] == 5 and game->history.size() != 0 and game->history.back().getPiece() == 'P' and
                                 game->history.back().getEnd()[0] == 4 and game->history.back().getInit()[0] == 6 and abs(init[1] - game->history.back().getEnd()[1]) == 1 and
                                 end[1] == game->history.back().getEnd()[1]) {
                            game->removePiece_setup(game->history.back().getEnd());
                            game->makeMove(init, end);
                            playerindex = (playerindex + 1) % 2;
                        }
                        else if (condition2 and temp->getType() == 'P' and init[0] == 3 and end[0] == 2 and game->history.size() != 0 and game->history.back().getPiece() == 'p' and
                                 game->history.back().getEnd()[0] == 3 and game->history.back().getInit()[0] == 1 and abs(init[1] - game->history.back().getEnd()[1]) == 1 and
                                 end[1] == game->history.back().getEnd()[1]) {
                            game->removePiece_setup(game->history.back().getEnd());
                            game->makeMove(init, end);
                            playerindex = (playerindex + 1) % 2;
                        }
                        else if (condition2 and temp->getType() == 'k' and init[0] == 0 and init[1] == 4 and end[0] == 0 and end[1] == 2 and gameboard->getBoard()[0][0].getPiece() != nullptr
                                 and gameboard->getBoard()[0][0].getPiece()->getType() == 'r' and gameboard->getBoard()[0][1].getPiece() == nullptr and gameboard->getBoard()[0][2].getPiece() == nullptr
                                 and gameboard->getBoard()[0][3].getPiece() == nullptr) {
                            game->makeMove({0,4}, {0,2});
                            game->makeMove({0,0}, {0,3});
                            playerindex = (playerindex + 1) % 2;
                        }
                        else if (condition2 and temp->getType() == 'k' and init[0] == 0 and init[1] == 4 and end[0] == 0 and end[1] == 6 and gameboard->getBoard()[0][7].getPiece() != nullptr
                                 and gameboard->getBoard()[0][7].getPiece()->getType() == 'r' and gameboard->getBoard()[0][5].getPiece() == nullptr and gameboard->getBoard()[0][6].getPiece() == nullptr) {
                            game->makeMove({0,4}, {0,6});
                            game->makeMove({0,7}, {0,5});
                            playerindex = (playerindex + 1) % 2;
                        }
                        else if (condition2 and temp->getType() == 'K' and init[0] == 7 and init[1] == 4 and end[0] == 7 and end[1] == 2 and gameboard->getBoard()[7][0].getPiece() != nullptr
                                 and gameboard->getBoard()[7][0].getPiece()->getType() == 'R' and gameboard->getBoard()[7][1].getPiece() == nullptr and gameboard->getBoard()[7][2].getPiece() == nullptr
                                 and gameboard->getBoard()[7][3].getPiece() == nullptr) {
                            game->makeMove({7,4}, {7,2});
                            game->makeMove({7,0}, {7,3});
                            playerindex = (playerindex + 1) % 2;
                        }
                        else if (condition2 and temp->getType() == 'K' and init[0] == 7 and init[1] == 4 and end[0] == 7 and end[1] == 6 and gameboard->getBoard()[7][7].getPiece() != nullptr
                                 and gameboard->getBoard()[7][7].getPiece()->getType() == 'R' and gameboard->getBoard()[7][5].getPiece() == nullptr and gameboard->getBoard()[7][6].getPiece() == nullptr) {
                            game->makeMove({7,4}, {7,6});
                            game->makeMove({7,7}, {7,5});
                            playerindex = (playerindex + 1) % 2;
                        }else{
                            cout << "Invalid Movement, Becasue legalMove " << condition1 << " and correctplayer " << condition2 << " are not satisfied!" << endl;
                            valid_move = 1;
                        }
                    }
                }else{
                    cout << "invalid position " << endl;
                    valid_move = 1;
                }
            }else{
                //ai move
                game->aiMove(playerindex);
                playerindex = (playerindex + 1) % 2;
            }
            int ischecked = game->isChecked();
            if((ischecked == 3) or (ischecked == 1 and playerindex == 1) or (ischecked == 2 and playerindex == 0))  {
                cout << "Invalid! Your king will be in check" << endl;
                game->undo();
                playerindex = (playerindex + 1) % 2;
            }
            gameboard->GraphicDisplay(window);
            gameboard->TextDisplay();
            //check if the king is in checked;
            if(valid_move == 0){
                int iswon = game->isWon(playerindex);
                if(iswon == 1){
                    WhiteScore++;
                    if(game != nullptr){
                        setupBoard=0;
                        delete gameboard;
                        pls[0]->pieces.clear();
                        pls[1]->pieces.clear();
                        gameboard = new Board{};
                        game->changeboard(gameboard);
                        game->default_board();
                        current_run = 0;
                    }
                    playerindex = 0;
                    cout << "Good Game and Have A Nice Day XD" << endl;
                    cout << "To start a new game please type game, otherwise press Ctrl+D to end the game!"<<endl;
                    string continuue;
                    while(cin >> continuue and continuue != "game"){}
                    gameboard->GraphicDisplay(window);
                    gameboard->TextDisplay();
                }else if (iswon == 2){
                    BlackScore++;
                    if(game != nullptr){
                        setupBoard=0;
                        delete gameboard;
                        pls[0]->pieces.clear();
                        pls[1]->pieces.clear();
                        gameboard = new Board{};
                        game->changeboard(gameboard);
                        game->default_board();
                        current_run = 0;
                    }
                    
                    playerindex = 0;
                    cout << "Good Game and Have A Nice Day XD" << endl;
                    cout << "To start a new game please type game, otherwise press Ctrl+D to end the game!"<<endl;
                    string continuue;
                    while(cin >> continuue and continuue != "game"){}
                }else{
                    ischecked = game->isChecked();
                    if(ischecked == 0){
                    }else if(ischecked == 1){
                        cout << "white is in check" << endl;
                    }else if(ischecked == 2){
                        cout << "Black is in check" << endl;
                    }else if(ischecked == 3){
                        cout <<"Both White and Black are in check" << endl;
                    }
                }
            }            
            
    
        
        }else if(command == "setup"){
            
            if(current_run == 1){
                cout << "The game has started, you are not able to set up" << endl;
            }else if(current_run == 2){
                cout << "You have to type game to start the game first before set_up mode" << endl;
            }else{
                delete gameboard;
                gameboard = new Board{};
                game->changeboard(gameboard);
                pls[0]->pieces.clear();
                pls[1]->pieces.clear();
                gameboard->GraphicDisplay(window);
                gameboard->TextDisplay();
                setupBoard=1;
                string c;
                while(!cin.eof()){
                    cin >> c;
                    //read until + - = done are read
                    while(c != "+" and c != "-" and c != "=" and c != "done"){
                        cin >> c;
                    }
                    if(c == "done"){
                        if(game->checkValid()){
                            cout << "leave setup Mode" << endl;
                            gameboard->GraphicDisplay(window);
                            gameboard->TextDisplay();
                            break;
                        }else{
                            cout << "You have to make sure the board is valid!" << endl;
                            
                        }
                    }else if (c == "+"){
                        char c1;
                        string c2;
                        cin >> c1;
                        cin >> c2;
                        vector<int> pos = transfer(c2);
                        if(pos != wrong){
                            game->addPiece(c1, pos);
                            gameboard->TextDisplay();
                            gameboard->GraphicDisplay(window);
                        }else{
                            cout << " Invalid Input " << endl;
                        }
                       
                    }else if(c == "-"){
                        string c1;
                        cin >> c1;
                        vector<int> position=transfer(c1);
                        if(position != wrong){
                            game->removePiece_setup(position);
                            gameboard->TextDisplay();
                            gameboard->GraphicDisplay(window);
                        }else{
                            cout << "Invalid Input" << endl;
                        }
                    }else{
                        string col;
                        cin >> col;
                        if(col == "B" or col == "b"){
                            playerindex = 1;
                            cout << "Black goes next" << endl;
                        }else if (col == "W" or col == "w"){
                            playerindex = 0;
                            cout << "White goes next" << endl;
                        }else{
                            cout << "we dont have that player pls entre valid color" << endl;
                        }
                    }
                }
            }
        }else{
            cout << inval << endl;
        }
    }
    
    cout << "Final Score:" << endl;
    cout << "White: " <<  WhiteScore << endl;
    cout << "Black: " << BlackScore <<  endl;
    //if none_command is called, then delete the game;
    if(game != nullptr){
        setupBoard=0;
        delete game;
        
    }
    
}
