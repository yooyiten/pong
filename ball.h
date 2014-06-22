#ifndef BALL_H
#define BALL_H

/*
 * ball.h:
 * 	header interface for ball.c, containing symbolic constant
 * 	definitions for ball attributes, ball struct definition, and
 * 	api function definitions
 */

#define BALL_SYMBOL	'o'	/* default symbol for drawing ball */
#define MAXNUM		6	/* maximum delay for the ball */

/* the ball object */
struct ball{
	int x_pos, y_pos,	/* the x and y position of the ball */
	    x_dir,		/* horizontal direction; +1 right, -1 left */
	    y_dir,		/* vertical direction; +1 down, -1 up */
  	    x_delay, y_delay,   /* delay before ball move */
	    x_count, y_count;   /* ticks left before move */
	char symbol;		/* the symbol used for drawing ball */
};

struct ball *init_ball();
void serve();
int ball_move();
void clear_ball();
void change_xdir(int);
void change_ydir(int);
void change_speed();

#endif	/* BALL_H */
