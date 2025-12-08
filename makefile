CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0`

SRC = \
    main.c \
    gui/gui.c \
    cellules/cellules.c \
    liste/liste.c \
    stack/stack.c

OBJ = $(SRC:.c=.o)

EXEC = monoplan

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

// make clean
// make
// ./monoplan