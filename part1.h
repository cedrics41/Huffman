//
// Created by David on 10/11/2020.
//
#include <stdio.h>

#ifndef HUFFMAN_PROJECT_HUFFMAN_H
#define HUFFMAN_PROJECT_HUFFMAN_H

//structure of the linked list used to gather letters from the text and cont their occurrences
typedef struct linkl{
    char letter;
    int occ;
    struct linkl * address;
}linkl;

//structure of the huffman tree to sort the letters according to their occurrences
typedef struct hufftree{
    char letter;
    int occ;
    struct hufftree* child_left;
    struct hufftree* child_right;
}hufftree;

//FIRST PART
int get_size();

//SECOND PART
void check_array(char letter, linkl *linked_list); //function to fill the list
void occurrences(linkl * index); //function test to print the list and be sure it works

//THIRD PART
linkl* get_higher(linkl* linked); // function to find the letter with the highest occurrence in the list
void add_letter(hufftree* Tree, linkl* higher, int count); //We had the letter to our tree
void deleter_higher(linkl* linked, char letter); //function that delete the element from the list
void print_tree(hufftree* Tree, int count); // function test to print the tree and be sure it works

//FORTH PART
void create_code(hufftree* Tree, FILE* Alice_d, int count); // function that go through the tree to create the dictionary
void deadlocate(hufftree * tree); // function to free the tree

//FIFTH PART
void Encod(); // function that print the final condensed text on a text file
#endif //HUFFMAN_PROJECT_HUFFMAN_H
