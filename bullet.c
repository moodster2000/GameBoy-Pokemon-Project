#include "bullet.h"
#include "mode0.h"
#include "game.h"
#include "hitSound.h"

PBULLET playerBullets[PLAYERBULLETCOUNT];
EBULLET enemyBullets[ENEMYBULLETCOUNT];
void initPlayerBullets()
{
    for (int i = 0; i < PLAYERBULLETCOUNT; i++)
    {
        playerBullets[i].active = 0;

        playerBullets[i].row = 0;
        playerBullets[i].col = 0;
        playerBullets[i].rdel = 1;
        playerBullets[i].cdel = 1;
        playerBullets[i].width = 8;
        playerBullets[i].height = 8;

        playerBullets[i].pos.x = 0;
        playerBullets[i].pos.y = 0;
        playerBullets[i].pos.dx = 0;
        playerBullets[i].pos.dy = 0;
    }
}
void initEnemyBullets()
{
    for (int i = 0; i < ENEMYBULLETCOUNT; i++)
    {
        enemyBullets[i].active = 0;

        enemyBullets[i].row = 0;
        enemyBullets[i].col = 0;
        enemyBullets[i].rdel = 2;
        enemyBullets[i].cdel = 2;
        enemyBullets[i].width = 8;
        enemyBullets[i].height = 8;

        enemyBullets[i].pos.x = 0;
        enemyBullets[i].pos.y = 0;
        enemyBullets[i].pos.dx = 0;
        enemyBullets[i].pos.dy = 0;
    }
}

void clearPlayerBullet(PBULLET *p)
{
    p->active = 0;

    p->row = 0;
    p->col = 0;
    p->rdel = 0;
    p->cdel = 0;
    p->width = 8;
    p->height = 8;

    p->pos.x = 0;
    p->pos.y = 0;
    p->pos.dx = 0;
    p->pos.dy = 0;
}

void clearEnemyBullet(EBULLET *p)
{
    p->active = 0;

    p->row = 0;
    p->col = 0;
    p->rdel = 0;
    p->cdel = 0;
    p->width = 8;
    p->height = 8;

    p->pos.x = 0;
    p->pos.y = 0;
    p->pos.dx = 0;
    p->pos.dy = 0;
}

void firePlayerBullet()
{
    for (int i = 0; i < PLAYERBULLETCOUNT; i++)
    {
        if (!playerBullets[i].active)
        {
            playerBullets[i].active = 1;

            playerBullets[i].pos.y = player.pos.y;
            playerBullets[i].pos.x = player.pos.x;

            playerBullets[i].cdel = 1;

            break;
        }
    }
}
void fireEnemyBullet()
{
    for (int i = 0; i < ENEMYBULLETCOUNT; i++)
    {
        if (!enemyBullets[i].active)
        {
            enemyBullets[i].active = 1;

            enemyBullets[i].pos.y = enemies[2].screenRow;
            enemyBullets[i].pos.x = enemies[2].screenCol;

            enemyBullets[i].cdel = 2;

            break;
        }
    }
}
void updatePlayerBullets()
{
    for (int i = 0; i < PLAYERBULLETCOUNT; i++)
    {
        // player bullet behaviour
        if (playerBullets[i].active)
        {
            // if in screen
            if (0 < playerBullets[i].pos.x && playerBullets[i].pos.x + 8 < player.pos.x + 8 + 90)
            {
                if (player.direction == 1)
                {
                    playerBullets[i].pos.x += playerBullets[i].cdel;
                }
                else if (player.direction == 0)
                {
                    playerBullets[i].pos.x -= playerBullets[i].cdel;
                }

                // collision with enemy
                for (int k = 0; k < ENEMYCOUNT; k++)
                {
                    if (enemies[k].active && collision(playerBullets[i].pos.y, playerBullets[i].pos.x, playerBullets[i].height,
                                  playerBullets[i].width, enemies[k].screenRow, enemies[k].screenCol, enemies[k].height, enemies[k].width))
                    {   
                        playerBullets[i].active = 0;
                        enemies[k].active = 0;
                        enemies[k].health = 0;
                        // playSoundB(hitSound_data, hitSound_length, 0);
                    }
                }
            }
            else
            { // bullet has left screen
                playerBullets[i].active = 0;
            }
        }
    }
}

void updateEnemyBullets()
{
    for (int i = 0; i < ENEMYBULLETCOUNT; i++)
    {
        // player bullet behaviour
        if (enemyBullets[i].active)
        {
            // if in screen but also limit bullet distance
            if (enemyBullets[i].pos.x - hOff >= 0 && enemyBullets[i].pos.x > enemies[2].screenCol  - 30)
            {
                enemyBullets[i].pos.x -= enemyBullets[i].cdel;

                // collision with player
                if (player.cheatTime == 0 && enemyBullets[i].active && collision(player.screenRow, player.screenCol, player.height,
                              player.width, enemyBullets[i].pos.y, enemyBullets[i].pos.x, enemyBullets[i].height, enemyBullets[i].width))
                {
                    // lose health
                    health--;
                    player.pos.x = 10;
                    player.pos.y = 112;
                    hOff = 0;
                    enemyBullets[i].active = 0;
                }
            }
            else
            { // bullet has left screen
                enemyBullets[i].active = 0;
            }
        }
    }
}

void drawPlayerBullets()
{
    // draw player bullets
    for (int i = 0; i < PLAYERBULLETCOUNT; i++)
    {
        if (playerBullets[i].active)
        {
            shadowOAM[56 + i].attr0 = playerBullets[i].pos.y | ATTR0_SQUARE | ATTR0_4BPP;
            shadowOAM[56 + i].attr1 = playerBullets[i].pos.x | ATTR1_TINY;
            shadowOAM[56 + i].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(0, 0);
        }
        else
        {
            shadowOAM[56 + i].attr0 = ATTR0_HIDE;
            clearPlayerBullet(&playerBullets[i]);
        }
    }
}
void drawEnemyBullets()
{
    // draw player bullets
    for (int i = 0; i < ENEMYBULLETCOUNT; i++)
    {
        if (enemyBullets[i].active)
        {
            shadowOAM[16 + i].attr0 = enemyBullets[i].pos.y | ATTR0_SQUARE | ATTR0_4BPP;
            shadowOAM[16 + i].attr1 = enemyBullets[i].pos.x | ATTR1_TINY;
            shadowOAM[16 + i].attr2 = ATTR2_PALROW(0) | ATTR2_TILEID(1, 0);
        }
        else
        {
            shadowOAM[16 + i].attr0 = ATTR0_HIDE;
            clearEnemyBullet(&enemyBullets[i]);
        }
    }
}