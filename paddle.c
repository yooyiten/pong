/* paddle.c:
 * 	the pong paddle and functions to initalize it, move it, and determine
 * 	its location
 */

#include	<stdio.h>
#include	<curses.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"paddle.h"
#include	"pong.h"

static struct paddle ppaddle;	/* the paddle */

/* initializes the paddle */
void init_paddle(){
	int winheight = getheight();
	int winwidth = getwidth();
	// initialize paddle attributes
	ppaddle.top = MARGIN + 1;
	ppaddle.height = (winheight-MARGIN*2)/3;
	ppaddle.bottom = ppaddle.top + ppaddle.height;
	ppaddle.col = winwidth-MARGIN*2+2;
	ppaddle.symbol = PADDLE_SYMBOL;
	mvwvline(stdscr, ppaddle.top, ppaddle.col, ppaddle.symbol,
		 ppaddle.height);
	refresh();
	return;
}

/* moves the paddle up one unit */
void paddle_up(){
	int new_top, new_bottom;
	new_top = ppaddle.top - 1;
	new_bottom = ppaddle.bottom - 1;

	if(new_top >= MARGIN + 1){
		mvwvline(stdscr,ppaddle.top, ppaddle.col, BLANK,
			 ppaddle.height);
		mvwvline(stdscr,new_top, ppaddle.col, ppaddle.symbol,
			 ppaddle.height);
		move(LINES-1, COLS-1);	/* park cursor */
		refresh();
		ppaddle.top = new_top;
		ppaddle.bottom = new_bottom;
	}
}

/* moves the paddle down one unit */
void paddle_down(){
	int winheight = getheight();
	int new_top, new_bottom;
	new_top = ppaddle.top + 1;
	new_bottom = ppaddle.bottom + 1;

	if(new_bottom <= winheight-MARGIN){
		mvwvline(stdscr,ppaddle.top,ppaddle.col, BLANK,
			 ppaddle.height);
		mvwvline(stdscr,new_top,ppaddle.col,ppaddle.symbol,
			 ppaddle.height);
		move(LINES-1, COLS-1);	/* park cursor */
		refresh();
		ppaddle.top = new_top;
		ppaddle.bottom = new_bottom;
	} 
}

/* checks whether the ball has touched the paddle
 * 	args: y is y-coordinate of ball
 * 	      x is x-coordinate of ball
 *	returns 1 if contact, 0 if not
 */
int paddle_contact(int y,int x){
	if( (x == ppaddle.col-1) && 
	    (y >= ppaddle.top && y <= ppaddle.bottom) ){
		return 1;
	}
	else{
		return 0;
	}
}
