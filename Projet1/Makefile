CFLAGS = -Wall -Wextra -pedantic -lm
objects = Reseau.o SVGwriter.o Chaine.o ArbreQuat.o Hachage.o
objectsReseau = ReconstitueReseau.o
objectsHash = ReconstitueHash.o
objectsArbre = ReconstitueArbre.o
objectslist = $(objects) $(objectsReseau) $(objectsHash) $(objectsArbre)
all = ReconstitueReseau ReconstitueHash ReconstitueArbre

prog: $(all) 
ReconstitueReseau: 
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsReseau)
ReconstitueHash: $(objects)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsHash)
ReconstitueArbre: $(objects)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsArbre)
ArbreQuat.o: ArbreQuat.c
Reseau.o: Reseau.c
Hachage.o : Hachage.c
.PHONY : clean
clean :
	-rm $(all) $(objectslist)
	-rm 14.res
	-rm test.html