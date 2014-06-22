/* ball.c:
 * 	the pong ball and functions to initalize it, move it, and change
 * 	its speed
 */

#include	<stdio.h>
#include	<curses.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"ball.h"
#include	"pong.h"

static struct ball pball;	/* the ball */

/* initializes the ball and returns pointer to it */
struct ball *init_ball(){
	int winwidth = getwidth();
	int winheight = getheight();
	// random start speed
	int rand_x_delay, rand_y_delay = 0;
	while(rand_y_delay == 0 || rand_x_delay == 0){
		rand_y_delay = (rand() % MAXNUM);
		rand_x_delay = (rand() % MAXNUM);
	}
	// initialize ball attributes
	pball.x_pos = winwidth/2;	/* start from center of screen */
	pball.y_pos = winheight/2;
	pball.x_count = pball.x_delay = rand_x_delay;
	pball.y_count = pball.y_delay = rand_y_delay;
	pball.x_dir = pball.y_dir = 1;
	pball.symbol = BALL_SYMBOL;	
	return &pball;
}

/* decrements the ball's counters and moves the ball if they are zero 
 * 	returns 1 if ball moved, 0 if not
 */

int ball_move(){
	int y_cur, x_cur, moved;
	y_cur = pball.y_pos;	/* previous position */
	x_cur = pball.x_pos;
	moved = 0;

	if( --pball.y_count == 0 ){
		pball.y_pos += pball.y_dir ;	/* move	*/
		pball.y_count = pball.y_delay;	/* reset*/
		moved = 1;
	}
	if( --pball.x_count == 0 ){
		pball.x_pos += pball.x_dir ;	/* move	*/
		pball.x_count = pball.x_delay;	/* reset*/
		moved = 1;
	}
	if( moved ){
		mvaddch(y_cur, x_cur, BLANK);
		mvaddch(pball.y_pos, pball.x_pos, pball.symbol);
	}
	return moved;	
}

/* erases the ball */
void clear_ball(){
	mvaddch(pball.y_pos, pball.x_pos, BLANK);
}

/* serves the ball to initial position */
void serve(){
	mvaddch(pball.y_pos, pball.x_pos, pball.symbol);
}

/* change the x direction of the ball 
 * 	args: dir is the direction to change to
 */
void change_xdir(int dir){
	pball.x_dir = dir;
}

/* change the y direction of the ball
 * 	args: dir is the direction to change to
 */
void change_ydir(int dir){
	pball.y_dir = dir;
}

/* randomly change the speed of the ball */
void change_speed(){
	int rand_x_delay, rand_y_delay = 0;
	while(rand_y_delay == 0 || rand_x_delay == 0){
		rand_y_delay = (rand() % MAXNUM);
		rand_x_delay = (rand() % MAXNUM);
	}
	pball.x_count = pball.x_delay = rand_x_delay;
	pball.y_count = pball.y_delay = rand_y_delay;
}
