#ifndef PONG_H
#define PONG_H

/*
 * pong.h:
 * 	header interface for pong, containing symbolic constant definitions
 * 	for the game and api function definitions
 */

#define	BLANK		' '	/* blank used for redrawing */
#define	TICKS_PER_SEC	50	/* affects speed */

#define	BALL_COUNT	3	/* number of plays for the ball */
#define BOUNCE		1	/* ball bounces against walls or paddle */
#define NO_CONTACT	0	/* ball does not touch paddle */
#define LOSE		-1	/* ball exits court */

#define MARGIN		3	/* the court border */

int getheight();
int getwidth();

#endif	/* PONG_H */
