CFLAGS = -Wall -Wextra -pedantic -lm
objects = ReconstitueReseau.o Reseau.o SVGwriter.o Chaine.o

ReconstitueReseau : $(objects)
	$(CC) -o $@ $(CFLAGS) $(objects)

.PHONY : clean
clean :
	-rm ReconstitueReseau $(objects)