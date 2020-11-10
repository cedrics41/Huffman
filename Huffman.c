void textToBinary(char *text, int textLength, char *binary, int binaryLength)
{
    char *octet = malloc(9);
    if(octet == NULL)
        exit(1);
    while(*text)
    {
        decimalToBinary(*text, octet);
        while(*octet)
            *binary++ = *octet++;
        *binary++ = ' ';
        ++text;
        octet -= 8;
    }
    *binary = '\0';
    binary -= binaryLength;
    free(octet);
}

void decimalToBinary(int decimal, char *octet)
{
	octet += 8;
	*octet = '\0';
	if(decimal == 0)
	{
		octet -= 8;
		octet = "00000000";
	}
	else
	{
		while(decimal > 0)
		{
			--octet;
			*octet = decimal % 2 + '0';
			decimal = decimal / 2;
		}
	}
    while(strlen(octet) < 8)
    {
        --octet;
        *octet = '0';
    }
}
