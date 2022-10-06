#include <stdlib.h>
#include <stdio.h>
#include "mode0.h"
#include "game.h"
#include "sound.h"

// state screens
#include "loseScreen.h"
#include "instructionScreen.h"
#include "startScreen.h"
#include "winScreen.h"
#include "pauseScreen.h"

// game
#include "skiesGameScreen.h"
#include "sunnyBackground.h"
#include "nightTime.h"

#include "grassGameScreen.h"
#include "spritesheetTest.h"

// sound
#include "gameSong.h"
#include "winSound.h"
#include "hitSound.h"

// Prototypes.
void initialize();

// State Prototypes.
void goToStart();
void start();
void instruction();
void goToInstructions();

void level1();
void goToLevel1();

void level2();
void goToLevel2();

void level3();
void goToLevel3();

void goToPause();
void pause();
void goToWin();
void win();
void goToLose();
void lose();

int seed;

// States.
enum
{
    START,
    LVL1,
    LVL2,
    LVL3,
    PAUSE,
    INSTRUCTION,
    WIN,
    LOSE
};
int state;

// Button Variables.
unsigned short buttons;
unsigned short oldButtons;

// Shadow OAM.
OBJ_ATTR shadowOAM[128];

int main()
{
    initialize();

    while (1)
    {
        // Update button variables.
        oldButtons = buttons;
        buttons = BUTTONS;

        // State Machine.
        switch (state)
        {
        case START:
            start();
            break;
        case LVL1:
            level1();
            break;
        case LVL2:
            level2();
            break;
        case LVL3:
            level3();
            break;
        case PAUSE:
            pause();
            break;
        case INSTRUCTION:
            instruction();
            break;
        case WIN:
            win();
            break;
        case LOSE:
            lose();
            break;
        }
    }
}

// Sets up GBA.
void initialize()
{
    REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
    REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
    buttons = BUTTONS;
    oldButtons = 0;

    setupSounds();
    setupInterrupts();
    goToStart();
}

// Sets up the start state.
void goToStart()
{

    DMANow(3, startScreenPal, PALETTE, 256);
    DMANow(3, startScreenTiles, &CHARBLOCK[0], startScreenTilesLen / 2);
    DMANow(3, startScreenMap, &SCREENBLOCK[28], startScreenMapLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    waitForVBlank();

    state = START;
    seed = 0;
    REG_DISPCTL = MODE0 | BG0_ENABLE;
}

// Runs every frame of the start state.
void start()
{
    seed++;
    waitForVBlank();
    if (BUTTON_PRESSED(BUTTON_START))
    {
        srand(seed);
        goToLevel1();
        initGame();

        stopSound();
        // works but dont want it right now
        playSoundA(gameSong_data, gameSong_length, 1);
    }
    if (BUTTON_PRESSED(BUTTON_SELECT))
    {
        goToInstructions();
    }
}

// Sets up the game state.
void goToLevel1()
{
    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE;
    // skies
    DMANow(3, sunnyBackgroundPal, PALETTE, skiesGameScreenPalLen / 2);
    REG_BG1CNT = BG_SIZE_WIDE | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
    DMANow(3, sunnyBackgroundTiles, &CHARBLOCK[0], sunnyBackgroundTilesLen / 2);
    DMANow(3, sunnyBackgroundMap, &SCREENBLOCK[28], sunnyBackgroundMapLen / 2);
    // grass
    REG_BG0CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(26);
    DMANow(3, grassGameScreenTiles, &CHARBLOCK[1], grassGameScreenTilesLen / 2);
    DMANow(3, grassGameScreenMap, &SCREENBLOCK[26], grassGameScreenMapLen / 2);

    // sprites
    DMANow(3, spritesheetTestTiles, &CHARBLOCK[4], spritesheetTestTilesLen / 2);
    DMANow(3, spritesheetTestPal, SPRITEPALETTE, spritesheetTestPalLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    waitForVBlank();
    state = LVL1;
}

// Runs every frame of the game state.
void level1()
{
    updateGame();

    drawGame();

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    if (BUTTON_PRESSED(BUTTON_START))
    {
        hOff = 0;
        REG_BG0HOFF = hOff;
        REG_BG1HOFF = hOff;
        REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
        pauseSound();
        goToPause();
    }
    
    // will be replaced later when health goes to you. just for testing purposes
    if (time_s == 0 || health == 0)
    {
        hOff = 0;
        REG_BG0HOFF = hOff;
        REG_BG1HOFF = hOff;
        REG_DISPCTL = MODE0 | BG0_ENABLE;
        REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
        pauseSound();
        goToLose();
    }
    if (level == 2)
    {
        hOff = 0;
        REG_BG0HOFF = hOff;
        REG_BG1HOFF = hOff;
        REG_DISPCTL = MODE0 | BG0_ENABLE;
        REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);

        continueToNextLevel();
        goToLevel2();
    }
}

// Sets up the game state.
void goToLevel2()
{
    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE;
    // skies
    DMANow(3, skiesGameScreenPal, PALETTE, skiesGameScreenPalLen / 2);
    REG_BG1CNT = BG_SIZE_WIDE | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
    DMANow(3, skiesGameScreenTiles, &CHARBLOCK[0], skiesGameScreenTilesLen / 2);
    DMANow(3, skiesGameScreenMap, &SCREENBLOCK[28], skiesGameScreenMapLen / 2);
    // grass
    REG_BG0CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(26);
    DMANow(3, grassGameScreenTiles, &CHARBLOCK[1], grassGameScreenTilesLen / 2);
    DMANow(3, grassGameScreenMap, &SCREENBLOCK[26], grassGameScreenMapLen / 2);

    // sprites
    DMANow(3, spritesheetTestTiles, &CHARBLOCK[4], spritesheetTestTilesLen / 2);
    DMANow(3, spritesheetTestPal, SPRITEPALETTE, spritesheetTestPalLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    waitForVBlank();
    state = LVL2;
}

// Runs every frame of the game state.
void level2()
{
    updateGame();
    REG_BG0HOFF = hOff;
    drawGame();

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    if (BUTTON_PRESSED(BUTTON_START))
    {
        hOff = 0;
        REG_BG0HOFF = hOff;
        REG_BG1HOFF = hOff;
        REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
        pauseSound();
        goToPause();
    }
    
    // will be replaced later when health goes to you. just for testing purposes
    if (time_s == 0 || health == 0)
    {
        hOff = 0;
        REG_BG0HOFF = hOff;
        REG_BG1HOFF = hOff;
        REG_DISPCTL = MODE0 | BG0_ENABLE;
        REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
        pauseSound();
        goToLose();
    }
    if (level == 3)
    {
        hOff = 0;
        REG_BG0HOFF = hOff;
        REG_BG1HOFF = hOff;
        REG_DISPCTL = MODE0 | BG0_ENABLE;
        REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);

        continueToNextLevel();
        goToLevel3();
    }
}

// Sets up the game state.
void goToLevel3()
{
    REG_DISPCTL = MODE0 | BG0_ENABLE | BG1_ENABLE | SPRITE_ENABLE;
    // skies
    DMANow(3, nightTimePal, PALETTE, nightTimePalLen / 2);
    REG_BG1CNT = BG_SIZE_WIDE | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
    DMANow(3, nightTimeTiles, &CHARBLOCK[0], nightTimeTilesLen / 2);
    DMANow(3, nightTimeMap, &SCREENBLOCK[28], nightTimeMapLen / 2);
    // grass
    REG_BG0CNT = BG_SIZE_SMALL | BG_CHARBLOCK(1) | BG_SCREENBLOCK(26);
    DMANow(3, grassGameScreenTiles, &CHARBLOCK[1], grassGameScreenTilesLen / 2);
    DMANow(3, grassGameScreenMap, &SCREENBLOCK[26], grassGameScreenMapLen / 2);

    // sprites
    DMANow(3, spritesheetTestTiles, &CHARBLOCK[4], spritesheetTestTilesLen / 2);
    DMANow(3, spritesheetTestPal, SPRITEPALETTE, spritesheetTestPalLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    waitForVBlank();
    state = LVL3;
}

// Runs every frame of the game state.
void level3()
{
    updateGame();
    REG_BG0HOFF = hOff;
    drawGame();

    waitForVBlank();
    DMANow(3, shadowOAM, OAM, 128 * 4);

    if (BUTTON_PRESSED(BUTTON_START))
    {
        hOff = 0;
        REG_BG0HOFF = hOff;
        REG_BG1HOFF = hOff;
        REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
        pauseSound();
        goToPause();
    }
    // will be replaced later when health goes to you. just for testing purposes
    if (time_s == 0 || health == 0)
    {
        hOff = 0;
        REG_BG0HOFF = hOff;
        REG_BG1HOFF = hOff;
        REG_DISPCTL = MODE0 | BG0_ENABLE;
        REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
        pauseSound();
        goToLose();
    }
    if (level == 4)
    {
        hOff = 0;
        REG_BG0HOFF = hOff;
        REG_BG1HOFF = hOff;
        REG_DISPCTL = MODE0 | BG0_ENABLE;
        REG_BG0CNT = BG_4BPP | BG_SIZE_SMALL | BG_CHARBLOCK(0) | BG_SCREENBLOCK(28);
        pauseSound();
        stopSound();
        playSoundA(winSound_data, winSound_length, 1);
        goToWin();
    }
}
// Sets up the pause state.
void goToPause()
{
    DMANow(3, pauseScreenPal, PALETTE, 256);
    DMANow(3, pauseScreenTiles, &CHARBLOCK[0], pauseScreenTilesLen / 2);
    DMANow(3, pauseScreenMap, &SCREENBLOCK[28], pauseScreenMapLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    waitForVBlank();

    waitForVBlank();

    state = PAUSE;
}

// Runs every frame of the pause state.
void pause()
{
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START))
    {
        if (level == 1)
        {
            goToLevel1();
        }
        else if (level == 2)
        {
            goToLevel2();
        }
        else if (level == 3)
        {
            goToLevel3();
        }
        stopSound();
        playSoundA(gameSong_data, gameSong_length, 1);
    }
}

// Sets up the instructions state.
void goToInstructions()
{
    DMANow(3, instructionScreenPal, PALETTE, 256);
    DMANow(3, instructionScreenTiles, &CHARBLOCK[0], instructionScreenTilesLen / 2);
    DMANow(3, instructionScreenMap, &SCREENBLOCK[28], instructionScreenMapLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    waitForVBlank();

    waitForVBlank();

    state = INSTRUCTION;
}

// Runs every frame of the instructions state.
void instruction()
{
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START))
        goToStart();
}

// Sets up the win state.
void goToWin()
{
    DMANow(3, winScreenPal, PALETTE, 256);
    DMANow(3, winScreenTiles, &CHARBLOCK[0], winScreenTilesLen / 2);
    DMANow(3, winScreenMap, &SCREENBLOCK[28], winScreenMapLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    waitForVBlank();

    state = WIN;
}

// Runs every frame of the win state.
void win()
{
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START))
    {
        goToStart();
        pauseSound();
    }
}

// Sets up the lose state.
void goToLose()
{
    DMANow(3, losescreenPal, PALETTE, 256);
    DMANow(3, losescreenTiles, &CHARBLOCK[0], losescreenTilesLen / 2);
    DMANow(3, losescreenMap, &SCREENBLOCK[28], losescreenMapLen / 2);
    hideSprites();
    DMANow(3, shadowOAM, OAM, 128 * 4);
    waitForVBlank();

    state = LOSE;
}

// Runs every frame of the lose state.
void lose()
{
    waitForVBlank();

    if (BUTTON_PRESSED(BUTTON_START))
        goToStart();
}