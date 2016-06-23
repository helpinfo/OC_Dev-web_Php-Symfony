#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL_image.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *zozor = NULL;
    SDL_Rect positionZozor;
    SDL_Event event; /* La variable contenant l'événement */
    int continuer = 1; /* Notre booléen pour la boucle */

    SDL_Init(SDL_INIT_VIDEO);

    SDL_WM_SetCaption("Gestion des événements en SDL", NULL);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_RESIZABLE);
    zozor = SDL_LoadBMP("zozor.bmp");
    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format, 0, 0, 255));

    /* On centre Zozor à l'écran */
    positionZozor.x = ecran->w / 2 - zozor->w / 2;
    positionZozor.y = ecran->h / 2 - zozor->h / 2;


    SDL_EnableKeyRepeat(10, 10); // repetition des touche 10ms
    SDL_ShowCursor(SDL_DISABLE); // Masquer curseur de la souris
    SDL_WarpMouse(ecran->w / 2, ecran->h / 2); //place le curseur au centre de l'ecran

    while (continuer) /* TANT QUE la variable ne vaut pas 0 */
    {
        SDL_WaitEvent(&event); /* On attend un événement qu'on récupère dans event */
        switch(event.type) /* On teste le type d'événement */
        {
            case SDL_QUIT: /* Si c'est un événement QUITTER */
                continuer = 0; /* On met le booléen à 0, donc la boucle va s'arrêter */
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        positionZozor.y--;
                        break;
                    case SDLK_DOWN: // Flèche bas
                        positionZozor.y++;
                        break;
                    case SDLK_RIGHT: // Flèche droite
                        positionZozor.x++;
                        break;
                    case SDLK_LEFT: // Flèche gauche
                        positionZozor.x--;
                        break;
                }
                break;
                case SDL_MOUSEBUTTONUP: /* Clic de la souris */
                    switch(event.button.button)
                    {
                        /* case SDL_BUTTON_LEFT:
                            positionZozor.x = event.button.x;
                            positionZozor.y = event.button.y;
                            break; */
                        case SDL_BUTTON_RIGHT:
                            continuer = 0;
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    positionZozor.x = event.motion.x;
                    positionZozor.y = event.motion.y;
                    break;
                case SDL_VIDEORESIZE:
                    positionZozor.x = event.resize.w / 2 - zozor->w / 2;
                    positionZozor.y = event.resize.h / 2 - zozor->h / 2;
                    break;
        }
        /* On efface l'écran (ici fond blanc) : */
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

        /* On fait tous les SDL_BlitSurface nécessaires pour coller les surfaces à l'écran */
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);

        /* On met à jour l'affichage : */
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(zozor);
    SDL_Quit();

    return EXIT_SUCCESS;
}
