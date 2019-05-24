#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function 
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, char *pattern) {
    // Implement if desire 
	// ORIGINAL CODE
    int i;
	int j;
	i = 0;
	j = 0;
	while(*(pattern+i) != '\0')
	{
		if(*(partial_line+j) == '\0' || *(partial_line+j) == '\n')
		{
			return 0;
		}
		else if((*(pattern+i+1) == '?' && *(pattern+i) != '\\') || (*(pattern+i) == '?' && *(pattern+i-1) == '\\' && *(pattern+i-2) == '\\'))
		{
			if(*(partial_line+j) != *(pattern+i) && *(partial_line+j) != *(pattern+i+2))
			{
				if(*(pattern+i) != '.' && *(pattern+i-1) != '\\')
				{
					return 0;
				}
			}
			else if(*(partial_line+j) != *(pattern+i) && *(partial_line+j) == *(pattern+i+2))
			{
				if(*(pattern+i) != '.' && *(pattern+i-1) != '\\')
				{
					j--;
				}
				else
				{
					i++;
				}
			}
			i++;
		}
		else if((*(pattern+i) == '\\' && *(pattern+i-1) != '\\') || (*(pattern+i) == '\\' && *(pattern+i-1) == '\\' && *(pattern+i-2) == '\\'))
		{
			j--;
		}
		else if((*(pattern+i) == '.' && *(pattern+i-1) != '\\') || (*(pattern+i) == '.' && *(pattern+i-1) == '\\' && *(pattern+i-2) == '\\'))
		{
			// do nothing
		}
		else if((*(pattern+i) == '+' && *(pattern+i-1) != '\\') || (*(pattern+i) == '+' && *(pattern+i-1) == '\\' && *(pattern+i-2) == '\\'))
		{
			if(matches_leading(partial_line+j, pattern+i-1) == 1){
				while(matches_leading(partial_line+j, pattern+i-1) == 1)
				{
					j++;
				}
			}
			j--;
		}
		else if(*(partial_line+j) != *(pattern+i))
		{
			return 0;
		}
		i ++;
		j ++;
	}
	
    return 1;
}

/**
 * You may assume that all strings are properly null terminated 
 * and will not overrun the buffer set by MAXSIZE 
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {

    //
    // Implement me 
    // ORIGINAL CODE
	int i = 0;
	int patLength = 0;
	while(*(pattern+i) != '\0')
	{
		if(*(pattern+i+1) == '?')
		{
			patLength -= 2;
		}
		if(*(pattern+i+1) == '\\' || *(pattern+i+1))
		{
			patLength --;
		}
			
		patLength ++;
		i ++;
	}

	int wordSize;
	i = 0;
	while(*(line+i) != '\0')
	{
		if(*(line+i) == '\n')
		{
			wordSize = i;
		}
		i++;
	}
	
	i = 0;
	while(*(line+i) != '\0' && *(line+i) != '\n')
	{
		if(patLength > wordSize)
		{
			return 0;
		}
		else if(matches_leading(line+i, pattern) == 1) 
		{
			return 1;
		}
		i++;
	}
	
    return 0;
}

//GIVEN CODE
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
