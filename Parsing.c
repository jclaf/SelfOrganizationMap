#include "Parsing.h"


void printArray(Vec_t* data, int n)
{
    printf("printArray\n:");
    for (int i = 0; i <n; i++)
    {
        printf("%d ",i);
        for (int j = 0; j < 4; j++)
        {
            printf("%lf ",data[i].v[j]);
        }
        printf("%s ",data[i].etiq);
        printf("Norme : %.2f \n",data[i].norm);
    }
}

void swap(Vec_t *a, Vec_t *b)
{
    Vec_t temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(Vec_t *data, int n)
{
    int j;
    srand(time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i);
        swap(&data[i], &data[j]);
    }
}


void update_label(char* v)
{
    if(strcmp(v,"Iris-setosa") ==0) strcpy(v,"S");
    if(strcmp(v,"Iris-virginica")==0) strcpy(v,"A");
    if(strcmp(v,"Iris-versicolor")==0) strcpy(v,"R");
}

void norm_v(Vec_t* data, int cpt)
{
    for (int i = 0; i < cpt; i++)
        for (int j = 0; j < 4; j++)
            data[i].v[j] = data[i].v[j]/data[i].norm;    
}

void norm_w(double* x, int cpt)
{
    double norm = DistEuclBis(x,cpt);

    for (int i = 0; i < cpt; i++)
        x[i] = x[i] /norm;   
}

double DistEuclBis(double *x, int cpt)
{
    int i = 0;
    double sum_tmp = 0.0;
    for(i=0;i<cpt;i++)
        sum_tmp += pow(x[i],2);
    //printf("%.2lf\n",sum_total);
    return sqrt(sum_tmp);
}

double DistEucl(double *x,double *y, int cpt)
{
    int i = 0;
    double sum_tmp = 0.0;
    for(i=0;i<cpt;i++)
        sum_tmp += pow(x[i]-y[i],2);
    //printf("%.2lf\n",sum_total);
    return sqrt(sum_tmp);
}

/*
void charger_fichier(Vec_t *data, size_t len,int count, char *line)
{
    int i = 0;
    double x[2];
    double y[2];
    //delimitation de la chaine de caractère
    char* tmp = strtok(line,",");
    
    while(tmp != NULL){
        //printf("%s",tmp);
        
        if(i == 4){ 
            data[count].etiq= (char*)malloc(20*sizeof(char));
            data[count].etiq = strtok(tmp,"\n");
        }else {
            data[count].v = (double*)malloc(4*sizeof(double));
            data[count].v = (double*)tmp;
            if(i < 2) x[i]=strtod(tmp,NULL);
            else y[i-2]=strtod(tmp,NULL);
        }
        tmp = strtok(NULL,",");
        
        i++;
    }
    //Normalisation
    

    for (int i = 0; i < 2; i++)
    {
        printf("test_x %.2f ",x[i]);
        printf("test_y %.2f ",y[i]);
    }
    printf("\n");
    
    memset(x, '0', 2);
    memset(y, '0', 2);
    
    //Chargement des donnée vecteurs et etiquettes
    for (int i = 0; i < 6; i++)
    {
        data->v = (double*)malloc(sizeof(double*));
        if(i == 4){ 
            data->etiq = (char*)malloc(sizeof(char*));
            strcpy(data->etiq,tmp);
        }else if(i == 5){
            //Normalisation
            //double x[2] ={strtod(tmp[i-5],NULL),atof(&(tmp[i-4]))};
            //double y[2] ={atof(&(tmp[i-3])),atof(&(tmp[i-2]))};
            //data->norm = DistEucl(x,y);
        }
        else {
            
            //(data->v)[i] = strtod(tmp[i],NULL);
        }
        
    }
    //Affichage
    
    
}*/




//Crée un fichier

int lire_fichier(Vec_t* vec, const char* file)
{
    FILE *fd; 
	ssize_t nread;
    size_t len = 255;
	//char *line = NULL;
    int count = 0;
    double x[2], y[2];
    fd = fopen(file, "r");
    
    vec[count].v = (double*)malloc(4*sizeof(double));
    vec[count].etiq = (char*)malloc(20*sizeof(char));
    while((fscanf(fd,"%lf,%lf,%lf,%lf,%s\n",&vec[count].v[0],&vec[count].v[1],&vec[count].v[2],&vec[count].v[3],vec[count].etiq) !=  EOF) )
    {   
        update_label(vec[count].etiq);
        count++;
        vec[count].v = (double*)malloc(4*sizeof(double));
        vec[count].etiq = (char*)malloc(20*sizeof(char));
    }
    //printArray(vec, 150);
    //vecteur norme
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if(j == 0) x[0] = vec[i].v[j];
            else if (j == 1) y[0] = vec[i].v[j];
            else if (j == 2) x[1] =vec[i].v[j];
            else y[1] = vec[i].v[j];
        }
        //printf("parametre norme %lu %lu %ld \n", sizeof(vec[i].v), sizeof(vec[i].v[0]), sizeof(vec[i].v)/sizeof(vec[i].v[0]));
        vec[i].norm = DistEucl(x,y,2);
    }

    norm_v(vec,150);

    /*
    while ((nread = getline(&line, &len, fd)) != -1) {    
        charger_fichier(vec,len,count,line);
        count++;

        
	}*/
    //printArray(vec,150);
    //printf("%d\n",count);
    /*for (int i = 0; i <count; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%lf ",vec[i].v[j]);
        }
        
        
        printf("%s ",vec[i].etiq);
        printf("Norme : %.2f \n",vec[i].norm);

        //printf("\n");
    }*/
    //printArray(vec,150);
    //free(line);
    fclose(fd);
    return 0;
}

//verifie l'existence du fichier
bool fichier_exist(const char* file)
{
    FILE *fd;
    if (fd = fopen(file, "r"))
    {
        fclose(fd);
        return true;
    }
  return false;
}


