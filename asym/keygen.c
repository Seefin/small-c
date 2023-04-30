#include "keygen.h"

char *PROGNAME = "keygen";

void PrintHelp(void)
{
    printf("%s\n", "RSA Key Generator, by Connor Findlay");
    printf("%s\n", "DO NOT USE THIS IMPLEMENTATION FOR ANYTHING SERIOUS EVER");
    printf("Version %.1f\n", VERSION);
    printf("%s\n", "Has a single mandatory flag, that accepts single filename as argument");
    printf("%s\n", "\t* Use -p/--private-key <key_file> to produce the public key for the supplied private key");
    printf("%s\n", "\t* Use -c/--create <basename> to create keypair with specified basename. Default: id_rsa");
    printf("%s\n", "Optional flags: -h for this text, and -v for the current version.");
    printf("%s\n", "DO NOT USE THIS IMPLEMENTATION FOR ANYTHING SERIOUS EVER");
}

uint32_t *GenPrime(void)
{
    /* So, I finally have to tackle bit-sequence representation in C.
     * Which is the absolute least of my problems in this function, but we'll get to that. Based on a
     * StackOverflow answer (https://stackoverflow.com/a/30590727), we represent an array of
     * bits as an array of 32-bit ints, and treat each bit in the int as a position in the array.
     * We use the SetBit, ClearBit, and TestBit macros to deal with each bit in the array.
     */
    FILE *RandFile = fopen("/dev/random","rb");
    uint32_t *rand = calloc(BITS/32, 32);
    for( int i = 0; i < (BITS/32); i ++){
        int ret = fread(&(rand[i]), 4, 1, RandFile);
        printf("Read %d bits from /dev/random\n",ret * 32); 
    }
    return NULL;
}


int CreatePubkey(char *private_file)
{
    (void)private_file;
    return 1;//NOT IMPLEMENTED
}

int CreateKeypair(char *basename)
{
    (void)basename;
    uint32_t *prime = GenPrime();
    (void) prime;
    return 1;//NOT IMPLEMENTED
}

int DoArgs(char **argv)
{
    //_Very_ basic commandline processing
    switch(argv[1][0]){
        //If it starts with '-' it's a flag, and we need to 
        // process it. If it is not -h or -v, we print the
        // usage statement and quit
        case '-':
            if( argv[1][1] == 'h' )
            {
                PrintHelp();
                return 0;
            }
            else if( argv[1][1] == 'v' )
            {
                printf("%s, version %.2f\n", argv[0], VERSION);
                return 0;
            }
            else if( argv[1][1] == 'p' )
            {
                return CreatePubkey(argv[2]);
            }
            else if( argv[1][1] == 'c' )
            {
                return CreateKeypair(argv[2]);
            }
            else
            {
                printf(USAGE_FMT,PROGNAME);
                return 1;
            }
            break;
        // Otherwise, we assume it's the filename, and attempt to open
        // it and print.
        default:
            PrintHelp();
            break;
    }
    return 0;
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

    return DoArgs(argv);
}
