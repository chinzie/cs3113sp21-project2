# cs3113sp21-project2


This project was divided up into 4 sections: BESTFIT, FIRSTFIT, WORSTFIT, NEXTFIT

I first made BESTFIT and after I was done I copy and pasted 95% of the code for the other sections.

The code is relatively the same for all sections except for where it decides to put new objects in the memory.
So each section has its own logic for "gaps" in the memory to decide where to put it based on its task.

My project achieves this by keeping track of the "position" for each object. I make gaps objects too in order to keep track of where everything is theoretically.
So if 3 objects are put into memory and one is taken away, the gap makes it so in memory I still have three objects to keep track of and all positions stay the same.

If an object that is smaller than a gap but can fit inside of it, it takes the gaps place, in theory, and takes its position. Since It shoved an object in a gap, the machine must now send everything behind it, including gaps, back a position. This is because if there is leftover gap from placing the object in the original gap space, I still want to keep track of that gap leftover. Now I theoretically keep track of all my objects and gaps and they are all in order by their "position".

For listing out all available space, I have my machine loop through the array and find gaps. It finds these gaps because they will have a change value that is either equal to 2 or 1. 1 means it has been filled in partially and 2 means it has not been filled in at all. Regardless, it prints out those gaps based on their position value as to print it out in order.

For listing out assigned objects, like the gaps, it prints them out in order of its position value, while ignoring gaps. It does this by focsuing on the change values, since objects that are not gaps will have change values of 0. If it aproaches upon a gap then it increments a position up, this is to simulate the machine moving up in the order as my program reserves a spot for every gap.

Lastly, this was probably not the most efficient form of accomplishing this but it is what I thought would work for me.
There is a bug for WORSTFIT AND FIRSTFIT where everything is correct except for when it prints out the available spaces, it is wrong on the amounts.

If I had more time I feel as if I could solve this bug but I spent over a week just on BESTFIT to work and all the bugs that came along with it but I am happy with what I have produced.
