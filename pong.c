#include	<stdio.h>
#include	<curses.h>
#include	<signal.h>
#include	<unistd.h>
#include	<stdlib.h>
#include	"pong.h"
#include	"alarmlib.h"
#include	"court.h"
#include	"ball.h"
#include	"paddle.h"

/* pong.c:
 * 	the main pong file which coordinates the objects in the game 
 * 	using signal handling
 */

static int balls_left;	/* number of remaining balls for play */
static int counter;	/* counter for calculating elapsed time */	
static int winheight;	/* height of the terminal window */
static int winwidth;	/* width of the terminal window */
static struct ball *pball;	/* pointer to the pong ball */

void set_up();
void wrap_up();
void init_pong();
int bounce_or_lose();
void print_balls();
void print_time();

int main()
{
	int	c;
	set_up();
	serve();
	while ( balls_left > 0 && (c = getch()) != 'Q' ){
		if(c == 'k' || c == 'm'){
			if(c == 'k'){ paddle_up(); }
			if(c == 'm'){ paddle_down(); }
			if(bounce_or_lose() != LOSE){
				move(LINES-1, COLS-1);	/* park cursor */
				refresh();
			}
			else{
				clear_ball();
				pball = init_ball();
				serve();
			}
		}
	}
	struct sigaction ignore_sa;	/* sigaction for ignoring SIGALRM */
	ignore_sa.sa_handler = SIG_IGN;
	sigemptyset(&ignore_sa.sa_mask);
	ignore_sa.sa_flags = 0;
	if(sigaction(SIGALRM, &ignore_sa, NULL) == -1){
		perror("Cannot set up sigaction for the ignoring SIGALRM");
		exit(1);
	}
	wrap_up();
	return 0;
}

/* initialize the pong components and curses */
void set_up()
{
	initscr();		/* turn on curses	*/
	noecho();		/* turn off echo	*/
	cbreak();		/* turn off buffering	*/

	balls_left = BALL_COUNT;	
	counter = 0;			
	getmaxyx(stdscr, winheight, winwidth);

	init_court();	/* initialize the court */
	init_paddle();	/* initialize the paddle */
	srand(getpid());
	pball = init_ball();	/* initialize and get pointer to  ball */
	init_pong();	/* initialize the game coordination */
	set_ticker( 1000 / TICKS_PER_SEC );	/* send millisecs per tick */
	print_balls();
	print_time();
}

/* returns the terminal window width */
int getwidth(){
	return winwidth;
}

/* returns the terminal window height */
int getheight(){
	return winheight;
}

/* prints the number of remaining balls in the game */
void print_balls(){
	char ballstat[14];
	move(2,MARGIN+1);
	sprintf(ballstat,"BALLS LEFT: %d",balls_left);
	addstr(ballstat);
	move(LINES-1, COLS-1);	/* park cursor */
	refresh();
}

/* prints the time elapsed in the game */
void print_time(){
	counter++;
	int time = counter / TICKS_PER_SEC;
	int mins = time / 60;
	int secs = time % 60;
	
	char totaltime[40];
	move(2,(winwidth/2 + MARGIN));
	sprintf(totaltime,"TOTAL TIME: %d:%02d", mins, secs);
	addstr(totaltime);
	move(LINES-1, COLS-1); /* park cursor */
	refresh();
}

/* initializes game coordination and signal handling 
 */
void init_pong(){
	struct sigaction ignore_sa;	/* sigaction for ignoring SIGINT */
	ignore_sa.sa_handler = SIG_IGN;
	sigemptyset(&ignore_sa.sa_mask);
	ignore_sa.sa_flags = 0;
	if(sigaction(SIGINT, &ignore_sa, NULL) == -1){
		perror("Cannot set up sigaction for the ignoring SIGINT");
		exit(1);
	}

	struct sigaction pong_sa; /* sigaction for coordinating pong objects */
	void update_game(int);	/* signal handler function */
	pong_sa.sa_handler = update_game;
	sigemptyset(&pong_sa.sa_mask);
	sigaddset(&pong_sa.sa_mask, SIGALRM); /* block SIGALRMS while in handler function */
	pong_sa.sa_flags = 0;
	if(sigaction(SIGALRM, &pong_sa, NULL) == -1){
		perror("Cannot set up sigaction for pong");
		exit(1);
	}
}

/* SIGALRM handler that coordinates the game components and updates as
 * needed
 */
void update_game(int s){
	print_time();
	if(ball_move() == 1){
		if(bounce_or_lose() != LOSE){
			move(LINES-1, COLS-1);	/* park cursor */
			refresh();
		}
		else{
			clear_ball();
			pball = init_ball();
			serve();
		}
	}
}

/* determines the action for the ball's position
 * 	if the ball contacts one of the three walls, it bounces
 * 	if the ball bounces against the paddle, modify the speed of the ball
 * 	if the ball sails past the paddle, take it out of play and serve
 * 	a new ball if any remain
 */
int bounce_or_lose(){
	int return_val = NO_CONTACT;

	if( (pball->x_pos == winwidth-MARGIN*2+2) ){
		balls_left--;
		print_balls();
		return_val = LOSE;
		return return_val;
	}
	else if(paddle_contact(pball->y_pos, pball->x_pos) == 1){
		change_xdir(-1);
		change_speed();
		return_val = BOUNCE;
		return return_val;
	}

	if ( pball->y_pos == MARGIN +1)
		change_ydir(1) , return_val = BOUNCE ;
	else if ( pball->y_pos == (winheight-MARGIN-1) )
		change_ydir(-1) , return_val = BOUNCE;

	if ( pball->x_pos == MARGIN +1)
		change_xdir(1) , return_val = BOUNCE ;

	return return_val;	
}

/* stop ticker and curses */
void wrap_up()
{
	set_ticker( 0 );
	endwin();		/* put back to normal */
}
