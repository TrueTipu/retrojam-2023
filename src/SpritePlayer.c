#include "Banks/SetAutoBank.h"

#include "Keys.h"
#include "SpriteManager.h"

#include "Scroll.h"
#include "Print.h"

#include "ZGBMain.h"

void SetTarget(Sprite* target, Sprite* spr) BANKED;

void SetSpot(INT8 x, INT8 y, Sprite* spr) BANKED;

void START() {
	
}


typedef enum{
	GROUND,
	FALLING,
	JUMPING
} PLAYERSTATE;
PLAYERSTATE state = FALLING;

INT8 fall_speed;
UINT8 gravity = 1;
UINT8 gravityslow = 0;

UINT8 koyote_timer;
UINT8 koyote_time = 6u;

UINT8 jbuff_timer;
UINT8 jbuff_time = 6u;

const UINT8 anim_idle[] = {2, 4, 5}; 
const UINT8 anim_walk[] = {3, 0, 1, 2};
const UINT8 anim_jump[] = {1, 2};
const UINT8 anim_fall[] = {1, 1};

UINT8 dir;

Sprite* hold = NULL;

Sprite* CheckSpriteCollision(){
	UINT8 i;
	Sprite* spr;
	
	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SpriteKey) {
			if(CheckCollision(THIS, spr)) {
				return spr;
			}
		}
	}
	return NULL;
}

INT8 touch_ground(){
	//Oikea reuna
	UINT8 tile = GetScrollTile((THIS->x + 7u)>> 3, (THIS ->y + THIS->mt_sprite_info->height) >> 3);
	//Vasen reuna
	UINT8 tile2 = GetScrollTile((THIS->x )>> 3, (THIS ->y + THIS->mt_sprite_info->height) >> 3);

	Sprite* spr = CheckSpriteCollision();
	if(spr != NULL){
		if((spr->mt_sprite->dy) < (THIS->y + THIS->mt_sprite_info->height)){
			return 1;
		}
	}
	
	return (tile == 2u || tile2 == 2u);
}

INT8 touch_ceiling(){
	//Oikea reuna
	UINT8 tile = GetScrollTile((THIS->x + 7u)>> 3, (THIS ->y - 1u ) >> 3);
	//Vasen reuna
	UINT8 tile2 = GetScrollTile((THIS->x )>> 3, (THIS ->y - 1u) >> 3);
	return (tile == 1u || tile2 == 1u);
}
void jump(){
	fall_speed = -4;
	koyote_timer = 0;
	jbuff_timer = 0;
	state = FALLING;
}
void FallPhysics(){
	DPRINT_POS(0, 0);
	DPrintf("%d", state);
	if(KEY_TICKED(J_A) && hold == NULL){
		jbuff_timer = jbuff_time;
	}	
	if(state == FALLING){
		TranslateSprite(THIS, 0, fall_speed);

		if(koyote_timer > 0){
			koyote_timer -= 1;
		}
		if(jbuff_timer > 0){
			jbuff_timer -= 1;
		}
		if(jbuff_timer > 0 && koyote_timer > 0){
			jump();
		}

		if(gravityslow == 0){
			fall_speed += gravity;
			gravityslow = 4;
		} else{
			gravityslow -= 1;
		}
		
		if(touch_ceiling()){
			fall_speed = 1;
		}
			

		if(touch_ground()){
			gravityslow = 0;
			fall_speed = 0;
			state = GROUND;
			while (touch_ground())
			{
				THIS->y--;
			}
			THIS->y++;
		}
		if (fall_speed > 0){
			SetSpriteAnim(THIS, anim_fall, 15);
		}
		else {
			SetSpriteAnim(THIS, anim_jump, 15);
		}
	}
	
	if(state == GROUND){
		if(jbuff_timer > 0){
			jump();
		}
		else if(!touch_ground()){
			koyote_timer = koyote_time;
			state = FALLING;
		}
	}
	
}

void UPDATE() {
	

	if(KEY_PRESSED(J_DOWN)) {
		TranslateSprite(THIS, 0, 1);
	}
	if(KEY_PRESSED(J_LEFT)) {
		dir = 1;
		TranslateSprite(THIS, -1, 0);
		if (state == GROUND) {
			SetSpriteAnim(THIS, anim_walk, 15);
		}
		Sprite* spr = CheckSpriteCollision();
		if(spr != NULL){
			if((spr->x + spr->mt_sprite_info->width) == (THIS->x)){
				TranslateSprite(THIS, 1, 0);	
			}
		}
	}
	if(KEY_PRESSED(J_RIGHT)) {
		dir = 0;
		TranslateSprite(THIS, 1, 0);
		if (state == GROUND) {
			SetSpriteAnim(THIS, anim_walk, 15);
		}
		Sprite* spr = CheckSpriteCollision();
		if(spr != NULL){
	
			if((spr->x) == (THIS->x + THIS->mt_sprite_info->width)){
				TranslateSprite(THIS, -1, 0);	
			}
		}
	}
	if(keys == 0) {
		if (state == GROUND) {
			SetSpriteAnim(THIS, anim_idle, 8);
		}

	}
	if(KEY_TICKED(J_B)){
		if(hold == NULL){
			UINT8 touched = 0;
			if(dir == 0){
				TranslateSprite(THIS, 1, 0);
				hold = CheckSpriteCollision();
				if(hold != NULL){
					if((hold->x) == (THIS->x + THIS->mt_sprite_info->width)){
						TranslateSprite(THIS, -1, 0);	
						touched = 1;
					}
				}
			}
			else
			{
				TranslateSprite(THIS, -1, 0);
				hold = CheckSpriteCollision();
				if(hold != NULL){
					if((hold->x + hold->mt_sprite_info->width) == (THIS->x)){
						TranslateSprite(THIS, 1, 0);
						touched = 1;
					}
				}
			}

			if(touched == 1){
				SetTarget(THIS, hold);
			}
			else{
				hold = NULL;
			}
		}
		else{
			if(dir == 0){
				SetSpot(THIS->x + 20, THIS->y +8, hold);
				hold = NULL;
			}
			if(dir == 1){
				SetSpot(THIS->x -10, THIS->y+ 8, hold);
				hold = NULL;
			}
		}
		
	}

	FallPhysics();
}

void DESTROY() {
}