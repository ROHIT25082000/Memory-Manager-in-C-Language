# Memory-Manager-in-C-Language
Memory Manager mimics the malloc function in C language 
1.)
The Allocation Policy is Worst Fit . 
2.)
Allocation (using Worst fit):- change
    The basic logic of my implementation for the Worst Fit Policy was to create a pointer of the type "Book" ie. Bookkeeping structure
    called maxPointer and then we traverse the Bookkeeping linked list 
    and  keep updating the max = 0 based on the size .After using a while loop for this my maxPointer points to the Worst fitting block
    .Then further investingation is done to know whether freeblock is enough to accomodate a book (structure) or not along with memory
    required .This investingation is shown in the comments of the code.If the space is not sufficient(For the required block excluding 
    Bookkeeping structure) then simply return NULL. 

Free function (with merging):-
    The cases of the Free can be tackled by keeping a previous (prev) and current (temp) pointer 
    If the prev block and next block is free the we merge the blocks and update the Bookkeeping structure with its fields
        i.  occ = (occupied or not)
        ii. num = free bytes from this.
        iii.link = next pointer (next block)
display Function:
    Initially we use the print the book size with start address and size.
    From then onwards I keep a pointer "temp" (to the book) from the first book.
    and I traverse the whole linked list and print the sizes ,address base on the "occ" and "num" fields
    of the structure.

3.)
The Explanation of the Bookkeeping structure
struct Book
{
    int num;                // Number of free bytes after current book structure.
    int occ;                // Checks Allocated(1) or free(0) 
    struct Book*link; //    points to the next Bookkeeping structures .
};
typedef struct Book Book;

4.)
The takeaway from this assignment was 
I understood the way the memory management takes place . 
Some policies like Worst fit were challenging but interesting to study
At last I enjoyed the power of pointers in a language like C and helped revise it.

-by Rohit Vishwakarma
    PES1201800152 
    Worst Fit Policy.
    
