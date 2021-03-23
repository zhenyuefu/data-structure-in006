CFLAGS = -Wall -Wextra -pedantic -lm
objects = ReconstitueHash.o Reseau.o SVGwriter.o Chaine.o Hachage.o

ReconstitueHash: $(objects)
	$(CC) -o $@ $(CFLAGS) $(objects)
Hachage.o: Hachage.c 
Reseau.o: Reseau.c
.PHONY : clean
clean :
	-rm ReconstitueHash $(objects)