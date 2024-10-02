#include "utils.h"
#include <unordered_map>
#include <vector>
#include <fstream>
#include <random>
#include <time.h>
#include <string>
using namespace std;

utils aiUtils;
fstream sModelIN("model.txt");
fstream sModelOUT("model.txt", sModelOUT.out | sModelOUT.app);

//Board'ı kaydedilip okunabilecek bir biçime çevirir.
string recoverBoard(char** board){
  string aiBoard = "";
  for (int i = 0; i < 9; i++) {
    aiBoard += board[i/3][i%3];
  }

  return aiBoard;
}

char** unrecoverBoard(string aiBoard){
  char** board;
  
  board = new char*[3];
  for(int i = 0; i < 3; i++){
    board[i] = new char[3];
  } 

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      board[i][j] = aiBoard[i*3+j];
    }
  }

  return board;
}

random_device rd;
mt19937 gen(rd());    
uniform_int_distribution<> distrib(0, 2);

class ai{
private:
  char** board;
  string aiBoard;
  unordered_map<string,float> model;
  string bestString = "";
  float bestValue = 0;
  vector<string> currentGame;
  vector<string> preGame;
  bool turn = true;
  string now;
public:
  void setBoard(char**);
  char** makeMove(char**, char, bool useBrain = false);
  char** winGame();
  char** loseGame();
  char** drawGame();
  void saveModel();
  void loadModel();
};

//Yapay zekanın içerisine board'ı aktarır.
void ai::setBoard(char** _board){
  board = _board;
  aiBoard = recoverBoard(_board);
  currentGame.push_back(aiBoard);
}

//Yapay zeka hamlesini yapar ve kayıt eder.
char** ai::makeMove(char** _board, char player, bool useBrain){
  if(useBrain == true){
    now = recoverBoard(_board);
    bestValue = 0;
    bestString = now;
    for(int i = 0; i < 9;i++){
      if(now[i] == '_'){
        now[i] = player;
        if(model[now] > bestValue){
          bestValue = model[now];
          bestString = now;
        }
        now[i] = '_';
      }
    }
    if(bestString != recoverBoard(_board)){
      board = unrecoverBoard(bestString);
      setBoard(board);
      return board;
    }
  }

  int valX = distrib(gen);
  int valY = distrib(gen);
  while(true){
    if(_board[valY][valX] == '_'){
      _board[valY][valX] = player;
      break;
    }
    valX = distrib(gen);
    valY = distrib(gen);
  }
  setBoard(_board);
  return _board;
}

char** ai::winGame(){
  for(auto var : currentGame) {
    model[var] += 2;
  }

  for(int i = 0; i < 3; i++){
    for(int j = 3; j < 3; j++){
      board[i][j] = '_';
    }
  }
  
  preGame = currentGame;
  currentGame.clear();
  setBoard(board);

  return board;
}

char** ai::loseGame(){
  for(auto var : currentGame) {
    model[var] -= 1;
  }

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      board[i][j] = '_';
    }
  }
  
  preGame = currentGame;
  currentGame.clear();
  setBoard(board);
  
  return board;
}

char** ai::drawGame(){
  for(auto var : currentGame) {
    model[var] += 1;
  }

  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      board[i][j] = '_';
    }
  }
  
  preGame = currentGame;
  currentGame.clear();
  setBoard(board);
  
  return board;
}

void ai::saveModel(){
  for(auto pair : model) {
    sModelOUT << pair.first << ":" << pair.second << endl;
  }
}

void ai::loadModel(){
  string line;
  while(getline(sModelIN, line)){
    int pos = line.find(":");
    model[line.substr(0,9)] = stof(line.substr(pos+1));
  }
}
