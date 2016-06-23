#include <stdio.h>
#include <stdlib.h>

int main()
{

    int nombre = 10;
    int *pointeurDeNombre = &nombre;


    printf("\n========\n");
    printf("Variable\n");
    printf("========\n");
    printf("Affiche nombre : %d \n", nombre);
    printf("Affiche &nombre : %d \n", &nombre);

    printf("\n====================\n");
    printf("Pointeur de Variable\n");
    printf("====================\n");
    printf("Affiche &pointeurDeNombre : %d \n", &pointeurDeNombre);
    printf("Affiche pointeurDeNombre : %d \n", pointeurDeNombre);
    printf("Affiche *pointeurDeNombre : %d \n", *pointeurDeNombre);
    return 0;
}
