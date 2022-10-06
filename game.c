#include <stdlib.h>
#include "mode0.h"
#include "game.h"
#include "bullet.h"
#include "hitSound.h"
#include "sound.h"

int hOff;
int vOff;
int level;
int health;
int time_s;

OBJ_ATTR shadowOAM[128];
PLAYER player;
ITEM food;
ITEM goal;
ITEM platform;

ENEMY enemies[ENEMYCOUNT];
// Initialize level 1
void initGame()
{
    vOff = 0;
    hOff = 0;
    level = 1;
    health = 3;
    time_s = 90;
    initPlayer();
    initEnemy();

    initPlayerBullets();
    initEnemyBullets();

    initItem();
}

void continueToNextLevel()
{
    vOff = 0;
    hOff = 0;
    time_s = 90;
    if (health < 3)
    {
        health = health + 1;
    }
    player.activeMoves = 0;
    initPlayer();
    initEnemy();

    initPlayerBullets();
    initEnemyBullets();

    initItem();
}

// Updates the game each frame
void updateGame()
{
    updatePlayer();
    updateEnemy();
    updatePlayerBullets();
    updateEnemyBullets();

    if (level > 1)
    {
        if (food.screenCol - hOff < 0)
        {
            food.active = 0;
        }
        else if ((food.screenCol - hOff) >= 0 && !player.activeMoves)
        {
            food.active = 1;
        }
    }
    if (level > 2)
    {
        if (platform.screenCol - hOff < 0)
        {
            platform.active = 0;
        }
        else if ((platform.screenCol - hOff) >= 0)
        {
            platform.active = 1;
        }
    }

    REG_BG0HOFF = hOff;
    if (hOff % 4 == 0)
    {
        REG_BG1HOFF = hOff;
    }
}

// Draws the game each frame
void drawGame()
{
    drawPlayer();
    drawPlayerBullets();

    drawEnemy();
    drawEnemyBullets();

    drawItems();
    drawGameStatus();
}

void initPlayer()
{

    player.width = 16;
    player.height = 16;
    player.rdel = 1;
    player.cdel = 1;

    player.prevAniState = 0;
    player.aniCounter = 0;
    player.curFrame = 0;
    player.numFrames = 3;
    player.aniState = 0;
    player.pos.x = 10;
    player.pos.y = 112;
    player.active = 1;
    player.pos.dx = 0;
    player.health = 3;
    player.hide = 0;
    player.jumping = 0;
    player.direction = 1;
    player.powerballTimer = 20;
    player.activeMoves = 0;
    player.cheatTime = 0;
}
void initEnemy()
{
    for (int i = 0; i < ENEMYCOUNT; i++)
    {
        enemies[i].width = 16;
        enemies[i].height = 16;
        enemies[i].rdel = 1;
        enemies[i].cdel = 1;
        enemies[i].screenRow = 112;
        enemies[i].screenCol = 100;

        enemies[i].prevAniState = 0;
        enemies[i].aniCounter = 0;
        enemies[i].curFrame = 0;
        enemies[i].numFrames = 4;
        enemies[i].aniState = 0;
        enemies[i].pos.x = 0;
        enemies[i].pos.y = 0;
        enemies[i].active = 0;
        enemies[i].pos.dx = 0;
        enemies[i].health = 1;
        enemies[i].hide = 0;
        enemies[i].jumping = 0;
        enemies[i].direction = 1;
        enemies[i].powerballTimer = 0;
    }
    if (level == 1)
    {
        // enemy 1
        enemies[0].active = 1;
        enemies[0].screenRow = 112;
        enemies[0].screenCol = 50;
        enemies[0].pos.y = 112;
        enemies[0].pos.x = 50;

        // enemy 2
        enemies[1].active = 1;
        enemies[1].screenRow = 112;
        enemies[1].screenCol = 160;
        enemies[1].pos.y = 112;
        enemies[1].pos.x = 160;
    }
    else if (level == 2)
    {
        // enemy 1
        enemies[0].active = 1;
        enemies[0].screenRow = 112;
        enemies[0].screenCol = 50;
        enemies[0].pos.y = 112;
        enemies[0].pos.x = 50;

        // enemy 2
        enemies[1].active = 1;
        enemies[1].screenRow = 105;
        enemies[1].screenCol = 180;
        enemies[1].pos.y = 105;
        enemies[1].pos.x = 180;
    }
    else if (level == 3)
    {
        // enemy 1
        enemies[0].active = 1;
        enemies[0].screenRow = 112;
        enemies[0].screenCol = 180;
        enemies[0].pos.y = 112;
        enemies[0].pos.x = 180;

        // enemy 2
        enemies[1].active = 1;
        enemies[1].screenRow = 105;
        enemies[1].screenCol = 50;
        enemies[1].pos.y = 105;
        enemies[1].pos.x = 50;

        // enemy 3
        enemies[2].active = 1;
        enemies[2].screenRow = 112;
        enemies[2].screenCol = 230 - hOff;
        enemies[2].pos.y = 112;
        enemies[2].pos.x = 230 - hOff;
    }
}

void initItem()
{
    if (level == 1)
    {
        goal.width = 16;
        goal.height = 32;
        goal.screenRow = 96;
        goal.screenCol = 225;
        goal.active = 1;

      

        food.width = 8;
        food.height = 8;
        food.pos.x = 40;
        food.pos.y = 40;
        food.screenCol = 50;
        food.screenRow = 112;
        food.active = 0;

        platform.width = 0;
        platform.height = 0;
        platform.screenRow = 0;
        platform.screenCol = 0;
        platform.active = 0;
    }
    else if (level == 2)
    {
        goal.width = 16;
        goal.height = 32;
        goal.screenRow = 96;
        goal.screenCol = 260;
        goal.active = 1;

      

        food.width = 8;
        food.height = 8;
        food.screenRow = 112;
        food.screenCol = 115;
        food.active = 1;

        platform.width = 0;
        platform.height = 0;
        platform.screenRow = 0;
        platform.screenCol = 0;
        platform.active = 0;
    }
    else if (level == 3)
    {
        goal.width = 16;
        goal.height = 32;
        goal.screenRow = 96;
        goal.screenCol = 330;
        goal.active = 1;

        food.width = 8;
        food.height = 8;
        food.screenRow = 76;
        food.screenCol = 135;
        food.active = 1;

        platform.width = 32;
        platform.height = 16;
        platform.screenRow = 88;
        platform.screenCol = 130;
        platform.active = 1;
    }
}

void updatePlayer()
{
    if (player.pos.y > 112)
    {
        player.pos.y = 112;
    }
    if (BUTTON_HELD(BUTTON_LEFT))
    {
        if (player.pos.x + hOff > 0)
        {
            player.pos.x -= player.cdel;
            hOff--;
        }
        player.direction = 0;
    }
    else if (BUTTON_HELD(BUTTON_RIGHT))
    {
        hOff++;
        if (player.pos.x < 224)
        {
            player.pos.x += player.cdel;
        }
        player.direction = 1;
    }
    else if (BUTTON_PRESSED(BUTTON_L))
    {
        hOff++;
        player.pos.x += 40;
        player.direction = 1;
        player.cheatTime = 500; //ACTIVE FOR ONLY 8 SECONDS
    }
    else
    {
        player.pos.dx = 0;
        player.pos.dy = 0;
        player.direction = 1;
    }

    if (player.cheatTime > 0)
    {
        player.cheatTime--;
    }

    if (player.jumping < 1)
    {
        // jump
        if (BUTTON_PRESSED(BUTTON_A))
        {
            player.jumping = 99;
        }
    }
    else if (player.jumping >= 1)
    {
        if (player.jumping > 50)
        {
            player.pos.y -= player.rdel;
            // player.pos.x += player.cdel;
        }
        else if (player.pos.y != 74 || player.jumping < 50 && collision(player.pos.y, player.pos.x, player.height,
                                                  player.width, platform.screenRow, (platform.screenCol - hOff), platform.height, platform.width) == 0)
        {
            player.pos.y += player.rdel;
            // player.pos.x += player.cdel;
        }
        if (player.pos.y != 74 || collision(player.pos.y, player.pos.x, player.height,
                      player.width, platform.screenRow, (platform.screenCol - hOff), platform.height, platform.width) == 0)
        {
            player.jumping = player.jumping - 1;
        }
        if (player.pos.y != 74 && collision(player.pos.y, player.pos.x, player.height,
                                            player.width, platform.screenRow, (platform.screenCol - hOff), platform.height, platform.width))
        {
            player.pos.y += player.rdel;
        }
    }
    if (platform.active && collision(player.pos.y, player.pos.x, player.height,
                                     player.width, platform.screenRow, (platform.screenCol - hOff), platform.height, platform.width))
    {
        player.jumping = 49;
    }
    // shoot bullet
    if (BUTTON_PRESSED(BUTTON_B) && player.powerballTimer >= 20 && player.activeMoves)
    {
        firePlayerBullet();
        playSoundB(hitSound_data, hitSound_length, 0);
        player.powerballTimer = 0;
    }
    player.powerballTimer++;

    update_pos(&player.pos);
    player.screenRow = player.pos.y;
    player.screenCol = player.pos.x;
    animatePlayer();

    // COLLISSIONS with enemies
    for (int k = 0; k < ENEMYCOUNT; k++)
    {
        if (player.cheatTime < 1  && enemies[k].active == 1 && collision(player.screenRow, player.screenCol, player.height, player.width, enemies[k].screenRow, enemies[k].screenCol, enemies[k].height, enemies[k].width))
        {
            playSoundB(hitSound_data, hitSound_length, 0);
            health--;
            player.pos.x = 10;
            player.pos.y = 112;
            hOff = 0;
        }
    }
    // collision with item to get new shooting move
    if (food.active && collision(player.screenRow, player.screenCol, player.height,
                                 player.width, food.screenRow, (food.screenCol - hOff), food.height, food.width))
    {
        player.activeMoves = 1;
        food.active = 0;
    }

    // collision with item to get new goal to win game.
    if (goal.active && collision(player.screenRow, player.screenCol, player.height,
                                 player.width, goal.screenRow, (goal.screenCol - hOff), goal.height, goal.width))
    {
        level++;
        goal.active = 0;
    }
}
enum
{
    RIGHTSIDE,
    LEFTSIDE,
    GHOST
};
void animatePlayer()
{
    player.prevAniState = player.aniState;
    // Change the animation frame every 15 frames of gameplay
    if (player.aniCounter % 15 == 0)
    {
        if (player.curFrame == 2)
        {
            player.curFrame = 0;
        }
        else
        {
            player.curFrame = (player.curFrame + 1);
        }
    }

    if (player.cheatTime > 0)
    {
        player.aniState = GHOST;
        player.curFrame = 0;
    } else if (BUTTON_HELD(BUTTON_LEFT))
    {
        player.aniState = LEFTSIDE;
    }
    else if (BUTTON_HELD(BUTTON_RIGHT))
    {
        player.aniState = RIGHTSIDE;
    }
    else
    {
        player.aniState = player.prevAniState;
        player.curFrame = 0;
    }
    player.aniCounter++;
}
void updateEnemy()
{
    if (level == 1)
    {
        // enemy 1
        if (enemies[0].pos.x == 50)
        {
            enemies[0].cdel = 1;
        }
        else if (enemies[0].pos.x == 100)
        {
            enemies[0].cdel = -1;
        }
        enemies[0].pos.x += enemies[0].cdel;
        update_pos(&enemies[0].pos);
        enemies[0].screenRow = enemies[0].pos.y;
        enemies[0].screenCol = enemies[0].pos.x - hOff;
        if (enemies[0].screenCol < 0)
        {
            enemies[0].active = 0;
        }
        else if (enemies[0].screenCol >= 0 && enemies[0].health > 0)
        {
            enemies[0].active = 1;
        }

        // enemy 2
        // enemy 1
        if (enemies[1].pos.x == 160)
        {
            enemies[1].cdel = 1;
        }
        else if (enemies[1].pos.x == 200)
        {
            enemies[1].cdel = -1;
        }
        enemies[1].pos.x += enemies[1].cdel;
        update_pos(&enemies[1].pos);
        enemies[1].screenRow = enemies[1].pos.y;
        enemies[1].screenCol = enemies[1].pos.x - hOff;
        if (enemies[1].screenCol < 0)
        {
            enemies[1].active = 0;
        }
        else if (enemies[1].screenCol >= 0 && enemies[1].health > 0)
        {
            enemies[1].active = 1;
        }
    }
    else if (level == 2)
    {
        // enemy 1
        if (enemies[0].pos.x == 50)
        {
            enemies[0].cdel = 1;
        }
        else if (enemies[0].pos.x == 100)
        {
            enemies[0].cdel = -1;
        }
        enemies[0].pos.x += enemies[0].cdel;
        update_pos(&enemies[0].pos);
        enemies[0].screenRow = enemies[0].pos.y;
        enemies[0].screenCol = enemies[0].pos.x - hOff;
        if (enemies[0].screenCol < 0)
        {
            enemies[0].active = 0;
        }
        else if (enemies[0].screenCol >= 0 && enemies[0].health > 0)
        {
            enemies[0].active = 1;
        }

        // enemy 2
        if (enemies[1].pos.x == 180 && enemies[1].pos.y == 105)
        {
            enemies[1].cdel = 1;
            enemies[1].rdel = 0;
        }
        else if (enemies[1].pos.x == 230 && enemies[1].pos.y == 105)
        {
            enemies[1].cdel = 0;
            enemies[1].rdel = -1;
        }
        else if (enemies[1].pos.x == 230 && enemies[1].pos.y == 80)
        {
            enemies[1].cdel = -1;
            enemies[1].rdel = 0;
        }
        else if (enemies[1].pos.x == 180 && enemies[1].pos.y == 80)
        {
            enemies[1].cdel = 0;
            enemies[1].rdel = 1;
        }

        enemies[1].pos.x += enemies[1].cdel;
        enemies[1].pos.y += enemies[1].rdel;
        update_pos(&enemies[1].pos);
        enemies[1].screenRow = enemies[1].pos.y - vOff;
        enemies[1].screenCol = enemies[1].pos.x - hOff;
        if (enemies[1].screenCol < 0)
        {
            enemies[1].active = 0;
        }
        else if (enemies[1].screenCol >= 0 && enemies[1].health > 0)
        {
            enemies[1].active = 1;
        }

        // enemy 3
    }
    else if (level == 3)
    {
        if (enemies[0].pos.x == 112)
        {
            enemies[0].cdel = 1;
        }
        else if (enemies[0].pos.x == 190)
        {
            enemies[0].cdel = -1;
        }

        // standard for all of them!!
        enemies[0].pos.x += enemies[0].cdel;
        update_pos(&enemies[0].pos);
        enemies[0].screenRow = enemies[0].pos.y;
        enemies[0].screenCol = enemies[0].pos.x - hOff;
        if (enemies[0].screenCol < 0)
        {
            enemies[0].active = 0;
        }
        else if (enemies[0].screenCol >= 0 && enemies[0].health > 0)
        {
            enemies[0].active = 1;
        }

        // enemy 2
        if (enemies[1].pos.x == 50 && enemies[1].pos.y == 105)
        {
            enemies[1].cdel = 1;
            enemies[1].rdel = 0;
        }
        else if (enemies[1].pos.x == 90 && enemies[1].pos.y == 105)
        {
            enemies[1].cdel = 0;
            enemies[1].rdel = -1;
        }
        else if (enemies[1].pos.x == 90 && enemies[1].pos.y == 80)
        {
            enemies[1].cdel = -1;
            enemies[1].rdel = 0;
        }
        else if (enemies[1].pos.x == 50 && enemies[1].pos.y == 80)
        {
            enemies[1].cdel = 0;
            enemies[1].rdel = 1;
        }

        // standard for all of them!!
        enemies[1].pos.x += enemies[1].cdel;
        enemies[1].pos.y += enemies[1].rdel;
        update_pos(&enemies[1].pos);
        enemies[1].screenRow = enemies[1].pos.y - vOff;
        enemies[1].screenCol = enemies[1].pos.x - hOff;
        if (enemies[1].screenCol < 0)
        {
            enemies[1].active = 0;
        }
        else if (enemies[1].screenCol >= 0 && enemies[1].health > 0)
        {
            enemies[1].active = 1;
        }

        // enemy 3
        if (enemies[2].pos.x == 230)
        {
            enemies[2].cdel = 1;
        }
        else if (enemies[2].pos.x == 290)
        {
            enemies[2].cdel = -1;
        }

        // standard for all of them!!
        enemies[2].pos.x += enemies[2].cdel;
        update_pos(&enemies[2].pos);
        enemies[2].screenRow = enemies[2].pos.y;
        enemies[2].screenCol = enemies[2].pos.x - hOff;
        if (enemies[2].screenCol < 0)
        {
            enemies[2].active = 0;
        }
        else if (enemies[2].screenCol >= 0 && enemies[2].health > 0)
        {
            enemies[2].active = 1;
        }

        if (enemies[2].powerballTimer == 50 && enemies[2].active)
        {
            fireEnemyBullet();
            enemies[2].powerballTimer = 0;
        }
        enemies[2].powerballTimer++;
    }
    animateEnemy();
}
void animateEnemy()
{
    for (int i = 0; i < ENEMYCOUNT; i++)
    {
        if (enemies[i].active)
        {
            enemies[i].prevAniState = enemies[i].aniState;
            // Change the animation frame every 15 frames of gameplay
            if (enemies[i].aniCounter % 15 == 0)
            {
                if (enemies[i].curFrame == 3)
                {
                    enemies[i].curFrame = 0;
                }
                else
                {
                    enemies[i].curFrame = (enemies[i].curFrame + 1);
                }
            }
            if (enemies[i].cdel < 0)
            {
                enemies[i].aniState = LEFTSIDE;
            }
            else if (enemies[i].cdel > 0)
            {
                enemies[i].aniState = RIGHTSIDE;
            }
            enemies[i].aniCounter++;
        }
    }
}

void drawPlayer()
{

    if (player.hide)
    {
        shadowOAM[0].attr0 |= ATTR0_HIDE;
    }
    else
    {
        shadowOAM[0].attr0 = player.pos.y | ATTR0_SQUARE | ATTR0_4BPP;
        shadowOAM[0].attr1 = player.pos.x | ATTR1_SMALL;
        shadowOAM[0].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(player.curFrame * 2 + player.aniState * 6, 1);
    }
}

void drawEnemy()
{
    if (level == 1)
    {
        for (int i = 0; i < ENEMYCOUNT; i++)
        {

            if (enemies[i].active == 0)
            {
                shadowOAM[i + 1].attr0 |= ATTR0_HIDE;
            }
            else
            {
                shadowOAM[i + 1].attr0 = enemies[i].screenRow | ATTR0_SQUARE | ATTR0_4BPP;
                shadowOAM[i + 1].attr1 = enemies[i].screenCol | ATTR1_SMALL;
                shadowOAM[i + 1].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(enemies[i].curFrame * 2 + enemies[i].aniState * 8, 3);
            }
        }
    }
    else if (level == 2)
    {
        for (int i = 0; i < 2; i++)
        {

            if (enemies[i].active == 0)
            {
                shadowOAM[i + 1].attr0 |= ATTR0_HIDE;
            }
            else
            {
                shadowOAM[i + 1].attr0 = enemies[i].screenRow | ATTR0_SQUARE | ATTR0_4BPP;
                shadowOAM[i + 1].attr1 = enemies[i].screenCol | ATTR1_SMALL;
                shadowOAM[i + 1].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(enemies[i].curFrame * 2 + enemies[i].aniState * 8, 3 + i * 2);
            }
        }
    }
    else if (level == 3)
    {
        for (int i = 0; i < ENEMYCOUNT; i++)
        {

            if (enemies[i].active == 0)
            {
                shadowOAM[i + 1].attr0 |= ATTR0_HIDE;
            }
            else
            {
                shadowOAM[i + 1].attr0 = enemies[i].screenRow | ATTR0_SQUARE | ATTR0_4BPP;
                shadowOAM[i + 1].attr1 = enemies[i].screenCol | ATTR1_SMALL;
                shadowOAM[i + 1].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(enemies[i].curFrame * 2 + enemies[i].aniState * 8, 3 + i * 2);
            }
        }
    }
}

void drawItems()
{
    if (food.active == 0)
    {
        shadowOAM[9].attr0 |= ATTR0_HIDE;
    }
    else
    {
        shadowOAM[9].attr0 = food.screenRow | ATTR0_SQUARE | ATTR0_4BPP;
        shadowOAM[9].attr1 = (food.screenCol - hOff) | ATTR1_TINY;
        shadowOAM[9].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 0);
    }

    if (goal.active == 0)
    {
        shadowOAM[10].attr0 |= ATTR0_HIDE;
    }
    else
    {
        shadowOAM[10].attr0 = goal.screenRow | ATTR0_TALL | ATTR0_4BPP;
        shadowOAM[10].attr1 = (goal.screenCol - hOff) | ATTR1_MEDIUM;
        shadowOAM[10].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 9);
    }

    if (platform.active == 0)
    {
        shadowOAM[15].attr0 |= ATTR0_HIDE;
    }
    else
    {
        shadowOAM[15].attr0 = platform.screenRow | ATTR0_WIDE | ATTR0_4BPP;
        shadowOAM[15].attr1 = (platform.screenCol - hOff) | ATTR1_MEDIUM;
        shadowOAM[15].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 13);
    }
}
void drawGameStatus()
{
    // level heaeder
    shadowOAM[11].attr0 = 140 | ATTR0_WIDE | ATTR0_4BPP;
    shadowOAM[11].attr1 = 20 | ATTR1_MEDIUM;
    shadowOAM[11].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 9);

    // level # heaeder
    shadowOAM[12].attr0 = 140 | ATTR0_TALL | ATTR0_4BPP;
    shadowOAM[12].attr1 = 53 | ATTR1_TINY;
    shadowOAM[12].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(6 + level, 9);

    // //health heaeder
    shadowOAM[13].attr0 = 145 | ATTR0_WIDE | ATTR0_4BPP;
    shadowOAM[13].attr1 = 80 | ATTR1_SMALL;
    shadowOAM[13].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 11);

    // //health # heaeder
    shadowOAM[14].attr0 = 140 | ATTR0_TALL | ATTR0_4BPP;
    shadowOAM[14].attr1 = 115 | ATTR1_TINY;
    shadowOAM[14].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(6 + health, 9);
}
void update_pos(Position *pos)
{
    pos->x += pos->dx;
    if (pos->x < 0)
    {
        pos->x += (SCREENWIDTH << 64);
    }
    else if (pos->x > SCREENWIDTH << 64)
    {
        pos->x -= SCREENWIDTH << 64;
    }

    pos->y += pos->dy;
    if (pos->y < 0)
    {
        pos->y += SCREENHEIGHT << 64;
    }
    else if (pos->y > SCREENHEIGHT << 64)
    {
        pos->y -= SCREENHEIGHT << 64;
    }
}
void displayTime()
{
    int time_s_1s = time_s % 10;
    int time_s_10s = time_s / 10;

    shadowOAM[52].attr0 = 145 | ATTR0_WIDE | ATTR0_4BPP;
    shadowOAM[52].attr1 = 140 | ATTR1_SMALL;
    shadowOAM[52].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(2, 12);

    shadowOAM[53].attr0 = 140 | ATTR0_TALL | ATTR0_4BPP;
    shadowOAM[53].attr1 = 172 | ATTR1_TINY;
    shadowOAM[53].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(6 + time_s_10s, 9);

    shadowOAM[54].attr0 = 140 | ATTR0_TALL | ATTR0_4BPP;
    shadowOAM[54].attr1 = 180 | ATTR1_TINY;
    shadowOAM[54].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(6 + time_s_1s, 9);
}
void interruptHandler(void)
{
    REG_IME = 0;

    if (REG_IF == INT_TM2)
    {
        if (level == 1)
        {
            if (time_s == 30)
            {
                for (int i = 0; i < 15; i++)
                {
                    PALETTE[i] += 221;
                }
            }
        }
        else if (level == 2)
        {
            if (time_s == 30)
            {
                for (int i = 0; i < 15; i++)
                {
                    PALETTE[i] += 90;
                }
            }
        }
        else if (level == 3)
        {
            if (time_s == 30)
            {
                for (int i = 0; i < 15; i++)
                {
                    PALETTE[i] += 20;
                }
            }
        }
        time_s--;
    }
    if (REG_IF & INT_VBLANK)
    {
        displayTime();
        DMANow(3, shadowOAM, OAM, 512);
    }
    if (REG_IF & INT_VBLANK)
    {
        if (soundA.isPlaying)
        {

            soundA.vBlankCount = soundA.vBlankCount + 1;
            if (soundA.vBlankCount > soundA.duration)
            {
                if (soundA.loops)
                {
                    // restart
                    playSoundA(soundA.data, soundA.length, soundA.loops);
                }
                else
                {
                    soundA.isPlaying = 0;
                    // turn off channel 1
                    dma[1].cnt = 0;
                    // turn off timer 0
                    REG_TM0CNT = 0;
                }
            }
        }

        if (soundB.isPlaying)
        {

            soundB.vBlankCount = soundB.vBlankCount + 1;
            if (soundB.vBlankCount > soundB.duration)
            {
                if (soundB.loops)
                {
                    playSoundB(soundB.data, soundB.length, soundB.loops);
                }
                else
                {
                    soundB.isPlaying = 0;
                    // turn off channel 2
                    dma[2].cnt = 0;
                    // turn off timer 1
                    REG_TM1CNT = 0;
                }
            }
        }

        REG_IF = INT_VBLANK;
    }

    REG_IF = REG_IF;
    REG_IME = 1;
}
void enableTimerInterrupts()
{
    REG_IE |= INT_TM2;

    REG_TM2CNT = 0;
    REG_TM2D = 65536 - 16384;
    REG_TM2CNT = TM_FREQ_1024 | TIMER_ON | TM_IRQ;
}
void setupInterrupts(void)
{
    REG_IME = 0;

    REG_INTERRUPT = interruptHandler;
    enableTimerInterrupts();

    REG_IE |= INT_VBLANK;
    REG_DISPSTAT |= INT_VBLANK_ENABLE;
    REG_IME = 1;
}

