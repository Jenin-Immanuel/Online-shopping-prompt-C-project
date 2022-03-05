#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help() {
    FILE *fptr;
    fptr = fopen("./Texts/help.txt", "r");
    char ch;
    while ((ch = fgetc(fptr)) != EOF) {
        printf("%c", ch);
    }
    fclose(fptr);
}

