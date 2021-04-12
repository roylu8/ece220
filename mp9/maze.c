#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

/*
Intro paragraph:
This program solves a given maze using recursive depth-first search.
First two numbers in the given text file are the height and width, then 
the structure of the maze. '%' are walls in the maze and a space represents
empty cells. 'S' and 'E' are the start and end of the maze respectively.

partners: briolat2, kaylanw4
*/

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
	int i, j;												//variables for loops
    FILE *file=fopen(fileName, "r");						//opens file
	maze_t *maze=malloc(sizeof(maze_t));					//allocates memory for struct
	fscanf(file, "%d %d\n", &maze->width, &maze->height);
	char **cells=malloc(maze->height*sizeof(char*));		//allocates memory for each row
	for(i=0; i<maze->height; i++){							//allocates memory for each cell of each row
		cells[i]=malloc(maze->width*sizeof(char));
	}
	for(i=0; i<maze->height; i++){							//duplicate the maze
		for(j=0; j<maze->width; j++){
			fscanf(file, "%c", &cells[i][j]);				//scans for each element within the maze
			if(cells[i][j]=='\n'){							//discards new line
				j--;
			}
			if(cells[i][j]=='S'){							//sets start of maze
				maze->startRow=i;
				maze->startColumn=j;
			}
			if(cells[i][j]=='E'){							//sets end of maze
				maze->endRow=i;
				maze->endColumn=j;
			}
		}
	}
	maze->cells = cells;									//fills struct
	fclose(file);
	return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
	int i;
    for(i=0; i<maze->height; i++){		//frees all mallocs
		free(maze->cells[i]);
	}
	
	free(maze->cells);
	free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    printf("%d %d\n", maze->width, maze->height);	//prints size of maze
	char **mazeRow=maze->cells;						//creates pointer to each row of maze
	int i;
	for(i=0; i<maze->height; i++){					//loops through each row and prints
		printf("%s\n", mazeRow[i]);
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
    if(col<0 || col>=maze->width || row<0 || row>=maze->height){		//base case testing if we are within maze
		return 0;
	}
    if(maze->cells[row][col]=='%' || maze->cells[row][col]=='*' 
	|| maze->cells[row][col]=='~') {									//base case testing if cell is empty
        return 0;
    }
	if(maze->cells[row][col]=='E'){										//base case testing if we are at the end
		maze->cells[maze->startRow][maze->startColumn]='S';
		return 1;
	}
	maze->cells[row][col]='*';											//marks cell as part of the path if passed base cases
	
	if(solveMazeDFS(maze,col-1,row)==1){								//tries finding an available path
		return 1;
	}
    if(solveMazeDFS(maze,col+1,row)==1){
		return 1;
	}
    if(solveMazeDFS(maze,col,row+1)==1){
		return 1;
	}
    if(solveMazeDFS(maze,col,row-1)==1){
		return 1;
	}
	
	maze->cells[row][col]='~';											//nonworking path
	
    return 0;
}
