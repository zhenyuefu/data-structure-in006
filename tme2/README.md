# Comparaison des deux structures



Les deux structures de données ont un temps d'exécution similaire pour la recherche basée sur le `num` et sur le `titre` car la table de hachage est indexée par le nom de l'auteur.

Nous avons volontairement laisser le nombre de donnée inférieur à 0,75 fois la longueur de la table de hachage afin de minimiser les conflits sans gaspiller d'espace.

En fonctions  `recherche_exemplaires`, nous obtenons les résultats indiqués ci-dessous.

![time](time.svg)

