#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL_image.h>

int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *zozor = NULL;
    SDL_Rect positionZozor;
    SDL_Event event;
    int continuer = 1;
    int pause = 1;
    int tempsPrecedent = 0, tempsActuel = 0;
    int versLaDroite = 1;

    SDL_Init(SDL_INIT_VIDEO );

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Gestion du temps en SDL", NULL);

    zozor = SDL_LoadBMP("zozor.bmp");
    SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format, 0, 0, 255));

    positionZozor.x = ecran->w / 2 - zozor->w / 2;
    positionZozor.y = ecran->h / 2 - zozor->h / 2;

    SDL_EnableKeyRepeat(10, 10);

    while (continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_p:
                        // voir comment mettre pause au defilement de zozor
                        break;
                }
                break;
        }

        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 30) /* Si 30 ms se sont écoulées */
        {
            if (versLaDroite)
            {
                positionZozor.x++; /* On bouge Zozor */
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */

                if (positionZozor.x + zozor->w == ecran->w)
                {
                    versLaDroite = 0;
                }
            }
            else
            {
                positionZozor.x--; /* On bouge Zozor */
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */

                if (positionZozor.x == 0)
                {
                    versLaDroite = 1;
                }
            }
        }
        else /* Si ça fait moins de 30 ms depuis le dernier tour de boucle, on endort le programme le temps qu'il faut */
        {
            SDL_Delay(30 - (tempsActuel - tempsPrecedent));
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);
        SDL_Flip(ecran);
    }

    SDL_FreeSurface(zozor);
    SDL_Quit();

    return EXIT_SUCCESS;
}
