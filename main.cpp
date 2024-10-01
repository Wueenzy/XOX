#include "ai.h"
using namespace std;

utils utils;
ai ai;

int main(){
  char** board;
  int x,y,k,rX,rY,rT;
  int count = 0;
  bool aiB;
  board = new char*[3];
  for(int i = 0;i < 3; i++){
    board[i] = new char[3];
  }
  
  for(int i = 0; i < 3; i++){
    for (int j = 0; j < 3; j++) {
      board[i][j] = '_';
    }
  }

  utils.setBoard(board);
  ai.setBoard(board);
  cout << "Ne yapmak istersiniz?(1-2 kişi, 2-Tek kişi, 3-AI vs AI)" << endl;
  cin >> k;
  if(k == 1){
    while(true){
      cout << "x ve y değeri giriniz!" << endl;
      cin >> x >> y;
      if (x < 3 && y < 3 && board[y][x] == '_') {
        board = utils.makeMove(x,y,aiB);
      }else {
        cout << "Tekrar giriniz!" << endl;
        while (true) {
          cin >> x >> y;
          if (x < 3 && y < 3 && board[y][x] == '_') {
            board = utils.makeMove(x,y,aiB);
            break;
          }else{
            cout << "Tekrar giriniz!" << endl;
          }
        }
      }
      system("clear");
      utils.printer();
      if (utils.checkWin()) {
        cout << board[y][x] << " kazandı!" << endl;
        break;
      }else if(utils.checkTie()){
        cout << "Berabere!" << endl;
        break;
      }
    }
  }else if(k == 2){
    aiB = true;
    while(true){
      cout << "x ve y değeri giriniz!" << endl;
      cin >> x >> y;
      if (x < 3 && y < 3 && board[y][x] == '_') {
        board = utils.makeMove(x,y,aiB);
      }else {
        cout << "Tekrar giriniz!" << endl;
        while (true) {
          cin >> x >> y;
          if (x < 3 && y < 3 && board[y][x] == '_') {
            board = utils.makeMove(x,y,aiB);
            break;
          }else{
            cout << "Tekrar giriniz!" << endl;
          }
        }
      }
      ai.setBoard(board);
      if (utils.checkWin()) {
        system("clear");
        utils.printer();
        cout << "Oyuncu kazandı!" << endl;
        break;
      }else if(utils.checkTie()){
        system("clear");
        utils.printer();
        cout << "Berabere!" << endl;
        break;
      }

      board = ai.makeMove(board);

      system("clear");
      utils.printer();
      if (utils.checkWin()) {
        cout << "AI kazandı!" << endl;
        break;
      }else if(utils.checkTie()){
        cout << "Berabere!" << endl;
        break;
      }
    }
  }else if(k==3){
    aiB = true;
    while(true){
      board = ai.makeMove(board, true, true);
      if (utils.checkWin()) {
        count++;
        system("clear");
        cout << "Oynanan oyun sayısı: " << count << endl;
        for(int i = 0; i < 3; i++){
          for (int j = 0; j < 3; j++) {
            board[i][j] = '_';
          }
        }
        ai.writeWin();
      }else if(utils.checkTie()){
        count++;
        system("clear");
        cout << "Oynanan oyun sayısı: " << count << endl;
        for(int i = 0; i < 3; i++){
          for (int j = 0; j < 3; j++) {
            board[i][j] = '_';
          }
        }
        ai.writeDraw();
      }

      board = ai.makeMove(board, true, false);

      if (utils.checkWin()) {
        count++;
        system("clear");
        cout << "Oynanan oyun sayısı: " << count << endl;
        for(int i = 0; i < 3; i++){
          for (int j = 0; j < 3; j++) {
            board[i][j] = '_';
          }
        }
      }else if(utils.checkTie()){
        count++;
        system("clear");
        cout << "Oynanan oyun sayısı: " << count << endl;
        for(int i = 0; i < 3; i++){
          for (int j = 0; j < 3; j++) {
            board[i][j] = '_';
          }
        }
        ai.writeDraw();
      }
    }
  }
  
  return 0;
}
