#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main ( int argc, char** argv )
{
    int nombreMystere = 0, nombreEntre = 0, compteur = 0, continuerPartie = 1, nombreMax = 0, choix = 0;

    // Boucle générale du programme tant que l'utilisateur n'arrete pas
    while(continuerPartie != 0)
    {
        const int MIN = 1;


        system("cls"); // on vide la console
        compteur = 0; // on pense à réinitialiser le compteur de coups

        // On demande le niveau
        printf("#####################\n");
        printf("  Le Nombre Mystere  \n");
        printf("#####################\n\n");

        printf("Choississez votre niveau :\n");
        printf("1 = entre 1 et 100\n");
        printf("2 = entre 1 et 1000\n");
        printf("3 = entre 1 et 10000\n\n");
        printf("Votre choix ? ");
        scanf("%d", &choix);
        switch(choix)
        {
        case 1:
            nombreMax = 100;
            break;
        case 2:
            nombreMax = 1000;
            break;
        case 3:
            nombreMax = 10000;
            break;
        default:
            nombreMax = 100;
            break;
        }


        // Génération du nombre aléatoire

        srand(time(NULL));
        nombreMystere = (rand() % (nombreMax - MIN + 1)) + MIN;

        /* La boucle du programme. Elle se répète tant que l'utilisateur n'a pas trouvé le nombre mystère */
        do
        {
            // on rajoute +1 à chaque boucle
            compteur++;

            // On demande le nombre
            printf("Trouvez le nombre entre %d et %d ? \n", MIN, nombreMax);
            scanf("%d", &nombreEntre);

            // On compare le nombre entré avec le nombre mystère

            if (nombreMystere > nombreEntre)
                printf("C'est plus !\n\n");
            else if (nombreMystere < nombreEntre)
                printf("C'est moins !\n\n");
            else
                printf("Bravo, vous avez trouve le nombre mystere en %d coups !!!\n\n", compteur);

        } while (nombreEntre != nombreMystere);

        // on demande au joueur si il veux continuer
                printf("Voulez vous recomencer une partie ? O/N \n");
                printf("1 - Oui \n");
                printf("2 - Non \n");

                scanf("%d", &continuerPartie);
                switch(continuerPartie)
                {
                case 1:
                    continuerPartie = 1;
                    break;
                case 2:
                    continuerPartie = 0;
                    break;
                default:
                    continuerPartie = 1;
                    break;
                }
    }
    return 0;
}
