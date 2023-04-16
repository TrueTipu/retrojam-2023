#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"

void DestroyItem(Sprite *doomedSprite) BANKED;


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
    data->key_type = TYPE3;
}

void UPDATE() {
}

void DESTROY() {
}