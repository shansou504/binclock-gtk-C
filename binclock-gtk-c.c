#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <time.h>
#include <string.h>

//Integer value of characters 0-9 since switch case
//statement only handles integers
//0 = 48
//1 = 49
//2 = 50
//3 = 51
//4 = 52
//5 = 53
//6 = 54
//7 = 55
//8 = 56
//9 = 57

gboolean update_time(gpointer user_data) {
	time_t t;
	struct tm *tp;
	char s[8];
	char clock[4][6][4];
	char str[200] = "";
//	circles
//	static char u[4] = "\u25CF";
//	static char d[4] = "\u25CB";
//	squares
	static char u[4] = "\u25A0";
	static char d[4] = "\u25A1";

	time(&t);
	tp = localtime(&t);
	strftime(s,8,"%H%M%S",tp);
	for (int r=0;r<4;r++) {
		for (int c=0;c<6;c++) {
			switch (r) {
				case 0:
					switch ((int)(s[c])) {
						case 49:
						case 51:
						case 53:
						case 55:
						case 57:
							strcpy(clock[r][c],u);
						break;
						default:
							strcpy(clock[r][c],d);
							break;
					}
					break;
				case 1:
					switch ((int)(s[c])) {
				   		case 50:
				   		case 51:
				   		case 54:
				   		case 55:
				   			strcpy(clock[r][c],u);
				   			break;
				  		default:
				   			strcpy(clock[r][c],d);
				   			break;
					}
					break;
				case 2:
					switch ((int)(s[c])) {
						case 52:
						case 53:
						case 54:
						case 55:
							strcpy(clock[r][c],u);
							break;
						default:
							strcpy(clock[r][c],d);
							break;
					}
					break;
				case 3:
					switch ((int)(s[c])) {
						case 56:
						case 57:
							strcpy(clock[r][c],u);
							break;
						default:
							strcpy(clock[r][c],d);
						break;
					}
					break;
				default:
					break;
			}
		}
	}
	for (int j=0;j<2;j++) {
		strcat(str,clock[3][j]);
	}
	strcat(str," ");
	for (int j=2;j<4;j++) {
		strcat(str,clock[3][j]);
	}
	strcat(str," ");
	for (int j=4;j<6;j++) {
		strcat(str,clock[3][j]);
	}
	for (int i=3;i>0;i--) {
		strcat(str,"\n");
		for (int j=0;j<2;j++) {
			strcat(str,clock[i-1][j]);
		}
		strcat(str," ");
		for (int j=2;j<4;j++) {
			strcat(str,clock[i-1][j]);
		}
		strcat(str," ");
		for (int j=4;j<6;j++) {
			strcat(str,clock[i-1][j]);
		}
	}

	const char *format = "<span font_desc=\"Sans 24\">\%s</span>";
	char *markup;
	markup = g_markup_printf_escaped (format, str);
	gtk_label_set_markup (GTK_LABEL (user_data), markup);
	g_free (markup);

	return G_SOURCE_CONTINUE;

}

int css (gpointer window) {

	GtkCssProvider *css_provider;
	css_provider = gtk_css_provider_new ();
	const gchar* style = 
		"window {\n"
		"	background: rgba(0,0,0,0);\n"
		"}";
	gtk_css_provider_load_from_data(css_provider, style, -1, NULL);

	GdkDisplay *display = gdk_display_get_default();
	GdkScreen* screen = gdk_display_get_default_screen(GDK_DISPLAY (display));
	GdkVisual* visual = gdk_screen_get_rgba_visual(screen);;

	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER (css_provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
	gtk_widget_set_visual (GTK_WIDGET (window), visual);

	return 0;
}

int main (void) {

	gtk_init(NULL, NULL);

//	window
	GtkWidget *window;
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_decorated (GTK_WINDOW (window), FALSE);
	gtk_window_set_default_size (GTK_WINDOW (window), 210, 160);
//	gtk_window_set_skip_taskbar_hint (GTK_WINDOW (window), TRUE);

//	window location
//	gtk_window_set_gravity (GTK_WINDOW (window), GDK_GRAVITY_NORTH_EAST);
//	gtk_window_move (GTK_WINDOW (window), 1710, 0);

//	icon
  const char* iconfile = "/usr/share/icons/hicolor/32x32/apps/binclock-gtk.png";
	GdkPixbuf *icon = gdk_pixbuf_new_from_file (iconfile, NULL);
	gtk_window_set_icon (GTK_WINDOW (window), GDK_PIXBUF (icon));

//	label
	GtkWidget *label;
	label = gtk_label_new (NULL);
	gtk_container_add (GTK_CONTAINER (window), label);
	gtk_widget_set_margin_bottom (GTK_WIDGET (label), 6);

//	transparent background
//	css(GTK_WINDOW (window));

//	show widgets
	gtk_widget_show_all (window);

//	refresh label
	g_timeout_add_seconds (1, update_time, label);

//	main
	gtk_main();

//	success
	return  0;
}
