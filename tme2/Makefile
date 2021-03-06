CFLAGS = -Wall -Wextra -pedantic
objects = biblioLC.o entreeSortieLC.o main.o
objects2 = biblioH.o iohash.o main_hash.o
objectsTime = biblioLC.o entreeSortieLC.o biblioH.o iohash.o test_time.o

all : biblio biblio_hash test_time
biblio : $(objects)
	$(CC) -o $@ $(CFLAGS) $(objects)
biblio_hash : $(objects2)
	$(CC) -o $@ $(CFLAGS) $(objects2)
test_time : $(objectsTime)
	$(CC) -o $@ $(CFLAGS) $(objectsTime)
main.o : entreeSortieLC.h biblioLC.h
main_hash.o:iohash.h biblioH.h
test_time.o:test_time.c
entreeSortieLC.o : entreeSortieLC.h biblioLC.h
biblioLC.o : biblioLC.h
biblioH.o : biblioH.h
iohash.o : iohash.h biblioH.h
.PHONY : clean
clean :
	-rm biblio $(objects)
	-rm biblio_hash $(objects2)
	-rm test_time $(objectsTime)