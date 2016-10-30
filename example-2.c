#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array2d.h"
//#include "array2d.c"
#include "../jansson/include/jansson.h"

// Made all of these global because I dont know how else to share data between methods
// in gtk

// This will store temp_data info. Couldn't figure out how to read the json file, but
// once we do temp_data should be stored here.
Array2dPtr arr;

//made these global in order to edit them as we go.
GtkWidget *grid;
GtkWidget *window;

//after a candy click, these get updated
int selected_row;
int selected_col;

// temporarily stores the int values for which image is being used.
int temp_data[100];

// indicates whether or not a candy has been selected
int selected_candy_bool = 0;

// This just stores the strings for our needed color images
const char* color_files[6] = {"images/blue.png", "images/green.png", "images/orange.png",
                              "images/purple.png", "images/red.png", "images/yellow.png"};
                              
                              
// connected to each candy to set the row
static void set_row(GtkWidget *widget, gpointer  data) {
   selected_row = (int) data;
}
// connected to each candy to set col. printf is not necessary, but helpful for now
static void set_col(GtkWidget *widget, gpointer  data) {
   selected_col = (int) data;
   selected_candy_bool = 1;
   printf("%d, %d\n", selected_row, selected_col);
}

// swaps the buttons for selected candy and new candy. new candy is either above,
// below, left, or right of selected candy
static void swap_buttons(int new_row, int new_col) {
   printf("%d, %d\n", selected_row, selected_col);
   printf("%d, %d\n", new_row, new_col);


   // get the indexes for the candies in temp_data
   int selected_index = selected_row * 10 + selected_col;
   int new_index = (new_row) * 10 + new_col;
      printf("index1: %d, index2: %d\n", selected_index, new_index);

   // get the int value associated with their pictures
   int selected_image = temp_data[selected_index];
   int new_image = temp_data[new_index];
   
   printf("color1: %d, color2: %d\n", selected_image, new_image);

   // swap the data in temp_data
   temp_data[selected_index] = new_image;
   temp_data[new_index] = selected_image;
   
   // destroy previous pictures
   gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID (grid), selected_col, selected_row));
   gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID (grid), new_col, new_row));

   // set up new buttons and attatch them
   GtkWidget *button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file (color_files[selected_image]));
   gtk_button_set_relief (button, GTK_RELIEF_NONE);
   g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) new_row);
   g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) new_col);
   
   gtk_grid_attach (GTK_GRID (grid), button, new_col, new_row, 1, 1);
   
   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file (color_files[new_image]));
   gtk_button_set_relief (button, GTK_RELIEF_NONE);
   g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) selected_row);
   g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) selected_col);
   
   gtk_grid_attach (GTK_GRID (grid), button, selected_col, selected_row, 1, 1);
   
   // This makes new buttons appear
   gtk_widget_show_all (window);
}

// connected to up arrow button
static void swap_up(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool) {
      if (selected_row != 0) {
         g_print ("clikced up\n");
         swap_buttons(selected_row - 1, selected_col);
         selected_candy_bool = 0;
      }
   }
}

// connected to down arrow button
static void swap_down(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool) {
      if (selected_row != 9) {
         g_print ("clikced down\n");
         swap_buttons(selected_row + 1, selected_col);

         selected_candy_bool = 0;
      }
   }
}

// connected to left arrow button
static void swap_left(GtkWidget *widget, gpointer  data){
   if (selected_candy_bool) {
      if (selected_col != 0) {
         g_print ("clikced left\n");
         swap_buttons(selected_row, selected_col - 1);

         selected_candy_bool = 0;
      }
   }
}

// connected to right arrow button
static void swap_right(GtkWidget *widget, gpointer  data){
  if (selected_candy_bool) {
      if (selected_col != 9) {
         g_print ("clikced right\n");
         swap_buttons(selected_row, selected_col + 1);

         selected_candy_bool = 0;
      }
   }
}


static void activate (GtkApplication *app, gpointer user_data) {
 //  GtkWidget *window;
//   GtkWidget *grid;
   GtkWidget *button;
   // GtkWidget *image[100];
   //GtkWidget *   gtk_image_new_from_file ();


   /* create a new window, and set its title */
   window = gtk_application_window_new (app);
   gtk_window_set_title (GTK_WINDOW (window), "Window");
   gtk_window_set_default_size (GTK_WINDOW (window), 500, 400);
   gtk_container_set_border_width (GTK_CONTAINER (window), 10);

   /* Here we construct the container that is going pack our buttons */
   grid = gtk_grid_new ();

   /* Pack the container in the window */
   gtk_container_add (GTK_CONTAINER (window), grid);

   //load images
   int count = 0;
   for (int row = 0; row < 10; row++) {
      for (int column = 0; column < 10; column++){
         button = gtk_toggle_button_new(); //use toggle button for button style
          // This code should be used once we can open files (int) *(arr->storage + arr->col * row + column)]));
         gtk_button_set_image(button, gtk_image_new_from_file (color_files[count % 6])); 
         gtk_button_set_relief (button, GTK_RELIEF_NONE); //button style
         temp_data[count] = count% 6;
         g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) row);
         g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) column);

         gtk_grid_attach (GTK_GRID (grid), button, column, row, 1, 1);
         count++;
      }
   }
//   gtk_widget_set_focus_on_click (GtkWidget image[0],
  //                                gboolean focus_on_click);


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


  /* Now that we are done packing our widgets, we show them all
   * in one go, by calling gtk_widget_show_all() on the window.
   * This call recursively calls gtk_widget_show() on all widgets
   * that are contained in the window, directly or indirectly.
   */
   gtk_widget_show_all (window);

}



void deserialize(char* file_name) {
	json_t* json = json_load_file(file_name, JSON_COMPACT, NULL);
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
	int numbers[rows * cols];
	for (size_t i = 0; i < json_array_size(json_data); i++) {
		numbers[i] = json_integer_value(json_array_get(json_data, i));
		 printf("\t\tdeserialized %d\n",numbers[i]);
	}



	//allocate 2d array in memeory
	arr = AllocateArray2d(rows, cols, sizeof(void*));
	
	//fill 2d array
	for (int r=0; r<rows; r++) {
	  for (int c=0; c<cols; c++) {
            FillArray2d(arr, r, c, &numbers[r * cols + c]);	    
	  }
	}
}



int main (int argc, char **argv) {
  // deserialize(*argv[1]);
   GtkApplication *app;
   int status;

   app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
   g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
   status = g_application_run (G_APPLICATION (app), argc, argv);
   g_object_unref (app);

   return status;
}

//try to read file from command line arg
// app = gtk_application_new ("org.gtk.example", G_APPLICATION_HANDLES_COMMAND_LINE);
// g_application_add_main_option_entries (app, argv[1]);