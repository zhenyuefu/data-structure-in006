CFLAGS = -Wall -Wextra -pedantic -lm
objects = ReconstitueArbre.o Reseau.o SVGwriter.o Chaine.o ArbreQuat.o Hachage.o

ReconstitueArbre: $(objects)
	$(CC) -o $@ $(CFLAGS) $(objects)
ArbreQuat.o: ArbreQuat.c
Reseau.o: Reseau.c
Hachage.o : Hachage.c
.PHONY : clean
clean :
	-rm ReconstitueArbre $(objects)
	-rm 14.res
	-rm test.html