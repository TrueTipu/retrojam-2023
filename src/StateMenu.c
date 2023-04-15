#include "Banks/SetAutoBank.h"
#include "main.h"


#include <gb/gb.h>
#include "ZGBMain.h"
#include "Scroll.h"
#include "Keys.h"
#include "Music.h"

IMPORT_MAP(credits);

void START() {
	INIT_BKG(credits);
}

void UPDATE() {
	if(KEY_TICKED(J_START)) {
		SetState(StateGame);
	}
}