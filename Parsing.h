#ifndef _PARSING_H
#define _PARSING_H

#include "Vec.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//faire un parsing des données et les mélange 
//remplir les structures
void printArray(Vec_t* data, int n);
void swap(Vec_t * a, Vec_t * b);
void shuffle(Vec_t *data, int n);
void update_label(char* v);
void norm_v(Vec_t* data, int cpt);
void norm_w(double* x, int cpt);
double DistEuclBis(double *x, int cpt);
double DistEucl(double *x,double *y,int cpt);
//void charger_fichier(Vec_t *data,size_t len,int count, char *line);
int lire_fichier(Vec_t *data,const char* file);
bool fichier_exist(const char* file);

#endif