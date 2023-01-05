#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int CharCheck(char c)
{
    int result = 0;
    if (c >= 65 && c <= 90)
    {
        result = 1; // Upper case
    }
    else if (c >= 97 && c <= 122)
    {
        result = 2; // Lower case
    }
    else if (c == '\n')
    {
        result = 3;
    }
    return result;
}

char * AddChar(char *str, char c)
{
    int len = strlen(str);
    char *temp = str;
    str = NULL;
    str = malloc(sizeof(char) * (len + 1));
    for (int i = 0; i < len; i++)
    {
        str[i] = temp[i];
    }
    str[len] = c;
    str[len + 1] = '\0';
    temp = NULL;
    return str;
}

char ChangeChar(char c, int key, bool side, int lowerLimit, int upperLimit)
{
    if (side == true)
    {
        c = (c-lowerLimit + key) % 26 + lowerLimit;
    }
    else if(side == false)
    {
        c = (c-upperLimit - key) % 26 + upperLimit;
    }
    else
    {
        fprintf(stderr, "Wrong input (bool side: right == 1, left == 0)\n");
        exit(1);
    }
    return c;
}

char *Cipher(FILE *f, int key, bool side)//true == right
{
    char *str = "";
    char c;
    while (true)
    {
        c = fgetc(f);
        int check = CharCheck(c);
        switch (check)
        {
        case 0:
            //ignore character
            break;
        //Upper case
        case 1:
            c = ChangeChar(c, key, side, 65, 90);
            break;
        //Lower case
        case 2:
            c = ChangeChar(c, key, side, 97, 122);
            break;
        case 3:
            return str;
            break;
        }
        str = AddChar(str, c);
    }
    return "something went wrong\n";
}

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Wrong input\n");
        exit(1);
    }
    int side = atoi(argv[1]);
    if (side < 0 || side > 1)
    {
        fprintf(stderr, "Wrong input(SIDE can be only 1 for right shift or 0 for left shift))\n");
        exit(1);
    }
    int key = atoi(argv[2]);
    if (key < 0)
    {
        fprintf(stderr, "Wrong input(KEY needs to be positive)\n");
        exit(1);
    }
    fprintf(stdout, "Place for your text:\n");
    FILE *f = stdin;
    char *result = Cipher(f, key, side);
    fprintf(stdout, "Cipher: %s\n", result);
    return 0;
}