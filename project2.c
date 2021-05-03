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

	int addressHolder;

	int gap;

	int gapLeft;

	int position;
};

int main(int argc, char *argv[])
{
	char *buf = (char *) malloc (10000000 *  sizeof(char));//buffer to hold arbitrary amount of numbers
	int count = 0;

	int holder;
	int origin;
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
		origin = holder;
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

	int hold = 0;
	//printf("holder is: %d\n", holder);

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
			
			
			i = i + 1;
			//allocate memory into memorysize array
			for (int k = 0; k < 32; k++)
			{
				if (pretemp[i] != '\n' && pretemp[i] != ' ')
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
			/*
			if (c > origin)
			{
				printf("FAIL REQUEST %s %d\n", str, c);
				break;
			}
			*/
			for (int i = 0; i < 32; i++)//reset memsize array for future use
			{
				memorySize[i] = '\0';
			}
			
			//stuff is stored temporarily
			//find out if space
			for (int i = 0; i <= index; i++)
			{
				if (index == 0)//first one
				{
					for (int i = 0; i < temp; i++)
                        		{
                                		strncat(arr[index].s, &process[i], 1);
                        		}
					if (c > origin)
                        		{
						//printf("here 1\n");
                                		printf("FAIL REQUEST %s %d\n", arr[index].s, c);
						for (int k = 0; k < 32; k++)
						{
							arr[index].s[k] = '\0';
						}

                                		break;
                        		}
					int address = memTemp;
                        		arr[index].amount = c;
                        		holder = holder - c;
					//printf("holder: %d\n", holder);
                        		arr[index].address = memTemp;
					arr[index].addressHolder = memTemp;
                        		printf("ALLOCATED ");
                        		printf("%s", arr[index].s);
                        		printf(" ");
					printf("%d", address);
                        		//arr[index].address = memTemp;
                        		memTemp = c + address;
                        		printf("\n");
                        		temp = 0;//reset
                        		//str[0] = '\0';//reset
					arr[index].gap = 0;
					arr[index].position = index;
                        		index++;
					break;
				}
				


				//printf("gap at %d is %d\n", i, arr[i].gap);
				if (arr[i].gap > 0)// && arr[i+1].address != '\0')//if there is a gap then consider it for best fit
				{
					//printf("gap found!\n");
					//find out if gap is big enough
					if (arr[i].gap >= c)
					{
						//find out if the hole it makes will be the smallest
						int hole = arr[i].gap - c;
						//printf("hole: %d = %d - %d\n", hole, arr[i].gap, c);
						int newHole = 0;
						int smallestHoleIndex = i;
						for (int j = i+1; j < index; j++)
						{
							if (arr[j].gap > 0 && arr[j].gap >= c)//gap exists and is big enough
							{
								newHole = arr[j].gap - c;
								
								if (newHole < hole)//smaller hole made
								{
									hole = newHole;//set hole equal to the smaller hole
									smallestHoleIndex = j;//save index of gap for smallest hole
								}
								else if (newHole == hole)
								{
									hole = hole;
								}
							}
						}
						//by now we have the smallest hole and its index
						//place the process in this gap theoretically

						for (int i = 0; i < temp; i++)
                                        	{
                                                	strncat(arr[index].s, &process[i], 1);
                                        	}

						//arr[index].amount = c;
						//printf("%d\n", arr[smallestHoleIndex].amount);
						arr[index].address = c;
						arr[index].amount = c;
						arr[index].gap = 0;
						//printf("%d\n", arr[smallestHoleIndex].address);
						int gapHolder = arr[smallestHoleIndex].address + arr[index].amount;

						//printf("Index: %d\n", smallestHoleIndex);
						int addressHold = arr[smallestHoleIndex].address;
						arr[index].addressHolder = addressHold;
						//printf("%d\n", addressHold);
						//printf("%d\n", arr[smallestHoleIndex].addressHolder);
						arr[smallestHoleIndex].gap = hole;
						//arr[smallestHoleIndex].address = arr[smallestHoleIndex - 1].amount + arr[smallestHoleIndex - 1].address;
						printf("ALLOCATED ");
                                        	printf("%s", arr[index].s);
                                        	printf(" ");
                                        	printf("%d", arr[smallestHoleIndex].addressHolder);
						arr[index].position = arr[smallestHoleIndex].position;
						arr[smallestHoleIndex].position = 11000;
                                        	//arr[index].address = memTemp;
                                        	//memTemp = c + address;
                                        	printf("\n");
                                        	temp = 0;//reset
                                        	//str[0] = '\0';//reset
                                        	//arr[index].gap = 0;

						//printf("new gap is: %d\n", arr[smallestHoleIndex].gap);
						arr[smallestHoleIndex].gapLeft = gapHolder;
						//arr[smallestHoleIndex].address = 100;
						index++;
						break;
					}
					
				}
				else if (arr[i+1].address == '\0' && holder - c >= 0)//if there is no gap but the next address is empty
				{
					//arr[i+1
					//].address == '\0' && 
					//printf("space found!\n");
					//printf("gap at %d is %d\n", i, arr[i].gap);
					for (int i = 0; i < temp; i++)
                        		{
                                		strncat(arr[index].s, &process[i], 1);
                        		}
					int address = memTemp;
                        		arr[index].amount = c;
                        		holder = holder - c;
					//printf("holder2: %d\n", holder); 
                        		arr[index].address = memTemp;
					arr[index].addressHolder = memTemp;
                        		printf("ALLOCATED ");
                        		printf("%s", arr[index].s);
                        		printf(" ");
					printf("%d", address);
                        		//arr[index].address = memTemp;
                        		memTemp = c + address;
                        		printf("\n");
                        		temp = 0;//reset
                        		//str[0] = '\0';//reset
					arr[index].gap = 0;
					arr[index].position = index;
                        		index++;
					break;
				}
				else if (origin - c < 0)//not enough space
				{
					//printf("%d - %d = %d\n", holder, c, holder - c);
					//printf("here 2\n");
					//printf("%d\n", holder - c);
					for (int i = 0; i < temp; i++)
                                        {
                                                strncat(arr[index].s, &process[i], 1);
                                        }
					arr[index].amount = c;
					printf("FAIL REQUEST %s %d\n", arr[index].s, arr[index].amount);
					for (int k = 0; k < 32; k++)
                                        {
                                                arr[index].s[k] = '\0';
                                        }
					break;
				}
				else if (holder == 0)
                                        {
                                                for (int i = 0; i < temp; i++)
                                                {
                                                        strncat(arr[index].s, &process[i], 1);
                                                }
                                                arr[index].amount = c;
                                                printf("FAIL REQUEST %s %d\n", arr[index].s, arr[index].amount);
                                                for (int k = 0; k < 32; k++)
                                                {
                                                        arr[index].s[k] = '\0';
                                                }
                                                break;
                                      	}
			}
		}


		else if (pretemp[i] == 'R' && pretemp[i+1] == 'E' && pretemp[i+2] == 'L')
		{
			//printf("RELEASE ");
			//know command will be RELEASE
			i = i + 8;
                        //allocate process name into process array
                        for (int k = 0; k < 32; k++)
                        {
                                if (pretemp[i] != ' ' && pretemp[i] != '\n')
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

			//printf("string: %s\n", str);
			//for (int i = 0; i < temp; i++)
			//{
			//	strncat(arr[index].s, &process[i], 1);
			//}

			int memHolder = 0;
			int indexHolder = 0;
			int breaker = 0;
			//printf("index: %d\n", index);
			for (int i = 0; i <= index; i++)
			{
				if (strcmp(str, arr[i].s) == 0)
				{
					//printf("found!\n");
					if (i+1==index)
					{
						holder = holder + arr[i].amount;
					}
					memHolder = arr[i].amount;
					indexHolder = i;
					//printf("holder: %d\n", indexHolder);
					break;
				}
				else if (i + 1 > index)
				{
					//cant be found
					printf("FAIL RELEASE %s\n", str);
					breaker = 1;
					break;
				}
			}
			if (breaker == 1)
			{
				for (int i = 0; i < temp; i++)
                        	{
                                	str[i] = '\0';
                        	}
				temp = 0;
			}
			else if (breaker == 0)
			{
				 //set gap
                        	printf("FREE ");
                        	printf("%s ", arr[indexHolder].s);
                        	printf("%d ", memHolder);
                        	printf("%d ", arr[indexHolder].address);
                        	printf("\n");

                        	//arr[indexHolder].amount = 0;
                        	//arr[indexHolder].address = 1000000;
                        	//arr[indexHolder].gap = 0;
                        	arr[indexHolder].gap = arr[indexHolder+1].address - (arr[indexHolder-1].amount + arr[indexHolder-1].address);//set gap
                        	arr[indexHolder].gap = arr[indexHolder].amount;
                        	for (int k = 0; k < temp; k++)
                        	{
                                	arr[indexHolder].s[k] = '\0';
                        	}
                        	//printf("gap set: %d = %d - %d + %d\n", arr[indexHolder].gap, arr[indexHolder+1].address, arr[indexHolder-1].amount, arr[indexHolder-1].address);
                        	for (int i = 0; i < temp; i++)
                        	{	
                                	str[i] = '\0';
                        	}

                        	temp = 0;

			}
			//set gap


			/*
			printf("FREE ");
			printf("%s ", arr[indexHolder].s);
			printf("%d ", memHolder);
			printf("%d ", arr[indexHolder].address);
			printf("\n");

			//arr[indexHolder].amount = 0;
			//arr[indexHolder].address = 1000000;
			//arr[indexHolder].gap = 0;
			arr[indexHolder].gap = arr[indexHolder+1].address - (arr[indexHolder-1].amount + arr[indexHolder-1].address);//set gap
			arr[indexHolder].gap = arr[indexHolder].amount;
			for (int k = 0; k < temp; k++)
			{
				arr[indexHolder].s[k] = '\0';
			}
			//printf("gap set: %d = %d - %d + %d\n", arr[indexHolder].gap, arr[indexHolder+1].address, arr[indexHolder-1].amount, arr[indexHolder-1].address);
			for (int i = 0; i < temp; i++)
			{
				str[i] = '\0';
			}
			
			temp = 0;
			*/
		}





		else if (pretemp[i] == 'L')
		{
			if (pretemp[i+5] == 'A' && pretemp[i+6] == 'S')
			{
				int tempPos = 0;
				//LIST ASSIGNED
				//printf("LIST ASSIGNED\n");
				//
				i = i + 13;
				for (int e = 0; e <= index; e++)
				{
					if (index == 0)
					{
						printf("NONE");
						break;
					}
					if (arr[e].gap != 0)//skip it because its a gap
					{
						continue;
					}
					else
					{
						for (int r = 0; r < index; r++)
						{
							if (arr[r].position == tempPos && arr[r].gap == 0)
							{
								printf("(%s, %d, %d) ", arr[r].s, arr[r].amount, arr[r].addressHolder);
								tempPos++;
								break;
							}
						}
					
					}
				}
				printf("\n");

			}
			else if (pretemp[i+5] == 'A' && pretemp[i+6] == 'V')
			{
				i = i + 14;
				//printf("%d, %d\n", holder, origin);

				for (int u = 0; u <= index; u++)
				{
					if (holder == origin)
					{
						printf("(%d, %d) ", origin, memTemp);
						break;
					}
					if (arr[u].gap > 0 && index > 1)
					{
						printf("(%d, %d) ", arr[u].gap, arr[u].gapLeft);
					}
					else if (u+1 >= index && memTemp < origin)
					{
						printf("(%d, %d) ", holder, memTemp);
						break;
					}
					else if (holder == 0)
					{
						printf("FULL");
						break;
					}
				}
				printf("\n");
				//LIST AVAILABLE
				//printf("LIST AVAILABLE\n");
				//printf("(%d, %d)\n", holder, memTemp);

			}
		}
		else if (pretemp[i] == 'F')
		{
			//FIND
			i = i + 5;
                        //allocate process name into process array
                        for (int k = 0; k < 32; k++)
                        {
                                if (pretemp[i] != ' ' && pretemp[i] != '\n')
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

                        char q[32];
                        for (int i = 0; i < 32; i++)
                        {
                                strncat(q, &process[i], 1);
                        }

			for (int k = 0; k <= index; k++)
			{
				if (strcmp(arr[k].s, q) == 0)
				{
					printf("(%s, %d, %d)\n", arr[k].s, arr[k].amount, arr[k].address);
					break;
				}
				else if (k+1 > index)
				{
					printf("FAULT\n");
					break;
				}
			}
			for (int i = 0; i < 32; i++)
			{
				q[i] = '\0';
			}
		}
	}


	return 0;
}
