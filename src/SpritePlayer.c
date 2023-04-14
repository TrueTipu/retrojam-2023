#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "SpriteManager.h"

#include "Scroll.h"


void START() {

}

typedef enum{
	GROUND,
	FALLING,
	JUMPING
} PLAYERSTATE;
PLAYERSTATE state = FALLING;

UINT8 fall_speed;
UINT8 gravity = 1;
UINT8 gravityslow = 0;

void FallPhysics(){
	
	TranslateSprite(THIS, 0, fall_speed);



	if(state == FALLING){
		if(gravityslow == 0){
			fall_speed += gravity;
			gravityslow = 2;
		} else{
			gravityslow -= 1;
		}
		
			

		UINT8 tile = GetScrollTile((THIS->x) >> 3, (THIS ->y + 12u) >> 3);
		if(tile == 1u){
			fall_speed = 0;
			state = GROUND;
			while (GetScrollTile((THIS->x) >> 3, (THIS ->y + 12u) >> 3) == 1u)
			{
				THIS->y--;
			}
		}
	}
	
	if(state == GROUND){
		if(KEY_PRESSED(J_A)){
			TranslateSprite(THIS, 0, -6);
			fall_speed -= 2;
			state = FALLING;
		}	
	}
	
}
void UPDATE() {
    if(KEY_PRESSED(J_UP)) {
		TranslateSprite(THIS, 0, -15);
	} 
	if(KEY_PRESSED(J_DOWN)) {
		TranslateSprite(THIS, 0, 1);
	}
	if(KEY_PRESSED(J_LEFT)) {
		TranslateSprite(THIS, -1, 0);
	}
	if(KEY_PRESSED(J_RIGHT)) {
		TranslateSprite(THIS, 1, 0);
	}


	FallPhysics();
}

void DESTROY() {
}