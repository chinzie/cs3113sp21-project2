#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdint.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	char *buf = (char *) malloc (10000000 *  sizeof(char));//buffer to hold arbitrary amount of numbers
	int count = 0;

	char *v;
	unsigned char e;
	if (argc > 1)
	{
		
		char *q = argv[1];
		v = q;
		if (*q == 'B')
		{
			printf("BESTFIT\n");
		}
		
		long int mem = atoi(argv[2]);//assign memory

		//printf("file input\n");
		FILE *file_handle;
		file_handle = fopen(argv[3], "r");
		//if the argument is coming from file input, not stdin
		//use fscanf one byte at a time
        	while (fscanf(file_handle, "%c", buf) == 1)
        	{
			buf[count] = *buf;
			
			if (count == 0)
			{
				e = buf[count];
			}
			
        	        count++;
	        }
		fclose(file_handle);
		
	}
	
	

	buf[0] = e;//file read seems to ignore the first element after loop so i allocate it here
	char pretemp[count];

	for (int i = 0; i < count; i++)
	{
		unsigned char c = buf[i];
		pretemp[i] = c;
	}

	//begin process
	
	if (*v == 'B')
	for (int i = 0; i < count; i++)
	{
		printf("hello\n");
		if (pretemp[i] == '#')
		{
			//printf("ignore\n");
			//go to next line
			for (int j = i; j < count;)
			{
				if (pretemp[j] == '\n')
				{
					i = j;
					break;
				}
				else
				{
					j++;
				}
			}
		}
		else if (pretemp[i] == 'R' && pretemp[i+1] == 'E' && pretemp[i+2] == 'Q')
		{
			//know command will be REQUEST
		}
		else if (pretemp[i] == 'R' && pretemp[i+1] == 'E' && pretemp[i+2] == 'L')
		{
			//know command will be RELEASE
		}
	}

	/*	
	for (int i = 0; i < count; i++)
	{
		printf("%c", pretemp[i]);
	}
	*/
	

	return 0;
}
