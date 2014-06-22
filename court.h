#ifndef COURT_H
#define COURT_H

/*
 * court.h:
 * 	header interface for court.c, containing symbolic constant 
 * 	definitions for court attributes, court struct definition, and
 * 	api function definitions
 */

#define HL_SYMBOL	'-'		/* default horizontal wall symbol */
#define VL_SYMBOL	'|'		/* default vertical wall symbol */

/* the court object */
struct court{
	int margin;		/* court border */
	char hsymbol;		/* the symbol used for horizontal walls */
	char vsymbol;		/* the symbol used for vertical wall */
};

void init_court();

#endif	/* COURT_H */
