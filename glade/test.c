#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
/*


*/




#define UI_FILE "follow.glade"
#define WIDGET_WINDOW "mainWindow"

/* Callback for the buttons */



/*
Ligne de compilation GCC:
gcc -Wno-format -o follow test.c -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic


*/



int main(int argc, char *argv[])
{
  GtkWidget *app;
  GtkWidget *Ouvrir;
  GtkWidget *quitter;
  GtkWidget *quit;	//Bouton fichier-> quit
  GtkWidget *Apropos;
  
  GtkBuilder *builder;
  GError *err = NULL; /* It is mandatory to initialize to NULL */

  /* Initialize gtk+*/
  gtk_init (&argc, &argv);

  builder = gtk_builder_new ();
  
  if(0 == gtk_builder_add_from_file (builder, UI_FILE, &err))
{
    /* Print out the error. You can use GLib's message logging */
    fprintf(stderr, "Error adding build from file. Error: %s\n", err->message);
    /* Your error handling code goes here */
}

  app = GTK_WIDGET (gtk_builder_get_object (builder, WIDGET_WINDOW));
  if (NULL == app)
{
    /* Print out the error. You can use GLib's message logging  */
    fprintf(stderr, "Unable to file object with id \"mainWindow\" \n");
    /* Your error handling code goes here */
}

Ouvrir = GTK_WIDGET (gtk_builder_get_object (builder, "Ouvrir"));
quitter = GTK_WIDGET (gtk_builder_get_object (builder, "quitter"));
quit = GTK_WIDGET (gtk_builder_get_object (builder, "quit"));
Apropos = GTK_WIDGET (gtk_builder_get_object (builder, "Apropos"));


  gtk_builder_connect_signals (builder, NULL);

  gtk_widget_show (app);

  gtk_main ();
  return EXIT_SUCCESS;
}


void	on_Ouvrir_activate(GtkMenuItem *m) {
	printf("Ouvrir activated\n");
	//Prouve que le bouton fonctionne
	printf("Le bouton fonctionne\n");
}

	
	
void on_quitter_activate(GtkMenuItem *m){
  gtk_main_quit();
}

void on_quit_activate(GtkMenuItem *m){
  gtk_main_quit();
}





//Variable Global utile plus la fonction ci-dessous

	GtkWidget *app_deux;
	GtkWidget *bouton;
    GtkBuilder *builder_deux;
    
    
void on_Apropos_activate(GtkMenuItem *m){
//ON crée un nouvelle fenetre

	
    builder_deux = gtk_builder_new ();
    GError *err = NULL;
  
  if(0 == gtk_builder_add_from_file (builder_deux, "popup.glade", &err))
{
    /* Print out the error. You can use GLib's message logging */
    fprintf(stderr, "Error adding build from file. Error: %s\n", err->message);
    /* Your error handling code goes here */
}
  
  app_deux = GTK_WIDGET (gtk_builder_get_object (builder_deux, "mainWindow_deux"));
  bouton = GTK_WIDGET (gtk_builder_get_object (builder_deux, "bouton"));
   if (NULL == bouton)
{
    /* Print out the error. You can use GLib's message logging  */
    fprintf(stderr, "Unable to file object with id \"mainWindow_deux\" \n");
    /* Your error handling code goes here */
}
  gtk_builder_connect_signals (builder_deux, NULL);
  gtk_widget_show_all (app_deux);

  gtk_main ();


}


void on_bouton_clicked(GtkButton *b){
  gtk_widget_destroy(app_deux);
}

