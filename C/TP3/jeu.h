#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

void jouer(SDL_Surface* ecran);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
void deplacerCaisse(int *premiereCase, int *secondeCase);

#endif // JEU_H_INCLUDED
