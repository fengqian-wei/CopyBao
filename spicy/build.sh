i686-w64-mingw32-gcc -o spicy.exe spicy.c spice-cmdline.c spicy-connect.c -I. $(mingw32-pkg-config --cflags --libs spice-client-glib-2.0 spice-client-gtk-2.0)

