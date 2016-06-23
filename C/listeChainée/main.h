#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    Element *premier;
};

#endif // MAIN_H_INCLUDED
