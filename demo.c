#include <stdio.h>
#include <stdlib.h>

int main(void){
    char* value = malloc(sizeof(char)*50);
    char values[6];
    value = "A";
    values[0] = *value;

    return 0;
}