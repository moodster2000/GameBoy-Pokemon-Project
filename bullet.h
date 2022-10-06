#define PLAYERBULLETCOUNT 5
#define ENEMYBULLETCOUNT 10

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} PositionofBullet;


// Struct for player bullets
typedef struct
{
    int active;

    int row;
    int col;
    int rdel;
    int cdel;
    int height;
    int width;

    PositionofBullet pos;

} PBULLET;

//
// Struct for enemy bullets, not sure if i can combine top one
typedef struct
{
    int active;

    int row;
    int col;
    int rdel;
    int cdel;
    int height;
    int width;

    PositionofBullet pos;

} EBULLET;

extern PBULLET playerBullets[PLAYERBULLETCOUNT];
extern EBULLET enemyBullets[ENEMYBULLETCOUNT];

void initPlayerBullets();
void firePlayerBullet();
void drawPlayerBullets();
void updatePlayerBullets();


void initEnemyBullets();
void fireEnemyBullet();
void drawEnemyBullets();
void updateEnemyBullets();