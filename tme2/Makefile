CFLAGS = -Wall -Wextra -pedantic
objects = biblioLC.o entreeSortieLC.o main.o
objects2 = biblioH.o iohash.o main_hash.o

all : biblio biblio_hash
biblio : $(objects)
	$(CC) -o $@ $(CFLAGS) $(objects)
biblio_hash : $(objects2)
	$(CC) -o $@ $(CFLAGS) $(objects2)
main.o : entreeSortieLC.h biblioLC.h
entreeSortieLC.o : entreeSortieLC.h biblioLC.h
biblioLC.o : biblioLC.h
biblioH.o : biblioH.h
iohash.o : iohash.h biblioH.h
.PHONY : clean
clean :
	-rm biblio $(objects)
	-rm biblio_hash $(objects2)