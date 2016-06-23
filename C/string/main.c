#include <stdio.h>
#include <stdlib.h>

//on inclus la librairie <string.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char chaine[] = "Salut";
    int longueurChaine = 0;

    //
    // strlen : calculer la longueur d'une chaîne
    //

    // On récupère la longueur de la chaîne dans longueurChaine
    longueurChaine = strlen(chaine);

    // On affiche la longueur de la chaîne
    printf("La chaine %s fait %d caracteres de long \n\n", chaine, longueurChaine);

    //
    //strcpy : copier une chaîne dans une autre
    //

    // On crée une une copie (vide) de taille 100 pour être sûr d'avoir la place pour la copie
    char copie[100] = {0};

    strcpy(copie, chaine); // On copie "chaine" dans "copie"

    // Si tout s'est bien passé, la copie devrait être identique à chaine
    printf("chaine vaut : %s\n", chaine);
    printf("copie vaut : %s\n\n", copie);


    //
    // strcat : concaténer 2 chaînes
    //

    /* On crée 2 chaînes. chaine1 doit être assez grande pour accueillir
    le contenu de chaine2 en plus, sinon risque de plantage */
    char chaine1[100] = "Salut ", chaine2[] = "Mateo21";

    strcat(chaine1, chaine2); // On concatène chaine2 dans chaine1

    // Si tout s'est bien passé, chaine1 vaut "Salut Mateo21"
    printf("chaine1 vaut : %s\n", chaine1);
    // chaine2 n'a pas changé :
    printf("chaine2 vaut toujours : %s\n\n", chaine2);


    //
    // strcmp : comparer 2 chaînes
    //

    if (strcmp(chaine1, chaine2) == 0) // Si chaînes identiques
    {
        printf("Les chaines sont identiques\n\n");
    }
    else
    {
        printf("La chaine 1 est differentes de la chaine 2 !\n\n");
    }


    //
    // strchr : rechercher un caractère
    //

    char *suiteChaine = NULL;

    suiteChaine = strchr(chaine2, 't');
    if (suiteChaine != NULL) // Si on a trouvé quelque chose
    {
        printf("Voici la fin de la chaine a partir du premier t : %s \n\n", suiteChaine);
    }

    return 0;
}
