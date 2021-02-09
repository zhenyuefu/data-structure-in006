#define V 100

void alloue_matrice(int **mat, int n);

void alloue_matrice_triangulaire(int **mat, int n);

void desalloue_matrice(int *mat, int n);

void desalloue_matrice_triangulaire(int *mat, int n);

void remplir_matrice_triangulaire(int *mat, int n);

void remplir_matrice(int *mat, int n);

void afficher_matrice(int *mat, int n);

int diff1(int *mat, int n);

int diff2(int *mat, int n);

void mat_produit(int *mat1, int *mat2, int *res, int n);

void mat_produit_sup_inf(int *mat_sup, int *mat_inf, int *res, int n);