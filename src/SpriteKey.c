#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "Print.h"
typedef enum{
	TYPE1,
	TYPE2,
	TYPE3
} KEYTYPE;

typedef struct {
    Sprite* target;
    UINT8 x;
    UINT8 y;
    KEYTYPE key_type;
} CUSTOM_DATA;


const UINT8 key1[] = {1, 0};
const UINT8 key2[] = {1, 1};
const UINT8 key3[] = {1, 2};
KEYTYPE GetType(Sprite* spr) BANKED{
    CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
    return data->key_type;
}

void SetKeyType(Sprite* spr, KEYTYPE key_type) BANKED{
    CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
     data->key_type = key_type;
}



void SetTarget(Sprite* target, Sprite* spr) BANKED{
    CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
    data->target = target;
}

void SetPosition(UINT8 new_x, UINT8 new_y) BANKED{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

    data->x = new_x;
    data->y = new_y;
}
void SetSpot(UINT8 x, UINT8 y, Sprite* spr) BANKED{
    CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
    data->x = x;
    data->y = y;
    data->target = NULL;
}
void START(){
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->target = NULL;
    data->x = THIS->x;
    data->key_type = TYPE2;
    data->y = THIS->y;
}

void UPDATE() {
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    if(data->target != NULL){
        THIS->x = data->target->x;
        THIS->y = data->target->y - 16;
    }
    else{
        THIS->x = data->x;
        THIS->y = data->y;
    }
    switch (data->key_type)
    {
    case TYPE1:
        SetSpriteAnim(THIS, key1, 15);
        break;
    case TYPE2:
        SetSpriteAnim(THIS, key2, 15);
        break;
    case TYPE3:
        SetSpriteAnim(THIS, key3, 15);
        break;
    default:
        break;
    }

}

void DESTROY() {
}