#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "part1.h"
#include "part2.h"

#define SIZE 1000

int main(){
    //CREATION OF THE LINKED LIST
    linkl * index = (linkl*)malloc(sizeof(linkl));
    index->address = NULL;

    FILE * Alice_i = fopen("Input.txt", "r,ccs=UTF-8");
    //fail-safe
     if (Alice_i==NULL){ //The program can't work if the first file doesn't exist
        printf("Exit 1.0: process failed to open the Input file");
        return 1;
     }

    //Variables used in this FIRST PART : Getting the content of the input file on an array
    int size = get_size();
    wint_t l = fgetwc(Alice_i);
    int i=0;
    char* content[size];
    while(l != WEOF){
        content[i] = l; //put each character of the text into an array
        l = fgetwc(Alice_i);
        i++;
    }
    fclose(Alice_i);


    // SECOND PART We fill our linked list
    //We go through the function "check_array" for every character of the text to see if they are already in our linked list
    for(int i=0; i<size; i++)
    {
        check_array(content[i], index); //filling of our linked list
    }
    //occurrences(index); // test function


    // CREATION OF THE HUFFMAN TREE
    hufftree* Tree = (hufftree*)malloc(sizeof(hufftree));

    //THIRD PART, we fill the tree
    linkl* higher = (linkl*)malloc(sizeof(linkl));
    int count=0;
    while(index->address != NULL)//WE FLL THE TREE AND EMPTY THE LINKED LIST ONE ELEMENT BY ONE
    {
        higher = get_higher(index); //We check which letter has the highest occurrence
        add_letter(Tree, higher, count); //We add it to our tree
        delete_higher(index, higher->letter); //We delete it from our linked list
        count+=1;
    }
    free(higher);//We don't need it anymore

    //print_tree(Tree,count); // test function

    // FOURTH PART : We create our dictionary
    FILE * Alice_d = fopen("Dictionary.txt", "w+, ccs=UTF-8");
    create_code(Tree, Alice_d, 0);//We go through the Huffman tree to find a code and write it on the dictionary
    deadlocate(Tree);//We free our tree
    fclose(Alice_d);

    //FIFTH PART
    Encod();//We print the compressed file on the text file

    printf("\n\nGood news : The text has been condensed !\n\n");

    return 0;
}
