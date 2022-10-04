#ifndef _BMU_H
#define _BMU_H

//Best Match Unit

typedef struct Bmu_t
{
    int l; //ligne
    int c; //colonne
    struct Bmu_t* next;
}Bmu_t;



#endif