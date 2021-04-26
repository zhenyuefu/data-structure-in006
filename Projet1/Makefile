CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -lm
objects = Reseau.o SVGwriter.o Chaine.o ArbreQuat.o Hachage.o Graphe.o
objectsReseau = ReconstitueReseau.o
objectsHash = ReconstitueHash.o
objectsArbre = ReconstitueArbre.o
objectsTime = TimeTest.o
objectslist = $(objects) $(objectsReseau) $(objectsHash) $(objectsArbre) $(objectsTime)
all = ReconstitueReseau ReconstitueHash ReconstitueArbre Time

prog: $(all) 
ReconstitueReseau: $(objects) $(objectsReseau)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsReseau)
ReconstitueHash: $(objects) $(objectsHash)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsHash)
ReconstitueArbre: $(objects) $(objectsArbre)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsArbre)
Time: $(objects) $(objectsTime)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsTime)
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