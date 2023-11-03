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
            return;
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
        i = 0;
        int j = 0;
        for(j = 0; j < pocet_zaznamov; j++)
        {
            printf("ID mer. modulu: %s\n", (id)[j]);
            printf("Pozicia modulu: %s\n", (poz)[j]);
            printf("Typ mer. veliciny: %s\n", (velic)[j]);
            printf("Hodnota: %s\n", (val)[j]);
            printf("Cas merania: %s\n", (time)[j]);
            printf("Datum merania: %s\n", (date)[j]);
            printf("\n");
        }
    }
    fseek(*fptr, 0, SEEK_SET);
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
            for (int i = 0; i < *pocet_zaznamov; i++) {
                free((*id)[i]);
                free((*poz)[i]);
                free((*velic)[i]);
                free((*val)[i]);
                free((*time)[i]);
                free((*date)[i]);
            }
        }
        
        fseek(fptr, 0, SEEK_SET);
        *id = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *poz = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *velic = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *val = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *time = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
        *date = (char**)malloc(sizeof(char*)*(*pocet_zaznamov));
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

void time_split(char *string_time, int* hour, int* minute){
    *hour = atoi(string_time)/100;
    *minute = atoi(string_time)%100;
}

void min_max(char** arr, float *min, float *max, int pocet){
    *min = atof(arr[0]);
    *max = atof(arr[0]);
    for (int i = 1; i < pocet; i++)
    {
        float aktualna_hodnota = atof(arr[i]);
        if (aktualna_hodnota < *min)
        {
            *min = aktualna_hodnota;
        }
        if (aktualna_hodnota > *max)
        {
            *max = aktualna_hodnota;
        }
    }
}

void c(FILE** fptr, int pocet_zaznamov, char** id, char** date){
    if (id == NULL)//overenie existencie polí
    {
        printf("Polia nie su vytvorene.\n");
    }else{
        int i = 0, j = 0, match = 1, rozdiel_m, period, ciach[3], stored[3], ciach_id_count = 0, zaciatok_hladania = 0, zapis = 0;
        char datastorage[50], id_storage[50];
        char** ciach_id = (char**)malloc(sizeof(char*)*pocet_zaznamov); //id ciachovania
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
            ciach_id[ciach_id_count] = strdup(id_storage);
            ciach_id_count++;
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
                            zapis++;
                            printf("ID. mer. modulu [%s] má %d mesiacov po ciachovani\n", id[i], rozdiel_m);            
                        }
                    }
                    if (stored[0]>ciach[0])
                    {
                        rozdiel_m = 12-ciach[1]+stored[1];
                        zapis++;
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
                fscanf(*fptr, "%s", datastorage);
                strcpy(datastorage, "");
            }
        }
        match = 0;
        i = 0;
        while (1)
        {
            if (i == pocet_zaznamov)
            {
                break;
            }
            for ( j = 0; j < ciach_id_count; j++)
            {
                if (strcmp(ciach_id[j], id[i]) == 0)
                {
                    match = 1;
                    break;
                }
            }
            if (match != 1)
            {
                printf("ID. mer. modulu [%s] nie je ciachovany\n", id[i]);
            }
            i++;
            match = 0;
        }
        
        if (zapis == 0)
        {
            printf("Data su korektne\n");
        }
    }
}

void s(FILE** fptr, int pocet_zaznamov, char** id, char** velic, char** poz, char** val, char** time, char** date){
    char input_id[6], input_velic[3];
    int pocet_nacitanych = 0, j = 0;
    char*** sorted = (char***)malloc(sizeof(char**)*6);
    *fptr = fopen("vystup_S.txt", "w");
    if (*fptr == NULL)
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
        if (strcmp(input_id, id[i]) == 0)
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
    }
    if (pocet_nacitanych == 0)
    {
        fprintf(*fptr, "%c", 'c');
        printf("Pre dany vstup neexistuju zaznamy\n");
    }else{
        j = 0;
        int date[2],  time[2];
        int pocitadlo = pocet_nacitanych - 1, zaciatok = 0, akt_poz;//zaciatok sa mení, ak pociatocny udaj nebol vacsi nez prvy porovnavany udaj
        int pozicie[pocet_nacitanych];
        int i = 0;
        
        for (int i = 0; i < (pocet_nacitanych-1); i++)
        {
            for (int k = 0; k < (pocet_nacitanych-1) - i; k++)
            {
                if ((atoi(sorted[5][k]) > atoi(sorted[5][k+1])) || ((atoi(sorted[5][k]) == atoi(sorted[5][k+1])) && (atoi(sorted[4][k]) > atoi(sorted[4][k+1]))))
                {
                    for (int x = 0; x < 6; x++)
                    {
                        char* tempor = sorted[x][k];
                        sorted[x][k] = sorted[x][k+1];
                        sorted[x][k+1] = tempor;
                    }   
                }   
            }
        }
        

        for (int i = 0; i < pocet_nacitanych; i++)//vypis do suboru
        {
            //delenie pozicie na lat a long
            char** vypis_pozicie = (char**)malloc(sizeof(char*)*2); 
            vypis_pozicie[0] = (char*)malloc(sizeof(char)*8);
            vypis_pozicie[1] = (char*)malloc(sizeof(char)*8);
            for (int j = 0; j < 14; j++)
            {
                if (j<7)
                {
                    vypis_pozicie[0][j] = poz[i][j];
                }else{
                    vypis_pozicie[1][j - 7] = poz[i][j];
                }
            }
            vypis_pozicie[0][7] = '\0';
            vypis_pozicie[1][7] = '\0';
            fprintf(*fptr, "%s%s\t%.5lf\t%s\t%s\n", sorted[5][i], sorted[4][i], atof(sorted[3][i]), vypis_pozicie[0], vypis_pozicie[1]);
            free(vypis_pozicie[0]);
            free(vypis_pozicie[1]);
            free(vypis_pozicie);
        }    
    }

    //cistenie polí na konci funkcie
    for (int i = 0; i < 6; i++)
    {
        for (int x = 0; x < pocet_nacitanych; x++)
        {
            free(sorted[i][x]);
        }  
    }
    free(sorted);
    //uzatvorenie txt
    if (fclose(*fptr) == EOF)
    {
        printf("Pre dany vstup nie je vytvoreny txt subor");
    }
}

void z(int* pocet_zaznamov, char*** id, char*** poz, char*** velic, char*** val, char*** time, char*** date) {
    char vlozene_id[10];
    char **new_array;

    printf("Zadajte ID mer. modulu pre vymazanie záznamov\n");
    scanf("%s", vlozene_id);
    
    int povodny_pocet_zaznamov = *pocet_zaznamov;
    int removed_records = 0;

    for (int current_index = 0; current_index < *pocet_zaznamov; current_index++) {
        if (*id == NULL || *poz == NULL || *velic == NULL || *val == NULL || *time == NULL || *date == NULL)
        {
            printf("Polia nie su vytvorene\n");
        }else{
        
            if (strcmp(vlozene_id, (*id)[current_index]) == 0) {
                free((*id)[current_index]);
                free((*poz)[current_index]);
                free((*velic)[current_index]);
                free((*val)[current_index]);
                free((*time)[current_index]);
                free((*date)[current_index]);
                
                for (int i = current_index; i < *pocet_zaznamov - 1; i++) {
                    (*id)[i] = (*id)[i + 1];
                    (*poz)[i] = (*poz)[i + 1];
                    (*velic)[i] = (*velic)[i + 1];
                    (*val)[i] = (*val)[i + 1];
                    (*time)[i] = (*time)[i + 1];
                    (*date)[i] = (*date)[i + 1];
                }

                current_index--;
                (*pocet_zaznamov)--;
                removed_records++;
            }
        }
    }
    *id = (char**)realloc(*id, (*pocet_zaznamov) * sizeof(char*));
    *poz = (char**)realloc(*poz, (*pocet_zaznamov) * sizeof(char*));
    *velic = (char**)realloc(*velic, (*pocet_zaznamov) * sizeof(char*));
    *val = (char**)realloc(*val, (*pocet_zaznamov) * sizeof(char*));
    *time = (char**)realloc(*time, (*pocet_zaznamov) * sizeof(char*));
    *date = (char**)realloc(*date, (*pocet_zaznamov) * sizeof(char*));

    printf("Vymazalo sa: %d zaznamov!\n", removed_records);
}

void h(int pocet_zaznamov, char** velic, char** val){
    if (velic == NULL || val == NULL)
    {
        printf("Polia nie su vytvorene\n");
    }else{
        char *rm[pocet_zaznamov], *rd[pocet_zaznamov], *ro[pocet_zaznamov];
        int rm_index = 0, rd_index = 0, ro_index = 0;
        float min, max;
        for (int i = 0; i < pocet_zaznamov; i++) {
            if (strcmp(velic[i], "RM") == 0) {
                rm[rm_index] = strdup(val[i]);
                rm_index++;
            } else if (strcmp(velic[i], "RD") == 0) {
                rd[rd_index] = strdup(val[i]);
                rd_index++;
            } else if (strcmp(velic[i], "RO") == 0) {
                ro[ro_index] = strdup(val[i]);
                ro_index++;
            }
        }
        printf("Typ mer. vel.\tPocetnost\tMinimum\tMaximum\n");
        if (rm_index != 0)
        {
            min_max(rm, &min, &max, rm_index);
            printf("RM\t\t%d\t\t%.2f\t\t%.2f\n", (rm_index), min, max);
        }
        if (rd_index != 0)
        {
            min_max(rd, &min, &max, rd_index);
            printf("RD\t\t%d\t\t%.2f\t\t%.2f\n", (rd_index), min, max);
        }
        if (ro_index != 0)
        {
            min_max(ro, &min, &max, ro_index);
            printf("RO\t\t%d\t\t%.2f\t\t%.2f\n", (ro_index), min, max);
        }

        for (int i = 0; i < rm_index; i++) {
            free(rm[i]);
        }
        for (int i = 0; i < rd_index; i++) {
            free(rd[i]);
        }
        for (int i = 0; i < ro_index; i++) {
            free(ro[i]);
        }
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
            s(&ptr_sort, pocet_zaznamov, id, velic, poz, val, time, date);
            break;

        case 'h':
            h(pocet_zaznamov, velic, val);
            break;
        
        case 'z':
            z(&pocet_zaznamov, &id, &poz, &velic, &val, &time, &date);
            break;
        
        case 'k':
            for (int i = 0; i < pocet_zaznamov; i++) {
                free(id[i]);
                free(poz[i]);
                free(velic[i]);
                free(val[i]);
                free(time[i]);
                free(date[i]);
            }
            free(id);
            free(poz);
            free(velic);
            free(val);
            free(time);
            free(date);
            fclose(ptr_ciachovanie);
            fclose(ptr_dataloger);
            exit(1);
            break;
        default:
            printf("Zadali ste nedefinovaný príkaz, skúste to prosím znovu...\n");
        }
        printf("Zadajte ďalší príkaz...\n");
    }
    return 0;
}