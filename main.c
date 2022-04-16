// CS 355
// Snake Game
// Cassidy, Tori, Darby, Aidan
 
#include <stdlib.h>
#include <stdio.h>
#include <curses.h>

int height = 30;
int width = 179;
 
void snakepit();
// =================== SNAKE CODE =========================
// Author: Aidan Daley and Darby Scott

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
// Later this function will be changed and used for collision and fruit collection logic. 
// May need to be split into 2 functions.
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
void moveSnake(Snake* snakeHead, int newX, int newY) {
	
	// Updates the last position, this will be useful for growing the snake
	snakeHead->lastX = snakeHead->x;
	snakeHead->lastY = snakeHead->y;
	
	// Update the x and the y position
	snakeHead->x = newX;
	snakeHead->y = newY;

	// if we aren't at the tail of the snake, update the next body part.
	if (snakeHead->next != NULL)
		moveSnake(snakeHead->next, snakeHead->lastX, snakeHead->lastY);
}

// takes input from the user and moves the snake using the moveSnakeMethod.
// Author: Tori
int controlSnake(Snake* head) {
	// getch data type is char.
	switch (getch()) {         
          case KEY_UP:        
             moveSnake(head, head->x - 1,head->y + 0); 
         break;
         case KEY_DOWN:
             moveSnake(head, head->x + 1,head->y + 0);
         break;
         case KEY_LEFT:
	     moveSnake(head, head->x + 0,head->y + -1);
         break;                                        
         case KEY_RIGHT:         
             moveSnake(head, head->x + 0,head->y + 1);       
         break;
	 default:
	 	return 1;
	}
	return 0;
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

// Free all memory and end the game.
void killSnake(Snake* head) {
	Snake *temp = head;
	if (temp->next != NULL)
		temp = temp->next;
	free(temp);
}
// Check for collisions
void checkSnakeCollision(Snake *head);

// Draw Snake 
// Author: Tori
void drawSnake(Snake *head) {
	Snake *temp = head;
	
	move(temp->x, temp->y);
	addstr("@");

	// if there is more of the snake, draw the next part
	if (temp->next != NULL) {
		temp = temp->next;
		drawSnake(temp);
	}
}
//============== End of Snake Code ========================


// Author: Cassidy
// Draws the board used in the game
void snakepit()
{
   int i;
   int j;
 
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
  
}


 //main method
int main()    
{      
	// ===================== Initializing Game ==========================
	initscr();
  	// create the snake head as a pointer.
	Snake *head = snakeInit(LINES/2, COLS/2);     
	for (int i; i < 5; i++)
		growSnake(head);
	
 	noecho();
 	curs_set(0);
	keypad(stdscr, TRUE);

	// ========================= Game Loop ===============================
	while(1) {
		clear();
		snakepit();
		drawSnake(head);

		// if any key but the arrow keys are pressed, end the game.
		int keyInput = controlSnake(head);
        	if (keyInput == 1)
			break;
		refresh();
	}
	endwin();
	killSnake(head);
  	return 0;
}

