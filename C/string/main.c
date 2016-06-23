#include <stdio.h>
#include <stdlib.h>

//on inclus la librairie <string.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char chaine[] = "Salut";
    int longueurChaine = 0;

    //
    // strlen : calculer la longueur d'une cha�ne
    //

    // On r�cup�re la longueur de la cha�ne dans longueurChaine
    longueurChaine = strlen(chaine);

    // On affiche la longueur de la cha�ne
    printf("La chaine %s fait %d caracteres de long \n\n", chaine, longueurChaine);

    //
    //strcpy : copier une cha�ne dans une autre
    //

    // On cr�e une une copie (vide) de taille 100 pour �tre s�r d'avoir la place pour la copie
    char copie[100] = {0};

    strcpy(copie, chaine); // On copie "chaine" dans "copie"

    // Si tout s'est bien pass�, la copie devrait �tre identique � chaine
    printf("chaine vaut : %s\n", chaine);
    printf("copie vaut : %s\n\n", copie);


    //
    // strcat : concat�ner 2 cha�nes
    //

    /* On cr�e 2 cha�nes. chaine1 doit �tre assez grande pour accueillir
    le contenu de chaine2 en plus, sinon risque de plantage */
    char chaine1[100] = "Salut ", chaine2[] = "Mateo21";

    strcat(chaine1, chaine2); // On concat�ne chaine2 dans chaine1

    // Si tout s'est bien pass�, chaine1 vaut "Salut Mateo21"
    printf("chaine1 vaut : %s\n", chaine1);
    // chaine2 n'a pas chang� :
    printf("chaine2 vaut toujours : %s\n\n", chaine2);


    //
    // strcmp : comparer 2 cha�nes
    //

    if (strcmp(chaine1, chaine2) == 0) // Si cha�nes identiques
    {
        printf("Les chaines sont identiques\n\n");
    }
    else
    {
        printf("La chaine 1 est differentes de la chaine 2 !\n\n");
    }


    //
    // strchr : rechercher un caract�re
    //

    char *suiteChaine = NULL;

    suiteChaine = strchr(chaine2, 't');
    if (suiteChaine != NULL) // Si on a trouv� quelque chose
    {
        printf("Voici la fin de la chaine a partir du premier t : %s \n\n", suiteChaine);
    }

    return 0;
}
