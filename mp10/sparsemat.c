/* This program creates a sparse matrix with linked lists using the given matrices. 
 * The purpose of a sparse matrix is to save time and space by not storing the empty 
 * or 0 values within the large matrix.  The new matrices are heaped via malloc with 
 * the list of tuples being stored using a linked list.
 * partners: briolat2, kaylan4
 */
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
sp_tuples * load_tuples(char* input_file)
{
    int row = 0;
    int col = 0;
    double value = 0;
    int num_rows = 0;
    int num_cols = 0;
    FILE* fp;

    //open file
    fp = fopen(input_file, "r");


    //scans for row and col in file
    fscanf(fp, "%d %d", &num_rows, &num_cols);

    //allocating mem
    sp_tuples* tuples = (sp_tuples*)malloc(sizeof(sp_tuples));

    //initializing tuples
    tuples->m = num_rows;
    tuples->n = num_cols;
    tuples->nz = 0;


	//read file
    while(feof(fp) == 0)
    {
        fscanf(fp, "%d %d %lf\n", &row, &col, &value);
        set_tuples(tuples, row, col, value);
    }

    //close file
    fclose(fp);

    //return matrix
    return tuples;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node* curr_node = NULL;

    //sets the first node
    curr_node = mat_t->tuples_head;

	//checks every node to see if one matches row and col
    while(curr_node != NULL)
    {
        if(curr_node->row == row && curr_node->col == col)
        {
            return curr_node->value;
        }

        curr_node = curr_node->next;
    }

    return 0;
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    //several nodes used
    sp_tuples_node* new_node = NULL;
    sp_tuples_node* curr_node = NULL;
    sp_tuples_node* next_node = NULL;
    sp_tuples_node* prev_node = NULL;


	//checks to see if we need to remove node
    if(value != 0)
    {
        new_node = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
        new_node->row = row;
        new_node->col = col;
        new_node->value = value;
        new_node->next = NULL;
        mat_t->nz = mat_t->nz + 1;
    }




    //checks if there is only one head node and nothing else
    if( mat_t->tuples_head == NULL)
    {
        mat_t->tuples_head = new_node;
        return;
    }

    //inserts node
    curr_node = mat_t->tuples_head;
    prev_node = NULL;
    while(curr_node != NULL)
    {

         next_node = curr_node->next;

        //checks if same row and col
        if(curr_node->row == row && curr_node->col == col )
        {
            //checks if val is zero
            if( value == 0)
            {
                curr_node->next = NULL;
                free(curr_node);
                mat_t->nz = mat_t->nz - 1;
                curr_node = NULL;

                //checks if prev node is head node
                if( prev_node == NULL)
                {
                    mat_t->tuples_head = next_node;
                }
                else
                {
                    prev_node->next = next_node;
                }
				
                return;
            }
            else
            {

                curr_node->value = value;
                free(new_node);
                mat_t->nz = mat_t->nz -1;
                return;
            }


        }
        //makes sure col is greater
        else if(curr_node->row > row || (curr_node->row == row && curr_node->col > col) )
        {
            //inserts the node
            if(new_node != NULL)
            {
                new_node->next = curr_node;

                if( prev_node == NULL)
                {
                    mat_t->tuples_head = new_node;
                }
                else
                {
                    prev_node->next = new_node;
                }
            }

            return;
        }


        //end of the list
        if(next_node == NULL && new_node != NULL)
        {
            curr_node->next = new_node;
        }

        //next node is now current node
        prev_node = curr_node;
        curr_node = next_node;
        next_node = NULL;
    }

}




void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE* fp;
    sp_tuples_node* curr_node = NULL;

	//open file
    fp = fopen(file_name, "w");

    if( fp == NULL)
    {
        printf("invalid file\n");
        return;
    }
	
	//print matrix row and col
    fprintf(fp, "%d %d\n", mat_t->m, mat_t->n);

	//saves the data of each node
    curr_node = mat_t->tuples_head;

    while(curr_node != NULL)
    {
        fprintf(fp, "%d %d %lf\n", curr_node->row, curr_node->col, curr_node->value);
        curr_node = curr_node->next;
    }

    fclose(fp);
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    //Check if the matrices are compatible
    if( matA->m != matB->m || matA->n != matB->n)
    {
        return NULL;
    }

    sp_tuples* matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    sp_tuples_node*  curr_node = NULL;

    matC->m = matA->m;
    matC->n = matA->n;
    matC->nz = 0;
    matC->tuples_head = NULL;

    //traverse matrix a
    curr_node = matA->tuples_head;
    while(curr_node != NULL)
    {
        int r = curr_node->row;
        int c = curr_node->col;
        double valA = 0;

        valA = gv_tuples(matA, r, c);

        set_tuples(matC, r, c, valA);

        curr_node = curr_node->next;
    }

    //traverse matrix b
    curr_node = matB->tuples_head;
    while(curr_node != NULL)
    {
        int r = curr_node->row;
        int c = curr_node->col;
        double valB = 0;
        double valC = 0;

        valB = gv_tuples(matB, r, c);
        valC = gv_tuples(matC, r, c);

        valC = valB + valC;

        set_tuples(matC, r, c, valC);

        curr_node = curr_node->next;
    }

    return matC;
}


//OPTIONAL
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){
	return NULL;
}



void destroy_tuples(sp_tuples * mat_t)
{
    sp_tuples_node* curr_node = NULL;
    sp_tuples_node* del_node = NULL;

	//deletes every node
    curr_node = mat_t->tuples_head;

    while(curr_node != NULL)
    {
        del_node = curr_node;
        curr_node = curr_node->next;

        free(del_node);
    }
	
	//deletes matrix ptr
    free(mat_t);
}