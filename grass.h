
//{{BLOCK(grass)

//======================================================================
//
//	grass, 256x160@4, 
//	+ palette 256 entries, not compressed
//	+ 61 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x20 
//	Total size: 512 + 1952 + 1280 = 3744
//
//	Time-stamp: 2022-04-10, 18:14:15
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_GRASS_H
#define GRIT_GRASS_H

#define grassTilesLen 1952
extern const unsigned short grassTiles[976];

#define grassMapLen 1280
extern const unsigned short grassMap[640];

#define grassPalLen 512
extern const unsigned short grassPal[256];

#endif // GRIT_GRASS_H

//}}BLOCK(grass)
