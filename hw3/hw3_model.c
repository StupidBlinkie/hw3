#include "hw3.h"


extern GtkWidget *grid;
extern GtkWidget *window;


int *data_from_json;  //remeber to free it. on exit?
Array2dPtr arr;
int selected_row;
int selected_col;
int selected_candy_bool = 0;
int moves_left = 30;
const char* color_files[6] = {"../images/blue.png", "../images/green.png", "../images/orange.png",
                              "../images/purple.png", "../images/red.png", "../images/yellow.png"};


//read json and load into 2d array arr
void deserialize(char* file){

   json_t* json = json_load_file(file, JSON_COMPACT, NULL);
   void * itr = json_object_iter(json);

   //read rows
   json_t* json_row = json_object_iter_value(itr);
   const int rows = json_integer_value(json_row);
   //read cols
   itr = json_object_iter_next(json, itr);
   json_t* json_col = json_object_iter_value(itr);
   const int cols = json_integer_value(json_col);
   //read array
   itr = json_object_iter_next(json, itr);
   json_t* json_data = json_object_iter_value(itr);

   data_from_json = (int*)malloc(rows * cols *sizeof(int));
   //store in an array
   for (size_t i = 0; i < json_array_size(json_data); i++) {
      data_from_json[i] = json_integer_value(json_array_get(json_data, i));  
   }
   
   //allocate 2d array in memeory
   arr = AllocateArray2d(rows, cols, sizeof(void*));
   
   //fill 2d array
   for (int r=0; r<rows; r++) {
     for (int c=0; c<cols; c++) {
       FillArray2d(arr, r, c, &data_from_json[r * cols + c]);
     }
   }
}
