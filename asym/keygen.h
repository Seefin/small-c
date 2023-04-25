#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PER_LINE 16
#define USAGE_FMT "Usage: %s -h -v <filename>\n"
#define VERSION 1.5f

void PrintHelp(void);
void DoArgs(char **argv);
