// Matthew Tran
// COEN12 TERM PROJECT
// Creating an ADT that would act like a dynamically growing and decreasing array
// while maintaining efficiency
// Ver. Tue Nov 30 20:12


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

// defining the struct for node
typedef struct node
{
    int first;
    int max;
    int count;
    struct node *prev;
    struct node *next;
    void **data;
}NODE;

// double linked, circular
// defining the struct for list
typedef struct list
{
    int countTotal;
    int numNodes;
    NODE *head;
    // instead of tail, use prev of dummyNode
    // less stuff to worry abt
}LIST;

// Function to create the list
// allocates memory for both the list and the dummy node
// O(1)
LIST *createList(void)
{
    
    LIST *lp;
    lp = malloc(sizeof(LIST));
    assert(lp != NULL);
    lp->countTotal = 0;
    lp->numNodes = 0;

    // initialize dummy
    NODE *dummy;
    dummy = malloc(sizeof(NODE));
    assert(dummy != NULL);
    lp->head = dummy;
    dummy->first = 0;
    dummy->max = 0;
    dummy->count = 0;
    dummy->prev = dummy;
    dummy->next = dummy;
    lp->numNodes++;
    return lp;
    
}

// function that destroys the list
// Will free the array, then free the node itself
// Once the data nodes are freed, the dummy node is freed
// O(logn)
void destroyList(LIST *lp)
{
    assert(lp != NULL);
 
    while(lp->numNodes>1)
    {
        NODE *temp;
        temp = lp->head->prev;
        
        lp->head->prev = temp->prev;
        temp->prev->next = lp->head;
        
        free(temp->data);
        free(temp);
        lp->numNodes--;
    }
    // free dummy
    free(lp->head);

    free(lp);
}

// function that returns the total number of elements
// in ALL of the nodes
// O(1)
int numItems(LIST *lp)
{
    assert(lp != NULL);
    //printf("total count  %d \n ",lp->countTotal);
    return lp->countTotal;
    
}



// This function will add the item at the front of the array/list
// This will take care of the three main cases:
// if this is the very first item
// if the first node array is full
// normal case
// O(1)
void addFirst(LIST *lp, void *item)
{
    assert(lp != NULL);
    assert(item != NULL);
    
    // case if nothing in list
    // Will create a node with an array size 10 and set everything up
    if(lp->countTotal == 0)
    {
        NODE *newNode;
        newNode = malloc(sizeof(NODE));
        assert(newNode != NULL);
        newNode->first = 0;
        newNode->max = 10;
        newNode->count = 0;
        newNode->prev = lp->head;
        newNode->next = lp->head;
        lp->head->prev = newNode;
        lp->head->next = newNode;
        newNode->data = malloc(sizeof(void*) * newNode->max);
        assert(newNode->data != NULL);
        newNode->data[0]=item;
        //increment counts
        newNode->count++;
        lp->numNodes++;
        //printf("add first works. first node \n");
    }
    // case if first is full
    // will allocate a new node with a new array that is double the size
    else if(lp->head->next->count==lp->head->next->max)
    {
        NODE *newNode;
        newNode = malloc(sizeof(NODE));
        assert(newNode != NULL);
        newNode->first = 0;
        newNode->max = lp->head->next->max * 2;
        newNode->count = 0;
        newNode->prev = lp->head;
        newNode->next = lp->head->next;
        lp->head->next->prev = newNode;
        lp->head->next = newNode;
        newNode->data = malloc(sizeof(void*) * newNode->max);
        assert(newNode->data != NULL);
        newNode->data[newNode->first] = item;
        
        //increment counts
        newNode->count++;
        lp->numNodes++;
        //printf("add first works. node full \n");
    }
    // normal case
    // adds and simply decrements count and moves the "first" index over
    else if(lp->head->next->count < lp->head->next->max)
    {
        int first = lp->head->next->first;
        int max = lp->head->next->max;

        if(first == 0)
        {
            lp->head->next->data[max-1] = item;
            lp->head->next->first = max-1;
        }else{

        int index = (first-1) % max;
        lp->head->next->data[index] = item;
        lp->head->next->first = (first-1) % max;
        }
        //increment counts
        lp->head->next->count++;
        //printf("add first works. norm case \n");
    }

    // incremement main counts
     lp->countTotal++;
    
}

// This function will add the item at the back of the array/list
// This will take care of the three main cases:
// if this is the very first item
// if the first node array is full
// normal case
// O(1)
void addLast(LIST *lp, void *item)
{
    
    assert(lp != NULL);
    assert(item != NULL);
    // case: this is the first element 
    // Will create a node with an array size 10 and set everything up
    if(lp->countTotal == 0)
    {
        NODE *newNode;
        newNode = malloc(sizeof(NODE));
        assert(newNode != NULL);
        newNode->first = 0;
        newNode->max = 10;
        newNode->count = 0;
        newNode->prev = lp->head;
        newNode->next = lp->head;
        lp->head->prev = newNode;
        lp->head->next = newNode;
        newNode->data = malloc(sizeof(void*) * newNode->max);
        assert(newNode->data != NULL);
        newNode->data[0]=item;
        //increment counts
        newNode->count++;
        lp->numNodes++;
//        printf("num nodes: %d \n",lp->numNodes);
        //printf("this works first node \n");
    }
    
    // case: last is filled
    // will allocate a new node with a new array that is double the size
    else if(lp->head->prev->count == lp->head->prev->max)
    {
        NODE *newNode;
        newNode = malloc(sizeof(NODE));
        assert(newNode != NULL);
        newNode->first = 0;
        newNode->max = (lp->head->prev->max)*2;
        newNode->count = 0;
        newNode->prev = lp->head->prev;
        newNode->next = lp->head;
        lp->head->prev->next = newNode;
        lp->head->prev = newNode;
        newNode->data = malloc(sizeof(void*) * newNode->max);
        assert(newNode->data != NULL);
        newNode->data[newNode->first]=item; // FIX FIX FIGURE THIS OUT FIX FIX
        newNode->count++;
        lp->numNodes++;
        //printf("this works filled \n");
        //printf("num nodes: %d \n",lp->numNodes);
        
    }
    
    // normal case
    // gets the index for the last item and adds it
    else if(lp->head->prev->count < lp->head->prev->max)
    {
        int first = lp->head->prev->first;
        int count = lp->head->prev->count;
        int max = lp->head->prev->max;


        int index = (first + count) % max;
        lp->head->prev->data[index] = item;
        //lp->head->prev->first = (first+1) % max;
        lp->head->prev->count++;
        assert(lp->head->prev->data[index] != NULL);
        //printf("add last normally. \n");
    }
    
    
    
    

    // incremement main counts
    lp->countTotal++;
}

// function to remove the first item in the list/array
// frees the node if there is nothing left in that node/array
// returns whatever was deleted
// O(1)
void *removeFirst(LIST *lp)
{
    assert(lp != NULL);

    // case if there is nothing left
    // frees the array/node and decrements the node counter
    if(lp->head->next->count == 0)
    {
        NODE *temp;
        temp = lp->head->next;
        lp->head->next = temp->next;
        temp->next->prev = lp->head;
        free(temp->data);
        free(temp);
        lp->numNodes--;
        //printf("empty node is free!! \n");
        //printf("num nodes: %d \n",lp->numNodes);
    }
    //printf("current first node's count %d \n",lp->head->next->count);
    
    // normal case
    int first = lp->head->next->first;
    int max = lp->head->next->max;
    void *ret;
    assert(lp->head->next->data[first] != NULL);
    ret = lp->head->next->data[first];
    lp->head->next->first = (first +1) % max;
    // decrement counts
    lp->head->next->count--;
    lp->countTotal--;
    //printf("first elt removed \n");
    return ret;
}

// function to remove the last item in the list/array
// frees the node if there is nothing left in that node/array
// returns what was deleted
// O(1)
void *removeLast(LIST *lp)
{
    // we are deleting first +count -1

    // last node empty
    // frees the array/node and decrements the node counter
    if (lp->head->prev->count == 0)
    {
        NODE *temp;
        temp = lp->head->prev;
        
        lp->head->prev = temp->prev;
        temp->prev->next = lp->head;
        
        free(temp->data);
        free(temp);
        lp->numNodes--;
        //printf("empty node is free!! \n");
    }

    // normal case
    int first = lp->head->prev->first;
    int max = lp->head->prev->max;
    int count = lp->head->prev->count;
    int index = (first + count -1) % max;
    void *ret;
    ret = lp->head->prev->data[index];
    // decrement counts    
    lp->head->prev->count--;
    lp->countTotal--;
    return ret;
}

// This function will get the very first item in the array/list
// O(1)
void *getFirst(LIST *lp)
{
    assert(lp!=NULL);
    return lp->head->next->data[lp->head->next->first];
}

// This function will get the very last item in the array/list
// O(1)
void *getLast(LIST *lp)
{
    assert(lp!=NULL);
    assert(lp->countTotal > 0);
    int first = lp->head->prev->first;
    int max = lp->head->prev->max;
    int count = lp->head->prev->count;
    int index = (first + count -1) % max;
    return lp->head->prev->data[index];
}

// Gets the item at the index passed from the parameter
// It will go from node to node until the index is within that node
// best: O(1) and avg O(logn)
void *getItem(LIST *lp, int index)
{ 
    assert(lp!=NULL);
    assert(lp->countTotal > 0);
    assert(index < lp->countTotal);
  
    NODE *tempFirst;
    tempFirst = lp->head->next;
    

    while (index >= tempFirst->count)
    {
        
        
        index = index - tempFirst->count;
        tempFirst = tempFirst->next;
    }
    //printf("%d",tempFirst->first);
    //fflush(stdout);
    
    return tempFirst->data[(index + tempFirst->first) % tempFirst->max]; //check 
    
}

// This will set the item at the specified index to the item that
// is passed in
// Will search each node until the index is within it
// best: O(1) and avg O(logn)
void setItem(LIST *lp, int index, void *item)
{
    assert(lp!=NULL);
    assert(lp->countTotal > 0);
    assert(index < lp->countTotal);
  
    NODE *tempFirst;
    tempFirst = lp->head->next;
    

    while (index >= tempFirst->count)
    {
        index = index - tempFirst->count;
        tempFirst = tempFirst->next;
        
    
    }
   
    tempFirst->data[(index + tempFirst->first) % tempFirst->max] = item;
}