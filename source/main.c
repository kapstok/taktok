#include "gba_macros.h"
#include "gba_types.h"
#include "gba_bios.h"
#include "gba_gfx.h"
#include "gba_drawing.h"
#include "gba_mathUtil.h"
#include "gba_input.h"

//include the header file for the bitmap image
#include "test.h"

#include <string.h>

void copyBitmapToPageLocation( u16* a_vidPage, const u16* bitmap, s16 w, s16 h, s16 x, s16 y);

u16* vid_page = vid_page_back;

u16* page_flip() {
	vid_page = (u16*)((u32)vid_page ^ VRAM_PAGE_SIZE);
	REG_DISPCNT ^= VIDEO_PAGE;	// update control register	
	return vid_page;
}

int main() {
	register_vblank_isr();
	s16 height = 90;
	s16 width = 70;

	//copy colour palette into memory
	memcpy(MEM_PALETTE, testPal, testPalLen);
	//set background memory to palette colour 1. Fill screen with white.
	// memset(vid_page_front, img_mario_walk_1Bitmap[0], SCREEN_W * SCREEN_H);
	// memset(vid_page_back, img_mario_walk_1Bitmap[0], SCREEN_W * SCREEN_H);
	
	//set GBA rendering context to MODE 3 Bitmap Rendering
	REG_DISPCNT = VIDEOMODE_4 | BGMODE_2;

	copyBitmapToPageLocation( vid_page_front, testBitmap, width, height, 10, 10);
	s8 keyFrame = 0;
	while (1) {
		vblank_intr_wait();

		PollKeys();

		if(keyPressed(A)) {
			page_flip();
		}
		
	}
	
	return 0;
}

//Function to copy bitmap data to screen based on width and height
void copyBitmapToPageLocation( u16* a_vidPage, const u16* bitmap, s16 w, s16 h, s16 x, s16 y) {
	u16 screenLocation = 0;
	u16 bitmapLocation = 0;

	for( s16 i = 0; i < h; ++i ) {
		screenLocation =  (y + i) * 120 + x; 
		bitmapLocation = (i * w>>1)+i;

		memcpy( &a_vidPage[screenLocation], &bitmap[bitmapLocation], w);
	}
}