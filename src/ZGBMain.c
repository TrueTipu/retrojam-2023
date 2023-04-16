#include "ZGBMain.h"
#include "Math.h"
UINT8 next_state = StateMenu;

UINT8 level = 0;

void addL() BANKED{
	level++;
}
UINT8 getL() BANKED{
	return level;
}



UINT8 GetTileReplacement(UINT8* tile_ptr, UINT8* tile) {
	if(current_state == StateGame) {
		if(U_LESS_THAN(255 - (UINT16)*tile_ptr, N_SPRITE_TYPES)) {
			*tile = 0;
			return 255 - (UINT16)*tile_ptr;
		}

		*tile = *tile_ptr;
	}

	return 255u;
}