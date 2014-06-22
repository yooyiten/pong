/* court.c:
 * 	the pong playing court and the functions to initialize and draw it
 */

#include	<stdio.h>
#include	<curses.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"court.h"
#include	"pong.h"

static struct court pcourt;	/* the court */

void walls_draw();

/* initializes the court */
void init_court(){
	// initialize court attributes
	pcourt.margin = MARGIN;
	pcourt.hsymbol = HL_SYMBOL;
	pcourt.vsymbol = VL_SYMBOL;
	walls_draw();
	return;
}

/* draw the three walls of the court */
void walls_draw(){
	int winheight = getheight();
	int winwidth = getwidth();
	int rightedge = winwidth-pcourt.margin*2; /* right edge of court */
	int bottomedge = winheight-pcourt.margin*2-1; /* bottom edge of court */
	
	clear();
	// draw top and bottom court lines
	mvwhline(stdscr, pcourt.margin, pcourt.margin, 
		 pcourt.hsymbol, rightedge);
	mvwhline(stdscr, winheight-pcourt.margin, pcourt.margin, 
		 pcourt.hsymbol, rightedge);
	// draw left court line
	mvwvline(stdscr, pcourt.margin+1, pcourt.margin, pcourt.vsymbol, 
		 bottomedge);
	refresh();
	return;
}
