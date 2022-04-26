#include "header.h"

//function definition of the subclass coordinates

void Coordinate::choose_coor(Chessboard& bd) {
    int r,c;
    while (1) {
        cin>>r>>c;
        row=r-1;
        col=c-1;
        if(row<0||row>8||col<0||col>8) {cout<<"The input exceeds the boundary！"<<endl << "Please enter again:" << endl;continue;}
        if(bd.board[row][col]!=0) break;
        else cout<<"Wrong input!" << endl << "No chess are located on the input coordinates!" << endl <<  "Please enter again:"<<endl;
    }
}


void Coordinate::set_coor(Chessboard& bd) {
    int r, c;
    while(1){
        cin>>r>>c;
        row=r-1;
        col=c-1;
        if(row<0||row>8||col<0||col>8) {cout<<"The input exceeds the boundary!" << endl <<  "Please enter again:"<<endl;continue;}
        if(bd.board[row][col]==0) break;
        else cout<<"Wrong input!" << endl << "There are existing chess on the selected input!" << endl << "Please enter again: "<<endl;
    }
}

void Coordinate::move_coor(Chessboard& bd, Coordinate& new_c) {   //This function is called by the oldc object of the Coordinate class in the main function
    int n_r = new_c.row, n_c = new_c.col, o_r = this->row, o_c = this->col;
    bd.move_chess(n_r, n_c, o_r, o_c); //Call bd member function for transposition operation
}

bool Coordinate::check_path(Chessboard &bd,Coordinate &new_c){
    return true;
}




//Definition of parent function
bool Chessboard::check_chess(int row, int col) {
    int middatanumflag = 0;//how many routs to combine for 5 consecutive pieces
    int num1 = 0; //subdiagonal
    int num2 = 0; //vertical
    int num3 = 0; //diagonal
    int num4 = 0; //horizontal

    char flag = board[row][col];//get the type of chess piece
    if (flag == 0) return false;

    /*checking subdiagonal*/
    int middata1 = row;
    int middata2 = col;
    //checking the upper-left most coordinate of the chessboard
    while ((middata1 != 0) && (middata2 != 0)) {
        middata1--;
        middata2--;
    }
    //
    while (middata1 != row) {
        if (board[middata1][middata2] == flag)
        {
            num1++;//number of diminishing set would add 1
            //put this memory into history
            y_history.push_back(middata2);
            x_history.push_back(middata1);
        }
        else{
            //Delete the memory
            for (int i = 0; i < num1; i++)
            {
                y_history.pop_back();
                x_history.pop_back();
            }
            num1 = 0;//reset to 0
        }
        middata1++;
        middata2++;
    }
    //continue identifying right-down direction
    while (((middata1 != 9) && (middata2 != 9)) && (board[middata1][middata2] == flag)){
        num1++;// the number of diminished chess add by 1
        y_history.push_back(middata2);
        x_history.push_back(middata1);
        middata1++;
        middata2++;
    }
    //If not the situation that 5 consecutive same characters
    if (num1<5) {
        //deleting memory
        for (int i=0;i<num1;i++) {
            y_history.pop_back();
            x_history.pop_back();
        }
        num1 = 0;
    }
    else middatanumflag++;




    /*checking vertical direction*/
    middata1=row;
    middata2=col;
    //obtaining the upper-most coordinate
    while (middata1!=0) {
        middata1--;
    }
    //comparing the upper-most coordinate with the identifying coordinate
    while (middata1 != row) {
        if (board[middata1][middata2]==flag) {
            num2++;//diminished chess piece add by 1
            //save this in the memory history
            y_history.push_back(middata2);
            x_history.push_back(middata1);
        }
        else {
            //clearing the history memory since there exist new points
            for (int i = 0; i < num2; i++) {
                y_history.pop_back();
                x_history.pop_back();
            }
            num2 = 0;// reset to zero
        }
        middata1++;
    }
    //Continue identifying vertical downward direction
    while ((middata1!=9) && (board[middata1][middata2]==flag)){
        num2++;//diminished chess piece add by 1
        y_history.push_back(middata2);
        x_history.push_back(middata1);
        middata1++;
    }
    //if not the situation of 5 consecutive same character, then clear the memory
    if (num2<5){
        //clearing the memory
        for (int i=0;i<num2;i++){
            y_history.pop_back();
            x_history.pop_back();
        }
        num2=0;
    }
    else middatanumflag++;




    /*checking the direction of diagonal*/
    middata1=row;
    middata2=col;
    //obtaining the right-upper-most coordinate
    while ((middata2!=8)&&(middata1!=0)) {
        middata1--;
        middata2++;
    }
    while (middata1!=row) {
        if (board[middata1][middata2]==flag){
            num3++;//diminished chess piece add by 1
            //put this into the memory
            y_history.push_back(middata2);
            x_history.push_back(middata1);
        }
        else {
            //
            for (int i=0;i<num3;i++)
            {
                y_history.pop_back();
                x_history.pop_back();
            }
            num3=0;//reset to 0
        }
        middata1++;
        middata2--;
    }
    //continue identifying left downward direction
    //if not reach the boundary and the type of chess is the same
    while (((middata1!=9)&&(middata2!=-1)) && (board[middata1][middata2]==flag)){
        num3++;//number of diminished set add by 1
        y_history.push_back(middata2);
        x_history.push_back(middata1);
        middata1++;
        middata2--;
    }
    //if not equal or greater to 5 consecutive same characters and then clear the memory
    if (num3<5){
        //clear the memory
        for (int i = 0; i < num3; i++){
            y_history.pop_back();
            x_history.pop_back();
        }
        num3=0;
    }
    else middatanumflag++;





    /*checking horizontal direction*/
    middata1=row;
    middata2=col;
    //obtaining the leftmost chess piece
    while (middata2!=0) {
        middata2--;
    }
    //comparing the leftmost chess with the coordinates of identified chess piece
    while (middata2!=col) {
        if (board[middata1][middata2]==flag){
            num4++;//number of diminished set add by 1
            //save this into the memory
            y_history.push_back(middata2);
            x_history.push_back(middata1);
        }
        else {
            //clear the memory, since there are new points
            for (int i = 0; i < num4; i++){
                y_history.pop_back();
                x_history.pop_back();
            }
            num4=0;//reset to 0
        }
        middata2++;
    }
    //continue identifying directions
    //if not reached the boundart and the identified chess piece is the same
    while ((middata2!=9) && (board[middata1][middata2]==flag)){
        num4++;//number of diminished set add by 1
        y_history.push_back(middata2);
        x_history.push_back(middata1);
        middata2++;
    }
    //if not five consecutive same characters then clear the memory
    if (num4<5){
        //clear the memory
        for (int i = 0; i < num4; i++){
            y_history.pop_back();
            x_history.pop_back();
        }
        num4=0;
    }
    else middatanumflag++;

    //finally, identify whether every directions contain diminished chess pieces
    if (middatanumflag > 1) return true;
    else return false;
}

bool Chessboard::check_chance(){
    bool move=false;
    for (int i=0;i<9;i++){
        for (int j=0;j<9;j++){
            if (check_chess(i,j)) move=true;
        }
    }
    //after obtaining the chess piece that need to be eliminated, the part that have been over counted should be subtracted
    vector<int> mid_x;
    vector<int> mid_y;
    for (int i=0;i<x_history.size();i++){
        int i2=0;
        for(i2=0;i2<mid_x.size();i2++){
            if ((x_history[i]==mid_x[i2])&&(y_history[i] == mid_y[i2])) break;
        }
        if (i2>=mid_x.size()){
            mid_x.push_back(x_history[i]);
            mid_y.push_back(y_history[i]);
        }
    }
    num_total=int (mid_x.size());


    //eliminating the set that satisfy the condition (i.e. 5 consecutive same chess)
    for (int i=0;i<x_history.size();i++){
        board[x_history[i]][y_history[i]]=0;
    }
    return move;
}

void Chessboard::show_board() {
    int i=0, j=0;
    cout<<endl<<"0 1 2 3 4 5 6 7 8 9"<<endl;
    for (i = 0; i < 9; i++) {
        cout << i + 1 << " ";
        for (j = 0; j < 9; j++) {
            if (board[i][j] != 0) cout << board[i][j] << " ";
            else cout << "  ";
        }
        cout << endl;
    }
    cout << endl;
    cout << "Your current score is:" << score  << endl;
    cout << "---------------------------------------" << endl;
}

void Chessboard::random_chess() {
    //This function will merely produce one piece of chess
    //[a, b] = [a, b+1), thus the formula should be rand() % (b + 1 - a) + a;
    int row, col, i;
    srand((unsigned)time(NULL));
    for (int cnt=0;cnt<3;cnt++) {
        while(1){
            row=rand()%9+0;
            col = rand() % 9 + 0;
            if (board[row][col] == 0) break;
        }
        i=rand()%7+0;
        board[row][col]=chess[i];
    }
}

void Chessboard::move_chess(int a, int b, int c, int d) {
    board[a][b] = board[c][d];
    board[c][d] = 0;
}

void Chessboard::reset() {
    //set the diminished pieces to 0
    num_total = 0;
    //cancel
    x_history.clear();
    y_history.clear();
}

void Chessboard::score_chess() {
    score = score + (num_total - 5) * 2 + 10;
}

int Chessboard::check_end() {
    int i=0,j=0,free=0;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(board[i][j]==0) free++;
            else continue;
            if(free>=3) return 4;
        }
    }
    return free;  //false indicate that it is not completely filled
}

void Chessboard::initialize() {
    int row, col, i = 0;
    srand((unsigned)time(NULL));
    while (1) {
        row = rand() % 9 + 0;
        col = rand() % 9 + 0;
        if (board[row][col] == 0) {
            board[row][col] = chess[i];
            i++;
        }
        if (i == 7) break;
    }
}

void Chessboard::show_score() {
    cout << "Your final score: " << score << endl;
}
