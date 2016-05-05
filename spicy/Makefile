CC = i686-w64-mingw32-gcc
CFLAGS = -O2 -I. $(shell mingw32-pkg-config --cflags spice-client-glib-2.0 spice-client-gtk-2.0)
LDFLAGS = $(shell mingw32-pkg-config --libs spice-client-glib-2.0 spice-client-gtk-2.0)


EXE = spicy.exe
FIRM_OBJS = spicy.o spice-cmdline.o spicy-connect.o extra-channel-main.o
APP_OBJS = keyboard.o display.o typer.o dtp.o fsender.o my_config.o util.o hash.o
ALL_OBJS = $(FIRM_OBJS) $(APP_OBJS)

.PHONY: all clean

all: $(EXE)

$(EXE): $(ALL_OBJS)
	$(CC) -o $(EXE) $(ALL_OBJS) $(LDFLAGS)

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	-rm *.o

