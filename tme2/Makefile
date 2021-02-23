CFLAGS = -Wall -Wextra -pedantic
objects = biblioLC.o entreeSortieLC.o main.o

biblio : $(objects)
	$(CC) -o $@ $(CFLAGS) $(objects)
main.o : entreeSortieLC.h biblioLC.h
entreeSortieLC.o : entreeSortieLC.h biblioLC.h
biblioLC.o : biblioLC.h
.PHONY : clean
clean :
	-rm biblio $(objects)