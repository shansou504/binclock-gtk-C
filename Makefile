CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

binclock-gtk : binclock-gtk-c.c
	cc -o binclock-gtk-c binclock-gtk-c.c $(CFLAGS) $(LIBS) -lm

install :
	cp binclock-gtk-c.desktop /usr/share/applications/
	cp resources/hicolor/16x16/apps/binclock-gtk-c.png /usr/share/icons/hicolor/16x16/apps/
	cp resources/hicolor/16x16/apps/binclock-gtk-c.png /usr/share/icons/hicolor/32x32/apps/
	cp binclock-gtk-c /usr/local/bin/

uninstall :
	rm /usr/share/applications/binclock-gtk-c.desktop
	rm /usr/share/icons/hicolor/16x16/apps/binclock-gtk-c.png
	rm /usr/share/icons/hicolor/32x32/apps/binclock-gtk-c.png
	rm /usr/local/bin/binclock-gtk-c

clean :
	rm binclock-gtk-c
