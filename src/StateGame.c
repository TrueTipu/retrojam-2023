#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
IMPORT_TILES(font);
IMPORT_MAP(mappinen);
IMPORT_MAP(hud);

UINT8 collision_tiles[] = {1, 2, 4, 5, 6, 0};

void START() {
	InitScroll(BANK(mappinen), &mappinen, collision_tiles, 0);

	INIT_HUD(hud);	

	scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);

	INIT_CONSOLE(font, 3);

	SpriteManagerAdd(SpriteItem, 70, 50);
		
	SpriteManagerAdd(SpriteKey, 70, 120);

	SpriteManagerAdd(SpriteDoor, 100, 104);


}

void UPDATE() {
}
