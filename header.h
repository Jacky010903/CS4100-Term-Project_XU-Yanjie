//  header.h
//  chess of characters
//
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>

using namespace std;


class Chessboard{
private:
    char board[9][9]; //chess table
    char chess[7]; // 7 types of chess: ABCDEFG
    int score;   //score
    int num_total;   //total number of chess which disappeared in the last round
    vector<int> x_history; //record the position of the chess which has been eliminated
    vector<int> y_history;
    bool check_chess(int row,int col); // check the status of every single chess, check if it still
                                       // exists

public:
    Chessboard(){     // create the Chessboard, and fill in every position with null at the begining
        memset(board,0,sizeof(board));
        for(int i=0;i<7;i++) chess[i]=65+i;//setting chesses as ABCDEFGH
        score=0;
        num_total=0;
    }
    void initialize(); //randomly initialize some chess
    void show_board(); //display the keyboard
    void random_chess(); //randomly initialize some chesses
    void reset(); //reset the table
    void score_chess(); //calculate the score
    void move_chess(int a,int b,int c,int d); //move the chess
    int check_end(); //check the chess
    void show_score();//display the score after the end of the game
    bool check_chance();  //check and elinimate， if return true, it means elinimation(s) has happened.
    friend class Coordinate;
};



class  Coordinate{
private:
    int row,col;
public:
    Coordinate(){
        row=0;col=0;
    }
    void choose_coor(Chessboard &bd);
    void set_coor(Chessboard &bd);
    void move_coor(Chessboard &bd,Coordinate &new_c);
    bool check_path(Chessboard &bd,Coordinate &new_c);
};

