/*
mazeio.cpp
*/

#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

/*************************************************
 * read_maze:
 * Read the maze from the given filename into a
 *  2D dynamically  allocated array.
 *
 * Return the pointer to that array.
 * Return NULL (a special address) if there is a problem,
 * opening the file or reading in the integer sizes.
 *
 * The first argument is the filename of the maze input.
 *  You should use an ifstream to open and read from this
 *  file.
 *
 * We also pass in two pointers to integers. These are
 * output parameters (i.e. declared by the caller and
 * passed-by-reference for this function to fill in).
 * Fill the integers pointed to by these arguments
 * with the number of rows and columns
 * read (the first two input values).
 *
 *************************************************/
char** read_maze(char* filename, int* rows, int* cols) 
{
    // *** You complete **** CHECKPOINT 1

   ifstream mazefile(filename);

   mazefile >> *rows >> *cols; // read in dim from file

   if(mazefile.fail()){
        return NULL; // if there was a problem reading dim, it will not proceed
    }

    char** maze_array = new char*[*rows]; // dynamic allocation of "2D array" pt 1

    for(int i = 0; i < *rows; i++){
        maze_array[i] = new char[*cols]; // dynamic allocation of "2D array" pt 2
    }

    // now that we have created a 2D array, we will read the maze into it using ifstream

    for(int i = 0; i < *rows; i++){
        for(int j = 0; j < *cols; j++){
            mazefile >> maze_array[i][j];
        }
    }

    return maze_array;
}

/*************************************************
 * Print the maze contents to the screen in the
 * same format as the input (rows and columns, then
 * the maze character grid).
 *************************************************/
void print_maze(char** maze, int rows, int cols)
{
    // *** You complete **** CHECKPOINT 1

    cout << rows << " " << cols << endl; // first print maze dimensions as seen in maze# files

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << maze[i][j]; // loop through maze array to print out values
        }
        cout << endl; // ensure each row starts on a newline
    }
}

