//CS 355
//Snake Game
//Cassidy, Tori, Darby, Aidan
 
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

int height = 30;
int width = 179;
 
void snakepit();

// =================== SNAKE CODE =========================
// Author: Aidan Daley

// This is the structure that the snake will be made of
// Each part of the body links to the next part of the body until you reach the tail.
typedef struct Snake {
	int x;
	int y;
	int lastX;
	int lastY;
	struct Snake* next;
} Snake; // not sure if this is actually needed...

// Initiates the snake onto the board at designated position.
Snake* snakeInit(int x, int y) {
	// Create the Snake head. Later we will add the body
	Snake *head = malloc(sizeof(Snake));	
	
	// Set position of the head on the game board.
	head->x = x;
	head->y = y;
	
	return head;
} // returns a memory address

// This function is primarily for testing purposes. It just gives the x and y of the head.
void getSnakeHeadPosition(Snake* snakeHead) {
	printf("Head x: %d, y: %d\n", snakeHead->x, snakeHead->y);
}

// For debugging purposes. Gives the coordinates of each body part of the snake
void printSnake(Snake* head) {
        printf("[x: %d, y: %d]\n", head->x, head->y);
        if (head->next != NULL)
                printSnake(head->next);

}


// This function takes a pointer to the head of snake and moves the snake in whatever way we determine
// By updating the x and y values of the snake.
// Currently it just moves the snake's head, but soon we will move the entire body.
void moveSnake(Snake* snakeHead, int changeX, int changeY) {
	
	// Updates the last position, this will be useful for growing the snake
	snakeHead->lastX = snakeHead->x;
	snakeHead->lastY = snakeHead->y;
	
	// Update the x and the y position
	snakeHead->x = snakeHead->x + changeX;
	snakeHead->y = snakeHead->y + changeY;
	
	// Debugging purposes. This just prints the head of the snake
	getSnakeHeadPosition(snakeHead);

}

// takes input from the user and moves the snake using the moveSnakeMethod.
void controlSnake(Snake* head) {
	getSnakeHeadPosition(head);
	switch (getch()) {         
          case KEY_UP:        
             moveSnake(head, -1,0); //snakeMove(head,x, y);
         break;
         case KEY_DOWN:
             moveSnake(head, 1,0);
         break;
         case KEY_LEFT:
	     moveSnake(head, 0,-1);
         break;                                        
         case KEY_RIGHT:         
             moveSnake(head, 0,1);       
         break;
	 case 'x':
	 endwin(); // close curses
	 break;
     }
}


// When the snake eats a fruit (which totally makes sense since snakes love fruit),
// the body grows. 
void growSnake(Snake *head) {
	Snake *temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	
	temp->next = snakeInit(temp->lastX, temp->lastY);
}
// This is a little tricky. Does the segment get added at the end of snake?
// Does this mean we should be tracking the last position of each body part of the snake?
// That way, when we get down to the tail, we just give it the coords of where the tail was
// last? I suppose that would work well. I'm going to think on it some more and see if I can
// find a better solution. (If we do this solution, we have to edit the move function);

// Free all memory and end the game.
void killSnake(Snake* head);

// Check for collisions
void checkSnakeCollision(Snake *head);

// draw Snake (CURRENTLY ONLY DRAWS HEAD OF SNAKE. COULD BE ISSUE WITH THIS FUNCTION OR GROWSNAKE()).
void drawSnake(Snake *head) {
	Snake *temp = head;
	printSnake(head);
	
	move(temp->x, temp->y);
	addstr("@");


	if (temp->next != NULL) {
		temp = temp->next;
	}
	refresh();
}
//============== End of Snake Code ========================


// Author: Cassidy
// Draws the board used in the game
void snakepit()
{
   int i;
   int j;
 
//   initscr(); // Moved to main loop
//   clear(); // Move to main loop
 
   for(i = 0; i < LINES; i++)
   {
       for(j = 0; j < COLS; j++)
       {
            move(i,j);
            if(i == 0 || i == LINES -1)
            {
                standout();
                addstr(" ");
            }
            if(j == 0 || j == COLS-1)
            {
                standout();
                addstr(" ");
            }
           
       }
   }
  
   refresh(); // Added to main 
   //getch();
   //endwin();
  
}


 //main method
 // Right now I'm just testing Code. I will implement a game loop and everything later.
 // - Aidan :)
int main()    
{      
	// ===================== Initializing Game ==========================
	initscr();
  	// create the snake head as a pointer.
	Snake *head = snakeInit(LINES/2, COLS/2);     
	growSnake(head);
	growSnake(head);
	growSnake(head);
	//printSnake(head);
	
	//clear(); // does this need to be moved to the game loop? I think so
 	noecho();
 	curs_set(0);
	//init_pair(1, COLOR_BLACK, COLOR_RED);
	keypad(stdscr, TRUE);

	// ========================= Game Loop ===============================

	while(1) {
		clear();
  		drawSnake(head);	
		snakepit();	
		controlSnake(head);	
		refresh();
	}
	//snakepit();
	endwin();
	free(head);
  	return 0;
}

