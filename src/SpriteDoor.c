#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

void DestroyItem(Sprite *doomedSprite) BANKED;

const UINT8 door1[] = {1, 0};
const UINT8 door2[] = {1, 1};
const UINT8 door3[] = {1, 2};
typedef enum{
	TYPE1,
	TYPE2,
	TYPE3
} KEYTYPE;
typedef struct {
    KEYTYPE key_type;
} CUSTOM_DATA;

KEYTYPE GetType(Sprite* spr) BANKED;

UINT8 TryOpen(Sprite* door, Sprite* key) BANKED{
    CUSTOM_DATA* data = (CUSTOM_DATA*)door->custom_data;
    if(data->key_type == GetType(key)){
        DestroyItem(door);
        return 1u;
    }
    else{
        return 0u;
    }
}
void SetDoorType(Sprite* spr, KEYTYPE key_type) BANKED{
    CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
     data->key_type = key_type;
}

void START() {
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
}
    
void UPDATE() {
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    switch (data->key_type)
    {
        case TYPE1:
            SetSpriteAnim(THIS, door1, 15);
            break;
        case TYPE2:
            SetSpriteAnim(THIS, door2, 15);
            break;
        case TYPE3:
            SetSpriteAnim(THIS, door3, 15);
            break;
        default:
            break;
    }
}

void DESTROY() {
}