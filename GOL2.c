/********
This is a test file for game of life. Adjustments made here.
********/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file_utils.h"

/***********************************************************************
 * The following program is used to play the game of life which was given
 * a set amount of rules. Any live cell with fewer than two neighbors
 * (underpopulation). Any living cell with more than three neighbors
 * dies (overcrowding). Any live cell with two or more live neighbors
 * lives another generation. Any dead cell with exactly three living
 * neighbors become a live cell. I was givin the rule of having to have
 * dynamic data to use. Must have save and load functions.
 *
 * @author Sean Thomas
 * @version Game of Life
 * @date 2/12/2018
 **********************************************************************/

//#DEFINE row = 0; //global for row
//#DEFINE col = 0; //global for column

/*******************************************************************
	* This method will check the nearby rows and columns to see if
	* they contain life. If they do they will count how many are
	* there and return. Will later be used for the play method.
	*
	*@param board creates a multi dimension array to act as board.
	*@param r Counts nearby life on x axis.
	*@param c Counts nearby life on y axis.
	*@param row contains how many rows are in the array.
	*@param col contains how many columns are in the array.
	*@return count returns the number of life around current life.
******************************************************************/
int adjacent(char** board, int row, int col, int r, int c){
	int count = 0;
	for (r=0; r<=row; r++){
		for(c=0;c<=col; c++){
			if(board[r-1][c-1]==1) //bottom left
				count++;
			if(board[r-1][c]==1)   //mid left
				count++;
			if(board[r-1][c+1]==1) //top left
				count++;
			if(board[r][c-1]==1)   //bottom
				count++;
			if(board[r][c+1]==1)   //top
				count++;
			if(board[r+1][c-1]==1) //bottom right
				count++;
			if(board[r+1][c+1]==1) //bottom left
				count++;
		}
	}
	return count;
}

/*******************************************************************
	* Uses the rules that were defined in the introduction to play
	* the game.
	*
	*@param board creates a multi dimension array to act as board.
	*@param row contains how many rows are in the array.
	*@param col contains how many columns are in the array.
******************************************************************/
void play (char** board, int row, int col){
	int i, j, a;
	char** newboard;
	for (i=0; i<row; i++){
		for(j=0; j<col; j++){
			a = adjacent(board, row, col, i, j);
			if (a==2) //ignore
				newboard[i][j] = board[i][j];
			if (a==3) //new life
				newboard[i][j] = 1;
			if (a < 2) //dead (underpopulation)
				newboard[i][j] = 0;
			if (a > 3) //dead (overcrowding)
				newboard[i][j] = 0;
			for (i=0; i<row; i++){
				for (j=0; j < col; j++){
					board[i][j] = newboard[i][j];
				}
			}
		}
	}
}
/*******************************************************************
	* Prints the board for the user to see.
	*
	*@param board creates a multi dimension array to act as board.
	*@param row contains how many rows are in the array.
	*@param col contains how many columns are in the array.
******************************************************************/
void print (char** board, int row, int col){
	int i,j;

	for (j=0; j<col; j++){
		for(i=0; i<row; i++){
			printf("%c", board[i][j] ? 'x' : ' ');
		}
		printf("\n");
	}
}

//http://www.cs.utexas.edu/users/djimenez/utsa/cs1713-3/c/life.txt //used a lot
//https://aticleworld.com/dynamically-allocate-2d-array-c/ //array basics
/*******************************************************************
	* Main method to run the program. Takes multiple arguments
	* which include file, row, and column.
	*
	*@param argc Name of argument statement.
	*@param argv All following arguments.
	*@return 0 returns 0 to end without error.
******************************************************************/
int main(int argc, char** argv){
	printf("Welcome to the game of life!\n");
	char loop = 'y';
	char s = 's';
	char* buffer;
	char* filename;
	int filesize;
	
	if(loop !='y')
		loop = 'n';
	char *r = argv[0]; //in command life takes the first argument which is row size.
	char *c = argv[1]; //takes second argument which is column size.
	filename = argv[2]; //see if we need argv or argc 
	
	//convert char into ints
	int row = (int) r;
	int col = (int) c;
	
	char **board = NULL;
	char **readbuffer = NULL;

	int irow = 0;
	int icol = 0;
	board = (char **)malloc(row * sizeof(char*));
		
		
	filesize = read_file(filename, &buffer); //read file in

	//initialize board
	for (irow = 0; irow < row; irow++)
		board[irow] = (char *)malloc(col * sizeof(char));

	if(board[irow] == NULL) //no rows given return
		printf("no rows or columns were entered into command line");
		return 1;

	for (irow = 0; irow < row; irow++){
		for(icol = 0; icol < col; icol++){
			board[irow][icol] = 0; //create empty board with at the moment all dead.
		}
	}
	int count =0;
	while (count != (row * col)){
		for(int i =0; i < row; i++){
			for(int j = 0; j < col; j++){
				readbuffer[i][j] = buffer[count]; 
				count++;
			}
		}	
	}
	board = readbuffer;
	//initialize_board (board, row, col); //may not need, replaced with array call above.
	//read file
	print(board, irow, icol); //check if working, else try globals and see if that fixes.
	play(board, irow, icol);

	count =0;   //reset count
	while (count != (row * col)){
		for(int i =0; i < row; i++){
			for(int j = 0; j < col; j++){
				buffer[count] = readbuffer[i][j]; 
				count++;
			}
		}	
	}
	readbuffer = board;
	write_file(filename, buffer, filesize); //write file out
	
	free (board[irow]);
	free (board);
	
	printf("do you wish to play again? (y/n) ");
	scanf(" %c", &loop);
	if(loop !='y')
		loop = 'n';
	
	
	return 0;
}