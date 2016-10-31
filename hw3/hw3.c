#include "hw3.h"


void loadfile(char* path);
void activate (GtkApplication *app, gpointer user_data);


Array2dPtr arr;  //has to define it in main



int main (int argc, char **argv) {
   if (argc != 2) {
      printf("Missing argument!");
      return 0;
   }
   json_t* json = json_load_file(argv[1], JSON_COMPACT, NULL);
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

   //store in an array
   int data[rows * cols];
   for (size_t i = 0; i < json_array_size(json_data); i++) {
      data[i] = json_integer_value(json_array_get(json_data, i));      
   }

   //allocate 2d array in memeory
   arr = AllocateArray2d(rows, cols, sizeof(void*));
   
   //fill 2d array
   for (int r=0; r<rows; r++) {
     for (int c=0; c<cols; c++) {
       FillArray2d(arr, r, c, &data[r * cols + c]);
     }
   }




   //gtk 
   GtkApplication *app;
   int status;

   app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
   g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
   status = g_application_run (G_APPLICATION (app), 0, argv);

   g_object_unref (app);
   return status;

}


