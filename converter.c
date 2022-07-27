/*C-progs/converter.c*/
/*future options should include: little/big endian; --help; 
 * usage; more compact error messages*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int radixConvert(const char* oldNum, int oldRadix, char* newNum, int newRadix)
{
    long data = 0L;
    char digit = 0;
    int i = 0;
    int size = strlen(oldNum);

    /*if any radix is out of bounds, end the program*/
    if ((oldRadix <= 1) || (oldRadix > 36) || (newRadix <= 1) || (newRadix > 36))
    {
        return 0;
    }

    /*convert oldnum from the old radix to radix 10*/
    for (i = 0; i < size; i++)
    {   
        /*(char)oldRadix + '0' - 1 this is to prevent out of bounds digits. i.e. 3 in base 3*/
        /*cast is valid since oldRadix was confirmed to be greater that 1 and less than 37, easily fitting 8 bits*/
        if (oldNum[i] >= '0' && oldNum[i] <= (char)oldRadix + '0' - 1)
        {
            data += (oldNum[i] - '0') * pow(oldRadix, size - i - 1);
        } 
        /*Same idea as above, although with ascii letters. i.e. G is prevented in radix 16*/
        else if (oldNum[i] >= 'A' && oldNum[i] <= (char)oldRadix + 'A' - 11)
        {
            data += (oldNum[i] - 'A' + 10) * pow(oldRadix, size - i - 1);
        }
        /*Provide support for lower case characters*/
        else if (oldNum[i] >= 'a' && oldNum[i] <= (char)oldRadix + 'a' - 11)
        {
            data += (oldNum[i] - 'a' + 10) * pow(oldRadix, size - i - 1);
        }
        else
        {
            return -1;
        }
    }
    i = 0;

    /*convert from radix 10 to newRadix*/
    /*code credit to xxx*/
    while (data > 0)
    {
        digit = data % newRadix;

        (digit < 10) ? (newNum[i] = digit + '0')
            :(newNum[i] = digit + 'A' - 10);
        data = data / newRadix;
        i++;
    }
    newNum[i] = '\0';
    

    /*Result must be reversed. int is appropriate placeholder as any ascii character will fit in it*/
    size = strlen(newNum);
    int index, j, k;
    k = size/2;
    for (index = 0; index < k; index++){
        j = newNum[index];
        newNum[index] = newNum[size - index - 1];
        newNum[size - index - 1] = j;
    }

    return 1;
}

int radixToDec(char* oldNum, int oldRadix, unsigned long *data, int i, int size)
{

    /*halt the recursion*/
    if (i >= size)
    {
        return 0;
    }

    /*(char)oldRadix + '0' - 1 this is to prevent out of bounds digits. i.e. 3 in base 3*/
    /*cast is valid since oldRadix was confirmed to be greater that 1 and less than 37, easily fitting 8 bits*/

    if (oldNum[i] >= '0' && oldNum[i] <= (char)oldRadix + '0' - 1)
    {
        *data += (oldNum[i] - '0') * pow(oldRadix, size - i - 1);
    } 

    /*Same idea as above, although with ascii letters. i.e. G is prevented in radix 16*/
    else if (oldNum[i] >= 'A' && oldNum[i] <= (char)oldRadix + 'A' - 11)
    {
        *data += (oldNum[i] - 'A' + 10) * pow(oldRadix, size - i - 1);
    }

    /*Provide support for lower case characters*/
    else if (oldNum[i] >= 'a' && oldNum[i] <= (char)oldRadix + 'a' - 11)
    {
        *data += (oldNum[i] - 'a' + 10) * pow(oldRadix, size - i - 1);
    }

    radixToDec(oldNum, oldRadix, data, ++i, size);
    return 0;
    
}


int decToRadix(unsigned long *data, int newRadix, char* result)
{

    int index = 0;          //ensure that index will be zero when recursion stops
    if (*data != 0)
    {
        char digit = *data % newRadix;          //get the digit

        *data = *data / newRadix;                                                           //change data
        index = decToRadix(data, newRadix, result);                                         //find the current index
        (digit < 10) ? (result[index] = digit + '0') : (result[index] = 'A' - 10 + digit);  //add the correct digit


        index += 1;                 //increment index
        result[index] = '\0';       //add a null terminator, in the recursive calls this will be overwritten, only top level call will persist
        return index;               //return the incremented index for the above recursive call
    }
    return 0;
}


int radixConvert2(char* oldNum, int oldRadix, char* newNum, int newRadix)
{
    unsigned long real = 0L;
    unsigned long *data = &real;

    /*if any radix is out of bounds, end the program*/
    if ((oldRadix <= 1) || (oldRadix > 36) || (newRadix <= 1) || (newRadix > 36))
    {
        return 1;
    }

    int size = strlen(oldNum);

    radixToDec(oldNum, oldRadix, data, 0, size);
    decToRadix(data, newRadix, newNum);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <integer> <radix 1> <radix 2>\n", argv[0]);
        return 1;
    }
    
    char newNum[64];
    if (radixConvert2(argv[1], atoi(argv[2]), newNum, atoi(argv[3])) == 0){

        printf("%s\n", newNum);
    }
    else {
        printf("%s <number> <radix of number> <translation radix>\n", argv[0]);
    }

    return 0;
}


