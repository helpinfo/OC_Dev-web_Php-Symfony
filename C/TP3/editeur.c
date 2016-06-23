#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "editeur.h"

void editeur(SDL_Surface* ecran)
{
    SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL;
    SDL_Rect position;
    SDL_Event event;

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0;
    int objetActuel = MUR, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    // Chargement des objets et du niveau
    mur = IMG_Load("mur.jpg");
    caisse = IMG_Load("caisse.jpg");
    objectif = IMG_Load("objectif.png");
    mario = IMG_Load("mario_bas.gif");

    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE);

    switch (event.type)
    {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                // On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
                carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                clicGaucheEnCours = 1; // On retient qu'un bouton est enfoncé
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) // Clic droit pour effacer
            {
                carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] = VIDE;
                clicDroitEnCours = 1;
            }
            break;
        case SDL_MOUSEBUTTONUP: // On désactive le booléen qui disait qu'un bouton était enfoncé
            if (event.button.button == SDL_BUTTON_LEFT)
                clicGaucheEnCours = 0;
            else if (event.button.button == SDL_BUTTON_RIGHT)
                clicDroitEnCours = 0;
            break;
        case SDL_MOUSEMOTION:
            if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
            {
                carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
            }
            else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
            {
                carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
            }
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    continuer = 0;
                    break;
                case SDLK_s:
                    sauvegarderNiveau(carte);
                    break;
                case SDLK_c:
                    chargerNiveau(carte);
                    break;
                case SDLK_1:
                    objetActuel = MUR;
                    break;
                case SDLK_2:
                    objetActuel = CAISSE;
                    break;
                case SDLK_3:
                    objetActuel = OBJECTIF;
                    break;
                case SDLK_4:
                    objetActuel = MARIO;
                    break;
            }
            break;
    }

    // Effacement de l'écran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    // Placement des objets à l'écran
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            position.x = i * TAILLE_BLOC;
            position.y = j * TAILLE_BLOC;

            switch(carte[i][j])
            {
                case MUR:
                    SDL_BlitSurface(mur, NULL, ecran, &position);
                    break;
                case CAISSE:
                    SDL_BlitSurface(caisse, NULL, ecran, &position);
                    break;
                case OBJECTIF:
                    SDL_BlitSurface(objectif, NULL, ecran, &position);
                    break;
                case MARIO:
                    SDL_BlitSurface(mario, NULL, ecran, &position);
                    break;
            }
        }
    }

    // Mise à jour de l'écran
    SDL_Flip(ecran);

    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(mario);
}
