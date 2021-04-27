CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -lm
objects = Reseau.o SVGwriter.o Chaine.o ArbreQuat.o Hachage.o Graphe.o Struct_File.o Struct_Liste.o
objectsReseau = ReconstitueReseau.o
objectsHash = ReconstitueHash.o
objectsArbre = ReconstitueArbre.o
objectsTime = TimeTest.o
objectsGraphe = ReorganiseReseau.o
objectslist = $(objects) $(objectsReseau) $(objectsHash) $(objectsArbre) $(objectsTime) $(objectsGraphe)
all = ReconstitueReseau ReconstitueHash ReconstitueArbre Time ReorganiseReseau

prog: $(all) 
ReconstitueReseau: $(objects) $(objectsReseau)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsReseau)
ReconstitueHash: $(objects) $(objectsHash)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsHash)
ReconstitueArbre: $(objects) $(objectsArbre)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsArbre)
Time: $(objects) $(objects) $(objectsTime)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsTime)
ReorganiseReseau: $(objects) $(objectsGraphe)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsGraphe)
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