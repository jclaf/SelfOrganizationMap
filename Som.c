#include "som.h"


int run(int argc, const char **argv)
{
    Vec_t* vec = (Vec_t *)calloc(150,sizeof(Vec_t));
    nConfig_t* config = (nConfig_t *)malloc(sizeof(nConfig_t));
    //lire_fichier(vec,"iris.data");
    if(argc >= 2){
        if(fichier_exist(argv[1]) == true) lire_fichier(vec,argv[1]);
        else {
            printf("Veuillez charger un fichier existant");
            return EXIT_FAILURE;
        }
    }
    //size_t n = sizeof(vec)/sizeof(*vec);
    //printArray(vec,150);
        
    double* moyenne = average_vector(vec,150);
    double* min = min_vector(moyenne,0.02);
    double* max = max_vector(moyenne,0.05);
    
    init_network(config,min,max,150);
    printf("Chargement de la Map: \n");
    print_map(config);
    
    //srand(time(NULL));
    //int i = rand() % (150);
    training_som(vec,config);
    //training_som(vec,config);
    printf("Après l'entrainement : \n");
    print_map(config);
    test_som(vec,config);
    printf("Résultat final : \n");
    //print_map_test(config);
    print_map(config);
    free(moyenne);
    free(min);
    free(max);
    free(vec);
    free(config);
    return 0;
}