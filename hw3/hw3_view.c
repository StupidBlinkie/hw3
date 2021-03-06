#include "hw3.h"
#include "hw3_model.h"
#include "hw3_control.h"


extern Array2dPtr arr;
extern const char* color_files[6];  //cant just say color_files..cause seg fault
// extern int selected_row;
// extern int selected_col;
extern int moves_left;


GtkWidget *grid;
GtkWidget *window;
GtkWidget *moves_label;

//print out borad in color numbers
// void printSummary(){
//  printf(" Array is %d by %d\n", arr->row, arr->col);
//   for (int r=0; r<arr->row; r++){
//     for(int c=0; c<arr->col; c++){
//       printf("%d ", *(int*)GetElement(arr, r, c));
//     }
//     printf("\n");
//   }
//   printf("\n\n");
// }

void activate (GtkApplication *app, gpointer user_data) {
   
   /* create a new window, and set its title */
   window = gtk_application_window_new (app);
   gtk_window_set_title (GTK_WINDOW (window), "Window");
   gtk_window_set_default_size (GTK_WINDOW (window), 500, 400);
   gtk_container_set_border_width (GTK_CONTAINER (window), 10);

   /* Here we construct the container that is going pack our buttons */
   grid = gtk_grid_new();

   /* Pack the container in the window */
   gtk_container_add (GTK_CONTAINER (window), grid);

   GtkWidget *button;
   //load images   (should be in view)
   for (int row = 0; row < arr->row; row++) {
      for (int column = 0; column < arr->col; column++){
         button = gtk_toggle_button_new();
         //reterive element from 2d array
         int temp = *(int*)GetElement(arr,row, column); 
         gtk_button_set_image(button, gtk_image_new_from_file (color_files[temp])); 
         gtk_button_set_relief (button, GTK_RELIEF_NONE); //added for button style
         
         g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) row);
         g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) column);

         gtk_grid_attach (GTK_GRID (grid), button, column, row, 1, 1);
      }
   }


   //four control buttons + 1 quit button
   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file ("../images/up.png"));
   g_signal_connect (button, "clicked", G_CALLBACK (swap_up), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 0, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file ("../images/down.png"));
   g_signal_connect (button, "clicked", G_CALLBACK (swap_down), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 1, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file ("../images/left.png"));
   g_signal_connect (button, "clicked", G_CALLBACK (swap_left), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 2, 1, 1);

   button = gtk_button_new_with_label (NULL);
   gtk_button_set_image(button, gtk_image_new_from_file ("../images/right.png"));
   g_signal_connect (button, "clicked", G_CALLBACK (swap_right), NULL);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 3, 1, 1);


   button = gtk_button_new_with_label ("Quit");
   g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
   gtk_grid_attach (GTK_GRID (grid), button, 10, 4, 1, 1);


   //generate label string and create label
   
   moves_label = gtk_label_new (NULL);
   view_update_moves_label();
   gtk_grid_attach (GTK_GRID (grid), moves_label, 10, 5, 1, 1);

   gtk_widget_show_all (window);
}





void view_destroy_candy(int row, int col){
  gtk_widget_destroy(gtk_grid_get_child_at(GTK_GRID (grid), row, col));
}

void view_create_candy(int candy, int row, int col){
   GtkWidget *button = gtk_toggle_button_new();
   gtk_button_set_image(button, gtk_image_new_from_file (color_files[candy]));
   gtk_button_set_relief (button, GTK_RELIEF_NONE);
   g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) row);
   g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) col);  
   gtk_grid_attach (GTK_GRID (grid), button, col, row, 1, 1);   //col,row <--> left offset, top offset

   gtk_widget_show_all (window);
}

void view_update_moves_label(){
   gchar *label_moves_left;
   label_moves_left = g_strdup_printf("%d", moves_left);
   gchar *label_text;
   label_text = g_strdup_printf("moves left: ");
   strcat (label_text, label_moves_left);
   //set new text
   gtk_label_set_text (moves_label, label_text);

}


int main (int argc, char **argv) {
   if (argc != 2) {
      printf("Missing argument!");
      return 0;
   }

   //load 2d array arr
   deserialize(argv[1]);

   //gtk
   GtkApplication *app;
   int status;
   app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
   g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
   status = g_application_run (G_APPLICATION (app), 0, argv);

   g_object_unref (app);
   return status;
}
