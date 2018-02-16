//https://stackoverflow.com/questions/42033932/c-program-to-reverse-conten
//t-of-a-file-and-write-that-to-another-file
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file_utils.h"

/*******************************************************************
	* Method used to open and read information from file.
	* 
	*@param filename Takes filename.
	*@param buffer pointer of a pointer to take each element at a time.
	*@return size returns size of file.
******************************************************************/
int read_file( char* filename, char **buffer ){
	FILE* file;
	file = fopen(filename, "r");
	
	struct stat st;
	stat(filename, &st);
	int size = st.st_size;
	
	*buffer = malloc(size);
	fread(*buffer, 1, size, file);
	return size;
}

/*******************************************************************
	* Method used to write and close information from file. 
	* 
	*@param filename Takes filename.
	*@param buffer pointer of a pointer to take each element at a time.
	*@return 1 returns true is successful.
******************************************************************/
int write_file(char* filename, char*buffer, int size) {
     FILE* file;
     file = fopen(filename, "w");
      for (int k = size - 1; k >= 0; k--) {
         char *x = buffer + k;
         fprintf(file, "%s", x);
     }
     return 1;
}