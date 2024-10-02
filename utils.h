#include <iostream>
using namespace std;

class utils{
private:
  bool turn = true;
public:
  void printer(char** board);
  char** makeMove(char**,int,int,bool ai = false);
  bool checkWin(char**);
  bool checkTie(char**);
};

//Board'ı ekrana yazdırır.
void utils::printer(char** board){
  system("clear");
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

//Oyunda yapılan hamleyi kaydeder.
char** utils::makeMove(char** board, int x, int y, bool ai){
  if(turn || ai){
    board[y][x] = 'X';
  }else{
    board[y][x] = 'O';
  }
  turn = !turn;
  return board;
}

//Oyunda kazanıldı mı diye kontrol eder.
bool utils::checkWin(char** board){
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

//Oyunda berabere kalındı mı diye kontrol eder.
bool utils::checkTie(char** board){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      if(board[i][j] == '_'){
        return false;
      }
    }
  }
  return true;
}
