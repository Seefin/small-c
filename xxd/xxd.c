#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PER_LINE 16
#define USAGE_FMT "Usage: %s -h -v <filename>\n"
#define VERSION 1.5f

char *PROGNAME = "xxd";

void PrintHelp(void);
void PrintHelp(void)
{
    printf("%s\n", "XXD clone in C, by Connor Findlay");
    printf("Version %.1f\n", VERSION);
    printf("%s\n", "Accepts single filename as argument, and has no flags");
    printf("%s\n", "except -h for this text, and -v for the current version.");
}

void PrintFile(char *filename);
void PrintFile(char *filename)
{
    unsigned char c[PER_LINE + 1] = {0};
    size_t bytesRead = 0;
    int address = 0;
    FILE *fp = NULL;

    fp = fopen(filename, "rb");
    if( fp == NULL )
    {
        printf("%s: %m\n", PROGNAME);
        exit(1);
    }

    fseek(fp, 0, SEEK_SET);
    while( (bytesRead = fread(&c, sizeof(unsigned char), PER_LINE, fp)) != 0 )
    {
        //Print 'address'
        printf("%08x: ", address);
        //Print HEX to screen
        for(size_t i = 0; i < bytesRead; i++)
            printf("%02x", c[i]);
        if( bytesRead < PER_LINE )
            for(size_t i = bytesRead; i < PER_LINE; i++)
                printf("%02x", 0);//Pad output to %16 == 0

        //Print ASCII
        for(size_t i = 0; i < bytesRead; i++)
            if( c[i] < 33 || c[i] > 126 )
                c[i] = '.';
        printf("    %s\n", c);
        memset(c, '\0', PER_LINE + 1);
        address += PER_LINE;
    }
    printf("\n");
    fclose(fp);
}

int main(int argc, char **argv)
{
    //Set program name for error messages
    if( strcmp(PROGNAME, argv[0]) != 0 )
        PROGNAME = argv[0];
    
    //Check argument number - need >= 2
    if( argc < 2 )
    {
        fprintf(stderr,USAGE_FMT, PROGNAME);
        exit(1);
    }

    //_Very_ basic commandline processing
    switch(argv[1][0]){
        //If it starts with '-' it's a flag, and we need to 
        // process it. If it is not -h or -v, we print the
        // usage statement and quit
        case '-':
            if( argv[1][1] == 'h' )
            {
                PrintHelp();
                exit(0);
            }
            else if( argv[1][1] == 'v' )
            {
                printf("%s, version %.2f\n", argv[0], VERSION);
                exit(0);
            }
            else
            {
                printf(USAGE_FMT,PROGNAME);
                exit(1);
            }
            break;
        // Otherwise, we assume it's the filename, and attempt to open
        // it and print.
        default:
            PrintFile(argv[1]);
            break;
    }
    return 0;
}
