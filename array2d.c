//
//  array2d.c
//  
//
//  Created by Yifan Gu on 10/19/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array2d.h"

Array2dPtr AllocateArray2d(int row, int col, int datasize){
    
    if(row<0 || col<0 || datasize<0){
        return NULL;
    }

    Array2dPtr arr;
    arr = (Array2dPtr)malloc(sizeof(Array2d));
    
    if(arr == NULL){
        return NULL;
    }
    
    arr->storage = malloc(row * col * datasize);
    
    arr->row = row;
    arr->col = col;
    return arr;
}


bool FillArray2d(Array2dPtr arr, int index_r, int index_c, void* data){
    //check for index 
    if(index_r < 0 || index_c < 0){
        return false;
    }
    if(index_r >= arr->row || index_c >= arr->col){
        printf("FILL ARRAY out of boundary, do nothing, error index passed (%d, %d)...\n", index_r,index_c);
        return false;
    }
    
    //check for null 
    if (arr == NULL || data == NULL){
        printf("FILL ARRAY NULL para");
        return false;
    }
    
    // printf("FILL ARRAY TEST..filling index...[%d], [%d]-----", index_r, index_c);
    //  printf("offset is %d  END\n", arr->col * index_r + index_c);        //!!!bug fix  arr->col
    *(arr->storage + arr->col * index_r + index_c) = data;

    return true;
}


bool Swap(Array2dPtr arr, 
    int from_row, int from_col, int to_row, int to_col){

    //check for index
    if(from_col >= arr->col || from_row >= arr->row ||
         to_col >= arr->col || to_row>= arr->row ||
         from_col<0 || from_col<0 || to_col<0 || to_row<0){
        printf("SWAP opreation out of boundary, do nothing\n");
        return false;
    }
    
    if (arr==NULL){
        return false;
    }
    
    //store values in temp variables and fill array
    int COL = arr->col;
    void* from = *(arr->storage + COL*from_row + from_col);
    void* to = *(arr->storage + COL*to_row + to_col);

    FillArray2d (arr, from_row, from_col, to);
    FillArray2d (arr, to_row, to_col, from);


    //old ...
    // int* to = *(arr->storage + (arr->col)*to_row + to_col);
    // int* temp = *(arr->storage + (arr->col)*from_row + from_col); //from 
    // *(arr->storage + (arr->col)*from_row + from_col) = to;
    // *(arr->storage + (arr->col)*to_row + to_col) = temp;
    return true;
}


void* GetElement (Array2dPtr arr, int row, int col){

    if (arr != NULL){
        if (row>=0 && row< arr->row && col>=0 && col< arr->col){
            return arr->storage[row * arr->col + col];
        }
    } 

    return NULL;
}
