#include <stdio.h>
#include <stdlib.h>

void v(FILE** fptr, char*** id, char*** pozicia, char*** veliciny, char*** hodnota, char*** cas, char*** datum/*mozno bude treba zmenit datovy typ...*/){
    /*
    Najprv zistujeme stav pointeru na subor. 
        - Ak subor nebol otvoreny, skusame ho otvorit
            - Ak neuspesne, vypise sa text
            - Ak uspesne, zistujeme status dynamickych polí - ich existenciu
                - Ak existuju = bola volana funkcia n(), vypiseme ich obsah
                - Ak neexistuju, vypiseme zaznamy zo suboru
    */
    if (*fptr == NULL)
    {   
        *fptr = fopen("dataloger.txt", "r");
    }
    int i = 0, len, n_of_scanned;
        char* data_storage = (char*)calloc(50, sizeof(char)*10);
        if (*fptr == NULL){
            printf("Neotvoreny subor\n");
            exit(1);
        }else if ((id == NULL)||(pozicia == NULL)||(veliciny == NULL)||(hodnota == NULL)||(cas == NULL)||(datum == NULL))
        {
           while (1)
           {
                i++;
                n_of_scanned = fscanf(*fptr, "%s", data_storage);
                if (n_of_scanned == -1)
                {
                    break;
                }
                
                switch (i)
                {
                    case 1:
                        printf("ID mer. modulu: %s\n", data_storage);
                        break;
                    
                    case 2:
                        printf("Pozicia modulu: %s\n", data_storage);
                        break;

                    case 3:
                        printf("Typ mer. veliciny: %s\n", data_storage);
                        break;
                    case 4:
                        printf("Hodnota: %s\n", data_storage);
                        break;
                    
                    case 5:
                        printf("Cas merania: %s\n", data_storage);
                        break;

                    case 6:
                        printf("Datum merania: %s\n\n", data_storage);
                        i = 0;
                        break;
                }
           }
           
        }
}

void n(FILE** fptr, int* pocet_zaznamov, char*** id, char*** pozicia, char*** veliciny, char*** hodnota, char*** cas, char*** datum){
    if (*fptr == NULL)
    {
        printf("Neotvorený subor.");
        exit(1);
    }else{
        int n_of_scanned = 0, i;
        char* data_storage = (char*)calloc(50, sizeof(char)*10);
        while (1)
           {
                i++;
                n_of_scanned = fscanf(&*fptr, "%s", data_storage);
                if (n_of_scanned == -1)
                {
                    break;
                }
                
                switch (i)
                {
                    case 1:
                        printf("ID mer. modulu: %s\n", data_storage);
                        break;
                    
                    case 2:
                        printf("Pozicia modulu: %s\n", data_storage);
                        break;

                    case 3:
                        printf("Typ mer. veliciny: %s\n", data_storage);
                        break;
                    case 4:
                        printf("Hodnota: %s\n", data_storage);
                        break;
                    
                    case 5:
                        printf("Cas merania: %s\n", data_storage);
                        break;

                    case 6:
                        printf("Datum merania: %s\n\n", data_storage);
                        i = 0;
                        break;
                }
           }
        
        
    }
    
}

int main(void){
    FILE *ptr_dataloger = NULL;
    int pocet_zaznamov = 0;
    char ***zaznam_id = NULL, ***zaznam_pozicia = NULL, ***zaznam_veliciny = NULL, ***zaznam_hodnot = NULL, ***zaznam_casov = NULL, ***zaznam_datumov = NULL;//mozno bude treba zmenit datovy typ...
    v(&ptr_dataloger, zaznam_id, zaznam_pozicia, zaznam_veliciny, zaznam_hodnot, zaznam_casov, zaznam_datumov);
    n(&ptr_dataloger, &pocet_zaznamov, zaznam_id, zaznam_pozicia, zaznam_veliciny, zaznam_hodnot, zaznam_casov, zaznam_datumov);
    return 0;
}