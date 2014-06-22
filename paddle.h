#ifndef PADDLE_H
#define PADDLE_H

/*
 * paddle.h:
 * 	header interface for paddle.c, containing symbolic constant
 * 	definitions for paddle attributes, paddle struct definition, and
 * 	api function definitions
 */

#define PADDLE_SYMBOL '#'	/* default symbol used for paddle */

/* the paddle object */
struct paddle{
	int top, bottom,	/* top and bottom y coordinates */
	    col,		/* x coordinate */
	    height;		/* height of paddle */
	char symbol;		/* the symbol used for the paddle */	
};

void init_paddle();
void paddle_up();
void paddle_down();
int paddle_contact(int,int);

#endif	/* PADDLE_H */
