#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
#include "Print.h"
typedef struct {
    Sprite* target;
    UINT8 x;
    UINT8 y;
} CUSTOM_DATA;

void SetTarget(Sprite* target, Sprite* spr) BANKED{
    CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
    data->target = target;
}
void SetSpot(INT8 x, INT8 y, Sprite* spr) BANKED{
    CUSTOM_DATA* data = (CUSTOM_DATA*)spr->custom_data;
    data->x = x;
    data->y = y;
    data->target = NULL;
}
void START(){
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->target = NULL;
    data->x = THIS->x;
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

}

void DESTROY() {
}