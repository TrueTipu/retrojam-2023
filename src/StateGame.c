#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
IMPORT_TILES(font);
IMPORT_MAP(map);
UINT8 collision_tiles[] = {1, 0};

void START() {
	scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	SpriteManagerAdd(SpriteItem, 70, 50);

	InitScroll(BANK(map), &map, collision_tiles, 0);
	
	INIT_CONSOLE(font, 3);
}

void UPDATE() {
}
