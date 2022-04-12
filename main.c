//CS 355
//Snake Game
//Cassidy, Tori, Darby, Aidan
 
#include <stdlib.h>
#include <stdio.h>
 
int height = 30;
int width = 179;
 
void snakepit();
 
//main method
int main()
{
   snakepit();
   return 0;
}
 
//Snakepit method which draws the border of the game
void snakepit()
{
   for(int i = 0; i <= height; i++){
       for(int j = 0; j <=width; j++){
           if(i == 0 || i == height){
               printf("=");
           }
           else if(j==0 || j==width){
               printf("|");
           }
           else {
               printf(" ");
           }
       }
       printf("\n");
   }
}
 
 
 

