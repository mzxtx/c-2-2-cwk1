
# code details

EXE = ./bin/cwk1
SRC= main.c menu.c books.c librarian.c user.c

# generic build details

CC=      gcc
CFLAGS= -std=c99 -Wall
CLINK=

# compile to object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

# build executable: type 'make'

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CLINK) -o $(EXE)

# clean up and remove object code and executable: type 'make clean'

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

main.o:      main.c menu.h book_management.h librarian.h user.h
menu.o:   menu.c  menu.h book_management.h librarian.h user.h
books.o: books.c  menu.h book_management.h librarian.h user.h
librarian.o:      librarian.c  menu.h book_management.h librarian.h user.h
user.o:   user.c  menu.h book_management.h librarian.h user.h


