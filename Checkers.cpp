#include<iostream>
#include<cstdlib>
#include<cmath>
#include <ctime>
using namespace std;
char board [8][8];
int row, col;
int newrow, newcol;
char turn = 'x';
struct Move {
    int fromrow, fromcol;
    int torow, tocol;
};
Move moves[100];
int movecount = 0;
bool cancapture (int r, int c);
bool canmove(int r, int c) {
    char piece = board[r][c];
    if(piece == 'x') {
        if(r + 1 <= 7 && c + 1 <= 7 &&
                board[r + 1][c + 1] == '.') {
            return true;
        }
        if(r + 1 <= 7 && c - 1 >= 0 &&
                board[r + 1][c - 1] == '.') {
            return true;
        }
        if(cancapture(r,c)) {
            return true;
        }
    }
    if(piece == 'o') {
        if(r - 1 >= 0 && c + 1 <= 7 &&
                board[r - 1][c + 1] == '.') {
            return true;
        }
        if(r - 1 >= 0 && c - 1 >= 0 &&
                board[r - 1][c - 1] == '.') {
            return true;
        }
        if(cancapture(r,c)) {
            return true;
        }
    }
    if(piece == 'X') {
        if(r + 1 <= 7 && c + 1 <= 7 &&
                board[r + 1][c + 1] == '.') {
            return true;
        }
        if(r + 1 <= 7 && c - 1 >= 0 &&
                board[r + 1][c - 1] == '.') {
            return true;
        }
        if(r - 1 >= 0 && c + 1 <= 7 &&
                board[r - 1][c + 1] == '.') {
            return true;
        }
        if(r - 1 >= 0 && c - 1 >= 0 &&
                board[r - 1][c - 1] == '.') {
            return true;
        }
        if(cancapture(r,c)) {
            return true;
        }
    }
    if(piece == 'O') {
        if(r + 1 <= 7 && c + 1 <= 7 &&
                board[r + 1][c + 1] == '.') {
            return true;
        }
        if(r + 1 <= 7 && c - 1 >= 0 &&
                board[r + 1][c - 1] == '.') {
            return true;
        }
        if(r - 1 >= 0 && c + 1 <= 7 &&
                board[r - 1][c + 1] == '.') {
            return true;
        }
        if(r - 1 >= 0 && c - 1 >= 0 &&
                board[r - 1][c - 1] == '.') {
            return true;
        }
        if(cancapture(r,c)) {
            return true;
        }
    }
    return false;
}//canmove
bool checkwin() {
    int xcount = 0;
    int ocount = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] == 'x' || board[i][j] == 'X') {
                xcount++;
            }
            if(board[i][j] == 'o' || board[i][j] == 'O') {
                ocount++;
            }
        }
    }
    if(xcount == 0) {
        cout << "'o' wins " << endl;
        return true;
    }
    if(ocount == 0) {
        cout << " 'x' wins " << endl;
        return true;
    }
    return false;
}//checkwin
void initialdisplay() {
    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if((i + j)% 2 != 0) {
                if(i < 3)
                    board[i][j] = 'x';
                else if(i > 4)
                    board[i][j] = 'o';
                else
                    board[i][j] = '.';
            }
            else {
                board[i][j] = '.';
            }
        }
    }
}//initialdisplay
void displayboard() {
    cout << "turn : " << turn << endl;
    cout << "  ";
    for(int j = 0; j < 8; j++) {
        cout << j << " ";
    }
    cout << endl;
    for(int i = 0; i < 8; i++) {
        cout << i << " ";
        for(int j = 0; j < 8; j++) {
            cout << board[i][j];
            if(j != 7) {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}//displayboard
bool selectpiece() {
    cout << "enter row and column " << endl;
    cin >> row >> col;
    if(row < 0 || row > 7 || col < 0 || col > 7) {
        cout << "wrong position " << endl;
        return false;
    }
    if(board[row][col] == '.') {
        cout << "not a real piece here try another " << endl;
        return false;
    }
    if(turn == 'x' && board[row][col] != 'x' &&
            board[row][col] != 'X') {
        cout << "not your turn " << endl;
        return false;
    }
    if(turn == 'o' && board[row][col] != 'o' &&
            board[row][col] != 'O') {
        cout << "not your turn " << endl;
        return false;
    }
    cout << "you selected : " << board[row][col] << endl;
    return true;
}//selectpiece
void king() {
    if(board[newrow][newcol] == 'x' && newrow == 7) {
        board[newrow][newcol] = 'X';
        cout << "x promoted " << endl;
    }
    if(board[newrow][newcol] == 'o' && newrow == 0) {
        board[newrow][newcol] = 'O';
        cout << "o promoted " << endl;
    }
}//king
bool capture(int rowdiff, int coldiff) {
    int midrow = (row + newrow) / 2;
    int midcol = (col + newcol) / 2;
    if(rowdiff == 2 && coldiff == 2) {
        if((board[row][col] == 'x' ||
                board[row][col] == 'X') &&
                board[midrow][midcol] != 'o' &&
                board[midrow][midcol] != 'O') {
            cout << "no enemy to kill " << endl;
            return false;
        }
        if((board[row][col] == 'o' ||
                board[row][col] == 'O') &&
                board[midrow][midcol] != 'x' &&
                board[midrow][midcol] != 'X') {
            cout << "no enemy to kill " << endl;
            return false;
        }
        board[newrow][newcol] = board [row][col];
        board[row][col] = '.';
        board[midrow][midcol] = '.';
        row = newrow;
        col = newcol;
        return true;
    }
    return false;
}//capture
bool cancapture(int r, int c) {
    char piece = board[r][c];
    if (piece == 'x') {
        if(r + 2 <= 7 && c + 2 <= 7) {
            if((board[r + 1][c + 1] == 'o' ||
                    board[r + 1][c + 1] == 'O') &&
                    board[r + 2][c + 2] == '.') {
                return true;
            }
        }
        if(r + 2 <= 7 && c - 2 >= 0) {
            if((board[r + 1][c - 1] == 'o' ||
                    board[r + 1][c - 1] == 'O') &&
                    board[r + 2][c - 2] == '.') {
                return true;
            }
        }
    }
    if(piece == 'o') {
        if(r - 2 >= 0 && c + 2 <= 7) {
            if((board[r - 1][c + 1] == 'x' ||
                    board[r - 1][c + 1] == 'X') &&
                    board[r - 2][c + 2] == '.') {
                return true;
            }
        }
        if(r - 2 >= 0 && c - 2 >= 0) {
            if((board[r - 1][c - 1] == 'x' ||
                    board[r - 1][c - 1] == 'X') &&
                    board[r - 2][c - 2] == '.') {
                return true;
            }
        }
    }
    if(piece == 'X') {
        if(r + 2 <= 7 && c + 2 <= 7) {
            if((board[r + 1][c + 1] == 'o' ||
                    board[r + 1][c + 1] == 'O') &&
                    board[r + 2][c + 2] == '.') {
                return true;
            }
        }
        if(r + 2 <= 7 && c - 2 >= 0) {
            if((board[r + 1][c - 1] == 'o' ||
                    board[r + 1][c - 1] == 'O') &&
                    board[r + 2][c - 2] == '.') {
                return true;
            }
        }
        if(r - 2 >= 0 && c + 2 <= 7) {
            if((board[r - 1][c + 1] == 'o' ||
                    board[r - 1][c + 1] == 'O') &&
                    board[r - 2][c + 2] == '.') {
                return true;
            }
        }
        if(r - 2 >= 0 && c - 2 >= 0) {
            if((board[r - 1][c - 1] == 'o' ||
                    board[r - 1][c - 1] == 'O') &&
                    board[r - 2][c - 2] == '.') {
                return true;
            }
        }
    }
    if(piece == 'O') {
        if(r + 2 <= 7 && c + 2 <= 7) {
            if((board[r + 1][c + 1] == 'x' ||
                    board[r + 1][c + 1] == 'X') &&
                    board[r + 2][c + 2] == '.') {
                return true;
            }
        }
        if(r + 2 <= 7 && c - 2 >= 0) {
            if((board[r + 1][c - 1] == 'x' ||
                    board[r + 1][c - 1] == 'X') &&
                    board[r + 2][c - 2] == '.') {
                return true;
            }
        }
        if(r - 2 >= 0 && c + 2 <= 7) {
            if((board[r - 1][c + 1] == 'x' ||
                    board[r - 1][c + 1] == 'X') &&
                    board[r - 2][c + 2] == '.') {
                return true;
            }
        }
        if(r - 2 >= 0 && c - 2 >= 0) {
            if((board[r - 1][c - 1] == 'x' ||
                    board[r - 1][c - 1] == 'X') &&
                    board[r - 2][c - 2] == '.') {
                return true;
            }
        }
    }
    return false;
}//cancapture
bool legalmove() {
    if(newrow < 0 || newrow > 7 || newcol < 0 || newcol > 7) {
        cout << "wrong position " << endl;
        return false;
    }
    int rowdiff = abs (newrow - row);
    int coldiff = abs (newcol - col);
    if(!((rowdiff == 1 && coldiff == 1) ||
            (coldiff == 2 && rowdiff == 2))) {
        cout << "invalid move try again " << endl;
        return false;
    }
    if(board[newrow][newcol] != '.') {
        cout << "space already occupied " << endl;
        return false;
    }
    if((newrow + newcol) % 2  == 0) {
        cout << "wrong square get back in " << endl;
        return false;
    }
    if(board[row][col] == 'x' && newrow <= row) {
        cout << "'x' moves down" << endl;
        return false;
    }
    if(board[row][col] == 'o' && newrow >= row) {
        cout << "'o' moves up" << endl;
        return false;
    }
    cout << "you selected :  " << newrow << " " << newcol << endl;
    return true;
}//legalmove
void movement() {
    cout << "enter row and column " << endl;
    cin >> newrow >> newcol;
    int rowdiff = abs (newrow - row);
    int coldiff = abs (newcol - col);
    if(!legalmove()) {
        return;
    }
    if(rowdiff == 2 && coldiff == 2) {
        if(!(capture(rowdiff, coldiff))) {
            return;
        }
        while(cancapture(row,col)) {
            displayboard();
            cout << "capture available " << endl;
            cout << "enter new position : " << endl;
            cin >> newrow >> newcol;
            rowdiff = abs(newrow - row);
            coldiff = abs(newcol - col);
            if(!legalmove()) {
                return;
            }
            rowdiff = abs(newrow - row);
            coldiff = abs(newcol - col);
            if(rowdiff != 2 || coldiff != 2) {
                cout << "you must capture again " << endl;
                return;
            }
            if(!(capture(rowdiff, coldiff))) {
                return;
            }
        }
    }
    if(rowdiff == 1 && coldiff == 1) {
        board[newrow][newcol] = board [row][col];
        board[row][col] = '.';
    }
    if(turn == 'x') {
        turn = 'o';
    } else {
        turn = 'x';
    }
    king();
}//movement
bool stalemate() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(turn == 'x' && (board[i][j] == 'x' ||
                               board[i][j] == 'X')) {
                if(canmove(i,j)) {
                    return false;
                }
            }
            if(turn == 'o' && (board[i][j] == 'o' ||
                               board[i][j] == 'O')) {
                if(canmove(i,j)) {
                    return false;
                }
            }
        }
    }
    cout << "STALEMATE \n no legal moves remaining " << endl;
    return true;
}//stalemate
void findmoves() {

    movecount = 0;
    Move capturemoves[100];
    int capturecount = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] == 'o' || board[i][j] == 'O') {
                int dr[4] = {-1,-1,1,1};
                int dc[4] = {-1,1,-1,1};
                for(int k = 0; k < 4; k++) {
                    row = i;
                    col = j;
                    // NORMAL MOVE
                    newrow = i + dr[k];
                    newcol = j + dc[k];
                    if(newrow >= 0 && newrow <= 7 &&
                       newcol >= 0 && newcol <= 7) {
                        int rowdiff = abs(newrow - row);
                        int coldiff = abs(newcol - col);
                        if(board[newrow][newcol] == '.') {
                            if(rowdiff == 1 && coldiff == 1) {
                               if((board[i][j] == 'o' && newrow < row)
                                   || board[i][j] == 'O') {
                                    moves[movecount].fromrow = i;
                                    moves[movecount].fromcol = j;
                                    moves[movecount].torow = newrow;
                                    moves[movecount].tocol = newcol;
                                    movecount++;
                                }
                            }
                        }
                    } // CAPTURE MOVE
                    newrow = i + dr[k] * 2;
                    newcol = j + dc[k] * 2;
                    if(newrow >= 0 && newrow <= 7 &&
                       newcol >= 0 && newcol <= 7) {
                        int rowdiff = abs(newrow - row);
                       int coldiff = abs(newcol - col);
                        if(board[newrow][newcol] == '.') {
                            if(rowdiff == 2 && coldiff == 2) {
                                int midrow = (row + newrow) / 2;
                                int midcol = (col + newcol) / 2;
                                if(board[midrow][midcol] == 'x' ||
                                   board[midrow][midcol] == 'X') {
                                    if((board[i][j] == 'o' && newrow < row)
                                       || board[i][j] == 'O') {
                                        capturemoves[capturecount].fromrow = i;
                                        capturemoves[capturecount].fromcol = j;
                                        capturemoves[capturecount].torow = newrow;
                                        capturemoves[capturecount].tocol = newcol;
                                        capturecount++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(capturecount > 0){
    movecount = capturecount;
    for(int i = 0; i < capturecount; i++){
    moves[i] = capturemoves[i];
    }
    }
}//findmoves
void aimove(){
findmoves();
if(movecount == 0){
return;
}
int r = rand() % movecount;
row = moves[r].fromrow;
col = moves[r].fromcol;
newrow = moves[r].torow;
newcol = moves[r].tocol;
board[newrow][newcol] = board[row][col];
board[row][col] = '.';
int rowdiff = abs(newrow - row);
int coldiff = abs(newcol - col);
if(rowdiff == 2 && coldiff == 2){
int midrow = (row + newrow) / 2;
int midcol = (col + newcol) / 2;
board[midrow][midcol] = '.';
row = newrow;
col = newcol;
while(cancapture(row,col)){
bool found = false;
int dr[4] = {-2,-2,2,2};
int dc[4] = {-2,2,-2,2};
for(int k = 0; k < 4 && !found;k++){
int tr = row + dr[k];
int tc = col + dc[k];
if(tr < 0 || tr > 7 || tc < 0 || tc > 7)
continue;
int midrow = (row + tr) / 2;
int midcol = (col + tc) / 2;
if(board[tr][tc] == '.'){
if(board[row][col] == 'o' || board[row][col] == 'O'){
if(board[midrow][midcol] == 'x' || board[midrow][midcol] == 'X'){
board[tr][tc] = board[row][col];
board[row][col] = '.';
board[midrow][midcol] = '.';
row = tr;
col = tc;
found = true;
}
}
}
}
}
}
king();
turn = 'x';
}//aimove
int main()
{
    initialdisplay();
    srand(time(0));
    while(true) {
        displayboard();
        findmoves();
        cout << "moves found: " << movecount << endl;

        for(int i = 0; i < movecount; i++) {

            cout << moves[i].fromrow << " "
                 << moves[i].fromcol << " -> "
                 << moves[i].torow << " "
                 << moves[i].tocol << endl;

        }
        if(turn == 'o'){
        aimove();
        }
        else{
        if(selectpiece()){
        movement();
        }
        }
        if(checkwin()) {
            break;
        }
        if(stalemate()) {
            break;
        }
    }
    return 0;
}//main