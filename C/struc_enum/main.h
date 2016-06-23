#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

void initialiserCoordonnees(Coordonnees* point);

typedef struct Coordonnees Coordonnees;
struct Coordonnees
{
    int x; // Abscisses
    int y; // Ordonn�es
};

typedef struct Personne Personne;
struct Personne
{
    char nom[100];
    char prenom[100];
    char adresse[1000];

    int age;
    int garcon; // Bool�en : 1 = gar�on, 0 = fille
};

typedef enum Volume Volume;
enum Volume
{
    MUET = 0,
    FAIBLE = 10,
    MOYEN = 50,
    FORT = 100
};

#endif // MAIN_H_INCLUDED
