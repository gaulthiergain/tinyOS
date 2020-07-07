#include "fb.h"
#include "io.h"

static struct framebuffer *fb 		=	{0};
static unsigned char curr_color 	=	FB_BLACK | FB_WHITE;
static unsigned short cursor_idx 	=	0;


static void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg){
	fb[i].c = c;
	fb[i].colors = (((fg & 0x0F) << 4) | (bg & 0x0F)); 
}

static void fb_move_cursor(unsigned char pos){
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_CMD);
	outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_CMD);
	outb(FB_DATA_PORT, pos & 0x00FF);
}

void fb_init(void){
	fb = (struct framebuffer *) 0x000B8000;
}

void fb_clean_screen(void){
	unsigned int i;
	unsigned char buf[] = " ";
	fb_move_cursor(0);
	for (i = 0; i < FB_NUM_CELLS; ++i){
		fb_write_cell(cursor_idx, buf[0], FB_BLACK, FB_WHITE);
		cursor_idx++;
	}
	cursor_idx = 0;
	fb_move_cursor(cursor_idx);
}

void fb_change_color(unsigned char fg, unsigned char bg){
	curr_color &= (fg | bg);
}

void fb_write(unsigned char *buf, unsigned short len){
	unsigned int i;
	unsigned char fg = curr_color & 0xF0;
	unsigned char bg = curr_color & 0x0F;
	for (i = 0; i < len; ++i){
		fb_write_cell(cursor_idx, buf[i], fg, bg);
		cursor_idx = (cursor_idx + 1) % FB_NUM_CELLS;
	}
	fb_move_cursor(cursor_idx - 1);
}
