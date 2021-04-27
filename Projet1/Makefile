CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic
objects = ListeChainee.o ArbreQuaternaire.o Hachage.o Reseau.o Chaine.o SVGwriter.o
objectsReconstitue = ReconstitueReseau.o
objectsTime = TimeTest.o
objectsGraphe = ReorganiseReseau.o Graphe.o Struct_File.o Struct_Liste.o
objectslist = $(objects) $(objectsReconstitue) $(objectsTime) $(objectsGraphe)
all = ChaineMain ReconstitueReseau Time ReorganiseReseau

prog: $(all) 
ChaineMain : ChaineMain.o Chaine.o SVGwriter.o
	gcc -Wall -ggdb -o ChaineMain ChaineMain.o Chaine.o SVGwriter.o -lm
ReconstitueReseau: $(objects) $(objectsReconstitue)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsReconstitue) -lm
Time: $(objects) $(objects) $(objectsTime)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsTime) -lm
ReorganiseReseau: $(objects) $(objectsGraphe)
	$(CC) -o $@ $(CFLAGS) $(objects) $(objectsGraphe) -lm
SVGwriter.o : SVGwriter.h
Reseau.o: Reseau.h Chaine.h
Hachage.o : Hachage.h Reseau.h
ArbreQuaternaire.o : ArbreQuaternaire.h Reseau.h
ListeChainee.o : ListeChainee.h Reseau.h 
Graphe.o : Graphe.h Struct_File.h Struct_Liste.h
.PHONY : clean
clean :
	-rm $(all) $(objectslist)
	-rm exemple.cha
	-rm sd_projet.html