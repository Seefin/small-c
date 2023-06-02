/** BigInteger library for C programming.
 *
 * This is my attempt at making a consistent and efficent approach
 * to large integers in C.
 *
 * This should NOT be treated as the best way to do this, it is primarily based
 * off of me learning as I go.
 *
 * @author Connor Findlay, 2023
 * @licence NONE
 */

/**
 * NOTES SECTION
 * -------------
 *  + Strings are right out, that's just trash and the overhead is
 *    completely stupid.
 *  + Arrays of uint_t aren't terrible, but overflows and their handling
 *    become a thing we need to manage.
 */
#ifndef BigInt_h
#define BigInt_h

#include <stdlib.h>
#include <inttypes.h>

typedef struct _UInt {
    uint64_t *integer;
    short sign;
    size_t size;
    char *hex;
} UInt;

UInt u_int_create(short sign, int size, ...);
void u_int_free(UInt *bignum);
#endif
