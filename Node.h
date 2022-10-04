#ifndef _NODE_H
#define _NODE_H

//neurone 60

typedef struct Node_t
{
    double* w; //vecteur mémoire
    double act; //fonction d'activation
    char* id; //nom de la donnée
}Node_t;

#endif