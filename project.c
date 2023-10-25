#include <stdio.h>
#include <stdlib.h>

void v(FILE** fptr, int* pocet_zaznamov, char** id){
    if (*fptr == NULL)
    {   
        *fptr = fopen("dataloger.txt", "r");
        if (*fptr == NULL){
            printf("Neotvoreny subor\n");
            exit(1);
        }
    }
    int i = 0, j=0, len, n_of_scanned;
    char* data_storage = malloc(sizeof(char)*50);
    if (( id == NULL))
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
                    j++;
                    *pocet_zaznamov = j;
                    break;
            }
        }
        fseek(*fptr, 0, SEEK_SET);
    }else{
        printf("Vypis z data_structure");
    }
}

void n(FILE* fptr, int* pocet_zaznamov, int pocet_hodnot, char** id){
    if (fptr == NULL)
    {
        printf("Neotvorený subor.");
        exit(1);
    }else{
        fseek(fptr, 0, SEEK_SET);
        int n_of_scanned, i;
        char *data_storage = malloc(sizeof(char)*50);
        id = (char**)malloc(sizeof*pocet_zaznamov);
        for (int i = 0; i < *pocet_zaznamov; i++)
        {
            for (int j = 0; j < pocet_hodnot; j++)
            {
                fscanf(fptr, "%s", data_storage);
                switch (j)
                {
                case 0:
                    id[j]=data_storage;
                    break;
                
                default:
                    break;
                }
            }
            
        }
    }
    
}

int main(void){
    FILE *ptr_dataloger = NULL;
    int pocet_zaznamov = 1, pocet_hodnot = 6;
    char** id = NULL;

    v(&ptr_dataloger, &pocet_zaznamov, id);
    n(ptr_dataloger, &pocet_zaznamov, pocet_hodnot, id);
    return 0;
}