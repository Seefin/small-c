#include "BigInt.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

/** Create a UInt for the given sign, of given length, with given contents (optional).
 *
 *  Uses varargs
 */
UInt u_int_create(short sign, int size, ...)
{
    //Assign memory
    UInt number;
    number.integer = malloc(sizeof(uint64_t[size]));
    number.hex = malloc(size * 8);
    
    //Read the integer blocks chunks the list
    va_list blocks;
    va_start(blocks, size);
    for(int i = 0;  i < size; i++)
    {
        number.integer[i] = va_arg(blocks, uint64_t);
    }
    va_end(blocks);

    //Assign metadata
    number.size = size;
    number.sign = sign;
    for( int j = 0; j < size; j++)
    {
        char x[16];//At most 8 bytes/64 bits per element
        snprintf(x,16, "%lX",number.integer[j]);
        strncat(number.hex, x, 16);
    }

    return number;
}
void u_int_free(UInt *bignum)
{
    free(bignum->hex);
    free(bignum->integer);
}
