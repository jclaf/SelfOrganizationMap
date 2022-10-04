#include "nConfig.h"
void print_map_test(nConfig_t* c)
{
    for(int i=0;i<c->nb_ligne;i++)
    {
        for(int j=0;j<c->nb_colonne;j++)
            {
                for(int k=0;k<4;k++)
                {
                printf("%lf ",c->Map[i][j].w[k]);
                }
        printf("\n");
        }
    }
}

void print_map(nConfig_t* c)
{
    for(int i=0;i<c->nb_ligne;i++)
    {
        for(int j=0;j<c->nb_colonne;j++)
            {
                printf("%s ",c->Map[i][j].id);
            }
        printf("\n");
    }
}

//permet d'obtenir la moyenne des vecteurs données
double* average_vector(Vec_t* data,int n)
{
    double *tmp = malloc(4*sizeof(double));
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < n; j++)
            tmp[i]+= data[j].v[i];
        tmp[i]=tmp[i]/n;
        //printf("tmp[%d] : %lf", i,tmp[i]);
    }
    return tmp;
}

double* min_vector(double* d, double n)
{
    double* tmp = malloc(4*sizeof(double));
    for (int i = 0; i < 4; i++)
        tmp[i] = d[i]-n;
    return tmp;
}

double* max_vector(double* d, double n)
{
    double* tmp = malloc(4*sizeof(double));
    for (int i = 0; i < 4; i++)
        tmp[i] = d[i]+n;
    return tmp;
}

//nConfig->alpha
void learning_rate(nConfig_t * c, double alpha_init,int t, int t_total)
{
    c->alpha = alpha_init * (1-((double)t/(double)t_total));
}

int neighbor(nConfig_t* c,int i, int j,Bmu_t* head)
{
    int row = (head->l-1)/c->nb_ligne;
    int col = (head->c-1)%c->nb_colonne;
    int dR1 = max(0, (row - c->Nhd_size));
    int dR2 = min(c->nb_ligne, (row + c->Nhd_size));
    int dC1 = max(0, (col - c->Nhd_size));
    int dC2 = min(c->nb_colonne, (col + c->Nhd_size));
    return (((dR1 <= i) && (i <= dR2)) && ((dC1 <= j) && (j <= dC2)));
    
   /*
    if((head->l-c->Nhd_size)>=0 
    && (head->c-c->Nhd_size)>=0 
    && (head->l+c->Nhd_size)<=c->nb_ligne && (head->c+c->Nhd_size)<=c->nb_ligne && (head->l+c->Nhd_size)<=c->nb_colonne && (head->c+c->Nhd_size)<=c->nb_colonne) return 1;
    return 0;*/
}

void update_BMU(double * v, nConfig_t* c)
{
    int nhd_s = c->Nhd_size;
    int cpt =0;
    int x[2], y[2];
    while(cpt <= nhd_s)
    {
        //top
        x[0] = (c->bmu->l-cpt<0)? 0 : c->bmu->l-cpt;
        y[0] = (c->bmu->c-cpt<0)? 0 : c->bmu->c-cpt ;
        
        //bottom
        x[1] = (c->bmu->l+cpt>c->nb_ligne)?c->nb_ligne: c->bmu->l+cpt;
        y[1] = (c->bmu->c+cpt>c->nb_colonne)?c->nb_colonne:c->bmu->c+cpt;
        //printf("x[%d]-y[%d]",x[1],y[1]);
        
            for (int i = x[0]; i < x[1]; i++){
                for (int j = y[0]; j < y[1]; j++){
                    //if(neighbor(c,i, j, c->bmu)){
                        for(int k= 0; k < 4; k++){
                            c->Map[i][j].w[k]+=c->alpha*(v[k]-c->Map[i][j].w[k]);
                            
                        }
                    //}
                }
            }
           cpt++;
       // }
    }
}

void select_BMU(int* x, int *y,int k, nConfig_t * c)
{
    printf("%d",k);
    Bmu_t* tmp = c->bmu;
    int choice = rand()% k;
    while(choice != 0)
    {
        tmp = tmp->next;
        choice--;
    }
    *x = tmp->l;
    *y = tmp->c;
    //return &tmp[0];
}

Bmu_t * choose_best(Bmu_t *tmp_Bmu)
{
    int cpt =0;
    while(tmp_Bmu->next){
        cpt++;
        tmp_Bmu = tmp_Bmu->next;
    }
    if(cpt>1){
        srand(time(NULL));
        int r = rand()%cpt;
        int k =1;
        while(k!=r && tmp_Bmu->next){
            tmp_Bmu = tmp_Bmu->next;
            k++;
        }
        Bmu_t* n_win = (Bmu_t*)malloc(sizeof(Bmu_t));
        n_win->l=tmp_Bmu->l;
        n_win->c=tmp_Bmu->c;
        n_win->next = NULL;
        return n_win;
    }
    return tmp_Bmu;
}



void search_BMU(Vec_t *data, nConfig_t* c, int k)
{
    //Bmu_t* tmp_Bmu = NULL;
    //Bmu_t* n_win = (Bmu_t*)malloc(sizeof(Bmu_t));
    //Bmu_t* tmp_Bmu = (Bmu_t*)malloc(sizeof(Bmu_t));
    
    double min_dist = 9999.;
    int bmu_size = 0;
    for (int i = 0; i < c->nb_ligne; i++)
    {
        for (int j = 0; j < c->nb_colonne; j++)
        {
            c->Map[i][j].act = DistEucl(data[k].v,c->Map[i][j].w, 4);
            if(c->Map[i][j].act<min_dist)
            {
                
                min_dist = c->Map[i][j].act;
                //free(tmp_Bmu);
                c->bmu->l=i;
                c->bmu->c=j;
                c->bmu->next = NULL;
                
                
                
                //c->bmu = win;
                bmu_size = 1;
                //continue;
                /*if(c->bmu->next == NULL){
                    min_dist = c->Map[i][j].act;
                    c->bmu->next = tmp_Bmu;
                }else{
                    min_dist = c->Map[i][j].act;
                    tmp = c->bmu->next;
                    c->bmu->next = tmp_Bmu;
                    tmp_Bmu->next = tmp;
                }*/
                
                
               // c->bmu->l = i;
               // c->bmu->c = j;
                
                
                //c->bmu = c->bmu->next;
            }


        

           /* if( c->Map[i][j].act == min_dist && !bmu_size)
            {
                Bmu_t* tmp_Bmu = c->bmu;
                Bmu_t* n_win = (Bmu_t*)malloc(sizeof(Bmu_t));
                while(tmp_Bmu != NULL && tmp_Bmu->next != NULL)
                   tmp_Bmu = tmp_Bmu->next;
                //bmu_size+=1;
                n_win->l=i;
                n_win->c=j;
                n_win->next = NULL;
                tmp_Bmu->next=n_win;
            }*/
        }
    }
    
    c->bmu = choose_best(c->bmu);

}

void test_som(Vec_t * data, nConfig_t* c)
{
    double min_dist = 9999.;
    shuffle(data,150);
    for (int i = 0; i < c->nb_ligne; i++)
    {
        for (int j = 0; j < c->nb_colonne; j++)
        {
            for (int k = 0; k < 150; k++)
            {
                c->Map[i][j].act = DistEucl(c->Map[i][j].w,data[k].v, 4);
                if(c->Map[i][j].act<min_dist){
                    //strcpy(c->Map[c->bmu->l][c->bmu->c].id, data[k].etiq);
                    min_dist = c->Map[i][j].act;
                }
                //strcpy(c->Map[c->bmu->l][c->bmu->c].id, data[k].etiq);
            }
            min_dist = 9999.;
        }
    }
    
}


void training_som(Vec_t * data, nConfig_t* c)
{  
    //double min_dist = 9999.;
    //phase 1
    double alpha_init = c->alpha;
    for (int i = 0; i < c->nb_it/4; i++)
    {
        
        learning_rate(c,alpha_init,i,c->nb_it);
        shuffle(data,150);
        for (int k = 0; k < 150; k++)
        {
            //search BMU
            //int bmu_size = 1, x=0, y=0;
            search_BMU(data, c, k);
           // min_dist = 9999.;
            //printf("%d \n", bmu_size);
            //select_BMU(&x,&y,k,c); 
            /*Bmu_t * win = c->bmu;
            while(win != NULL)  {
                strcpy(c->Map[win->l][win->c].id, data[k].etiq);
                win = win->next;
            }*/
               
                 
            update_BMU(data[k].v,c);  
        }
    }
    alpha_init = 0.08;
    //phase 2
    for (int i = 0; i < c->nb_it - (c->nb_it/4); i++)
    {
        
        
        c->Nhd_size = round(0.4*c->nb_nodes);
        if(i>=500 && i<1000) c->Nhd_size = round(.3*c->nb_nodes);
        else c->Nhd_size = 8;
        learning_rate(c,alpha_init,i,c->nb_it);
        shuffle(data,150);
        for (int k = 0; k < 150; k++)
        {
            //search BMU
            //int bmu_size = 1, x=0, y=0;
            search_BMU(data, c, k);
            //min_dist = 9999.;
            //printf("%d \n", bmu_size);
            //select_BMU(&x,&y,k,c); 
            Bmu_t * win = c->bmu;
            while(win != NULL)  {
                strcpy(c->Map[win->l][win->c].id, data[k].etiq);
                win = win->next;
            }
                  
            update_BMU(data[k].v,c);  
        }
    }
}

double* init_random_w(double* min, double* max)
{
    double k = (double)rand()/(RAND_MAX+1.0); 
    double * tmp = malloc(4*sizeof(double));
    for (int i = 0; i < 4; i++)
        tmp[i]=k*(max[i]-(double)abs(min[i]))+(double)abs(min[i]);
    return tmp;
}


void init_network(nConfig_t *c, double* min, double* max, int n)
{
    c->nb_nodes = 5*sqrt(n);
    c->nb_ligne = c->nb_nodes/10;
    c->nb_colonne = 10;

    //initialisation BMU
    c->bmu = (Bmu_t*)malloc(sizeof(Bmu_t));
    
    c->bmu->next = NULL;
    //initialisation Map
    c->Map = (Node_t**)malloc(c->nb_ligne*sizeof(Node_t*));
    for (int x = 0; x < c->nb_ligne; x++)
    {
        c->Map[x] = (Node_t*)malloc(sizeof(Node_t)*c->nb_colonne);
    }
    
    for (int x = 0; x < c->nb_ligne; x++)
    {
        for (int y = 0; y < c->nb_colonne; y++)
        {
            //c->Map[x][y].w = (double*)malloc(4*sizeof(double));
            c->Map[x][y].w = init_random_w(min,max);
            norm_w(c->Map[x][y].w, 4);
            c->Map[x][y].id = (char*)malloc(20*sizeof(char));
            strcpy(c->Map[x][y].id, ".");
            c->Map[x][y].act = 0;
        }   
    }

/*
for (int x = 0; x < c->nb_ligne; x++)
    {
        for (int y = 0; y < c->nb_colonne; y++)
        {
    for (int i = 0; i < 4; i++)
    {
        printf("%lf ",c->Map[x][y].w[i]);
    }
    printf("\n");
        }
    }
    */
    //initialisation itération
    c->nb_it = 2000;
    
    //taille du voisinage 
    c->Nhd_size = round(0.5*c->nb_nodes);

    //alpha
    c->alpha = 0.9;
}


