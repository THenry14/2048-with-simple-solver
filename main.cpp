/*

Wojciech Szymczyk

Implementation of 2048 game and its solver

*/

#include "class2048.h"
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef __unix__
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

int main( int argc, char* argv[] )
{
#ifdef __unix__
    static struct termios oldt, newt;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

    newt.c_lflag &= ~(ICANON);

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif

    srand( static_cast<uint>( time( NULL ) ) );
    game2048 g; g.start();

    // Wait for user input to see how game ends. Useful on Windows.
    char c;
    cin >> c;

    return EXIT_SUCCESS;
}
