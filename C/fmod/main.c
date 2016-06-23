#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <fmod/fmod.h>

#define LARGEUR_FENETRE         512 /* DOIT rester � 512 imp�rativement car il y a 512 barres (correspondant aux 512 floats) */
#define HAUTEUR_FENETRE         400 /* Vous pouvez la faire varier celle-l� par contre */
#define RATIO                   (HAUTEUR_FENETRE / 255.0)
#define DELAI_RAFRAICHISSEMENT  25 /* Temps en ms entre chaque mise � jour du graphe. 25 ms est la valeur minimale. */
#define TAILLE_SPECTRE          512

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL;
    SDL_Event event;
    int continuer = 1, hauteurBarre = 0, tempsActuel = 0, tempsPrecedent = 0, i = 0, j = 0;
    float spectre[TAILLE_SPECTRE];

    /* Initialisation de FMOD
       ----------------------

       On charge FMOD, la musique on lance la lecture de la musique.

    */

    FMOD_SYSTEM *system;
    FMOD_SOUND *musique;
    FMOD_CHANNEL *canal;
    FMOD_RESULT resultat;


    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    /* On ouvre la musique */
    resultat = FMOD_System_CreateSound(system, "ma_musique.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);

    /* On v�rifie si elle a bien �t� ouverte (IMPORTANT) */
    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier mp3\n");
        exit(EXIT_FAILURE);
    }

    /* On joue la musique */
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);

    /* On r�cup�re le pointeur du canal */
    FMOD_System_GetChannel(system, 0, &canal);

    /* Initialisation de la SDL
       ------------------------

       On charge la SDL, on ouvre la fen�tre et on �crit dans sa barre de titre
       On r�cup�re au passage un pointeur vers la surface ecran
       Qui sera la seule surface utilis�e dans ce programme */

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Visualisation spectrale du son", NULL);

    /* Boucle principale */

    while (continuer)
    {
        SDL_PollEvent(&event); // On doit utiliser PollEvent car il ne faut pas attendre d'�v�nement de l'utilisateur pour mettre � jour la fen�tre
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        }

        /* On efface l'�cran � chaque fois avant de dessiner le graphe (fond noir) */
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

        /* Gestion du temps
           -----------------
           On compare le temps actuel par rapport au temps pr�c�dent (dernier passage dans la boucle)
           Si �a fait moins de 25 ms (DELAI_RAFRAICHISSEMENT)
           Alors on attend le temps qu'il faut pour qu'au moins 25 ms se soient �coul�es.
           On met ensuite � jour tempsPrecedent avec le nouveau temps */

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent < DELAI_RAFRAICHISSEMENT)
        {
            SDL_Delay(DELAI_RAFRAICHISSEMENT - (tempsActuel - tempsPrecedent));
        }
        tempsPrecedent = SDL_GetTicks();

        /* Dessin du spectre sonore
           ------------------------

           C'est la partie la plus int�ressante. Il faut r�fl�chir un peu � la fa�on de dessiner pour y arriver, mais c'est tout � fait faisable (la preuve).

           On remplit le tableau de 512 floats via FMOD_Channel_GetSpectrum()
           On travaille ensuite pixel par pixel sur la surface ecran pour dessiner les barres.
           On fait une premi�re boucle pour parcourir la fen�tre en largeur.
           La seconde boucle parcourt la fen�tre en hauteur pour dessiner chaque barre.
        */

        /* On remplit le tableau de 512 floats. J'ai choisi de m'int�resser � la sortie gauche */
        FMOD_Channel_GetSpectrum(canal, spectre, TAILLE_SPECTRE, 0,  FMOD_DSP_FFT_WINDOW_RECT);

        SDL_LockSurface(ecran); /* On bloque la surface ecran car on va directement modifier ses pixels */

        /* BOUCLE 1 : on parcourt la fen�tre en largeur (pour chaque barre verticale) */
        for (i = 0 ; i < LARGEUR_FENETRE ; i++)
        {
            /* On calcule la hauteur de la barre verticale qu'on va dessiner.
               spectre[i] nous renvoie un nombre entre 0 et 1 qu'on multiplie par 20 pour zoomer afin de voir un peu mieux (comme je vous avais dit).
               On multiplie ensuite par HAUTEUR_FENETRE pour que la barre soit agrandie par rapport � la taille de la fen�tre. */
            hauteurBarre = spectre[i] * 20 * HAUTEUR_FENETRE;

            /* On v�rifie que la barre ne d�passe pas la hauteur de la fen�tre
               Si tel est le cas on coupe la barre au niveau de la hauteur de la fen�tre. */
            if (hauteurBarre > HAUTEUR_FENETRE)
                hauteurBarre = HAUTEUR_FENETRE;

            /* BOUCLE 2 : on parcourt en hauteur la barre verticale pour la dessiner */
            for (j = HAUTEUR_FENETRE - hauteurBarre ; j < HAUTEUR_FENETRE ; j++)
            {
                /* On dessine chaque pixel de la barre � la bonne couleur.
                   On fait simplement varier le rouge et le vert, chacun dans un sens diff�rent.

                   j ne varie pas entre 0 et 255 mais entre 0 et HAUTEUR_FENETRE.
                   Si on veut l'adapter proportionnellement � la hauteur de la fen�tre, il suffit de faire le calcul j / RATIO, o� RATIO vaut (HAUTEUR_FENETRE / 255.0).
                   J'ai d� r�fl�chir 2-3 minutes pour trouver le bon calcul � faire, mais c'est du niveau de tout le monde. Il suffit de r�fl�chir un tout petit peu */
                setPixel(ecran, i, j, SDL_MapRGB(ecran->format, 255 - (j / RATIO), j / RATIO, 0));
            }
        }

        SDL_UnlockSurface(ecran); /* On a fini de travailler sur l'�cran, on d�bloque la surface */

        SDL_Flip(ecran);
    }

    /* Le programme se termine.
       On lib�re la musique de la m�moire
       et on ferme FMOD et SDL */

    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);

    SDL_Quit();

    return EXIT_SUCCESS;
}

/* La fonction setPixel permet de dessiner pixel par pixel dans une surface */
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;

    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}
