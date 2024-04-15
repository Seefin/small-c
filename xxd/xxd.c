// vim: tabstop=4 shiftwidth=4 noexpandtab
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PER_LINE 16
#define USAGE_FMT "Usage: %s -h -v <filename>\n"
#define VERSION 1.60f

char *PROGNAME = "xxd";

void PrintHelp(void);
void PrintHelp(void)
{
	printf("%s\n", "XXD clone in C, by Connor Findlay");
	printf("Version %.1f\n", VERSION);
	printf("%s\n", "Accepts a single filename as an argument, and has no flags");
	printf("%s\n", "except -h for this text, and -v for the current version.");
	printf("%s\n", "A single hyphen '-' indicates that standard input should be");
	printf("%s\n", "read instead of a file");
}

void PrintFile(FILE *fp);
void PrintFile(FILE *fp)
{
	unsigned char c[PER_LINE + 1] = {0};
	size_t bytesRead = 0;
	int address = 0;

	if( fp == NULL )
	{
		printf("%s: %m\n", PROGNAME);
		exit(1);
	}
	//Clear EOF and ERR flags from stream
	clearerr(fp);
	//Read from stream to EOF
	while( feof(fp) == 0 )
	{
		//Read data in
		bytesRead = fread(&c, sizeof(unsigned char), PER_LINE, fp);
		// If we read no bytes, or we encountered an error, skip this line
		if( bytesRead == 0 || ferror(fp) ){
			memset(c, '\0', PER_LINE + 1);
			address += PER_LINE;
			continue;
		}
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
	FILE *fp;
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
			else if( argv[1][1] == '\0' )
			{
				PrintFile(stdin);
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
			fp = fopen(argv[1], "rb");
			PrintFile(fp);
			break;
	}
	return 0;
}
