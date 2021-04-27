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
	char process[32];
	char memorySize[32];

	if (*v == 'B')
	for (int i = 0; i < count; i++)
	{
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
			printf("REQUEST ");
			//know command will be REQUEST
			i = i + 8;
			//allocate process name into process array
			for (int k = 0; k < 32; k++)
			{
				if (pretemp[i] != ' ')
				{
					process[k] = pretemp[i];
					i++;
				}
				else
				{
					//reached end of process name
					break;
				}
			}
			for (int h = 0; h < 32; h++)
			{
				printf("%c", process[h]);
			}
			printf(" ");
			
			//allocate memory into memorysize array
			for (int k = 0; k < 32; k++)
			{
				if (pretemp[i] != '\n')
				{
					memorySize[k] = pretemp[i];
					i++;
				}
				else 
				{
					printf("this should happen\n");
					//reached end of memory size
					break;
				}
			}
			for (int h = 0; h < 32; h++)
			{
				printf("%c", memorySize[h]);
			}
			printf("\n");

		}
		else if (pretemp[i] == 'R' && pretemp[i+1] == 'E' && pretemp[i+2] == 'L')
		{
			//know command will be RELEASE
		}
		else if (pretemp[i] == 'L')
		{
			if (pretemp[i+5] == 'A' && pretemp[i+6] == 'S')
			{
				//LIST ASSIGNED
			}
			else if (pretemp[i+5] == 'A' && pretemp[i+6] == 'V')
			{
				//LIST AVAILABLE
			}
		}
		else if (pretemp[i] == 'F')
		{
			//FIND
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
