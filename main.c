#include <stdio.h>
#include <stdlib.h>
#include "Proto.h"
#define TAILLE_MAX 1000
int main()
{
    char text[TAILLE_MAX];
    char *binary;
	int textLength, binaryLength, occ =0,cpt = -1;
	FILE* fptr = NULL;
	FILE* fptr1= NULL;

	fptr = fopen("Alice_input.txt","r");
	fgets(text, TAILLE_MAX, fptr);
	fclose(fptr);
	textLength = strlen(text);
    binaryLength = textLength * 9;      // 8 binary digits + 1 space separator
    binary = malloc(binaryLength + 1);  // + 1 null terminator
    if(binary == NULL)
        exit(1);

    textToBinary(text, textLength, binary, binaryLength);
    printf("Your binary encoding is:\n%s\n", binary);
    fptr1 = fopen("Alice_output.txt","w+");
    fprintf(fptr1,"%s", binary);
    fclose(fptr1);
    free(binary);

    fptr = fopen("Alice_input.txt","r");
    do{
        occ = fgetc(fptr);
        if(occ != NULL){
            cpt = cpt+1;
        }
    }while (occ != EOF);
    fclose(fptr);
    fptr = fopen("Alice_input.txt","a");
    fprintf(fptr," %d",cpt);
    fclose(fptr);
    fptr1 = fopen("Alice_output.txt","a");
    fprintf(fptr1,"%d",cpt*8);
    return 0;
}
