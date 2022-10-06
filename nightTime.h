
//{{BLOCK(nightTime)

//======================================================================
//
//	nightTime, 512x256@4, 
//	+ palette 256 entries, not compressed
//	+ 274 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 512 + 8768 + 4096 = 13376
//
//	Time-stamp: 2022-04-11, 15:44:16
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.3
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_NIGHTTIME_H
#define GRIT_NIGHTTIME_H

#define nightTimeTilesLen 8768
extern const unsigned short nightTimeTiles[4384];

#define nightTimeMapLen 4096
extern const unsigned short nightTimeMap[2048];

#define nightTimePalLen 512
extern const unsigned short nightTimePal[256];

#endif // GRIT_NIGHTTIME_H

//}}BLOCK(nightTime)
