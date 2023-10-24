#include <stdio.h>
#include <stdlib.h>

void v(FILE **fptr, char ***id, char ***pozicia, char ***veliciny, char ***hodnota, char ***cas, char ***datum /*mozno bude treba zmenit datovy typ...*/)
{
    int i = 0, len, n_of_scanned;
    char *data_storage = (char *)calloc(50, sizeof(char) * 10);
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
        if (*fptr == NULL)
        {
            printf("Neotvoreny subor\n");
            exit(1);
        }
    }
    if ((id == NULL) || (pozicia == NULL) || (veliciny == NULL) || (hodnota == NULL) || (cas == NULL) || (datum == NULL))
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
    }else
    {
        printf("Vypis z blokov");
    }
}

void n(FILE **fptr, int pocet_zaznamov, int pocet_riadkov, char *data_storage)
{
    if (*fptr == NULL)
    {
        printf("Neotvorený subor.");
        exit(1);
    }
    else
    {
        int n_of_scanned = 0, i, j = 0;
        fseek(*fptr, 0, SEEK_SET);
        for (j = 0; j < pocet_zaznamov; j++)
        {
            n_of_scanned = fscanf(*fptr, "%s", data_storage);
            if (n_of_scanned == -1)
            {
                break;
            }
            for (i = 0; i < 6; i++)
            {
            }
        }
    }
}

int main(void)
{
    FILE *ptr_dataloger = NULL;
    int pocet_zaznamov = 0;
    int pocet_riadkov = 6;
    char data_structure[pocet_zaznamov][pocet_riadkov];
    v(&ptr_dataloger, &data_structure);
    n(&ptr_dataloger, pocet_zaznamov, pocet_riadkov, );
    return 0;
}