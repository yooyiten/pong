---
Course: CSCI E-28, Unix Systems Programming
Assignment: pong
Author: Yoora Yi Tenen
---

    Purpose: 
      Implements a one-player version of pong using a three-sided court 
      and one paddle, utilizing signal handling.

    Outline:
      pong takes an object-oriented approach and defines the ball, court,
      paddle, and ticker functionalities in separate files. The pong file
      is the main file and coordinates these components of the game, as well
      as keeping track of remaining balls and elapsed time. The bounce2d
      example from class is used as the starting point, and alarmlib is
      used without modification.
  
      pong begins by turning on curses, turning off echo and buffering, 
      and getting the size of the terminal window. The objects of the game 
      are initialized: the three walls of the court and the paddle are drawn as
      determined by the size of the terminal window, the ticker is started, 
      and the ball is set with a random speed and a pointer to the ball is 
      returned to pong.
  	
      Two sigactions are also set up, one for ignoring SIGINT, and one for
      updating the game in response to SIGALRM. The signal handler for 
      SIGALRM calls the functions to print the elapsed time, move the ball,
      and determine if the ball bounces or is taken out of play.
      
      The player can move the paddle up or down by pressing the 'k' or 'm'
      key respectively. Whenever the paddle is moved, the function to
      determine if the ball ounces or is taken out of play is again called.
      
      The player can exit the game by entering the 'Q' character, and the 
      game automatically exits if there are no remaining balls for play.
      In either case, a sigaction is set up to ignore SIGALRM, and ticker
      and curses are stopped before exiting. 

    Output:
      The pong court has three walls, with the remaining balls and elapsed
      time displayed above the top wall. The paddle can be moved up and down
      on the right wall-less side of the court. The ball bounces against
      the walls and paddle. The game continues until all the available balls
      are used and no other output is displayed to the user.

    Input:
      pong accepts as user input the following characters:
    
        'k' to move the paddle up a unit
        'm' to move the paddle down a unit.
        'Q' to exit the game

    Data Structures:
      pong uses the sigaction struct as part of the sigaction method of
      signal handling. Structs are defined for the ball, court, and paddle 
      components.
      	
      The ball struct contains members to hold the x and y position,
      the horizontal and vertical directions, the delay before move,
      ticks remaining before move, and the symbol to draw the ball. A
      pointer to this struct is returned to pong for the functionality
      which determines the action to take based on the ball's position.
      
      The court struct contains members to hold the margin for the court
      and the symbols used to draw the horizontal walls and the vertical
      wall.
      
      The paddle struct contains members to hold the top and bottom
      coordinates, the x coordinate, and the height of the paddle.
