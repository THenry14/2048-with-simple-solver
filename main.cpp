/*

Wojciech Szymczyk

Implementation of 2048 game and its solver

*/

#include "class2048.h"
#include <time.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <algorithm>																

using namespace std;									
  
int main( int argc, char* argv[] )						
{
    srand( static_cast<uint>( time( NULL ) ) );			
    game2048 g; g.start();								
    return system( "pause" );							
}
