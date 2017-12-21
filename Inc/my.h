#ifndef _MY_H
# define _MY_H

enum value {LIBRE, BLANC, NOIR};
enum bool {FALSE, TRUE, NON_VISITE};

typedef struct sGrille{
    int nb_Lig;  // n
    int nb_Col;  // m
    int **matrice;
    int **seqLig;
    int **seqCol;
}tGrille;

tGrille *init_grille(char *file);
void showGrille(tGrille *grille);
int enumeration(tGrille *grille, int k_case, int color);
int nb_seqLig(int lig, tGrille *grille);
int TestVecteurLigne(tGrille *grille, int ligne);

#endif
