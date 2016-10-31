


// void activate (GtkApplication *app, gpointer user_data) {

//    GtkWidget *button;

//    /* create a new window, and set its title */
//    window = gtk_application_window_new (app);
//    gtk_window_set_title (GTK_WINDOW (window), "Window");
//    gtk_window_set_default_size (GTK_WINDOW (window), 500, 400);
//    gtk_container_set_border_width (GTK_CONTAINER (window), 10);

//    /* Here we construct the container that is going pack our buttons */
//    grid = gtk_grid_new();

//    /* Pack the container in the window */
//    gtk_container_add (GTK_CONTAINER (window), grid);

//    //load images   (should be in view)
//    int count = 0;
//    for (int row = 0; row < 10; row++) {
//       for (int column = 0; column < 10; column++){
//          button = gtk_toggle_button_new(); //use toggle button for button style
//          //reterive element from 2d array
//          int temp = GetElement(arr,row, col); 
//          gtk_button_set_image(button, gtk_image_new_from_file (color_files[temp%6])); 
//          gtk_button_set_relief (button, GTK_RELIEF_NONE); //added for button style
         
//          g_signal_connect (button, "clicked", G_CALLBACK (set_row), (gpointer) row);
//          g_signal_connect (button, "clicked", G_CALLBACK (set_col), (gpointer) column);

//          gtk_grid_attach (GTK_GRID (grid), button, column, row, 1, 1);
//          count++;
//       }
//    }



//    //four control buttons + 1 quit button
//    button = gtk_button_new_with_label (NULL);
//    gtk_button_set_image(button, gtk_image_new_from_file ("images/up.png"));
//    g_signal_connect (button, "clicked", G_CALLBACK (swap_up), NULL);
//    gtk_grid_attach (GTK_GRID (grid), button, 10, 0, 1, 1);

//    button = gtk_button_new_with_label (NULL);
//    gtk_button_set_image(button, gtk_image_new_from_file ("images/down.png"));
//    g_signal_connect (button, "clicked", G_CALLBACK (swap_down), NULL);
//    gtk_grid_attach (GTK_GRID (grid), button, 10, 1, 1, 1);

//    button = gtk_button_new_with_label (NULL);
//    gtk_button_set_image(button, gtk_image_new_from_file ("images/left.png"));
//    g_signal_connect (button, "clicked", G_CALLBACK (swap_left), NULL);
//    gtk_grid_attach (GTK_GRID (grid), button, 10, 2, 1, 1);

//    button = gtk_button_new_with_label (NULL);
//    gtk_button_set_image(button, gtk_image_new_from_file ("images/right.png"));
//    g_signal_connect (button, "clicked", G_CALLBACK (swap_right), NULL);
//    gtk_grid_attach (GTK_GRID (grid), button, 10, 3, 1, 1);


//    button = gtk_button_new_with_label ("Quit");
//    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
//    gtk_grid_attach (GTK_GRID (grid), button, 10, 4, 1, 1);


//    gtk_widget_show_all (window);

// }