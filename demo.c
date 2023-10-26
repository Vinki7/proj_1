#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char **values =NULL;
    values = (char**)malloc(sizeof(char*)*50);
    for (int i = 0; i < 50; i++)
    {
        *values= (char*)malloc(sizeof(char)*50);
    }
    
    char* value = (char*)malloc(sizeof(char)*50);
    value = "Arr";
    strcpy(*values, value);
    printf("%s", *values);
    return 0;
}