#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <limits>
using namespace std;

//==========================
// Board Class
//==========================
class Board
{
private:
    char grid[3][3];
public:
    Board()
    {
        // TODO : initialize the grid empty
        reset();
    }
    void display()const
    {
       cout<<"    1   2   3\n";
        for(int i=0; i<3; i++)
        {
            cout<<" "<< i+1 <<"  ";
            for(int j=0; j<3; j++)
            {
                cout<< grid[i][j];
                if(j<2)
                {
                    cout<<" | ";
                }
            }
            cout<<"\n";
            if(i<2)
            {
                cout<<"   ---+---+---\n";
            }
        }
        //TODO : print  the formated grid
        //    1   2   3
        // 1  X | O |
        //   ---+---+---
        // 2    | O |
        //   ---+---+---
        // 3    |   |
    }
    bool makemove(int row,int col,char symbol)
    {
        if(isValid(row,col))
        {
            grid[row][col]=symbol;
            return true;
        }
        return false;


    }
    bool isValid(int row,int col)const
    {
        if(row>=0 && row<3 && col>=0 && col<3 && grid[row][col]==' ')
        {
            return true;
        }
        return false;
        // TODO : check if the cell is empty return true if yes
    }
    bool checkWin(char symbol)const
    {
        for(int i=0; i<3; i++)
        {
            if(grid[i][0]==symbol && grid[i][1]==symbol && grid[i][2]==symbol)
            {
                return true;
            }
        }
        for(int j=0; j<3; j++)
        {
            if(grid[0][j]==symbol && grid[1][j]==symbol && grid[2][j]==symbol)
            {
                return true;
            }
        }
        if(grid[0][0]==symbol && grid[1][1]==symbol&& grid[2][2]==symbol)
        {
            return true;
        }
        if(grid[0][2]==symbol && grid[1][1]==symbol && grid [2][0]==symbol)
        {
            return true;
        }
        return false;
    }
    bool isFull()const
    {
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(grid[i][j]==' ')
                {
                    return false;
                }

            }
        }
        return true;

    }
    char getCell(int row, int col )
    {
        return grid[row][col];

    }
    void reset()
    {
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                grid[i][j]=' ';
            }
        }

    }

    // i don't think we need getsize
    int getSize()
    {
        return 3;
        //TODO : return the grid dimension
    }
};
//==========================
// Player Class
//==========================

class Player
{
private:
    string name ;
    char symbol;
public:
    Player(const string& name,char symbol) : name(name), symbol(static_cast<char>(toupper(symbol)))
    {
        // AI logic assumes opponent is the other of {X, O} (see AIplayer::Minmax),
        // so reject anything else fast rather than silently corrupting gameplay.
        if(this->symbol != 'X' && this->symbol != 'O')
        {
            cerr << "Player symbol must be 'X' or 'O' (got '" << symbol << "').\n";
            exit(1);
        }
    }
    virtual ~Player() {}

    virtual void getMove(int& row, int& col)= 0; // pure virtual
    //for human to make move go to the human player class

    string getName()const { return name; }
    char getSymbol()const { return symbol; }

    void setName(const string& newName)
    {
        name = newName;
    }


};
//===================
//Humanplayer
//===================
class Humanplayer : public Player
{
private:
    const Board& gameBoard;
public:
    Humanplayer(const string & name, char symbol, const Board& board)
        : Player(name,symbol), gameBoard(board) {}


    void getMove(int& row, int & col )override
    {
        int r, c;
        while(true)
        {
            cout << getName() << " (" << getSymbol() << "), enter row and column (1-3): ";
            if(!(cin >> r >> c))
            {
                if(cin.eof())
                {
                    cout << "\nInput closed. Exiting.\n";
                    exit(0);
                }
                cout << "Invalid input. Please enter two numbers.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            r -= 1;
            c -= 1;
            if(gameBoard.isValid(r, c))
            {
                row = r;
                col = c;
                return;
            }
            cout << "Invalid move. Cell is out of range or already occupied. Try again.\n";
        }
    }


};


//=================
//ENUMERATION
//=================
enum class Difficulty
{
    EASY,
    HARD
//may increase in the future
};


//==========================
// AIplayer Class
//==========================
class AIplayer : public Player
{
private:
    Difficulty difficultylevel;
    const Board* gameBoard; // the way for ai to see the board
    // easy mode choses a insta win move or a random move
    void getRandomMove( int& row,int&col )
    {
        //TODO : used if diff is easy to return just change row and col (you have the board)

        for(int r =0; r<3; r++)
        {
            for(int c=0; c<3; c++)
            {
                if(gameBoard->isValid(r,c))
                {
                    Board tempboard = *gameBoard;
                    tempboard.makemove(r,c,getSymbol());
                    if(tempboard.checkWin(getSymbol()))
                    {
                        row=r;
                        col=c;
                        return;
                    }
                }
            }
        }


        while(true)
        {
            int r = rand() %3;
            int c = rand()%3;
            if(gameBoard->isValid(r,c))
            {
                row=r;
                col=c;
                break;
            }
        }

    }
    //helper function
    int Minmax(Board currboard,char currsymbol)
    {
        if(currboard.isFull())
        {
            return evaluateBoard(currboard);
        }
        char opsymbol = (currsymbol=='X') ? 'O' : 'X';
        int bestscore;
        if(currsymbol== getSymbol())
        {
            bestscore=-100;
        }
        else
        {
            bestscore=100;
        }

        for(int r =0; r<3; r++)
        {
            for(int c=0; c<3; c++)
            {
                if(currboard.isValid(r,c))
                {
                    Board testBoard = currboard;


                    testBoard.makemove(r,c,currsymbol);
                    int score= Minmax(testBoard,opsymbol);


                    if(currsymbol== getSymbol())
                    {
                        bestscore=max(bestscore,score);
                    }
                    else
                    {
                        bestscore=min(bestscore,score);
                    }
                }
            }
        }

        return bestscore;
    }

    void getBestMove( int& row,int&col)
    {
        //TODO : used if diff is hard to return just change row and col (you have the board)
        int bestscore=-10000;
        int br,bc;//the cell coordinations of best score

        for(int r =0; r<3; r++)
        {
            for(int c=0; c<3; c++)
            {
                if(gameBoard->isValid(r,c))
                {
                    Board tboard=*gameBoard;

                    if(Minmax(tboard,getSymbol())>bestscore)
                    {
                        bestscore=Minmax(tboard,getSymbol());
                        br=r;
                        bc=c;
                    }
                }
            }
        }
        row=br;
        col=bc;
    }

public:
    //if u have other solutions for the constructor error change the (:Player .......)
    AIplayer(const string& name,char symbol, Difficulty difficulty,const Board*board): Player(name,symbol)
    {
        //TODO initialize the difficulty and board they will be handed to this function later
        difficultylevel = difficulty;
        gameBoard = board;
    }

    void getMove(int & row, int & col)override
    {
        // TODO : Do the move after checking if valid
        if(difficultylevel==Difficulty::EASY)
        {
            getRandomMove(row,col);
        }
        else
        {
            getBestMove(row,col);
        }


    }


    void setDifficulty(Difficulty newDifficulty)
    {
        //TODO : update the difficulty
        difficultylevel = newDifficulty;
    }


    //functions bellow can be changed
    // need a function to help navigate the possibilities and evaluate as explained in the record
    int evaluateBoard(const Board & board )
    {
        // use checkWin and evaluate (w/d/L) (10/0/-10)
        char opsymbol = (getSymbol() == 'X')?'O':'X';
        if(board.checkWin(getSymbol()))
        {
            return 10;
        }
        else if(board.checkWin(opsymbol))
        {
            return -10 ;
        }
        else
        {
            return 0;
        }

    }


};


//==========================
// Game Class
//==========================
class Game
{
private:
    Board board;
    Player* player1;
    Player* player2;
    Player* currentplayer;
public:
    Game():board(),player1(nullptr),player2(nullptr),currentplayer(nullptr) {}

    ~Game()
    {
        delete player1;
        delete player2;

    }

    void start()
    {
        showMenu();
       while(true){
        board.display();
        playerTurn();

    if(checkGameEnd()){
        displayResult();
        break;
    }

    switchplayer();
}
    }
    void showMenu()
    {
        int choice;
        cout << "1.Player vs Player \n2.Player vs Computer (Easy) \n3.Player vs Computer (Hard)\n";
        cin >> choice;
        if(choice == 1){
            setupPvP();
        }
        else if(choice == 2){
            setupPvC(Difficulty :: EASY);
        }
        else{
            setupPvC(Difficulty :: HARD);
        }
    }
    void setupPvP()
    {
        string n1,n2;
        cout << "Player 1: ";
        cin >> n1;
        cout << "Player 2: ";
        cin >> n2;
        player1 = new Humanplayer(n1, 'X');
        player2 = new Humanplayer(n2, 'O');
        currentplayer = player1;
    }
    void setupPvC(Difficulty difficulty)
    {
        string n ;
        cout << "Your name: ";
        cin >> n ;
        player1 = new Humanplayer(n, 'X');
        player2 = new AIplayer("AI", 'O', difficulty, &board);
        currentplayer = player1;
    }
    void switchplayer()
    {
        currentplayer = (currentplayer == player1)? player2:player1;
    }
    void playerTurn()
    {
        int r,c;
        while(true){
            currentplayer -> getMove(r,c);
            if(board.makemove(r,c,currentplayer->getSymbol())){
                break;
            }
                else{
                cout << "Invalid move! \n";
            }
        }

    }
    bool checkGameEnd()
    {
        return board.checkWin(currentplayer->getSymbol()) || board.isFull();
    }
    void displayResult()
    {
        board.display();
        if(board.checkWin(currentplayer->getSymbol())){
            cout << currentplayer->getName() << " wins! \n";
        }
        else{
            cout << "Draw! \n";
        }
    }
    void reset()
    {
    board.reset();
    currentplayer = player1;
    }
};


int main()
{
    srand(time(0));
    Game Tic_Tac_Toe;
    Tic_Tac_Toe.start();
    return 0;

}





