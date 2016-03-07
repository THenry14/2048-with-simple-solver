/*

Wojciech Szymczyk

Implementation of 2048 game and its solver

*/

#include "class2048.h"
#include <iomanip>
#include <algorithm>

using namespace std;

int main( int argc, char* argv[] )
{
    srand( static_cast<uint>( time( NULL ) ) );
    game2048 g; g.start();
    return EXIT_SUCCESS;
}
