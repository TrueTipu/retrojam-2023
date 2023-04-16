#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Keys.h"

IMPORT_TILES(font);
IMPORT_MAP(mappinen);
IMPORT_MAP(hud);
Sprite *getHoldedItem() BANKED;
void SetPosition(UINT8 new_x, UINT8 new_y) BANKED;




typedef struct
{
	UINT16 x;
	UINT16 y;
	UINT8 type;
	Sprite *sprite_id;
	UINT8 destroyed;
} item;

item items[100];
UINT8 sprite_idx;

UINT8 collision_tiles[] = {1, 2, 4, 5, 6, 0};

void DestroyItem(Sprite *doomedSprite) BANKED{
	for(int i = 0; i < sprite_idx; i++){
		if(items[i].sprite_id == doomedSprite){
			items[i].destroyed = 1;
		}
	}
	SpriteManagerRemoveSprite(doomedSprite);
}


void AddItem(UINT8 n_type, UINT16 n_x, UINT16 n_y){
	item n_i;
	n_i.x = n_x;
	n_i.y = n_y;
	n_i.type = n_type;
	n_i.sprite_id = NULL;
	n_i.destroyed = 0;

	items[sprite_idx] = n_i;
	items[sprite_idx].sprite_id = SpriteManagerAdd(items[sprite_idx].type, items[sprite_idx].x, items[sprite_idx].y);
	sprite_idx++;

}

void START()
{
	sprite_idx = 0;


	InitScroll(BANK(mappinen), &mappinen, collision_tiles, 0);

	INIT_HUD(hud);

	scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	AddItem(SpriteKey, 70u, 120u);

	//AddItem(SpritePipe, 120, 112);

	AddItem(SpriteDoor, 100, 110);

	INIT_CONSOLE(font, 3);
}

void UPDATE()
{
	Sprite *item_in_hold = getHoldedItem();

	for (int i = 0; i < sprite_idx; i++)
	{
		if (items[i].destroyed == 1){
			continue;
		}
		if (item_in_hold == items[i].sprite_id)
		{
			if (item_in_hold != NULL)
			{
				items[i].x = item_in_hold->x;
				items[i].y = item_in_hold->y;
			}
		}
		else if (items[i].sprite_id != NULL)
		{
			items[i].x = items[i].sprite_id->x;
			items[i].y = items[i].sprite_id->y;
		}
		if (((INT16)(scroll_target->x - items[i].x) < 80 && (INT16)(scroll_target->x - items[i].x) > -80) && items[i].sprite_id == NULL)
		{
			items[i].sprite_id = SpriteManagerAdd(items[i].type, items[i].x, items[i].y);
		}
		if ((INT16)(scroll_target->x - items[i].x) > 80 || (INT16)(scroll_target->x - items[i].x) < -80)
		{
			SpriteManagerRemoveSprite(items[i].sprite_id);
			items[i].sprite_id = NULL;
		}
	}
}
