#include "sudoku.h"

/* In this program, we have created a Sudoku puzzle solver
 * through recursive backtracking. This was done by first 
 * checking if the suggested value was valid to place in the
 * selected unassigned cell. This was done through the function
 * is_val_valid, which checks if any values were repetitive in its
 * repestive rows, columns, and 3x3 zones. Next, you would 
 * recursively continue solving in order to make sure later values 
 * are valid.
 * partners: briolat2, kaylanw4
 */

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  for(int temp=0; temp<9; temp++){	//loop through rows
	  if(sudoku[i][temp]==val){		//checks if val is present at row
		  return 1;
	  }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int temp=0; temp<9; temp++){	//loop through columns
	  if(sudoku[temp][j]==val){		//checks if val is present in column
		  return 1;
	  }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int startrow = (i/3)*3;	//sets top left corner of 3x3 zone as starting point
  int startcol = (j/3)*3;
  for(int x=0;x<3;x++){		//loops to cycle through the 3x3 zone
	  for(int y=0;y<3;y++){
		if(sudoku[startrow+x][startcol+y]==val){	//checks if value exist in 3x3 zone
			return 1;
		}
	  }
  }
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  if(is_val_in_row(val, i, sudoku)==1){
	  return 0;
  }
  else if(is_val_in_col(val, j, sudoku)==1){
	  return 0;
  }
  else if(is_val_in_3x3_zone(val, i, j, sudoku)==1){
	  return 0;
  }
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j;
  bool filled=true;
  for(i=0; i<9; i++){			//checks if all cells are assigned by numbers
	  for(j=0; j<9; j++){
		  if(sudoku[i][j]==0){
			  filled=false;
			  break;
		  }
	  }
	  if(!filled){
		  break;
	  }
  }
  if(filled){					//if all cells are assigned, puzzle is solved
	  return true;
  }
   
  for (int num = 1; num <= 9; num++) {		//tests number 1-9 for unassigned cell
    if (is_val_valid(num, i, j, sudoku)) { 
      sudoku[i][j] = num; 
      if (solve_sudoku(sudoku)) {			//continues sudoku puzzle after solving previous unassigned cell
        return true;
      }
      sudoku[i][j] = 0; 					//sets cell to zero if value doesn't work
    }
  }
  return false;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





