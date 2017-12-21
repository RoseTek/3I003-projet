#include <stdio.h>
#include <stdlib.h>
#include "my.h"


int PropagLigne (tGrille *grille, int i, int *marqueC, int *pNb){
  int j;
  int c1, c2;
  int cptcolor = 0;
  int nb = 0;
  
  for (j=0; j<grille->nb_Col; j++)
    {
      if (grille->matrice[i][j] == 0)
	{
	  grille->matrice[i][j] = BLANC;
	  c1 = TestVecteurLigne(grille, i);
	  grille->matrice[i][j] = NOIR;
	  c2 = TestVecteurLigne(grille, i);
	  grille->matrice[i][j] = LIBRE;
	  /* printf("case %d %d retourne c1: %d, c2: %d\n", i, j, c1, c2); */
	  //Si le coloriage de la case est impossible, on retourne faux
	  if (!c1 && !c2)
	    {
	      return FALSE;
	    }

	  //Si le coloriage de la case en blanc aboutit a un coloriage de ligne valide
	  if (c1 && !c2)
	    {
	      grille->matrice[i][j] = BLANC;
	      cptcolor++;
	      if (!marqueC[j])
		{
		  marqueC[j] = TRUE;
		  nb++;		  
		}
	    }

	  //Si le coloriage de la case en noir aboutit a un coloriage de ligne valide
	  if(!c1 && c2)
	    {
	      grille->matrice[i][j] = NOIR;
	      cptcolor++;
	      if (!marqueC[j])
		{
		  marqueC[j] = TRUE;
		  nb++;
		}
	    }
	}
    }
  *pNb = nb;
  return TRUE;
}

int PropagCol (tGrille *grille, int i, int *marqueL, int *pNb){
  int j;
  int c1, c2;
  int cptcolor = 0;
  int nb = 0;
  
  for (j=0; j<grille->nb_Lig; j++){
    if (grille->matrice[j][i] == 0){
      grille->matrice[j][i] = 1;
      c1 = TestVecteurCol(grille, i);
      grille->matrice[j][i] = 2;
      c2 = TestVecteurCol(grille, i);
      grille->matrice[j][i] = 0;
      /* printf("case %d %d retourne c1: %d, c2: %d\n", j, i, c1, c2); */
      //Si le coloriage de la case est impossible, on retourne faux
      if (!c1 && !c2){
	return FALSE;
      }

      //Si le coloriage de la case en blanc aboutit a un coloriage de colonne valide
      if (c1 && !c2){
	grille->matrice[j][i] = 1;
	cptcolor++;
	if (!marqueL[j]){
	  marqueL[j] = TRUE;
	  nb++;
	}
      }

      //Si le coloriage de la case en noir aboutit a un coloriage de colonne valide
      if(!c1 && c2){
	grille->matrice[j][i] = 2;
	cptcolor++;
	if (!marqueL[j]){
	  marqueL[j] = TRUE;
	  nb++;
        }
      }
    }
  }
  *pNb = nb;
  return TRUE;
} 

int propagation(tGrille *grille){
  int *marqueL, *marqueC;
  int nbmL, nbmC, nb =0;
  int i, j;
  int ok;

  /* printf("taille de la matrice : n = %d, m = %d\n", grille->nb_Lig, grille->nb_Col); */
  ok = TRUE;
  marqueL = (int *) malloc (grille->nb_Lig * sizeof(int));
  marqueC = (int *) malloc (grille->nb_Col * sizeof(int));
  for (i=0 ; i<grille->nb_Lig ; i++)
    marqueL[i] = TRUE;
  for (i=0 ; i<grille->nb_Col ; i++)
    marqueC[i] = TRUE;
  nbmL = grille->nb_Lig;
  nbmC = grille->nb_Col;

  while (ok && (nbmL != 0 || nbmC != 0))
    {
      /* printf("nbmC = %d, nbmL = %d\n", nbmC, nbmL); */
      i = 0;
      while (ok && i<grille->nb_Lig)
	{
	  if (marqueL[i]){
	    ok = PropagLigne(grille, i, marqueC, &nb);
	    /* printf("nb : %d\n", nb); */
	    nbmC += nb;
	    marqueL[i] = FALSE;
	    nbmL --;
	  }
	  i++;
	}
      
      /* printf("apres propagLigne\n"); */
      /* showGrille(grille); */
      j=0;
      while (ok && j<grille->nb_Col)
	{
	  if(marqueC[j]){
	    ok = PropagCol (grille, j, marqueL, &nb);
	    /* printf("nb : %d\n", nb); */
	    nbmL += nb;
	    marqueC[j] = FALSE;
	    nbmC--; // erreur énoncé ??
	  }
	  j++;
	}
      /* printf("apres propagCol\n"); */
      /* showGrille(grille); */
    }
  free(marqueC);
  free(marqueL);
  
  return ok;
}
