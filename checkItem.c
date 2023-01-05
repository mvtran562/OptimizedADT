#include "list.c"

int main(int argv, char* argc[]) {
	LIST *lp;
	lp = createList();
	
	addFirst(lp, (void*) 1); //index 0
	addFirst(lp, (void*) 2); //index 1
	addFirst(lp, (void*) 3); //index 2
	
	addFirst(lp, (void*) 4);
	addFirst(lp, (void*) 5);
	addFirst(lp, (void*) 6);
	addFirst(lp, (void*) 7);
	addFirst(lp, (void*) 8);
	addFirst(lp, (void*) 9);
	addFirst(lp, (void*) 10);
	addFirst(lp, (void*) 11);


	int i;
	for(i = 0; i < 3; i++)
	{
		printf("\nIndex 0: %d",getItem(lp, i));
		fflush(stdout);
	}
	
	
	for(i = 0; i < 3; i++) {
		printf("\nNumber %d: %d", i, removeFirst(lp));
		fflush(stdout);
	}
	destroyList(lp);

}
