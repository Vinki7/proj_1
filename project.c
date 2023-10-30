#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void v(FILE** fptr, int pocet_zaznamov, char** id, char** poz, char** velic, char** val, char** time, char** date){
    if (*fptr == NULL)
    {   
        *fptr = fopen("dataloger.txt", "r");
        if (*fptr == NULL){
            printf("Neotvoreny subor\n");
            exit(1);
        }
    }
    int i = 0, len, n_of_scanned;
    char data_storage[50];
    if ((id == NULL))
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
        fseek(*fptr, 0, SEEK_SET);
    }else{
        fseek(*fptr, 0, SEEK_SET);
        i = 0;
        int j = 0;
        while (j < pocet_zaznamov)
        {
            i++;
            switch (i)
            {
            case 1:
                printf("ID mer. modulu: %s\n", (id)[j]);
                break;
            
            case 2:
                printf("Pozicia modulu: %s\n", (poz)[j]);
                break;
            
            case 3:
                printf("Typ mer. veliciny: %s\n", (velic)[j]);
                break;
            
            case 4:
                printf("Hodnota: %s\n", (val)[j]);
                break;
            
            case 5:
                printf("Cas merania: %s\n", (time)[j]);
                break;
            case 6:
                printf("Datum merania: %s\n", (date)[j]);
                i = 0;
                j++;
                printf("\n");
                break;
            }
        }
    }
}

void n(FILE *fptr, int* pocet_zaznamov, int pocet_hodnot, char*** id, char*** poz, char*** velic, char*** val, char*** time, char*** date){
    if (fptr == NULL)
    {
        printf("Neotvoreny subor\n");
        exit(1);
    }else{
        fseek(fptr, 0, SEEK_SET);
        char data_storage[50];
        int i=0, j=0, n_of_scanned;
        while (1)
        {
            n_of_scanned = fscanf(fptr, "%s", data_storage);
            if (n_of_scanned == -1)
            {
                break;
            }
            i++;
            if (i == 6)
            {
                j +=1 ;
                i = 0;
            }
        }
        *pocet_zaznamov = j;
        fseek(fptr, 0, SEEK_SET);
        *id = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *poz = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *velic = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *val = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *time = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *date = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        /*
        Difference between strdup and strcpy?
        Both copy a string. strcpy wants a buffer to copy into. 
        strdup allocates a buffer using malloc().
        for (i = 0; i < *pocet_zaznamov; i++)
        {
            (*id)[i] = (char*)malloc(sizeof(char) * 50);
            (*poz)[i] = (char*)malloc(sizeof(char) * 50);
            (*velic)[i] = (char*)malloc(sizeof(char) * 50);
            (*val)[i] = (char*)malloc(sizeof(char) * 50);
            (*time)[i] = (char*)malloc(sizeof(char) * 50);
            (*date)[i] = (char*)malloc(sizeof(char) * 50);
        }
        */
        j = 0;
        i = 0;
        while (1)
        {
            if (fscanf(fptr, "%s", data_storage) == -1)
            {
                break;
            }
            i++;
            
            switch (i)
            {
            case 1:
                (*id)[j] = strdup(data_storage);
                break;
            
            case 2:
                (*poz)[j] = strdup(data_storage);
                break;
            
            case 3:
                (*velic)[j] = strdup(data_storage);
                break;
            
            case 4:
                (*val)[j] = strdup(data_storage);
                break;
            
            case 5:
                (*time)[j] = strdup(data_storage);
                break;
            case 6:
                (*date)[j] = strdup(data_storage);
                i = 0;
                j++;
                break;
            }
        }
        fseek(fptr, 0, SEEK_SET);
        
    }
}

int main(void){
    FILE *ptr_dataloger = NULL;
    int pocet_zaznamov = 0, pocet_hodnot = 6;
    char **id = NULL, **poz = NULL, **velic = NULL, **val = NULL, **time = NULL, **date = NULL;

    v(&ptr_dataloger, pocet_zaznamov, id, poz, velic, val, time, date);
    n(ptr_dataloger, &pocet_zaznamov, pocet_hodnot, &id, &poz, &velic, &val, &time, &date);
    v(&ptr_dataloger, pocet_zaznamov, id, poz, velic, val, time, date);

    free(id);
    free(poz);
    free(velic);
    free(val);
    free(time);
    free(date);
    return 0;
}