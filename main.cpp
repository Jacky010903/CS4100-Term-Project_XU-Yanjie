#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <vector>
#include "header.h"
using namespace std;


int main()
{
    Chessboard board;     //define a chessboard
    Coordinate newc, oldc;  //define the new and old coordinate
    bool move_chance = false; //define a multi-direction marker of elimination
    board.initialize(); //initialize
    board.show_board(); //display the chessboard
    while (1) {
        cout << "Please input the coordinate of the chess which will be moved: " << endl;
        oldc.choose_coor(board);
        cout << "Please input the coordinate that the moved chess to be placed: " << endl;
        newc.set_coor(board);
        oldc.check_path(board,newc);
        oldc.move_coor(board,newc);  //move the chess
        move_chance=board.check_chance();  //check and return a multi-direction marker
        board.score_chess();
        board.reset(); //clear data
        if(board.check_end()<3) break;//check the chessboard，if the left positions were less than 3, then the game will be terminated.
        board.random_chess(); //ramdonly place 3 postions
        board.show_board(); //display the chessboard

        if (board.check_end()==0) break; //check the chess board，if every grid is filled, then exit the game

        while (1) {    // to deal with multi-direction elinimation
            if (move_chance) {
                cout<<"You have an extra chance to move the chess"<<endl;
                cout<<"Please input the coordinate of the chess which will be moved: "<<endl;
                oldc.choose_coor(board);
                cout<<"Please input the coordinate that the moved chess to be placed: "<<endl;
                newc.set_coor(board);
                oldc.move_coor(board,newc); //move the chess
                board.check_chance();  //check
                board.score_chess();
                board.show_board();
                board.reset();
            }
            else break;
        }

        board.reset();
        board.check_end();
        if (board.check_end()==true) break;
    }

    cout << "The game is over." << endl;
    board.show_score();
 return 0;
}

