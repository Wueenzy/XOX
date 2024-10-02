#include "ai.h"
using namespace std;

utils utils;
ai ai;

int main(){
  char** board;
  int x,y,k;
  int count = 0;
  //Boardı oluşturup içerisini doldurur.
  board = new char*[3];
  for(int i = 0;i < 3; i++){
    board[i] = new char[3];
  }
  
  for(int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++) {
      board[i][j] = '_';
    }
  }
  
  //Oyunda yapılmak istenen şeyi seçtirir.
  cout << "Ne yapmak istersiniz?(1- 2 Oyuncu, 2- Tek Oyuncu, 3- Modeli Eğit)" << endl;
  cin >> k;
  if(k == 1){
    for(int i = 0; i < 9; i++){
      utils.printer(board);
      cout << "x ve y değeri giriniz: " << endl;
      cin >> x >> y;
      while(true){
        if(x < 3 && y < 3 && y >= 0 && x >= 0 && board[y][x] == '_'){
          board = utils.makeMove(board,x,y);
          break;
        }else{
          system("clear");
          utils.printer(board);
          cout << "Girdiğiniz değer geçersiz!" << endl << "Tekrar x ve y değerini giriniz: " << endl;
          cin >> x >> y;
        }
      }
      utils.printer(board);
      if(utils.checkWin(board)){
        cout << board[y][x] << " Kazandı!" << endl;
        break;
      }
      if(utils.checkTie(board)){
        cout << "Berabere" << endl;
        break;
      }
    }
  } else if (k == 2) {
    ai.loadModel();
    for(int i = 0; i < 9; i++){
      utils.printer(board);
      cout << "x ve y değeri giriniz: " << endl;
      cin >> x >> y;
      while(true){
        if(x < 3 && y < 3 && y >= 0 && x >= 0 && board[y][x] == '_'){
          board = utils.makeMove(board,x,y,true);
          break;
        }else{
          system("clear");
          utils.printer(board);
          cout << "Girdiğiniz değer geçersiz!" << endl << "Tekrar x ve y değerini giriniz: " << endl;
          cin >> x >> y;
        }
      }
      if(utils.checkWin(board)){
        cout << "Oyuncu Kazandı!" << endl;
        break;
      }
      if(utils.checkTie(board)){
        cout << "Berabere" << endl;
        break;
      }
      board = ai.makeMove(board, 'O');
      if(utils.checkWin(board)){
        cout << "AI Kazandı!" << endl;
        break;
      }
      if(utils.checkTie(board)){
        cout << "Berabere" << endl;
        break;
      }
    }
  } else if (k == 3) {
    while(true){
      board = ai.makeMove(board,'X');
      if(utils.checkWin(board)){
        count++;
        board = ai.loseGame();
      }
      if(utils.checkTie(board)){
        count++;
        board = ai.drawGame();
      }
      board = ai.makeMove(board, 'O');
      if(utils.checkWin(board)){
        count++;
        board = ai.winGame();
      }
      if(utils.checkTie(board)){
        count++;
        board = ai.drawGame();
      }
      system("clear");
      cout << count << endl;
      count++;
      if(count > 10000){
        ai.saveModel();
        break;
      }
    }
  }
  
  return 0;
}
