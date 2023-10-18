#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <time.h>
#include <string.h>
#include <math.h>

gboolean update_time(gpointer user_data) {
	time_t t;
	time(&t);
	struct tm *tp;
	tp = localtime(&t);
	int hh = tp->tm_hour;
	int mm = tp->tm_min;
	int ss = tp->tm_sec;
	int tar[7];
	tar[0] = hh/10;
	tar[1] = hh%10;
	tar[2] = mm/10;
	tar[3] = mm%10;
	tar[4] = ss/10;
	tar[5] = ss%10;
	char str[200] = "";
	static char u[4] = "\u25A0";
	static char d[4] = "\u25A1";

	for (int r=3;r>-1;r--) {
		if (r!=3) {
			strcat(str,"\n");
		}
		for (int c=0;c<6;c++) {
			if (tar[c]&(int)(pow(2,(double)(r)))) {
				strcat(str,u);
			} else {
				strcat(str,d);
			}
			if (c>0 && c<5 && c%2!=0) {
				strcat(str," ");
			}
		}
	}

	const char *format = "<span font_desc=\"Sans 24\">\%s</span>";
	char *markup;
	markup = g_markup_printf_escaped (format, str);
	gtk_label_set_markup (GTK_LABEL (user_data), markup);
	g_free (markup);

	return G_SOURCE_CONTINUE;

}

static void activate (GtkApplication *app, gpointer user_data) {
//	window
	GtkWidget *window;
	window = gtk_application_window_new (app);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
	gtk_window_set_default_size (GTK_WINDOW (window), 210, 160);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);

//	window location
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);

//	icon
  const char* iconfile = "/usr/share/icons/hicolor/32x32/apps/binclock-gtk-c.png";
	GdkPixbuf *icon = gdk_pixbuf_new_from_file (iconfile, NULL);
	gtk_window_set_icon (GTK_WINDOW (window), GDK_PIXBUF (icon));

//	label (clock)
	GtkWidget *label;
	label = gtk_label_new (NULL);
	gtk_container_add (GTK_CONTAINER (window), label);
	gtk_widget_set_margin_bottom (GTK_WIDGET (label), 6);

//	show widgets
	gtk_widget_show_all (window);

//	quit app if already open
	g_signal_connect (app, "activate", G_CALLBACK (g_application_quit), app);

//	refresh label
	g_timeout_add_seconds (1, update_time, label);

}


int main (int argc, char **argv) {

  GtkApplication *app;
  int status;

  app = gtk_application_new ("com.github.shansou504.binclock_gtk_c", 0);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;

}
