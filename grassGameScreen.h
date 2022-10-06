
//{{BLOCK(grassGameScreen)

//======================================================================
//
//	grassGameScreen, 256x160@4, 
//	+ palette 256 entries, not compressed
//	+ 61 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x20 
//	Total size: 512 + 1952 + 1280 = 3744
//
//	Time-stamp: 2022-04-10, 18:14:28
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GRASSGAMESCREEN_H
#define GRIT_GRASSGAMESCREEN_H

#define grassGameScreenTilesLen 1952
extern const unsigned short grassGameScreenTiles[976];

#define grassGameScreenMapLen 1280
extern const unsigned short grassGameScreenMap[640];

#define grassGameScreenPalLen 512
extern const unsigned short grassGameScreenPal[256];

#endif // GRIT_GRASSGAMESCREEN_H

//}}BLOCK(grassGameScreen)
