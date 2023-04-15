#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, hattu)\
_SPRITE_DMG(SpriteItem, tavarat)\
_SPRITE_DMG(SpriteKey, tavarat)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif