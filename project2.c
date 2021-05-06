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

	int changed;

	int positionHolder;

	int skip;
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
			//printf("c is: %d\n", c);
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
					arr[index].positionHolder = index;
                        		index++;
					//printf("increment3\n");
					break;
				}
				

				//printf("%d ", c);
				//printf("%d\n", holder);
				

				int gapChecker = 0;
				//printf("gap at %d is %d\n", i, arr[i].gap);
				if (arr[i].gap > 0 && arr[i].changed != 3)// && arr[i+1].address != '\0')//if there is a gap then consider it for best fit
				{
					int trap = 0;
					for (int w = 0; w < index; w++)
					{
						if (arr[w].gap > 0)
						{
							trap = w;
						}
					}
					
					//printf("gap found!\n");
					if (i+1 == index && arr[i].gap < c)
					{
						//printf("no gap found\n");
						gapChecker = 1;
					}

					int skip = 0;
					//printf("%d\n", c);
					//find out if gap is big enough
					if (arr[i].gap >= c)
					{
						//find out if the hole it makes will be the smallest
						int hole = arr[i].gap - c;
						//printf("hole: %d = %d - %d\n", hole, arr[i].gap, c);
						int newHole = 0;
						int smallestHoleIndex = i;
						for (int j = i; j <= trap; j++)
						{
							//printf("trap: %d\n", trap);
							//printf("j is: %d\n", j);
							//printf("gap is : %d   %d\n", arr[j].gap, arr[j].changed);
							if (arr[j].gap > 0 && arr[j].gap >= c && arr[j].changed != 3)//gap exists and is big enough
							{
								//printf("hello\n");
								//printf("index is %d, j is %d\n", index, j);
								newHole = arr[j].gap - c;
								//printf("hole: %d\n", hole);
								//printf("holderhole: %d\n", holder - c);
								if (newHole < hole)//smaller hole made
								{
									//printf("smaller hole: %d\n", newHole);
									hole = newHole;//set hole equal to the smaller hole
									smallestHoleIndex = j;//save index of gap for smallest hole
								}
								else if (newHole == hole)
								{
									hole = hole;
								}
								if ((j == trap && holder - c < hole && holder - c >= 0))// ||(j==trap && holder - c < newHole && holder - c >= 0))
								{
									for (int i = 0; i < temp; i++)
                                        				{
                                                				strncat(arr[index].s, &process[i], 1);
                                        				}
                                        				int address = memTemp;
                                        				arr[index].amount = c;
                                        				holder = holder - c;
									//printf("c : %d\n", c);
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
                                        				//going on the top
                                        				int count = 0;
                                        				for (int j = 0; j <index; j++)
                                        				{
                                                				if (arr[j].changed != 3)
                                                				{
                                                        				count++;
                                                				}
                                        				}

                                       	 				arr[index].position = count;
                                        				arr[index].positionHolder = count;
                                        				index++;
                                        				//printf("increment2\n");
									skip = 1;
                                        				break;
								}
							}
							else if ((j == trap && holder - c < hole && holder - c >= 0))// ||(j==trap && holder - c < newHole && holder - c >= 0))
                                                                {
                                                                        for (int i = 0; i < temp; i++)
                                                                        {
                                                                                strncat(arr[index].s, &process[i], 1);
                                                                        }
                                                                        int address = memTemp;
                                                                        arr[index].amount = c;
                                                                        holder = holder - c;
                                                                        //printf("c : %d\n", c);
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
                                                                        //going on the top
                                                                        int count = 0;
                                                                        for (int j = 0; j <index; j++)
                                                                        {
                                                                                if (arr[j].changed != 3)
                                                                                {
                                                                                        count++;
                                                                                }
                                                                        }

                                                                        arr[index].position = count;
                                                                        arr[index].positionHolder = count;
                                                                        index++;
                                                                        //printf("increment2\n");
                                                                        skip = 1;
                                                                        break;
                                                                }
						}
						if (skip == 1)
						{
							break;
						}
						//printf("here\n");
						//printf("smallestHoleIndex: %d\n", smallestHoleIndex);
						//printf("hole: %d\n", hole);
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
						if (smallestHoleIndex == index - 1)
						{
							//printf("last ");
							holder = holder - arr[index].amount;
							//printf("%d\n", holder);
						}
						arr[index].gap = 0;
						//printf("%d\n", arr[smallestHoleIndex].address);
						int gapHolder = arr[smallestHoleIndex].address + arr[index].amount;

						arr[smallestHoleIndex].changed = 1;
						//printf("indexer: %d\n", index);
						//printf("Index: %d\n", smallestHoleIndex);
						int addressHold = arr[smallestHoleIndex].addressHolder;
						arr[index].addressHolder = addressHold;
						//printf("%d\n", addressHold);
						//printf("%d\n", arr[smallestHoleIndex].addressHolder);
						arr[smallestHoleIndex].gap = hole;
						//arr[smallestHoleIndex].address = arr[smallestHoleIndex - 1].amount + arr[smallestHoleIndex - 1].address;
						printf("ALLOCATED ");
                                        	printf("%s", arr[index].s);
                                        	printf(" ");
                                        	printf("%d", arr[smallestHoleIndex].addressHolder);

						//printf("position: %d\n", arr[smallestHoleIndex].position);
						//
						arr[index].position = arr[smallestHoleIndex].position;
						//arr[smallestHoleIndex].position = arr[index].position + 1;//increment gap position
						

						for (int i = 0; i < index; i++)
						{
							//printf("position: %d  %d\n", arr[i].position, arr[i].addressHolder);
						}
						//printf("hole: %d\n", hole);
						if (hole > 0)
						{
							arr[smallestHoleIndex].position = arr[smallestHoleIndex].position + 1;
							//printf("new position: %d\n", arr[smallestHoleIndex].position);
							for (int g = 0; g <= index; g++)
                                                	{
		//printf("%d <= %d at %d != %d  %d\n", arr[smallestHoleIndex].position, arr[g].position, arr[smallestHoleIndex].addressHolder, arr[g].address, arr[g].amount);
                                                      if (arr[smallestHoleIndex].position <= arr[g].position && arr[g].addressHolder != arr[smallestHoleIndex].addressHolder && arr[g].changed != 3)                                                        	{
                                                                	//printf("position %d now is %d\n", arr[g].position, arr[g].position + 1);
                                                                	arr[g].position = arr[g].position + 1;
                                                        	}
                                                	}
						}
						else if (hole == 0)
						{
							arr[index].position = arr[smallestHoleIndex].position;
							arr[smallestHoleIndex].changed = 3;
						}


						//shuffle all positions that are above the filled gap including the gap
						//if (arr[smallestHoleIndex].position >= arr[smallestHoleIndex+1].position)
						//for (int g = arr[smallestHoleIndex].position; g < index; g++)
						//{
						//	if (arr[smallestHoleIndex].position <= arr[g].position)// && arr[g].gap == 0)
						//	{
						//		//printf("changing %d at %d\n", arr[g].position, g);
						//		arr[g].position = arr[g].position + 1;
						//	}
						//}
						/*
						else
						{
							arr[smallestHoleIndex].position = arr[index].position + 1;//increment gap position
						}
						*/
						


						/*
						int val = index;
						if (arr[smallestHoleIndex].position == 11000)
						{
                                                        //printf("posHold: %d\n", arr[index].positionHolder);
							arr[index].changed = 1;
							for (int g = 0; g < index; g++)
							{
								if (arr[g].changed == 1 && arr[g+1].position == 11000)
								{
									arr[index].position = arr[g].position + 1;
								}
							}
						}
						else
						{
							arr[index].position = arr[smallestHoleIndex].position;
                                                	arr[index].positionHolder = arr[smallestHoleIndex].positionHolder;
                                                	//printf("posHold: %d\n", arr[index].positionHolder);
                                                	//arr[smallestHoleIndex].position = 11000;
							arr[index].changed = 1;
						}
						*/

						//arr[index].position = arr[smallestHoleIndex].position;
						//arr[index].positionHolder = arr[smallestHoleIndex].positionHolder;
						//printf("posHold: %d\n", arr[index].positionHolder);
						//arr[smallestHoleIndex].position = 11000;
                                        	//arr[index].address = memTemp;
                                        	//memTemp = c + address;
                                        	printf("\n");
                                        	temp = 0;//reset
                                        	//str[0] = '\0';//reset
                                        	//arr[index].gap = 0;

						//printf("new gap is: %d\n", arr[index].amount);
						//arr[smallestHoleIndex].gapLeft = gapHolder;
						//arr[smallestHoleIndex].amount = gapHolder;
						arr[smallestHoleIndex].addressHolder = arr[smallestHoleIndex].addressHolder + arr[index].amount;
						index++;
						//printf("increment\n");
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
					/*
					for (int i = 0; i < index; i++)
                                        {
                                                 printf("position: %d  %d\n", arr[i].position, arr[i].addressHolder);
                                        }
					*/
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
					//going on the top
					int count = 0;
					for (int j = 0; j < index; j++)
					{
						if (arr[j].changed == 0 || arr[j].changed == 1 || arr[j].changed == 2)
						{
							count = count + 1;
						}
					}

					//printf("count: %d\n", count);
					arr[index].position = count;
					arr[index].positionHolder = count;
                        		index++;
					for (int i = 0; i < index; i++)
                                        {
                                                 //printf("position: %d  %d\n", arr[i].position, arr[i].changed);
                                        }
					//printf("increment2\n");
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
				else if ((holder == 0 && gapChecker ==1) || (c > holder && i == index))
                                        {
						//printf("here3\n");
						//printf("%d\n", holder);
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
					if (i==index)
					{
						holder = holder + arr[i].amount;
					}
					memHolder = arr[i].amount;
					indexHolder = i;
					//printf("holder: %d\n", holder);
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
                        	printf("%d ", arr[indexHolder].addressHolder);
                        	printf("\n");


                        	//arr[indexHolder].amount = 0;
                        	//arr[indexHolder].address = 1000000;
                        	//arr[indexHolder].gap = 0;
                        	//arr[indexHolder].gap = arr[indexHolder+1].address - (arr[indexHolder-1].amount + arr[indexHolder-1].address);//set gap
                        	arr[indexHolder].gap = arr[indexHolder].amount;
                        	for (int k = 0; k < temp; k++)
                        	{
                                	arr[indexHolder].s[k] = '\0';
                        	}
                        	//printf("gap set: %d\n", arr[indexHolder].gap);
                        	for (int i = 0; i < temp; i++)
                        	{	
                                	str[i] = '\0';
                        	}


                        	temp = 0;
				//arr[indexHolder].position = 11000;
				arr[indexHolder].changed = 2;

				//printf("indexHolder: %d\n", indexHolder);
				//printf("%d\n", arr[indexHolder].position);
				//combine gaps
				//both conditions cannot be true at the same time
				//printf("%d, %d\n", arr[arr[indexHolder].position - 1].gap, arr[arr[indexHolder].position - 1].changed);
				//printf("%d, %d\n", arr[arr[indexHolder].position + 1].gap, arr[arr[indexHolder].position + 1].changed);

				int pos = arr[indexHolder].position;
				for (int f = 0; f < index; f++)
				{
					if (arr[f].position == pos + 1 && arr[f].gap > 0 && arr[f].changed != 3)//if the object has a gap and its position is one above it, changed = 3 means ignore
					{
						//printf("right below you\n");
						arr[indexHolder].position = arr[indexHolder].position; //position stays the same
						arr[indexHolder].gap = arr[indexHolder].gap + arr[f].gap;//add the gaps
						arr[indexHolder].addressHolder = arr[indexHolder].addressHolder;//address stays the same
						arr[indexHolder].changed = 2; //set change to 2 meaning its a gap
					        arr[f].changed = 3;//forget about this forever
						for (int g = 0; g < index; g++)//shuffle down by one
						{
							if (arr[g].position > arr[indexHolder].position)
							{
								arr[g].position = arr[g].position - 1;
							}
						}
						break;
					}
				}
				
				for (int f = 0; f < index; f++)
				{
					if (arr[f].position == pos - 1 && arr[f].gap > 0 && arr[f].changed != 3)
					{
						//printf("right above you\n");
						arr[indexHolder].position = arr[f].position;
						arr[indexHolder].gap = arr[indexHolder].gap + arr[f].gap;
						arr[indexHolder].addressHolder = arr[f].addressHolder;
						arr[indexHolder].changed = 2;
						arr[f].changed = 3;
						for (int g = 0; g < index; g++)
						{
							if (arr[g].position > arr[indexHolder].position)
							{
								arr[g].position = arr[g].position - 1;
							}
						}
						break;
					}
				}



						


						








				/*
				if (arr[indexHolder-1].gap > 0 && arr[indexHolder-1].changed == 1)
				{
					int positioner = indexHolder - 1;
					if(arr[indexHolder-1].position == 11000)
					{
						for (int g = positioner; g > -1; g--)
						{
							if (arr[g].position != 11000)
							{
								positioner = g;
								break;
							}
						}
					}


					if (indexHolder != 0)
						arr[indexHolder].gap = arr[positioner].gap + arr[indexHolder].gap;
					else
						arr[indexHolder].gap = arr[indexHolder].amount;
					if (indexHolder != 0)
						arr[indexHolder].addressHolder = arr[positioner].addressHolder;
					else
						arr[indexHolder].addressHolder = arr[indexHolder].addressHolder;
					//printf("%d\n", arr[indexHolder-1].addressHolder);
					arr[positioner].changed = 3;//ignore the previous gap
					arr[indexHolder].position = arr[positioner].position;
					arr[positioner].position = 11000;//gone forever

					printf("higher gap\n");
					//gap under it
				}
				else if (arr[indexHolder+1].gap > 0 && arr[indexHolder+1].changed == 1)
				{
					int positioner = indexHolder + 1;
					if (arr[indexHolder+1].position == 11000)
					for (int g = positioner; g < index; g++)
					{
						if (arr[g].position != 11000)
						{
							positioner = g;
							break;
						}
					}
					if (indexHolder != 0)
                                                arr[indexHolder].gap = arr[positioner].gap + arr[indexHolder].gap;
                                        else
                                                arr[indexHolder].gap = arr[indexHolder].amount;
                                        if (indexHolder != 0)
                                                arr[indexHolder].addressHolder = arr[indexHolder].addressHolder;
                                        else
                                                arr[indexHolder].addressHolder = arr[indexHolder].addressHolder;
                                        //printf("%d\n", arr[indexHolder-1].addressHolder);
                                        arr[positioner].changed = 3;//ignore the previous gap
                                        arr[indexHolder].position = arr[positioner].position;
                                        arr[positioner].position = 11000;//gone forever

					printf("lower gap\n");
					//gap above it
				}
				*/

			}
		}
		else if (pretemp[i] == 'L')
		{
			if (pretemp[i+5] == 'A' && pretemp[i+6] == 'S')
			{
				int faq = index + 25;
				int tempPos = 0;
				//LIST ASSIGNED
				//printf("LIST ASSIGNED\n");
				//
				i = i + 13;

				for (int e = 0; e <= faq; e++)
				{
					//printf("temp = %d\n", tempPos);
					//printf("e = %d\n", e);
					if (index == 0)
					{
						printf("NONE");
						break;
					}
					
					else
					{
						int none = 0;
						for (int h = 0; h < index; h++)
						{
							if (arr[h].changed != 0)
							{
								none = 1;
							}
							else if (arr[h].changed == 0)
							{
								none = 0;
								break;
							}
						}
						if (none == 1)
						{
							printf("NONE");
							break;
						}
					}
					//printf("gap is: %d\n", arr[e].gap);
					//if (arr[tempPos].gap == 0)
                                        //{
						//printf("hello\n");
                                                for (int r = 0; r <= index; r++)
                                                {
                                                        //printf("index: %d\n", r);
                                                        //printf("%d  %d\n", tempPos, arr[r].position);
                                                        //printf("(%s, %d, %d, %d, %d, %d)\n", arr[r].s, arr[r].amount, arr[r].addressHolder, arr[r].position, arr[r].gap, arr[r].changed);
							/*
							if (arr[r].gap == 0 && arr[r].position == 11000 && arr[r].changed == 0)
							{
								printf("heyyyyyyyyyy\n");
								//printf("(%s, %d, %d) ", arr[r].s, arr[r].amount, arr[r].addressHolder);
                                                                //tempPos++;
                                                                //printf("temp: %d\n", tempPos);
                                                                break;
							}
							*/
							/*
							if (arr[r].gap == 0 && arr[r].position == 11000 && arr[r].changed == 1 && arr[r].skip == 0)
							{
								printf("(%s, %d, %d) ", arr[r].s, arr[r].amount, arr[r].addressHolder);
								arr[r].skip = 1;
							}
							*/
							if (arr[r].position == tempPos && arr[r].gap == 0 && arr[r].changed == 0)
                                                        {
								//printf("hellllo\n");
                                                                printf("(%s, %d, %d) ", arr[r].s, arr[r].amount, arr[r].addressHolder);
                                                                tempPos++;
                                                                //printf("temp: %d\n", tempPos);
							}
							else if (arr[r].position == 11000)
							{
								tempPos++;
								continue;
							}
							else if (arr[r].position == tempPos && arr[r].gap != 0 && arr[r].changed == 1)
							{
								tempPos++;
								
							}
							else if (arr[r].position == tempPos && arr[r].gap != 0 && arr[r].changed == 2)
							{
								tempPos++;
							}
							//else
							//{
							//	tempPos++;
							//}
							//else if (r+1 >= index)
							//{
							//	tempPos++;
							//	break;
							//}
                                                }

                                        //}
					/*
					else if (arr[e].gap != 0 && arr[e].changed == 3)
					{
						
						//printf("looking: (%s, %d, %d, %d, %d, %d)\n", arr[e].s, arr[e].amount,
                                                 //                               arr[e].addressHolder, arr[e].position, arr[e].changed, arr[e].gap);
						//printf("hi\n");
						if (arr[e].changed == 2 || arr[e].changed == 3)//unoccupied
						{
							//printf("heeeeee\n");
							tempPos++;
							continue;
						}
						else if (arr[e].changed == 1)
						{
							for (int r = 0; r <= index; r++)
                                                	{
                                                        	//printf("index: %d\n", r);
                                                        	//printf("%d  %d\n", tempPos, arr[r].position);
                                                        	printf("(%s, %d, %d, %d, %d)\n", arr[e].s, arr[e].amount, arr[e].addressHolder, arr[e].position, arr[e].gap);
                                                        	//printf("%d\n", tempPos);
                                                        	if (arr[r].position == tempPos && arr[r].gap == 0)
                                                        	{
									//printf("herrrrrreee\n");
                                                                	printf("(%s, %d, %d) ", arr[r].s, arr[r].amount, arr[r].addressHolder);
                                                                	tempPos++;
                                                                	//printf("temp: %d\n", tempPos);
                                                                	break;
                                                        	}
                                                	}

						}
						
						
							if (arr[e].position == 11000)
							{
								printf("here\n");
								continue;
							}
							else if (arr[e].changed == 1)
							{
								printf("skipped: (%s, %d, %d, %d, %d)\n", arr[e].s, arr[e].amount, 
										arr[e].addressHolder, arr[e].position, arr[e].changed);
								printf("skipper\n");
								tempPos++;
							}
							
						
						//printf("%d\n", arr[e].position);
						//printf("skip\n");
						//tempPos++;
						continue;
					}
					else if (arr[e].gap != 0 && arr[e].changed == 1)
					{
						//printf("skip too\n");
						continue;
					}
					else
					{
						//printf("hey\n");
						tempPos++;
						continue;
					}	
					
				}
				*/
			}
				printf("\n");

			}
			else if (pretemp[i+5] == 'A' && pretemp[i+6] == 'V')
			{
				int tempPos = 0;
				int noGap = 0;
				i = i + 14;
				//printf("%d, %d\n", holder, origin);

				for (int u = 0; u <= index; u++)
				{
					//printf("%d\n", arr[u].gap);
					if (holder == origin)
					{
						printf("(%d, %d) ", origin, memTemp);
						break;
					}
					int none = 0;
                                        for (int h = 0; h < index; h++)
                                        {
                                               if (arr[h].changed != 0)
                                               {
                                                       none = 1;
                                               }
                                               else if (arr[h].changed == 0)
                                               {
                                                        none = 0;
                                                       break;
                                               }
                                         }
                                        if (none == 1)
                                        {
						none = 0;
                                                  printf("(%d, %d) ", origin, none);
                                                  break;
                                        }
					else if (u+1 >= index && memTemp < origin)
                                        {
                                                printf("(%d, %d) ", holder, memTemp);
                                                break;
                                        }
                                        else if (holder == 0 && u + 1 > index && noGap == 0)
                                        {
                                                printf("FULL");
                                                break;
                                        }
					else
					{
						for (int r = 0; r <= index; r++)
						{
							if (arr[r].position == tempPos && arr[r].gap > 0 && (arr[r].changed == 1 || arr[r].changed == 2))
							{
								printf("(%d, %d) ", arr[u].gap, arr[u].addressHolder);
								tempPos++;
								noGap = 1;
							}
							else if (arr[r].position == tempPos && arr[r].changed == 0)
							{
								tempPos++;
							}
						}
					}
					/*
					else if (u+1 >= index && memTemp < origin)
					{
						printf("(%d, %d) ", holder, memTemp);
						break;
					}
					else if (holder == 0 && u + 1 > index && noGap == 0)
					{
						printf("FULL");
						break;
					}
					*/
				}
				printf("\n");
				//LIST AVAILABLE
				//printf("LIST AVAILABLE\n");
				//printf("(%d, %d)\n", holder, memTemp);

			}
		}
		else if (pretemp[i] == 'F' && pretemp[i+1] == 'I')
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
					printf("(%s, %d, %d)\n", arr[k].s, arr[k].amount, arr[k].addressHolder);
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
