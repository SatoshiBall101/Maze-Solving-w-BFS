/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h" // #include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// Add other prototypes here for any functions you wish to use

int is_valid(char** mymaze, int rows, int cols);


// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result;
    // int retval;

    int valid;

    char** mymaze=NULL;

    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }

    mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1

    if(mymaze == NULL){
      cout << "Couldnt read dimensions.";
      return 1;
    }

    // For checkpoint 2 you should check the validity of the maze
    // You may do so anywhere you please and can abstract that
    // operation with a function or however you like.

    valid = is_valid(mymaze, rows, cols); // will return 0 if maze is valid (1 or 2 if not)

    if(valid == 2)
    {
      cout << invalid_maze_message;

      for(int i = 0; i < rows; i++){
        delete[] mymaze[i]; // returning memory of "2D array"
      }

      delete[] mymaze;
      
      return 0;
    }
    
    if(valid == 1)
    {
      cout << invalid_char_message;

      for(int i = 0; i < rows; i++){
        delete[] mymaze[i]; // returning memory of "2D array"
      }

      delete[] mymaze;
      
      return 0;
    }

    result = maze_search(mymaze, rows, cols);

    if (result == 0)
    {
      cout << no_path_message;

      for(int i = 0; i < rows; i++){
        delete[] mymaze[i]; // returning memory of "2D array"
      }

      delete[] mymaze;
      
      return 0;
    }





    //================================
    // When working on Checkpoint 4, you will need to call maze_search
    // and output the appropriate message or, if successful, print
    // the maze.  But for Checkpoint 1, we print the maze, regardless.
    print_maze(mymaze, rows, cols);
    

    //================================
    // ADD CODE BELOW 
    // to delete all memory that read_maze allocated: CHECKPOINT 2

    for(int i = 0; i < rows; i++){
        delete[] mymaze[i]; // returning memory of "2D array"
    }

    delete[] mymaze;

    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
    // *** You complete **** CHECKPOINT 4

    bool found_f = false;

    int retval;

    bool** visited_array = new bool*[rows]; // dynamic allocation of "2D array" pt 1

    for(int i = 0; i < rows; i++){
        visited_array[i] = new bool[cols]; // dynamic allocation of "2D array" pt 2
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            visited_array[i][j] = false; // setting all elements to false (ie unvisited)
        }
    }

    Location** predecessor_array = new Location*[rows]; // dynamic allocation of "2D array" pt 1

    for(int i = 0; i < rows; i++){
        predecessor_array[i] = new Location[cols]; // dynamic allocation of "2D array" pt 2
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            predecessor_array[i][j].row = -1; 
            predecessor_array[i][j].col = -1; // setting all elements to (-1,-1) so we know if predecessor element is used or not 
        }
    }

    // lets begin by adding the S location to queue

    Queue q1(rows*cols); 

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if (maze[i][j] == 'S')
            {
              Location start;
              start.row = i; //something wrong here?
              start.col = j; 
              visited_array[i][j] = true; // mark start loc as explored
              q1.add_to_back(start); // add S location to back of queue
            }
        }
    }

    Location temp;

    while(!q1.is_empty() && found_f == false)
    {
      
      temp = q1.remove_from_front(); // extract item from queue front into temp location

      for(int i = 0; i < 4; i++)
      {
        if(i==0 && temp.row >= 1)
          { // we want to explore N first (ie same column, but row - 1)


              temp.row = temp.row - 1; // same col, -1 row = NORTH

              if(maze[temp.row][temp.col]!= '#' && visited_array[temp.row][temp.col] == false)
              {
                visited_array[temp.row][temp.col] = true; // it is now being explored
                q1.add_to_back(temp); // add this location to the back

                Location temp_predecessor; // make a temp loc to hold the predecessor

                temp_predecessor = temp;

                temp_predecessor.row = temp.row + 1; // make sure to go back to predecessor

                predecessor_array[temp.row][temp.col] = temp_predecessor; 

                if(maze[temp.row][temp.col] == 'F')
                {
                  found_f = true;
                  temp.row = temp.row + 1; // return temp to original location
                  break;
                }

              }

              temp.row = temp.row + 1; // return temp to original location

            
          }

          if(i==1 && temp.col >= 1)
          { // we want to explore W next (ie same row, but col - 1)


            temp.col = temp.col - 1; // same row, -1 col = WEST

            if(maze[temp.row][temp.col]!= '#' && visited_array[temp.row][temp.col] == false)
            {
              visited_array[temp.row][temp.col] = true; // it is now being explored
              q1.add_to_back(temp); // add this location to the back

              Location temp_predecessor; // make a temp loc to hold the predecessor

              temp_predecessor = temp;

              temp_predecessor.col = temp.col + 1; // make sure to go back to predecessor

              predecessor_array[temp.row][temp.col] = temp_predecessor; 

              if(maze[temp.row][temp.col] == 'F')
             {
              found_f = true;
              temp.col = temp.col + 1; // return temp to original location
              break;
             }
            }
            
            temp.col = temp.col + 1; // return temp to original location
          
        }

        if(i==2 && temp.row < rows - 1)
        { // we want to explore S next (ie same col, but row + 1)

          temp.row = temp.row + 1; // same col, +1 row = SOUTH

          if(maze[temp.row][temp.col]!= '#' && visited_array[temp.row][temp.col] == false)
          {
            visited_array[temp.row][temp.col] = true; // it is now being explored
            q1.add_to_back(temp); // add this location to the back

            Location temp_predecessor; // make a temp loc to hold the predecessor

            temp_predecessor = temp;

            temp_predecessor.row = temp.row - 1; // make sure to go back to predecessor

            predecessor_array[temp.row][temp.col] = temp_predecessor; 

            if(maze[temp.row][temp.col] == 'F')
            {
              found_f = true;
              temp.row = temp.row - 1; // return temp to original location
              break;
            }
          }
          temp.row = temp.row - 1; // return temp to original location
        }

        if(i==3 && temp.col < cols - 1)
        { // we want to explore E last (ie same row, but col + 1)

          temp.col = temp.col + 1; // same row, +1 col = EAST

          if(maze[temp.row][temp.col]!= '#' && visited_array[temp.row][temp.col] == false)
          {
            visited_array[temp.row][temp.col] = true; // it is now being explored
            q1.add_to_back(temp); // add this location to the back

            Location temp_predecessor; // make a temp loc to hold the predecessor

            temp_predecessor = temp;

            temp_predecessor.col = temp.col - 1; // make sure to go back to predecessor

            predecessor_array[temp.row][temp.col] = temp_predecessor;

            if(maze[temp.row][temp.col] == 'F')
             {
              found_f = true;
              temp.col = temp.col - 1; // return temp to original location
              break;
             } 
          }
          temp.col = temp.col - 1; // return temp to original location
        }
      }
  } 

  if(found_f == false)
  {
    retval = 0; // yikes! no path found
  }
  else if(found_f == true)
  {
    while(maze[temp.row][temp.col] != 'S')
    {
      maze[temp.row][temp.col] = '*';
      temp = predecessor_array[temp.row][temp.col];
    }

    retval = 1; // everything went okay
  }

  // deallocate memory 
  
  for(int i = 0; i < rows; i++){
        delete[] predecessor_array[i]; // returning memory of "2D array"
    }

    delete[] predecessor_array;

  for(int i = 0; i < rows; i++){
        delete[] visited_array[i]; // returning memory of "2D array"
    }

    delete[] visited_array;

  return retval;

}

int is_valid(char** mymaze, int rows, int cols){

  int S_counter = 0;
  int F_counter = 0;

  for(int i = 0; i < rows; i++)
  {
        for(int j = 0; j < cols; j++)
        {
            if (mymaze[i][j] == 'S')
            {
              S_counter++;
            } 
            if (mymaze[i][j] == 'F')
            {
              F_counter++;
            } 
            if (mymaze[i][j] != '.' && mymaze[i][j] != 'F' && mymaze[i][j] != 'S' && mymaze[i][j] != '#')
            {
              return 1; // 1 if invalid char used
            }
        }
  }

        if (S_counter == 1 && F_counter == 1)
        {
          return 0; // 0 if valid
        }
        else
        {
          return 2; // 2 if maze has more than 1 'S' and/or 'F'            
        }
}

