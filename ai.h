#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>
#include "utils.h"
using namespace std;

utils a;
fstream winModel("winModel.txt", winModel.out | winModel.app);
fstream drawModel("drawModel.txt", drawModel.out | drawModel.app);

class ai{
private:
  char** board;
  string _board;
  vector<string> currentGame;
  vector<string> _winModel;
  vector<string> _drawModel;
  bool trueModel = false;
public:
  void setBoard(char**);
  char** makeMove(char** xox, bool ai2 = false, bool realPlayer = false);
  void readModel();
  char** readBoard(string a);
  void writeWin();
  void writeDraw();
};

void ai::setBoard(char** xox){
  _board = "";
  board = xox;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      _board += board[i][j];
    }
  }
  currentGame.push_back(_board);
}

char** ai::makeMove(char** xox, bool ai2, bool realPlayer){
  int rX;
  int rY;
  srand((unsigned) time(NULL));
  board = xox;
  while (true) {
    rX = rand()%3;
    rY = rand()%3;
    trueModel = false;
    for(string& a : _winModel){
      if(trueModel && a != "_________"){
        board = readBoard(a);
        setBoard(board);
        return board;
      }else{
        if(_board == a){
          trueModel = true;
        }
      }
    }
    for(string& a : _drawModel){
      if(trueModel && a != "_________"){
        board = readBoard(a);
        setBoard(board);
        return board;
      }else{
        if(_board == a){
          trueModel = true;
        }
      }
    }
    if(board[rY][rX] == '_'){
      if(ai2){
        if(realPlayer){
          board[rY][rX] = 'X';
        }else{
          board[rX][rY] = 'O';
        }
        break;
      }
    }
  }
  setBoard(board);
  return board;
}

string line;
void ai::readModel(){
  if (!winModel.is_open()) {
        cout << "Error opening the file!" << endl;
  }else {
    string line;
    while(getline(winModel, line)){
      _winModel.push_back(line);
    }
    while(getline(drawModel,line)){
      _drawModel.push_back(line);
    }
    cout << "Model başarıyla okundu." << endl;
  }
}

char** ai::readBoard(string a){
  char** board_;
  board_ = new char*[3];
  for(int i = 0; i < 3; i++){
    board_[i] = new char[3];
  }
  
  for(int i = 0; i < 9; i++){
    board_[i/3][i%3] = a[i];
  }

  return board_;
}

void ai::writeWin(){
  for(auto var : currentGame) {
    winModel << var << endl;
  }
  currentGame.clear();
}

void ai::writeDraw(){
  for(auto var : currentGame){
    drawModel << var << endl;
  }
  currentGame.clear();
}
