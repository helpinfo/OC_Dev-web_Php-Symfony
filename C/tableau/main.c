#include <stdio.h>
#include <stdlib.h>

// Prototype de la fonction d'affichage
void affiche(int tableau[], int tailleTableau);
int sommeTableau(int tableau[], int tailleTableau);
double moyenneTableau(int tableau[], int tailleTableau);
void copie(int tableauOriginal[], int tableauCopie[], int tailleTableau);
void ordonnerTableau(int tableau[], int tailleTableau);

int main(int argc, char *argv[])
{
    int tableau[4] = {15, 81, 22, 13};
    int tableauCopie[4] = {0};

    // On affiche le contenu du tableau
    printf("Voici le tableau : \n\n");
    affiche(tableau, 4);

    // on aditionne les valeur du tableau
    printf("\n la somme du tableau est de %d \n", sommeTableau(tableau, 4));
    printf("la moyenne du tableau est de %f \n", moyenneTableau(tableau, 4));

    printf("Voici la copie du tableau : \n\n");
    copie(tableau, tableauCopie, 4);

    printf("\n Voici le tableau ordonné : \n\n");
    ordonnerTableau(tableau , 4);
    affiche(tableau, 4);

    return 0;
}

void ordonnerTableau(int tableau[], int tailleTableau)
{
    int c,i,tmp;

    // tri a bulle : effectue le tri autant de fois qu'il y as de case
    for(i = 0 ; i < tailleTableau ; i++)
    {
        // TANTQUE C=0 et que C est inferieur a tailleTableau faire:
        for(c = 0 ; c < tailleTableau ; c++)
        {
            // Si la case C du tableau est superieur a la case C+1 du tableau alors

            // tmp = case C+1 du tableau
            // case N+1 du tableau = case N du tableau
            // case N du tableau = tmp

            if(tableau[c] > tableau[c+1])
            {
                tmp = tableau[c];
                tableau[c] = tableau[c+1];
                tableau[c+1] = tmp;
            }
        }
    }
}

void copie(int tableauOriginal[], int tableauCopie[], int tailleTableau)
{
    int i;

    for (i = 0 ; i < tailleTableau ; i++)
    {
        tableauCopie[i] = tableauOriginal[i];
        printf("%d\n", tableauCopie[i]);
    }
}

double moyenneTableau(int tableau[], int tailleTableau)
{
    double moyenne = 0;
    int i;
    double somme = 0;

   for (i = 0 ; i < tailleTableau ; i++)
   {
       somme = somme + tableau[i];
   }

   moyenne = somme / tailleTableau;

    return moyenne;
}

int sommeTableau(int tableau[], int tailleTableau)
{
   int i;
   int somme = 0;

   for (i = 0 ; i < tailleTableau ; i++)
   {
       somme = somme + tableau[i];
   }

   return somme;
}

void affiche(int tableau[], int tailleTableau)
{
    int i;

    for (i = 0 ; i < tailleTableau ; i++)
    {
        printf("%d\n", tableau[i]);
    }
}
