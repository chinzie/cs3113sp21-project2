#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdint.h>
#include <ctype.h>

struct ACTION
{
	char s[32];

	int amount;

	int address;
};

int main(int argc, char *argv[])
{
	char *buf = (char *) malloc (10000000 *  sizeof(char));//buffer to hold arbitrary amount of numbers
	int count = 0;

	int holder;
	char *v;
	unsigned char e;
	if (argc > 1)
	{
		
		char *q = argv[1];
		v = q;
		/*
		if (*q == 'B')
		{
			printf("BESTFIT\n");
		}
		*/
		
		int mem = atoi(argv[2]);//assign memory

		holder = mem;
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

	char processStorage[100000];
	int processIndex = 0;
	int memoryStorage[100000];
	int memoryIndex = 0;

	int memTemp = 0;

	int temp = 0;


	struct ACTION arr[10000];
	int index = 0;


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
			//printf("REQUEST ");
			//know command will be REQUEST
			i = i + 8;
			//allocate process name into process array
			for (int k = 0; k < 32; k++)
			{
				
				if (pretemp[i] != ' ')
				{		
					process[k] = pretemp[i];
					i++;	
					temp++;
				}
				else
				{
					//reached end of process name
					break;
				}
			}
			
			for (int h = 0; h < sizeof(process); h++)
			{
				//printf("%c", process[h]);
			}
			//printf(" ");
			
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
					//reached end of memory size
					break;
				}
			}
			
			int c = atoi(memorySize);//append all chars to an int
			
			//char str[32];
			for (int i = 0; i < temp; i++)
			{
				strncat(arr[index].s, &process[i], 1);
			}
			arr[index].amount = c;
			holder = holder - c;
			printf("ALLOCATED ");
			printf("%s", arr[index].s);
			printf(" ");
			printf("%d", memTemp);
			arr[index].address = memTemp;
			memTemp = c + memTemp;
			printf("\n");
			temp = 0;//reset
			//str[0] = '\0';//reset
			index++;
		}
		else if (pretemp[i] == 'R' && pretemp[i+1] == 'E' && pretemp[i+2] == 'L')
		{
			//printf("RELEASE ");
			//know command will be RELEASE
			i = i + 8;
                        //allocate process name into process array
                        for (int k = 0; k < 32; k++)
                        {
                                if (pretemp[i] != '\n')
                                {
                                        process[k] = pretemp[i];
                                        i++;
					temp++;
                                }
                                else
                                {
                                        //reached end of process name
                                        break;
                                }
                        }
			char str[32];
			for (int i = 0; i < temp; i++)
			{
				strncat(str, &process[i], 1);
			}
			

			int memHolder;
			int indexHolder;
			for (int i = 0; i < index; i++)
			{

				if (strcmp(str, arr[i].s) == 0)
				{
					//printf("found");
					memHolder = arr[i].amount;
					indexHolder = i;
					break;
				}
			}

			printf("FREE ");
			printf("%s ", arr[indexHolder].s);
			printf("%d ", memHolder);
			printf("%d ", arr[indexHolder].address);
			printf("\n");
			str[0] = '\0';
			arr[indexHolder].s[0] = '\0';

		}
		else if (pretemp[i] == 'L')
		{
			if (pretemp[i+5] == 'A' && pretemp[i+6] == 'S')
			{
				//LIST ASSIGNED
				//printf("LIST ASSIGNED\n");
			}
			else if (pretemp[i+5] == 'A' && pretemp[i+6] == 'V')
			{
				//LIST AVAILABLE
				//printf("LIST AVAILABLE\n");
				printf("(%d, %d)\n", holder, memTemp);
			}
		}
		else if (pretemp[i] == 'F')
		{
			//FIND
		}
	}


	return 0;
}
