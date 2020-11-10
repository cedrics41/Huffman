#ifndef PROTO_H_INCLUDED
#define PROTO_H_INCLUDED
#include "Huffman.c"
unsigned long binaryToDecimal(char *binary, int length);
void textToBinary(char *text, int textLength, char *binary, int binaryLength);
void decimalToBinary(int decimal, char *octet);


#endif // PROTO_H_INCLUDED
