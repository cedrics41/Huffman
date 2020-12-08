//
// Created by David on 10/11/2020.
//
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "part1.h"

int get_size()
{
    FILE *Alice_i=fopen("Input.txt", "r, ccs=UTF-8"); //only want to read the input file
    wint_t l = fgetwc(Alice_i);
    int count = 0;

    while(l!=WEOF) // as long as l exist
    {
        count++;
        l = fgetwc(Alice_i); //change first letter
    }
    fclose(Alice_i); // close all files to free memory

    return count;
}

void check_array(char letter, linkl * start)
{
    //Function that checks if a letter has already been counted, if not than it adds the new letter to the linked list
    int end =0;
    if (start!=NULL){
        while ((start!= NULL) && (end == 0)){
            //if we find the letter in the list then we modify its occurrences
            if(start->letter == letter){
                (start->occ)+=1;
                end=1;
            //else, we go to the next element
            }else{
                if (start->address==NULL){ // if it is he end of the list we stop
                    end=2;
                }else{
                    start = start->address; // else we keep going
                }
            }
        }
    }
    //If the letter not in the list
    if (end==2){
        //New element to our list
        linkl * new_link;
        new_link = (linkl*)malloc(sizeof(linkl));
        //linking it to the already existing list
        start->address=new_link;
        //Variables
        new_link->letter=letter;
        new_link->occ=1;
        new_link->address=NULL;
    }
}

void occurrences(linkl * index){
    //Test function that go through the list and display the occurrences to see if it works up to this point
    //PRINT VERIFICATION
    index=index->address;
    while(index!=NULL){
        printf("\n\nLetter: %c", index->letter);
        printf("\nOccurrences: %d", index->occ);
        index=index->address;
    }
}

linkl* get_higher(linkl* linked)
{
    //Function that goes through the linked list to find the element with the highest occurrences
    linked=linked->address;
    linkl* temp=(linkl*)malloc(sizeof(linkl)); //we create a temp to not mess with the pointer
    int highest=0; //can't have an occurrence smaller than 1
    while(linked != NULL)
    {
        if((linked->occ)> highest) // pretty self-explanatory
        {
            temp = linked;
            highest = linked->occ;
        }
        linked = linked->address;
    }
    return temp; //it returns the element with the highest occurrence
}


void add_letter(hufftree* Tree, linkl* higher, int count)
{
    //Function that add the element with the highest occurrence to our tree
    //We create a space for it
    hufftree* new_el;
    new_el = (hufftree*)malloc(sizeof(hufftree));
    new_el->letter = higher->letter;
    new_el->occ = higher->occ;


    //We create the "link" special to huffman trees to connect letters in order
    hufftree* empty;
    empty = (hufftree*)malloc(sizeof(hufftree));
    empty->letter = '£';
    empty->occ = 0;    //It is the start of our tree so we create a "link"

    if(Tree == NULL)
        Tree = empty; // We create the start of the tree if he doesn't already exist

    int yep=0;
    while(yep<=count) //According to the number of time we went through the loop
    {
        Tree->occ+=new_el->occ;
        if(Tree->child_right == NULL){ //Until we didn't reach the end of our tree
            Tree->child_left = new_el; //Add our new element to the left
            Tree->child_right = empty; //Add a link to the right, new end of our list
            return;
        }
        Tree = Tree->child_right; // Keep going
        yep+=1;
    }
}


void delete_higher(linkl* linked, char letter)
{
    //Function that delete in the linked list the element with the highest occurrence
    if(linked == NULL)
        return;

    linkl* buffer = linked; // to not mess with the pointer
    linkl* temp; // to keep the next one in memory

    while((buffer->address) != NULL)
    {
        if(buffer->address->letter == letter) //we look for the element that has the letter
        {
            temp = buffer->address->address; // We keep the next one in memory to not lose it
            free(buffer->address); //We free the element wanted
            buffer->address = temp; //We connect the list
            return; //our work is done
        }
        buffer = buffer->address; // keep going till we find it
    }
    if(buffer->address == NULL){ //if there is only one element left
        if(buffer->letter == letter)
            free(buffer); //we free it
    }
}

void print_tree(hufftree* Tree,int count)
{
    //TEST FUNCTION
    int yep=0;
    while(yep<count)
    {
        printf("Letter : [%c]\n", Tree->child_left->letter);
        Tree = Tree->child_right;
        yep+=1;
    }
}

void create_code(hufftree* Tree, FILE* Alice_d, int count)
{
    //We go through the huffman tree to create the code, recursive way
    if(Tree->child_right==NULL) // if we are at the end of the tree we leave
        return;
    else{ //else we keep going
        fputwc(Tree->child_left->letter, Alice_d); //We write the letter we found
        for(int i=0; i<count; i++)
            fputwc('1', Alice_d); //Write as much 1's as we want right
        if(Tree->child_right->child_right != NULL)//if it isn't the last letter of the tree
            fputwc('0', Alice_d); //we print a 0 at the end
            fputwc('\n', Alice_d); // and go to the next line
            //if it is the last one we want its code to be equal to the previous one with the last 0 being a 1
        create_code(Tree->child_right,Alice_d, count+1);//we keep going
    }
}

void deadlocate(hufftree * tree)
{
    //do nothing if passed a non-existent node
    if (tree == NULL)
        return;

    //now onto the recursion
    deadlocate(tree->child_left); //we free the tree element by element
    deadlocate(tree->child_right);

    free(tree);//we free the pointer associated with the tree
}

void Encod() // We print the final code on a text file
{
    FILE *Alice_i=fopen("Input.txt", "r, ccs=UTF-8"); //only want to read the input file
    FILE *Alice_o=fopen("Compress.txt", "w+, ccs=UTF-8"); // want to change the output file
    wint_t l = fgetwc(Alice_i);
    while(l!=WEOF) // as long as l exist
    {
        FILE* Alice_d = fopen("Dictionary.txt", "r, ccs=UTF-8"); //only want to read the dictionary, read from the start so we open it in a loop
        wint_t l2 = fgetwc(Alice_d);
        while((l2 != WEOF) && (l != l2)) //as long as l2 exist we compare the two letters
        {
            wint_t l3;
            l3=fgetwc(Alice_d); //we pass all characters without looking since l!=l2
            while((l3 != WEOF) && (l3 != '\n')){ //until we reach the end of the line
                l3=fgetwc(Alice_d);
            }
            l2 = fgetwc(Alice_d);
        }
        // if l == l2 :
        l2=fgetwc(Alice_d); //we start to look at the code
        while(l2!=WEOF && l2!='\n'){ //until we reach the end of the line
            fputwc(l2,Alice_o); //we print the code in our file
            l2=fgetwc(Alice_d); // pass to another 1 or 0 of the code
        }
        l = fgetwc(Alice_i); //change first letter
        fclose(Alice_d); // close the dictionary
    }
    fclose(Alice_i); // close all files to free memory
    fclose(Alice_o);
}


//===========================================================================================
// NOT IN THE PROJECT
// DISUSSION OF WHAT COULD BE IMPROVED, REAL HUFFMAN TREE
/*
hufftree * return_hufftree(linkl * linked)
{
    if(linked==NULL) //fail-safe
        return NULL;
    //pre-run to put all the link->tree to NULL
    linkl* buffer = linked; //not messing with the pointer
    linkl* temp; // to keep the next one in memory
    int fail_safe=0;
    int max_occurence=0;

    while(buffer->address != NULL && fail_safe < 100){
        buffer->tree=NULL;
        max_occurence+=buffer->occ;
        fail_safe+=1;
        if(buffer->address!=NULL)
            buffer=buffer->address;
    }
    linkl * last_element = buffer;
    temp = last_element;
    buffer=linked;
    //huffman tree
    linked * min1, min2, node;
    while(buffer->occ < max_occurence){
        //getting the two minimums
        min1= get_minimum(buffer, NULL);
        min2= get_minimum(buffer, min1);
        //creating a little tree
        node= create_huffman(min1,min2);
        //putting it at the end of the list
        temp->address = node;
        temp= temp->address;
        //reset loop
        if (buffer->address!=NULL)
            buffer= buffer->address;
        else{
            buffer->address= last_element;
            last_element= temp;
            buffer= linked;
        }
    }

    //free
    free(last_element);
    free(min1);
    free(min2);
    free(node);
    //return
    return buffer->tree;
}

linkl * get_minimum(linkl * linked, linked * min)
{
    linkl* buffer_2 = linked; //not messing with the pointer
    //min base
    int min_occ = linked->occ;
    linkl* min_add = linked;
    //loop
    while(buffer_2->adress!=NULL){
        if (buffer_2->occ < min_occ && buffer_2!=min){
            min_occ = buffer_2->address;
            min_add = buffer_2;
        }
    }
    //remove minimum from list
    buffer_2 = linked;
    linkl * temp = buffer_2;
    int count=0;
    while(buffer_2->adress!=NULL && count!=-1){
        if (buffer_2==min_add && count!=0){
            buffer_2=temp;
            buffer_2->adress=buffer_2->address->address;
            count=-1;
        }
        //change of variables
        count+=1;
        temp = buffer_2;
        buffer_2 = buffer_2->adress;
    }
    free(buffer_2);
    free(temp);
    return min_add;
}

linkl * create_huffman(linkl * node_1, linkl * node_2)
{
    hufftree * node_l;
    hufftree * node_r;
    //letter
    node_l->letter = node_1->letter;
    node_r->letter = node_2->letter;
    //occ
    node_l->occ = node_1->occ;
    node_r->occ = node_2->occ;
    //final
    hufftree * node_f;
    node_f->letter = '£';
    node_f->child_left = node_l;
    node_f->child_right= node_r;
    node_f->occ= node_l->occ + node_r->occ;
    linkl * link;
    link->occ= node_f->occ;
    link->tree = node_f;
    return link;
}
*/
//===================================================================================================================

