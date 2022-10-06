
//{{BLOCK(skiesGameScreen)

//======================================================================
//
//	skiesGameScreen, 512x256@4, 
//	+ palette 256 entries, not compressed
//	+ 320 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 10240 + 4096 = 14848
//
//	Time-stamp: 2022-04-10, 19:35:21
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SKIESGAMESCREEN_H
#define GRIT_SKIESGAMESCREEN_H

#define skiesGameScreenTilesLen 10240
extern const unsigned short skiesGameScreenTiles[5120];

#define skiesGameScreenMapLen 4096
extern const unsigned short skiesGameScreenMap[2048];

#define skiesGameScreenPalLen 512
extern const unsigned short skiesGameScreenPal[256];

#endif // GRIT_SKIESGAMESCREEN_H

//}}BLOCK(skiesGameScreen)
