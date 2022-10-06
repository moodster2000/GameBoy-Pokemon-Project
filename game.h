#define ENEMYCOUNT 3


typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int rdel;
    int cdel;
    int width;
    int height;

    //powerBall Stuff
    int direction;
    int powerballTimer;
    int activeMoves;

    //animation stuff to not be used right now
    int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;

    Position pos;

    int health;
    int cheat;
    int hide;
    int jumping;
    int active;

    int cheatTime;
} PLAYER;

typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int rdel;
    int cdel;
    int width;
    int height;
    int movingDirection;
    //powerBall Stuff
    int direction;
    int powerballTimer;

    //animation stuff to not be used right now
    int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;

    Position pos;

    int health;
    int cheat;
    int hide;
    int jumping;
    int active;
} ENEMY;


typedef struct {
    int screenRow;
    int screenCol;
    int worldRow;
    int worldCol;
    int rdel;
    int cdel;
    int width;
    int height;

    //animation stuff to not be used right now
    int aniCounter;
    int aniState;
    int prevAniState;
    int curFrame;
    int numFrames;

    Position pos;
    int active;
} ITEM;



extern int hOff;
extern int vOff;
extern OBJ_ATTR shadowOAM[128];
extern PLAYER player;
extern ENEMY enemies[ENEMYCOUNT];

extern ITEM food;
extern ITEM goal;
extern ITEM platform;

extern int level;
extern int health;
extern int time_s;

// Prototypes
void initGame();
void continueToNextLevel();
void updateGame();
void drawGame();

// player prototype
void initPlayer();
void drawPlayer();
void updatePlayer();



// changes based on level enemy prototype
void initEnemy();
void updateEnemy();
void drawEnemy();


// Flag Pole or Target changes based on level
void initItem();
void drawItem();


// Flag Pole or Target
void initGoal();
void updateGoal();
void drawGoal();

//game status
void drawGameStatus();


//interrupts
void setupInterrupts();
void interruptHandler();
void displayTime();