#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "SpriteManager.h"

#include "Scroll.h"
#include "Print.h"


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

INT8 touch_ground(){
	//Oikea reuna
	UINT8 tile = GetScrollTile((THIS->x + 7u)>> 3, (THIS ->y + 14u) >> 3);
	//Vasen reuna
	UINT8 tile2 = GetScrollTile((THIS->x )>> 3, (THIS ->y + 14u) >> 3);
	return (tile == 1u || tile2 == 1u);
}

INT8 touch_ceiling(){
	//Oikea reuna
	UINT8 tile = GetScrollTile((THIS->x + 7u)>> 3, (THIS ->y - 1u ) >> 3);
	//Vasen reuna
	UINT8 tile2 = GetScrollTile((THIS->x )>> 3, (THIS ->y - 1u) >> 3);
	return (tile == 1u || tile2 == 1u);
}

void FallPhysics(){

	if(state == FALLING){
		TranslateSprite(THIS, 0, fall_speed);


		if(gravityslow == 0){
			fall_speed += gravity;
			gravityslow = 4;
		} else{
			gravityslow -= 1;
		}
		
		if(touch_ceiling()){
			fall_speed = 1;
			DPRINT_POS(15, 0);
			DPrintf("oi");
		}
			

		if(touch_ground()){
			gravityslow = 0;
			fall_speed = 0;
			while (touch_ground())
			{
				THIS->y--;
			}
			THIS->y++;
			state = GROUND;
		}
	}
	
	if(state == GROUND){
		if(KEY_TICKED(J_A)){
			fall_speed -= 4;
			state = FALLING;
		}	
		else if(!touch_ground()){
			state = FALLING;
		}
	}
	
}
void UPDATE() {
	DPRINT_POS(0, 0);
	DPrintf("x:%d y:%d  %d", THIS->x, THIS->y, state);

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