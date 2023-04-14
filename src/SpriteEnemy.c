#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
typedef struct {
	INT8 vy;
} CUSTOM_DATA;

const UINT8 enemy_anim_idle[] = {4, 1, 2, 1, 0};

void START() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
	data->vy = 1;
}

void UPDATE() {
	CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    SetSpriteAnim(THIS, enemy_anim_idle, 3);
	if(TranslateSprite(THIS, 0, data->vy)) {
		data->vy = -data->vy;
	}
}

void DESTROY() {
}