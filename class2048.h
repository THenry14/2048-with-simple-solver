
enum movementDirection { UP, DOWN, LEFT, RIGHT };
typedef unsigned int uint;

class tile
{
public:
    tile();
    uint value;
    bool blocked;
};

class game2048
{
public:

    game2048();
    bool done, moved, userPlaying;
    uint score, win;
    void start();

private:

	char getinput();
    void drawBoard();
    void aiSolver();
	void checkResult();
    void waitKey();
    void addTile();
    bool canMove();
    bool testAdd( int x, int y, uint v );
    void moveVert( int x, int y, int d );
    void moveHori( int x, int y, int d );
    void move( movementDirection d );
};

