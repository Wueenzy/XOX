#include <iostream>
using namespace std;

class utils{
private:
  char** board;
  bool turn = true;
public:
  void printer();
  void setBoard(char** xox);
  char** makeMove(int,int,bool);
  bool checkWin();
  bool checkTie();
};

void utils::printer(){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

void utils::setBoard(char** xox){
  board = xox;
}

char** utils::makeMove(int x, int y,bool ai){
  if (turn) {
    board[y][x] = 'X';
  }else{
    board[y][x] = 'O';
  }
  if(ai){
    return board;
  }
  turn = !turn;
  return board;
}

bool utils::checkWin(){
  for(int i = 0; i < 3; i++){
    if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != '_'){
      return true;
    }else if(board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != '_'){
      return true;
    }else if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != '_'){
      return true;
    }else if(board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != '_'){
      return true;
    }
  }
  return false;
}

bool utils::checkTie(){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(board[i][j] == '_'){
        return false;
      }
    }
  }
  return true;
}
