#include <iostream>
#include <string>
#include <vector>
using namespace std;

//==========================
// Board Class
//==========================
class Board {
private:
    char grid[3][3];
public:
    Board(){
    // TODO : initialize the grid empty
    }
    void display()const {
    //TODO : print  the formated grid
    //    1   2   3
    // 1  X | O |
    //   ---+---+---
    // 2    | O |
    //   ---+---+---
    // 3    |   |
    }
    bool makemove(int row,int col,char symbol){

                 // TODO : check if valid move make the change return success status
                 }
    bool isValid(int row,int col)const{
                 // TODO : check if the cell is empty return true if yes
                 }
    bool checkWin(char symbol)const{
                 //TODO : check all win conditions
                 }
    bool isFull()const {
                // TODO : check if there is no empty cells
    }
    char getCell(int row, int col ){
               // TODO : return the symbol if exists
    }
    void reset(){
               // TODO : empty the grid
    }

    // i don't think we need getsize
    int getSize(){
       //TODO : return the grid dimension
    }
};
//==========================
// Player Class
//==========================

class Player {
private:
    string name ;
    char symbol;
public:
    Player(const string& name,char symbol){
         //TODO : initialize the player (can he enter a symbol outside the X,O?)
    }

    virtual void getMove(int& row , int& col)= 0;// pure virtual
    //for human to make move go to the human player class

    string getName()const{} // return the name
    char getSymbol()const{} // return the symbol

    void setName(const string& name ){
       //TODO : update the name
    }


};
//===================
//Humanplayer
//===================
class Humanplayer : public Player {
public:
    Humanplayer(const string & name , char symbol) : Player(name,symbol){}


    void getMove(int& row , int & col )override{
    // call the needed functions from board and change row,col
    }


};


//=================
//ENUMERATION
//=================
enum class Difficulty{
  EASY,
  HARD
//may increase in the future
};


//==========================
// AIplayer Class
//==========================
class AIplayer : public Player{
private:
    Difficulty difficultylevel;
    const Board* gameBoard; // the way for ai to see the board

   void getRandomMove( int& row,int&col ){
   //TODO : used if diff is easy to return just change row and col (you have the board)

   }
   void getBestMove( int& row,int&col) {
   //TODO : used if diff is hard to return just change row and col (you have the board)
   }

public:
    //if u have other solutions for the constructor error change the (:Player .......)
   AIplayer(const string& name,char symbol, Difficulty difficulty,const Board*board): Player(name,symbol){
   //TODO initialize the difficulty and board they will be handed to this function later
   }

   void getMove(int & row, int & col)override{
   // TODO : Do the move after checking if valid

   }
   void setDifficulty(Difficulty newDifficulty){
   //TODO : update the difficulty
   }


   //functions bellow can be changed
   // need a function to help navigate the possibilities and evaluate as explained in the record
    int evaluateBoard(const Board & board ){
    // use checkWin and evaluate (w/d/L) (10/0/-10)
    }


};


//==========================
// Game Class
//==========================
class Game {
private:
Board board;
Player* player1;
Player* player2;
Player* currentplayer;
public:
    Game():board(),player1(nullptr),player2(nullptr),currentplayer(nullptr){}

    ~Game(){
    delete player1;
    delete player2;

    }

    void start(){

    // every thing happens here (looping until the game ends,changing the currentplayer, checking if game ended )
    }
    void showMenu(){
    // make him choose between pvp , pvc (hard,easy) , exit
    }
    void setupPvP(){
    // make him enter their names and sumbols
    }
    void setupPvC(Difficulty difficulty){
    // make him enter his name and symbol , pass the difficulty to the ai
    }
    void switchplayer(){
    // after each move chnge what currentplayer points at
    }
    void playerTurn(){
    int r,c;
    //if human get the cell he wants if ai make r=c=0
    //getMove function should handle the rest
    //make the change happen in the board

    }
    bool checkGameEnd(){
    // the function needed is in board class
    // i didn't fully understand the pdf here
    }
    void displayResult(){
    // display the board
    }
    void reset(){
    //prepare for new round
    }
};


int main(){
    Game Tic_Tac_Toe;
    Tic_Tac_Toe.start();
    return 0;

}





