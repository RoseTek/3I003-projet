#include <stdio.h>
#include <stdlib.h>
#include "my.h"

/* FONCTIONS D'AFFICHAGE STRUCTURE */

static void show_seq(int **sequence, int size, char type){
    int i, n;

    for (i=0; i<size; i++){
	printf("%c%d\t", type, i+1);
	n=0;
	while (sequence[i][n] != -1){
	    printf("%d   ", sequence[i][n]);
	    n++;
	}
	printf("\n");
    }
}

/* Pour afficher l'etat de la grille et l'ensemble l'ensemble des sequences pour les lignes et les colonnes */
void showWholeGrille(tGrille *grille){
  int i,n;
  printf("Matrice a %d lignes, %d colonnes :\n", grille->nb_Lig, grille->nb_Col); 
  for (i=0 ; i<grille->nb_Lig ; i++){
  	for (n=0 ; n<grille->nb_Col ; n++)
  	    printf("%d ", grille->matrice[i][n]);
  	printf("\n");
  }
  printf("\nLignes:\n");
  show_seq(grille->seqLig, grille->nb_Lig, 'L');
  printf("\nColonnes:\n");
  show_seq(grille->seqCol, grille->nb_Col, 'C');
}

/* Pour afficher l'etat de la grille */
void showGrille(tGrille *grille){
  int i,n;
  for (i=0 ; i<grille->nb_Lig ; i++){
    for (n=0 ; n<grille->nb_Col ; n++)
      if (grille->matrice[i][n] == NOIR)
	  printf(" ");
      else
	if(grille->matrice[i][n] == BLANC)
	printf("█");
	else
	  printf("_");
    printf("\n");
  }
}

/* GETTER */
int nb_seqLig(int ligne, tGrille *grille){
  int i = 0;

  while (grille->seqLig[ligne][i] != -1)
    i++;
  return i;
}

int nb_seqCol(int col, tGrille *grille){
  int i = 0;

  while (grille->seqCol[col][i] != -1)
    i++;
  return i;
}

/* INITIALISATION STRUCTURE */

static void *my_err(char *msg){
    printf("%s\n", msg);
    return NULL;
}

static void init_seq(FILE *f, int **sequence, int nb_Ligne){
    int i, nb_val, n,ret;

    for (i=0; i<nb_Ligne; i++){
	ret = fscanf(f, "%d", &(nb_val));
	sequence[i] = malloc(sizeof(int) * (nb_val+1)); //termine par -1
	for (n=0; n<nb_val ; n++)	   
	    ret = fscanf(f, "%d", &(sequence[i][n]));
	sequence[i][nb_val] = -1;
    }
}

tGrille *init_grille(char *file){
    tGrille *grille;
    FILE *f;
    int n, i, ret;
    
    if ((f= fopen(file, "r")) == NULL)
	return my_err("Ouverture fichier impossible");
    grille = (tGrille *)malloc(sizeof(tGrille));
    ret = fscanf(f, "%d %d", &(grille->nb_Lig), &(grille->nb_Col));
    grille->matrice = (int **)malloc(sizeof(int *)*grille->nb_Lig);
    for (n=0 ; n<grille->nb_Lig ; n++){
	grille->matrice[n] = (int *)malloc(sizeof(int)*grille->nb_Col);
	for (i=0; i<grille->nb_Col; i++)
	    grille->matrice[n][i] = (int)LIBRE;
    }
    grille->seqLig = (int **)malloc(sizeof(int *)*grille->nb_Lig);
    grille->seqCol = (int **)malloc(sizeof(int *)*grille->nb_Col);
    init_seq(f, grille->seqLig, grille->nb_Lig);    
    init_seq(f, grille->seqCol, grille->nb_Col);
    fclose(f);
    return grille;
}
