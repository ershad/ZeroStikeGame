/*
 * main.cpp
 * This file is part of ZeroStrikeGame
 *
 * Copyright (C) 2010 - Ershad K <ershad92@gmail.com>
 *
 * ZeroStrikeGame is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * ZeroStrikeGame is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ZeroStrikeGame; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, 
 * Boston, MA  02110-1301  USA
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

char board[10][10];

int lines = 10; //************* <--
int maximumCircles;
int userScore = 0;
int compScore = 0;
int user = 0;
int computer = 1;

int lastPlayed; // 0 for man and 1 for computer

char cDefault = 'O';
char cUser = 'x';
char cComputer = '@';
char cStriked = '#';
char compMove[3]; //***************** <---

void drawBoard_init(); 
int maxCircles();
void printBoard();
void markOnBoard(char input[], char cChar);
void checkMove();
void compPlay(); // very important, the AI part...

int main()
{
  char point[4];
  // cout << "Number of lines : ";
  // cin >> lines;
  drawBoard_init();
  cout << "Maximum number of circles : " << maximumCircles; 
  cout << "\n\n";

  do 
    {	  
      cout << "\n Enter co-ordinates : ";
      cin >> point;

      markOnBoard(point,cUser); // char[], char
      lastPlayed = user;
      checkMove();
      printBoard();
  	
      compPlay();  	
      markOnBoard(compMove,cComputer);
      lastPlayed = computer;
      checkMove();
      printBoard();
  
      cout << "\n Your score: " << userScore << "     Comp's Score:" << compScore;
  	
  
    } while (point[0] != 'n');
  
  return 0;
}

void compPlay()
{
  int i;
  int j;
  int hSmallest = 60;
  int zeroCount = 0;
  int temp;
	
  int xMoveH; //must be a number <= 10
  int yMoveH; //must be an alphabet <= j
	
	
  //Let's find the most-marked row; + most-marked column
	
  for (i = 0; i < lines; i++)
    {
      zeroCount = 1;
      for (j = 0; j < i; j++)
	{
		
	  if (board[i][j] != cStriked)
	    {  		
	      if (board[i][j] == cDefault)
		{
		  zeroCount++;
		  temp = zeroCount;
		}
	    }
	}
		
      if (temp < hSmallest)
	{
	  hSmallest = temp;
	  xMoveH = j;
	  yMoveH = i;
	}
	      

    }

  compMove[0] = yMoveH + 97;
  compMove[1] = xMoveH + 49;
  compMove[2] = '\0';

  cout << " \n compMove = " << compMove << endl;
	
}


void checkMove()
{
  /*****************************************************************************
	The program should check in horizontal and vertical directions for fully
	marked circles. 
	
	If found once, make it some other chars, like
	O
	@ O 
	O x #
	O O # O
	# # # #
 	O O # O O O
  *****************************************************************************/
	
  int i;
  int j;
  int k;
  int tempScore;
  int hFlag = 0;
  int vFlag = 0;
	
  /****************************************************************************
		Horizontal check...	
  *****************************************************************************/
  for (i = 0; i < lines; i++)
    {
      hFlag = 0;
      for (j = 0; j <= i; j++)
	{
	  if ( (board[i][j] == cDefault) || (board[i][j] == cStriked))
	    {
	      hFlag = 1;
	      break;
	    }
	}
		
      if (hFlag == 0)
	{
	  tempScore = i + 1;
	  if (lastPlayed == user)
	    userScore = userScore + tempScore;
	  else if (lastPlayed == computer)
	    compScore = compScore + tempScore;
				
	  for (k = 0; k <= i; k++)
	    board[i][k] = cStriked;	
	}
    }
	
  /*****************************************************************************
		Vertical check...
  *****************************************************************************/
	
  for (j = 0 ; j < lines; j++)
    {
      vFlag = 0;
      for (i = j; i < lines; i++)
	{
	  if ( (board[i][j] == cDefault) || (board[i][j] == cStriked))
	    {
	      vFlag = 1;
	      break;
	    }
	}
			
      if (vFlag == 0)
	{
	  tempScore = 10 - j;
				
	  if (lastPlayed == user)
	    userScore = userScore + tempScore;
	  else if (lastPlayed == computer)
	    compScore = compScore + tempScore;
					
	  for (k = j; k < lines; k++)
	    board[k][j] = cStriked;	
	}
    }
	
  cout << "\n Score = " << userScore << "\n"; //Debug
}

void markOnBoard(char input[], char cChar)
{
  int y;
  int x;
	
  char ctemp[3];
  ctemp[0] = input[1];
  ctemp[1] = input[2];
  ctemp[2] = '\0';
	
  x = atoi(ctemp) - 1 ;
	
  y = input[0] - 97;

  //x = input[1] - 49;	
  //if (input[2] == '0')
  //	x = 9;
		
  if ( (x > 9) || (input[0] > 'j') || (x > y) || board[y][x] != cDefault)
    cout << "\n *** Invalid co-ordinate/marking, try again! ***\n\n";
  else
    {
      board[y][x] = cChar;
      cout << "\n  y = " << y << "  x = " << x << "\n\n"; 
    }
}

void printBoard()
{
  int i;
  int k;
  char count = 'a';
	
  for ( i = 0; i < lines; i++) 
    {
      cout << "\t";
      cout << count++ << " |";
		
      for (int j = 0; j <= i; j++)
	{
	  cout << board[i][j] << " ";
	}
      cout << endl;
    }
	
  cout << "\t";
  cout << "   ";
  for ( k = 0; k < i; k++)
    cout << "- ";
		
  cout << endl;
		
  cout << "\t";
  cout << "   ";
  for (k = 0; k < i; k++)
    cout << k+1 << " ";
}

int maxCircles ()
{
  int maxValue;
  maxValue = (lines  * (lines + 1 ) ) / 2;
  return maxValue;
}

void drawBoard_init()
{
  int i;
  int k;
  char count = 'a';
	
  for ( i = 0; i < lines; i++) 
    {
      cout << "\t";

      cout << count++ << " |";
		

      for (int j = 0; j <= i; j++)
	{
	  board[i][j] = cDefault;
			
	  cout << cDefault << " ";
	}
      cout << endl;
    }
	
  cout << "\t";
  cout << "   ";
  for ( k = 0; k < i; k++)
    cout << "- ";
		
  cout << endl;
		
  cout << "\t";
  cout << "   ";
  for (k = 0; k < i; k++)
    cout << k+1 << " ";
	
  maximumCircles = maxCircles();
}
