/* Intro paragraph:
 * countLiveNeighbor takes the input from update board and checks
 * the if its 8 neighbors are dead or alive, then returns the number of 
 * neighbors that are alive. updateBoard makes a copy of the current board and
 * iterates through every value in the original board and uses countLiveNeighbor 
 * to check whether or not the current value is dead or alive. Then updates the new
 * board with these values. a copy must be made because you can't keep checking the 
 * updated board as there might be additional cells surrounding the current one youre 
 * checking. aliveStable checks whether the updated board is the same as the original 
 * in order to avoid infinite loops. Returns 1 if the current board stays
 * the same for the next step. Otherwise return 0.
 *
 * partners: briolat2, kaylanw4
 */

/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */

int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    
    int alive = 0;
 
    //check the rows like you would a 2D array
    for(int checkRow = row-1; checkRow <= row+1; checkRow++){	//between former and latter row
        if(!(checkRow < 0 || checkRow >= boardRowSize)){
            for(int checkCol = col-1; checkCol <= col+1; checkCol++){	//between former and latter column
                if(!(checkCol < 0 || checkCol >= boardColSize || (checkRow == row && checkCol == col))){
                    int elementOnBoard = boardColSize * checkRow + checkCol;
                    int element = *(board + elementOnBoard);
                    if(element == 1){ //checks if cell is alive
                        alive++;
                    }
                }
            }
        }
    }
 
    return alive;    
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int counter;
	int currentboard[boardRowSize*boardColSize];
	int i,j;
	for(i=0; i<boardRowSize; i++){
		for(j=0; j<boardColSize; j++){
			currentboard[i*boardColSize+j]=*(board+i*boardColSize+j);	//duplicate board
		}
	}
	for(i=0; i<boardRowSize*boardColSize; i++){
		counter = countLiveNeighbor(currentboard, boardRowSize, boardColSize, i/boardColSize, i%boardColSize);
		if(counter<2 || counter>3){
			*(board+i)=0; //dead cell
		}
		else if(counter==3){
			*(board+i)=1; //live cell
		}
	}
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int nextboard[boardRowSize*boardColSize];
	for(int i=0; i<boardRowSize; i++){
		for(int j=0; j<boardColSize; j++){
			nextboard[i*boardColSize+j]=*(board+i*boardColSize+j);	//duplicate board
		}
	}
	updateBoard(nextboard, boardRowSize, boardColSize);				//update board
	for(int i=0; i<boardRowSize*boardColSize; i++){
		if(*(board+i) != nextboard[i]){
			return 0;												//change is detected
		}
	}
	return 1;														//no change is detected
}
