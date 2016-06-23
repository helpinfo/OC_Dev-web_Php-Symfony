#include <stdio.h>
#include <stdlib.h>

/* Je mets le prototype en haut. Comme c'est un tout
petit programme je ne le mets pas dans un .h, mais
en temps normal (dans un vrai programme), j'aurais plac�
le prototype dans un fichier .h bien entendu */

void decoupeMinutes(int *pointeurSurHeures, int *pointeurSurMinutes);

int main(int argc, char *argv[])
{

    int heures = 0, minutes = 90;

   /* On a une variable minutes qui vaut 90.
    Apr�s appel de la fonction, je veux que ma variable
    "heures" vaille 1 et que ma variable "minutes" vaille 30 */

    decoupeMinutes(&heures, &minutes);

    printf("%d heures et %d minutes", heures, minutes);

    return 0;
}

void decoupeMinutes(int *pointeurHeures, int *pointeurMinutes)
{
    *pointeurHeures = *pointeurMinutes / 60;  // 90 / 60 = 1
    *pointeurMinutes = *pointeurMinutes % 60; // 90 % 60 = 30
}
