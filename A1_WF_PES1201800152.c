#include<stdio.h>
#include<stdlib.h>
#include"assignment_1.h"

char*p;
//function to allocate memory for the global array p, n number of bytes long.
typedef struct Book
{
	int num;	// Number of bytes free after this book.
	int occ;	// Occupied or not .
	struct Book*link; // link for next book.
}Book;

Book*head = NULL;			// head : a pointer for the first Book.
int totalsize;				// The variable holding the total allocated size .
void allocate(int n)
{	
	totalsize= n;
	char * p = (char *)malloc(sizeof(char)*n);
	head  = (Book*)p;							// allocating the first  bookkeeping structure .
	head->num = n-sizeof(Book);				// The free size initially 
	head->occ = 0;						//  indicating free 
	head->link = NULL;			
} 

void* mymalloc(int size)
{
	if(size >totalsize)
		return NULL;
	int max1 = 0;   // variable for finding the worst fit . 
 	Book*temp;
	Book*maxPointer= NULL;
	temp = head;
	while(temp!=NULL)
	{	
		if(temp->num >= size + sizeof(Book) && temp->occ == 0) // making sure the free space is big enough cushion = 10 bytes **
		{
			if(max1 < temp->num)
			{
				maxPointer = temp;
				max1 = temp->num;

			}
		}
		temp = temp->link;
	}
	if(maxPointer==NULL && temp==NULL) // if will execute only if previous while loop could not find a worst fitting block  
	{									// that is big enough.
		//printf("I am here\n");  // This was done during the testing 
		int max2 = 0;
		temp = head;
		while(temp!=NULL)			// This while loop searches memory block of bytes not as big to
		{							// allocate a bookeeping structure .
			if( (size + sizeof(Book)> temp->num)&&(temp->num  >= size) && (temp->occ == 0)) // ** 10
			{
				//printf("I came in \n"); // This was done during the testing 
				if(max2 < temp->num)
				{
					maxPointer = temp;
					max2 = temp->num;
				}
			}
			temp = temp->link;
		}
	}
	else
	{								// This will create a new book structure in the free block because the memory is sufficient
									// to hold the bookkeeping structure.
		char * return_pointer = (char*)(maxPointer+1);	
		Book*newBook = (Book*)(return_pointer+size);
		newBook->num = (maxPointer->num) - (size + sizeof(Book));
		newBook->occ = 0;
		newBook->link = maxPointer->link;
		maxPointer->num = size;
		maxPointer->occ = 1;
		maxPointer->link = newBook;
		return (void*)return_pointer;
	}
	
	if(maxPointer==NULL)
	{
						// This if block is entered if none of the memory space is big enough for the size asked itself. 
		//printf("I am here in the if\n");
		return NULL;
	}
	else
	{
		//printf("I am here in the else");  // Used during  the testing of the code .
		char * return_pointer = (char*)(maxPointer+1); // This block is executed if the free size available is same as asked in 
		maxPointer->occ = 1;							//  instruction this however doesn't create a new book structure 
		return (void*)return_pointer;				// Allocates in previous book structures.
	}
	return NULL;
}

void myfree(void *b)
{
	Book*prev=NULL; // prev pointer folloowing the temp pointer.
	Book*temp;    // temp pointer 
	Book*currBook = (Book*)b; //Takes a pointer to the memory to be freed and cast it to find corresponding book structure
	currBook = currBook -1;// Finds the book 
	temp = head;
	while(temp!=currBook)	// Visits every bookeeping structure..
	{
		prev = temp;
		temp = temp->link;
	}
	if(temp->occ==1) // check if occupied 
	{
		if(prev == NULL)  // Applies all the testcases when prev is NULL 
		{
			if(temp->link!=NULL) // next bookeeping structure exists
			{
				if(temp->link->occ ==0)  // check whether next block is free for merging 
				{
					temp->occ = 0;  // frees the allocation
					temp->link = temp->link->link;
					temp->num = temp->num + temp->link->num+sizeof(Book); // merges the free memory in temp.
				}
				else if(temp->link->occ ==1)
				{
					temp->occ = 0; //no merging of free memory as next block is occupied .
				}
			}
			else if(temp->link==NULL)	// next bookeeping structure doesn't exist.
			{
				temp->occ =0; // simply free the current memory .
			}
		}
		else // when prev is not NULL
		{
			if(temp->link!=NULL)// next bookeeping structures exists and checks .
			{
				if(prev->occ ==0) // if previous is free
				{
					temp->occ =0;		// frees the memory block
					prev->num += temp->num+sizeof(Book);  // merges the all free blocks  
					if(temp->link->occ==0) // if next is also free 
					{
						prev->num+=temp->link->num+sizeof(Book); // merges the free memory from the right side
						prev->link = temp->link->link;
					}
					else if(temp->link->occ==1)// if next is not free 
					{
						prev->link = temp->link; // manages the link of the bookeeping. 
					}
				}
				else if(prev->occ ==1)// if previous is  not free
				{
					if(temp->link->occ==0)// if next is also free 
					{
						temp->occ = 0;
						temp->num +=temp->link->num+sizeof(Book);
						temp->link = temp->link->link;
					}
					else if(temp->link->occ==1)// if next is not free 
					{
						temp->occ = 0;// just frees the current memory
					}
				}
				
			}
			else if(temp->link==NULL)// next bookeeping structure doesn't exists 
			{
				if(prev->occ==0) // only checks the previous blocks
				{
					temp->occ = 0;
					prev->num +=temp->num + sizeof(Book);// merges if the prev is block is free 
					prev->link = NULL;
				}
				else if(prev->occ ==1)
				{
					temp->occ = 0; 		// only frees the current block of memory .
				}
			}
		}
	}
}

void print_book()
{
	printf("The size of the bookkeeping structure = %ld\n",sizeof(Book));
}

void display_mem_map()
{
	Book*temp=head;
	int count = 0;
	printf("%d\t%ld\t%s\n",count,sizeof(Book),"book");	 // always printed as every allocated memory block will have one Book
	count+=sizeof(Book);								// starting.
	while(temp!=NULL)
	{
		if(temp->occ==1) // The if the block is allocated 	.
		{
			printf("%d\t%d\t%s\n",count,temp->num,"allocated");  // prints allocated number of bytes. 
 			count+=temp->num;
			if(temp->link!=NULL){
			printf("%d\t%ld\t%s\n",count,sizeof(Book),"book");  // prints size of book after every block.
			count+=sizeof(Book);
			}

		}
		else if(temp->occ==0)   // The if the block is not allocated 	.
		{
			printf("%d\t%d\t%s\n",count,temp->num,"free"); // prints the free number of the bytes .
			count += temp->num;
			if(temp->link!=NULL){
			printf("%d\t%ld\t%s\n",count,sizeof(Book),"book"); //  prints size of book after every block.
			count+=sizeof(Book);
			}

		}
		temp = temp->link;
	}
}



