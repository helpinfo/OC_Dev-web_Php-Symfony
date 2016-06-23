#include <stdlib.h>
#include <stdio.h>

#include <SDL/SDL.h>
#include <SDL_image.h>

int main ( int argc, char** argv )
{
    SDL_Surface *ecran = NULL, *imageDeFond = NULL,*sapin = NULL /*, *zozor = NULL*/;
    SDL_Rect positionFond, positionSapin/*, positionZozor*/;
    SDL_Event event;

    positionFond.x = 0;
    positionFond.y = 0;
    positionSapin.x = 500;
    positionSapin.y = 260;

    /*positionZozor.x = 500;
    positionZozor.y = 260;*/

    SDL_Init(SDL_INIT_VIDEO);

    /* Chargement de l'icône AVANT SDL_SetVideoMode */
    SDL_WM_SetIcon(IMG_Load("sdl_icone.bmp"), NULL);

    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);

    /* Chargement et blittage d'une image Bitmap dans une surface */
    imageDeFond = IMG_Load("lac_en_montagne.bmp");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);


    /* Chargement et blittage de Zozor sur la scène */
   // zozor = SDL_LoadBMP("zozor.bmp");
    /* On rend le bleu derrière Zozor transparent : */
    //SDL_SetColorKey(zozor, SDL_SRCCOLORKEY, SDL_MapRGB(zozor->format, 0, 0, 255));
    /* Transparence Alpha moyenne (128) : */
    //SDL_SetAlpha(zozor, SDL_SRCALPHA, 128);
    /* On blitte l'image maintenant transparente sur le fond : */
    //SDL_BlitSurface(zozor, NULL, ecran, &positionZozor);

    /* Chargement d'un PNG avec IMG_Load
    Celui-ci est automatiquement rendu transparent car les informations de
    transparence sont codées à l'intérieur du fichier PNG */
    sapin = IMG_Load("sapin.png");
    SDL_BlitSurface(sapin, NULL, ecran, &positionSapin);

    SDL_Flip(ecran);

    SDL_FreeSurface(imageDeFond); /* On libère la surface */
    // SDL_FreeSurface(zozor);
    SDL_FreeSurface(sapin);
    SDL_Quit();

    return EXIT_SUCCESS;
}
