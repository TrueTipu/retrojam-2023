#include "Banks/SetAutoBank.h"

#include "SpriteManager.h"
const UINT8 anim_corr[] = {14,0 , 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};


void START() {
}

void UPDATE() {
    SetSpriteAnim(THIS, anim_corr, 15);

}

void DESTROY() {}
