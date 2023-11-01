#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    fseek(*fptr, 0, SEEK_SET);
}

void dealokacia_polí(int pocet_zaznamov, char*** id, char*** poz, char*** velic, char*** val, char*** time, char*** date){
    int i = 0, j = 0;
    while (1)
    {
        j++;
        if (i == pocet_zaznamov)
        {
            break;
        }
        switch (j)
        {
        case 1:
            free((*id)[i]);
            break;
        
        case 2:
            free((*poz)[i]);
            break;
        case 3:
            free((*velic)[i]);
            break;

        case 4:
            free((*val)[i]);
            break;

        case 5:
            free((*time)[i]);
            break;

        case 6:
            free((*date)[i]);
            i++;
            j=0;
            break;
        }
    }
}


void k(FILE **fptr_1, FILE** fptr_2, int pocet_zaznamov, char*** id, char*** poz, char*** velic, char*** val, char*** time, char*** date){
    dealokacia_polí(pocet_zaznamov, id, poz, velic, val, time, date);
    free(*id);
    free(*poz);
    free(*velic);
    free(*val);
    free(*time);
    free(*date);
    fclose(*fptr_1);
    fclose(*fptr_2);
    exit(1);
}

void n(FILE *fptr, int* pocet_zaznamov, int pocet_hodnot, char*** id, char*** poz, char*** velic, char*** val, char*** time, char*** date){
    if (fptr == NULL)
    {
        printf("Neotvoreny subor\n");
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
            if (i == pocet_hodnot)
            {
                j +=1 ;
                i = 0;
            }
        }
        *pocet_zaznamov = j;
        if (*id != NULL)
        {
            dealokacia_polí(*pocet_zaznamov, id, poz, velic, val, time, date);
        }
        
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

void date_split(char *string_date, int* year, int* month, int* day){
    *year = atoi(string_date)/10000;
    *month = (atoi(string_date)%10000)/100;
    *day = atoi(string_date)%100;
}

void c(FILE** fptr, int pocet_zaznamov, char** id, char** date){
    if (id == NULL)//overenie existencie polí
    {
        printf("Polia nie su vytvorene.\n");
    }else{
        int i = 0, j = 0, match = 1, rozdiel_m, period, ciach[3], stored[3];
        char datastorage[50], id_storage[50];
        printf("Zadajte číslo reprezentujúce rozdiel mesiacov ciachovaní a v meraní...\n");
        scanf("%d", &period);
        fseek(*fptr, 0, SEEK_SET);

        if (*fptr == NULL)
        {
            *fptr = fopen("ciachovanie.txt", "r");
            if (*fptr == NULL)
            {
                printf("Subor sa nepodarilo otvoriť...\n");
                return;
            }
        }
        
        while (1)//zakladny cyklus
        {
            match = 0;
            if (fscanf(*fptr, "%s", datastorage) == -1)//overenie - koniec suboru
            {
                break;
            }
            strcpy(id_storage, datastorage);//uchovanie id z ciachovania v array
            fscanf(*fptr, "%s", datastorage);//naskenovanie datumu z ciach.
            for (i = 0; i < pocet_zaznamov; i++)//iterovaci cyklus - postupne zvysuje i reprezentujuci index a nasledne je hodnota i vkladana
            {
                if (strcmp(*id, "\n") == 0)//porovnanie - ak sa nacitany riadok rovna prazdnemu riadku
                {
                    break;
                }
                
                if (strcmp(id[i], id_storage) == 0)//porovnanie medzi id z pola a ciach. id, ak su identicke, vykona sa blok
                {
                    date_split(datastorage, &ciach[0], &ciach[1], &ciach[2]);
                    date_split(date[i], &stored[0], &stored[1], &stored[2]);//convert string zapisu na jednotlive ciselne hodnoty

                    if ((stored[0]==ciach[0])&&(stored[1]>ciach[1]))//porovnanie rokov a mesiacov
                    {
                        rozdiel_m = stored[1]-ciach[1];//odcitanie
                        if (rozdiel_m > period)
                        {
                            printf("ID. mer. modulu [%s] má %d mesiacov po ciachovani\n", id[i], rozdiel_m);            
                        }
                    }
                    if (stored[0]>ciach[0])
                    {
                        rozdiel_m = 12-ciach[1]+stored[1];
                        printf("ID. mer. modulu [%s] má %d mesiacov po ciachovani\n", id[i], rozdiel_m);
                    }
                    match = 1;
                }
                
            }
            if (match == 0)
            {
                if (i==pocet_zaznamov)
                {
                    i--;
                }
                
                printf("ID. mer. modulu [%s] nie je ciachovany\n", id_storage);
                fscanf(*fptr, "%s", datastorage);
                strcpy(datastorage, "");
            }
            
        }
        printf("Data su korektne\n");
    }
}

void s(FILE* fptr, int pocet_zaznamov, char** id, char** velic, char** poz, char** val, char** time, char** date){
    /*
    po aktivovani nacita ID |+
    nacita vel |+
    vytvori nove pole hodnot kde su zoradene ↑
    vypise zoradene hodnoty do suboru s nazvom vystup_S.txt v tvare:
    Ukážka vstupu (korektný vstup):
    A111a RM
    Ukážka txt súboru:
    202310081015 135.36 000 +48.1734 +19.4367
    202310081025 185.36000 +48.1784 +19.4567
    202310101055 125.36000 +48.1634 +19.4967 

    ak polia neboli vytvorené - hlaska |+
    ak pre vstup neex. zaznam - hlaska
    ak sa nepodari otvorit/zatvorit subor - hlaska |+
    */
    char input_id[6], input_velic[3];
    int pocet_nacitanych = 0, j=0;
    char*** sorted = (char***)malloc(sizeof(char**)*6);
    char*** assist_array = (char***)malloc(sizeof(char**));
    fptr = fopen("vystup_S.txt", "w");
    if (fptr == NULL)
    {
        printf("Pre dany vstup nie je vytvoreny txt subor");
        return;
    }
    if (id==NULL)
    {
        printf("Polia nie su vytvorene");
        return;
    }
    printf("Zadajte ID. mer. modulu a  typ mer. veliciny, oddelte ich medzerou\n");
    scanf("%s %s", input_id, input_velic);
    input_velic[0] = toupper(input_velic[0]);
    input_velic[1] = toupper(input_velic[1]);
    
    for (int i = 0; i < 6; i++)
    {
        sorted[i]=(char**)malloc(sizeof(char*)*pocet_zaznamov);
    }


    for (int i = 0; i < pocet_zaznamov; i++)//nacitanie dat do sorted[]
    {
        if (strcmp(velic[i], input_velic)==0)
        {
            sorted[0][j] = id[i];
            sorted[1][j] = poz[i];
            sorted[2][j] = velic[i];
            sorted[3][j] = val[i];
            sorted[4][j] = time[i];
            sorted[5][j] = date[i];
            j++;
            pocet_nacitanych++;
        }
        
    }
    if (pocet_nacitanych == 0)
    {
        fprintf(fptr, "%c", 'c');
        printf("Pre dany vstup neexistuju zaznamy\n");
    }else{
        //sorting algorythm
        
        for (int i = 0; i < pocet_nacitanych; i++)//vypis do suboru
        {
            //delenie pozicie na lat a long
            char lat[8], lon[8];
            for (int j = 0; j < 7; j++)
            {
                lat[j] = (sorted[1][i])[j];
            }
            for (int j = 7; j < 14; j++)
            {
                lon[j] = (sorted[1][i])[j];
            }
            fprintf(fptr, "%s%s\t%.5lf\t%s\t%s", sorted[5][i], sorted[4][i], atof(sorted[3][i]), lat, lon);//dokonci...
        }
        
    }

    //cistenie polí na konci funkcie
    for (int i = 0; i < pocet_zaznamov; i++)
    {
        free(sorted[i]);
    }
    free(sorted);
    for (int i = 0; i < 2; i++)
    {
        free(assist_array[i]);
    }
    free(assist_array);
    free(sorted);
    //uzatvorenie txt
    if (fclose(fptr) == EOF)
    {
        printf("Pre dany vstup nie je vytvoreny txt subor");
    }
    

}

int main(void){
    FILE *ptr_dataloger = NULL;
    FILE *ptr_ciachovanie = NULL;
    FILE *ptr_sort = NULL;

    int pocet_zaznamov = 0, pocet_hodnot = 6;
    char **id = NULL, **poz = NULL, **velic = NULL, **val = NULL, **time = NULL, **date = NULL;
    char prikaz;
    printf("Zadajte príkaz:\n");
    while (1)
    {
        scanf(" %c", &prikaz);
        switch (prikaz)
        {
        case 'v':
            v(&ptr_dataloger, pocet_zaznamov, id, poz, velic, val, time, date);
            break;
        
        case 'n':
            n(ptr_dataloger, &pocet_zaznamov, pocet_hodnot, &id, &poz, &velic, &val, &time, &date);
            break;

        case 'c':
            c(&ptr_ciachovanie, pocet_zaznamov, id, date);
            break;

        case 's':
            /* code */
            break;

        case 'h':
            /* code */
            break;
        
        case 'z':
            /* code */
            break;
        
        case 'k':
            k(&ptr_dataloger, &ptr_ciachovanie, pocet_zaznamov, &id, &poz, &velic, &val, &time, &date);
            break;
        default:
            printf("Zadali ste nedefinovaný príkaz, skúste to prosím znovu...\n");
        }
        printf("Zadajte ďalší príkaz...\n");
    }
    return 0;
}