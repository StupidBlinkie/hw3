#include "hw3_model.h"
// #include <stdio.h>
// #include <stdlib.h>


// 2d array to store board state

GtkWidget *grid;
GtkWidget *window;

//after a candy click, these get updated
int selected_row;
int selected_col;

// indicates whether or not a candy has been selected
int selected_candy_bool = 0;

// This just stores the strings for our needed color images
const char* color_files[6] = {"images/blue.png", "images/green.png", "images/orange.png",
                              "images/purple.png", "images/red.png", "images/yellow.png"};





void activate (GtkApplication *app, gpointer user_data) {

   GtkWidget *button;

   /* create a new window, and set its title */
   window = gtk_application_window_new (app);
   gtk_window_set_title (GTK_WINDOW (window), "Window");
   gtk_window_set_default_size (GTK_WINDOW (window), 500, 400);
   gtk_container_set_border_width (GTK_CONTAINER (window), 10);

   /* Here we construct the container that is going pack our buttons */
   grid = gtk_grid_new();

   /* Pack the container in the window */
   gtk_container_add (GTK_CONTAINER (window), grid);


  printf("in activate----");
  printSummary();

  //drawBoard();

   //load images   (should be in view)
   int count = 0;
   for (int row = 0; row < arr->row; row++) {
      for (int column = 0; column < arr->col; column++){
         //button = gtk_button_new_with_label (NULL);
         button = gtk_toggle_button_new(); //use toggle button for button style
         //reterive element from 2d array
         int temp = *(int*)GetElement(arr,row, column); 
         gtk_button_set_image(button, gtk_image_new_from_file (color_files[temp])); 
         gtk_button_set_relief (button, GTK_RELIEF_NONE); //added for button style
         
         g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) row);
         g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) column);

         gtk_grid_attach (GTK_GRID (grid), button, column, row, 1, 1);
         count++;
      }
   }



   //four control buttons + 1 quit button
   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file ("images/up.png"));
   g_signal_connect (button, "clicked", G_CALLBACK (swap_up), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 0, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file ("images/down.png"));
   g_signal_connect (button, "clicked", G_CALLBACK (swap_down), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 1, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file ("images/left.png"));
   g_signal_connect (button, "clicked", G_CALLBACK (swap_left), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 2, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file ("images/right.png"));
   g_signal_connect (button, "clicked", G_CALLBACK (swap_right), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 3, 1, 1);


   button = gtk_button_new_with_label ("Quit");
   g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 4, 1, 1);


   gtk_widget_show_all (window);

}


// connected to each candy to set the row
void set_row(GtkWidget *widget, gpointer  data) {
   selected_row = (int) data;
}
// connected to each candy to set col. printf is not necessary, but helpful for now
void set_col(GtkWidget *widget, gpointer  data) {
   selected_col = (int) data;
   selected_candy_bool = 1;
   printf("%d, %d\n", selected_row, selected_col);
}


void swap_buttons(int traget_row, int traget_col) {
   printf("selected: %d, %d\n", selected_row, selected_col);
   printf("to be swapped with: %d, %d\n", traget_row, traget_col);

   printf("in swap_button, before swap----");
   printSummary();

   // get the indexes for the candies in temp_data
   int selected_candy = *(int*)GetElement(arr, selected_row, selected_col);
   int traget_candy = *(int*)GetElement(arr, traget_row, traget_col);
   
   //update arr
   Swap(arr, selected_row, selected_col, traget_row, traget_col); 
   printf("in swap_button, after swap----");
   printSummary();


   //destroy two candies
   gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID (grid), selected_col, selected_row));
   gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID (grid), traget_col, traget_row));

  //create new ones, selected one shows in target, target location shows selected one
   GtkWidget *button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file (color_files[selected_candy]));
   gtk_button_set_relief (button, GTK_RELIEF_NONE);
   g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) traget_row);
   g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) traget_col);  
   gtk_grid_attach (GTK_GRID (grid), button, traget_col, traget_row, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file (color_files[traget_candy]));
   gtk_button_set_relief (button, GTK_RELIEF_NONE);
   g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) selected_row);
   g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) selected_col);
   gtk_grid_attach (GTK_GRID (grid), button, selected_col, selected_row, 1, 1);
   
   // This makes new buttons appear
   gtk_widget_show_all (window);
}

// connected to up arrow button
void swap_up(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool) {
      if (selected_row != 0) {
         g_print ("clikced up\n");
         swap_buttons(selected_row - 1, selected_col);
         selected_candy_bool = 0;
      }
   }
}

// connected to down arrow button
void swap_down(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool) {
      if (selected_row != 9) {
         g_print ("clikced down\n");
         swap_buttons(selected_row + 1, selected_col);
         selected_candy_bool = 0;
      }
   }
}

// connected to left arrow button
void swap_left(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool) {
      if (selected_col != 0) {
         g_print ("clikced left\n");
         swap_buttons(selected_row, selected_col - 1);
         selected_candy_bool = 0;
      }
   }
}

// connected to right arrow button
void swap_right(GtkWidget *widget, gpointer  data){
  if (selected_candy_bool) {
      if (selected_col != 9) {
         g_print ("clikced right\n");
         swap_buttons(selected_row, selected_col + 1);
         selected_candy_bool = 0;
      }
   }
}





void printSummary(){
 printf(" Array is %d by %d\n", arr->row, arr->col);
  for (int r=0; r<arr->row; r++){
    for(int c=0; c<arr->col; c++){
      printf("%d ", *(int*)GetElement(arr, r, c));
    }
  }
  printf("\n\n");
}