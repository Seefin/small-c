#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "lib/BigInt.h"

#define PER_LINE 16
#define USAGE_FMT "Usage: %s -h -v <filename>\n"
#define VERSION 1.5f

#define BITS 4096

void PrintHelp(void);
int DoArgs(char **argv);
int CreatePubkey(char *private_file);
int CreateKeypair(char *basename);
uint32_t *GenPrime(void);
