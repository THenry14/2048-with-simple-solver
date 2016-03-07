#include "class2048.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>

typedef unsigned int uint;
using namespace std;

void clearScreen() {
#ifdef _WIN32
  system("cls");
#endif

#ifdef __unix__
  system("clear");
#endif
}


	tile::tile() {
		value = 0;
		blocked = false;
	}

    game2048::game2048() {
    	done = false;
    	moved = true;
    	score = 0;
    	userPlaying = true;
	}

    tile board[4][4];

    void game2048::start(){
    win = 1;
	addTile();
	while(win == 1){
	    if(moved) addTile();
	    drawBoard();
	    if(done) break;
	    if(userPlaying) {waitKey(); checkResult();}
	    else { aiSolver(); checkResult(); }

	}
	string s;
		if(win == 2) {s = "You've made it!";}
		else {s = "Game Over!";}

	drawBoard();
	cout << s << endl << endl;
    }

	char game2048::getinput(){
    	if (_kbhit()){
       		_getch();
        	return _getch();				//this method ensures that after pressing a key an action is taken without need to press enter
    	}
    return 0;
	};

    void game2048::drawBoard(){
       clearScreen();
	cout << "SCORE: " << score << endl << endl;
	for(int y = 0; y < 4; y++){
	    cout << "+------+------+------+------+" << endl << "| ";
	    for( int x = 0; x < 4; x++ ){
		if( !board[x][y].value ) cout << setw( 4 ) << " ";
		else cout << setw( 4 ) << board[x][y].value;
		cout << " | ";
	    }
	    cout << endl;
	}
	cout << "+------+------+------+------+" << endl << endl;
    }

    void game2048::aiSolver(){
		int scoreUp, scoreDown, scoreRight, scoreLeft, maxScore;
		moved = false;
		cout << "Solving... ";
		for(int i=0; i<10; i++){
		move(UP);
		scoreUp+=score;
		move(DOWN);
		scoreDown+=score;
		move(LEFT);
		scoreLeft+=score;
		move(RIGHT);
		scoreRight+=score;}
		maxScore = max(scoreUp, max(scoreDown, max(scoreRight, scoreLeft)));

			if(maxScore==scoreUp){
				move(UP);
			}
			else if(maxScore==scoreDown){
				move(DOWN);
			}
			else if(maxScore==scoreRight){
				move(RIGHT);
			}
			else{
				move(LEFT);
			}

		for( int y = 0; y < 4; y++ )
	    	for( int x = 0; x < 4; x++ )
			board[x][y].blocked = false;
		_sleep(50);											// The solver is a kind of 'brute force'. It's no pretty, but pretty effective.
		}

	void game2048::checkResult(){
		for( int y = 0; y < 4; y++ ){
	    	for( int x = 0; x < 4; x++ ){
			if(board[x][y].value == 2048){
				win = 2;
			}
			}
		}
	}

    void game2048::waitKey(){
	moved = false;
	cout << "(W)Up (S)Down (A)Left (D)Right (P)AI Solver \n\n";
	getinput();
	switch(_getch()){
	    case 'w': move( UP );break;
	    case 'a': move( LEFT ); break;
	    case 's': move( DOWN ); break;
	    case 'd': move( RIGHT ); break;
	    case 'p': userPlaying = false;
	}
	for( int y = 0; y < 4; y++ )
	    for( int x = 0; x < 4; x++ )
		board[x][y].blocked = false;

    };

    void game2048::addTile(){
	for( int y = 0; y < 4; y++ )
	    for( int x = 0; x < 4; x++ )
		if( !board[x][y].value ){
		    uint a, b;
		    do
		    { a = rand() % 4; b = rand() % 4; }
		    while( board[a][b].value );

		    int s = rand() % 100;
		    if( s > 89 ) board[a][b].value = 4;
		    else board[a][b].value = 2;
		    if(canMove()) return;
		}
	done = true;
    }


    bool game2048::canMove(){
	for( int y = 0; y < 4; y++ )
	    for( int x = 0; x < 4; x++ )
		if( !board[x][y].value ) return true;

	for( int y = 0; y < 4; y++ )
	    for( int x = 0; x < 4; x++ )
	    {
		if( testAdd( x + 1, y, board[x][y].value ) ) return true;
		if( testAdd( x - 1, y, board[x][y].value ) ) return true;
		if( testAdd( x, y + 1, board[x][y].value ) ) return true;
		if( testAdd( x, y - 1, board[x][y].value ) ) return true;
	    }
	return false;
    }


    bool game2048::testAdd( int x, int y, uint v ){
	if( x < 0 || x > 3 || y < 0 || y > 3 ) return false;
	return board[x][y].value == v;
    }


    void game2048::moveVert( int x, int y, int d ){
	if( board[x][y + d].value && board[x][y + d].value == board[x][y].value && !board[x][y].blocked && !board[x][y + d].blocked  ){
	    board[x][y].value = 0;
	    board[x][y + d].value *= 2;
	    score += board[x][y + d].value;
	    board[x][y + d].blocked = true;
	    moved = true;
	}
	else if( !board[x][y + d].value && board[x][y].value ){
	    board[x][y + d].value = board[x][y].value;
	    board[x][y].value = 0;
	    moved = true;
	}
	if( d > 0 ) { if( y + d < 3 ) moveVert( x, y + d,  1 ); }
	else { if( y + d > 0 ) moveVert( x, y + d, -1 ); }
    }


    void game2048::moveHori( int x, int y, int d ){
	if( board[x + d][y].value && board[x + d][y].value == board[x][y].value && !board[x][y].blocked && !board[x + d][y].blocked  ){
	    board[x][y].value = 0;
	    board[x + d][y].value *= 2;
	    score += board[x + d][y].value;
	    board[x + d][y].blocked = true;
	    moved = true;
	}
	else if( !board[x + d][y].value && board[x][y].value ){
	    board[x + d][y].value = board[x][y].value;
	    board[x][y].value = 0;
	    moved = true;
	}
	if( d > 0 ) { if( x + d < 3 ) moveHori( x + d, y,  1 ); }
	else { if( x + d > 0 ) moveHori( x + d, y, -1 ); }
    }


    void game2048::move( movementDirection d ){
	switch( d ){
	    case UP:
	    	for( int x = 0; x < 4; x++ ){
		    int y = 1;
		    while( y < 4 ){
				if( board[x][y].value ) moveVert( x, y, -1 ); y++;
				}
		}
		break;

		case DOWN:
		for( int x = 0; x < 4; x++ ){
		    int y = 2;
		    while( y >= 0 ){
				if( board[x][y].value ) moveVert( x, y, 1 ); y--;
				}
		}
		break;

	    case LEFT:
		for( int y = 0; y < 4; y++ ){
		    int x = 1;
		    while( x < 4 ){
				if( board[x][y].value ) moveHori( x, y, -1 ); x++;
				}
		}
		break;

	    case RIGHT:
		for( int y = 0; y < 4; y++ ){
		    int x = 2;
		    while( x >= 0 ){
				if( board[x][y].value ) moveHori( x, y, 1 ); x--;
				}
		}
	}

    }

