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
typedef struct {
	int x;
	int y;
	struct SnakeBody* next;
} Snake;

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
	printf("Head x: %d\n", snakeHead->x);
	printf("Head y: %d\n", snakeHead->y);
}

// This function takes a pointer to the head of snake and moves the snake in whatever way we determine
// By updating the x and y values of the snake.
// Currently it just moves the snake's head, but soon we will move the entire body.
void moveSnake(Snake* snakeHead, int changeX, int changeY) {
	snakeHead->x = snakeHead->x + changeX;
	snakeHead->y = snakeHead->y + changeY;
	getSnakeHeadPosition(snakeHead);
}

// When the snake eats a fruit (which totally makes sense since snakes love fruit),
// the body grows. 
void growSnake(Snake *head);
// This is a little tricky. Does the segment get added at the end of snake?
// Does this mean we should be tracking the last position of each body part of the snake?
// That way, when we get down to the tail, we just give it the coords of where the tail was
// last? I suppose that would work well. I'm going to think on it some more and see if I can
// find a better solution. (If we do this solution, we have to edit the move function);

// Free all memory and end the game.
void killSnake(Snake* head);

// Check for collisions
void checkSnakeCollision(Snake *head);

// draw Snake
void drawSnake(Snake *head);


//============== End of Snake Code ========================


/*
// Author: Cassidy
// Draws the board used in the game
void snakepit()
{
   int i;
   int j;
 
   initscr();
   clear();
 
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
  
   refresh();
   getch();
   endwin();
  
}

*/
 //main method
 // Right now I'm just testing Code. I will implement a game loop and everything later.
 // - Aidan :)
int main()    
{      
        // create the snake head as a pointer.
        Snake *head = snakeInit(10,12);     
        getSnakeHeadPosition(head);
	moveSnake(head, 1, 2);
        //snakepit();
	free(head);
        return 0;
}

