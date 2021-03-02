CFLAGS = -Wall -Wextra -pedantic
objects = biblioLC.o entreeSortieLC.o main.o
objects2 = biblioH.o iohash.o test_hash.o

all : biblio test_hash
biblio : $(objects)
	$(CC) -o $@ $(CFLAGS) $(objects)
test_hash : $(objects2)
	$(CC) -o $@ $(CFLAGS) $(objects2)
main.o : entreeSortieLC.h biblioLC.h
entreeSortieLC.o : entreeSortieLC.h biblioLC.h
biblioLC.o : biblioLC.h
.PHONY : clean
clean :
	-rm biblio $(objects)
	-rm test_hash $(objects2)