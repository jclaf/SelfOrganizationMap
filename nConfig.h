#ifndef _NCONFIG_H
#define _NCONFIG_H

#include "Parsing.h"
#include "Node.h"
#include "Bmu.h"
#include "Vec.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))

//Configuration du reseau
typedef struct nConfig_t
{
    int nb_nodes;
    int nb_ligne;
    int nb_colonne;
    Bmu_t* bmu;
    Node_t** Map;
    int nb_it; //nombre itération
    int Nhd_size; // taille du voisinage
    double alpha;
}nConfig_t;

void print_map_test(nConfig_t* c);
void print_map(nConfig_t* c);

double* average_vector(Vec_t* data, int n);
double* min_vector(double * d, double n);
double* max_vector(double * d, double n);


//double activation_fct(Vec_t* data, Node_t* n);
void learning_rate(nConfig_t * c,double alpha_init,int t, int t_total);
int neighbor(nConfig_t* c,int i, int j, Bmu_t* head);
double dist_data_node(double * d1, double*d2);
void update_BMU(double * data, nConfig_t* c);
//void select_BMU(int * x,int * y,intnConfig_t * c);
Bmu_t * choose_best(Bmu_t *tmp_Bmu);
void search_BMU(Vec_t *data,nConfig_t* c, int k);

void test_som(Vec_t * data, nConfig_t* c);
void training_som(Vec_t * data, nConfig_t* c);
double* init_random_w(double* min, double* max);
void init_network(nConfig_t *c,double* min, double* max, int n);


#endif
