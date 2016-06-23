#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main()
{
    Coordonnees monPoint;
    Coordonnees *pointeur = &monPoint;

    monPoint.x = 10; // On travaille sur une variable, on utilise le "point"
    pointeur->x = 10; // On travaille sur un pointeur, on utilise la flèche

    initialiserCoordonnees(&monPoint);

    // enum attribution volume 50 a la variable musique
    Volume musique = MOYEN;

    return 0;
}

void initialiserCoordonnees(Coordonnees* point)
{
    // Initialisation de chacun des membres de la structure ici
    point->x = 0;
    point->y = 0;

}
