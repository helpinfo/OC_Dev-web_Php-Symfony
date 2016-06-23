#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <FMOD/fmod.h>

#define LARGEUR_FENETRE         512 /* DOIT rester � 512 imp�rativement car il y a 512 barres (correspondant aux 512 floats) */
#define HAUTEUR_FENETRE         400 /* Vous pouvez la faire varier celle-l� par contre :o) */
#define RATIO                   (HAUTEUR_FENETRE / 255.0)
#define DELAI_RAFRAICHISSEMENT  25 /* Temps en ms entre chaque mise � jour du graphe. 25 ms est la valeur minimale. */

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);


int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *ligne = NULL;
    SDL_Event event;
    SDL_Rect position;
    int continuer = 1, hauteurBarre = 0, tempsActuel = 0, tempsPrecedent = 0, i = 0, j = 0;
    float *spectre = NULL;

    /* Initialisation de FMOD
       ----------------------

    On charge FMOD, la musique, on active le module DSP et on lance la lecture
    de la musique */

    FSOUND_Init(44100, 4, 0);
    FSOUND_STREAM* musique = FSOUND_Stream_Open("ma_musique.mp3", 0, 0, 0);
    if (musique == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir la musique");
        exit(EXIT_FAILURE);
    }
    FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), 1);
    FSOUND_Stream_Play(FSOUND_FREE, musique);


    /* Initialisation de la SDL
       ------------------------

    On charge la SDL, on ouvre la fen�tre et on �crit dans sa barre de titre.
    On r�cup�re au passage un pointeur vers la surface ecran, qui sera la seule
    surface utilis�e dans ce programme */

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Visualisation spectrale du son", NULL);



    /* Boucle principale */

    while (continuer)
    {
        SDL_PollEvent(&event); /* On doit utiliser PollEvent car il ne faut pas attendre d'�v�nement
                                de l'utilisateur pour mettre � jour la fen�tre*/
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
        }

        /* On efface l'�cran � chaque fois avant de dessiner le graphe (fond noir */
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));


        /* Gestion du temps
           -----------------
        On compare le temps actuel par rapport au temps pr�c�dent (dernier passage dans la boucle)
        Si �a fait moins de 25 ms (DELAI_RAFRAISSEMENT), alors on attend le
        temps qu'il faut pour qu'au moins 25 ms se soit �coul�es. On met ensuite �
        jour tempsPrecedent avec le nouveau temps */

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent < DELAI_RAFRAICHISSEMENT)
        {
            SDL_Delay(DELAI_RAFRAICHISSEMENT - (tempsActuel - tempsPrecedent));
        }
        tempsPrecedent = SDL_GetTicks();



        /* Dessin du spectre sonore
           ------------------------

        C'est la partie la plus int�ressante. Il faut r�fl�chir un peu � la fa�on
        de dessiner pour y arriver, mais c'est tout � fait faisable (la preuve ^^ )

        On r�cup�re le pointeur vers le tableau de 512 floats via FSOUND_DSP_GetSpectrum()
        On travaille ensuite pixel par pixel sur la surface ecran pour dessiner les barres.
        On fait une premi�re boucle pour parcourir la fen�tre en largeur.
        La seconde boucle parcourt la fen�tre en hauteur pour chaque barre.
        */

        spectre = FSOUND_DSP_GetSpectrum(); /* On r�cup�re le pointeur vers le tableau de 512 floats */

        SDL_LockSurface(ecran); /* On bloque la surface ecran car on va directement modifier ses pixels */

        /* BOUCLE 1 : on parcourt la fen�tre en largeur (pour chaque barre verticale) */
        for (i = 0 ; i < LARGEUR_FENETRE ; i++)
        {
            /* On calcule la hauteur de la barre verticale qu'on va dessiner.
            spectre[i] nous renvoie un nombre entre 0 et 1 qu'on multiplie par 4 pour zoomer
            afin de voir un peu mieux (comme je vous avais dit). On multiplie ensuite
            par HAUTEUR_FENETRE pour que la barre soit agrandie par rapport � la taille
            de la fen�tre */
            hauteurBarre = spectre[i] * 4 * HAUTEUR_FENETRE;

            /* On v�rifie que la barre ne d�passe pas la hauteur de la fen�tre
            Si tel est le cas on coupe la barre au niveau de la hauteur de la fen�tre */
            if (hauteurBarre > HAUTEUR_FENETRE)
                hauteurBarre = HAUTEUR_FENETRE;

            /* BOUCLE 2 : on parcourt en hauteur la barre verticale pour la dessiner */
            for (j = HAUTEUR_FENETRE - hauteurBarre ; j < HAUTEUR_FENETRE ; j++)
            {
                /* On dessine chaque pixel de la barre � la bonne couleur.
                On fait simplement varier le rouge et le vert, chacun dans un sens diff�rent

                j ne varie pas entre 0 et 255 mais entre 0 et HAUTEUR_FENETRE. Si on veut l'adapter
                proportionnellement � la hauteur de la fen�tre, il suffit de faire le calcul
                j / RATIO, o� RATIO vaut (HAUTEUR_FENETRE / 255.0)
                J'ai d� r�fl�chir 2-3 minutes pour trouver le bon calcul � faire, mais c'est
                du niveau de tout le monde. Il suffit de r�fl�chir un tout petit peu ^^ */
                setPixel(ecran, i, j, SDL_MapRGB(ecran->format, 255 - (j / RATIO), j / RATIO, 0));
            }
        }

        SDL_UnlockSurface(ecran); /* On a fini de travailler sur l'�cran, on d�bloque la surface */

        SDL_Flip(ecran);
    }



    /* Le programme se termine.
    On d�sactive le module DSP, on lib�re la musique de la m�moire
    et on ferme FMOD et SDL */
    FSOUND_DSP_SetActive(FSOUND_DSP_GetFFTUnit(), 0);
    FSOUND_Stream_Close(musique);
    FSOUND_Close();

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
