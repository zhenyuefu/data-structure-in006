CC = gcc
CFLAGS = -Wall -Wextra -pedantic -lm
objects = Reseau.o SVGwriter.o Chaine.o ArbreQuat.o Hachage.o
objectsReseau = ReconstitueReseau.o
objectsHash = ReconstitueHash.o
objectsArbre = ReconstitueArbre.o
objectslist = $(objects) $(objectsReseau) $(objectsHash) $(objectsArbre)
all = ReconstitueReseau ReconstitueHash ReconstitueArbre

prog: $(all) 
ReconstitueReseau: $(objects) $(objectsReseau)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsReseau)
ReconstitueHash: $(objects) $(objectsHash)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsHash)
ReconstitueArbre: $(objects) $(objectsArbre)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsArbre)
SVGwriter.o : SVGwriter.h
Chaine.o : Chaine.h SVGwriter.h
Reseau.o: Reseau.h Chaine.h
Hachage.o : Hachage.h Reseau.h
ArbreQuat.o: ArbreQuat.h Reseau.h
.PHONY : clean
clean :
	-rm $(all) $(objectslist)
	-rm 14.res
	-rm test.html