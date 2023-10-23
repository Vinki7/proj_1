#include <stdio.h>
#include <stdlib.h>

void v(FILE* fptr, char* polia/*mozno bude treba zmenit datovy typ...*/){
    /*
    Najprv zistujeme stav pointeru na subor. 
        - Ak subor nebol otvoreny, skusame ho otvorit
            - Ak neuspesne, vypise sa text
            - Ak uspesne, zistujeme status dynamickych polí - ich existenciu
                - Ak existuju = bola volana funkcia n(), vypiseme ich obsah
                - Ak neexistuju, vypiseme zaznamy zo suboru
    */
    if (fptr == NULL)
    {   
        //treba zmenit file
        fptr = fopen("dataloger.txt", "r");
        int i, len;
        char* data_storage = (char*)calloc(50, sizeof(char)*10), break_point;
        if (fptr == NULL){
            printf("Neotvoreny subor\n");
            exit(1);
        }else if (polia == NULL)
        {
        while (1)
        {
            for (i = 0; i < 6; i++)
            {
                fscanf(fptr, "%s", data_storage);
                printf("%s\n", data_storage);
            }
            if (data_storage == "-1")
            {
                break;
            }
            
        }
        }
    }
}

int main(void){
    FILE *ptr_dataloger = NULL;
    char* zaznam_poli = NULL;//mozno bude treba zmenit datovy typ...
    v(ptr_dataloger, zaznam_poli);
    return 0;
}