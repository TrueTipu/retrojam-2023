#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
_STATE(StateMenu)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, hattu)\
_SPRITE_DMG(SpriteItem, tavarat)\
_SPRITE_DMG(SpriteKey, lisa_avaimet)\
_SPRITE_DMG(SpriteDoor, lisaovet)\
_SPRITE_DMG(SpritePipe, putki)\
_SPRITE_DMG(SpriteSand, tavarat)\
_SPRITE_DMG(SpriteCorrupted, melting)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif