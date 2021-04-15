
#include "belt.h"

/* this is a fisr in first out linked list */

// insert candy type in to link list belt
void produce(ProductType candy, Link * head)
{
    Link ptr = (node*) malloc(sizeof(struct node));// allocates memory for the node
    ptr->candy = candy;
    ptr->next = *head;
    *head = ptr;

    // update print variables
    produced++;
    if(candy == FrogBite) CFBnum++;
    else EESnum++;
}

// helps to update belt global variables
void consume_helper(ConsumerType consumer, ProductType candy)
{
    if(consumer == Lucy)
    {
        if(candy == FrogBite)
            lucyCFB++;
        else // escargot
            lucyEES++;
    }
    else // Ethel
    {
        if(candy == FrogBite)
            ethelCFB++;
        else // escargot
            ethelEES++;
    }
}

// removes and returns the last element in the Link
// Link * head to allow for modification of head pointer
ProductType consume(ConsumerType consumer, Link * head){

    if(*head == NULL) exit(-1);

    // traverse the Link
    Link prev = NULL;// prev is pointer
    Link ptr = *head;// ptr is pointer, not head itself
    while(ptr->next != NULL){
        prev = ptr;
        ptr = ptr->next;
    }

    // if only one node on list
    if(prev == NULL){
        Link tmp = (node*)(sizeof(struct node)); // create temporary node
        tmp = ptr;
        *head = NULL;

        // update consumer belt variables
        consume_helper(consumer, tmp->candy);
        return tmp->candy;
    }

    // if more than one node
    prev->next = NULL;
    // update consumer belt variables
    consume_helper(consumer, ptr->candy);
    return ptr->candy;
}

// count the number of candy type on list
int candycount(ProductType candy, Link head)
{
    Link ptr = head;
    int count = 0;
    while(ptr != NULL){
        if(ptr->candy == candy) count++;
        ptr = ptr->next;
    }
    return count;
}

//prints the Link for testing
void printlist(Link ptr){
    printf("Printing Linked List:\n");
    while(ptr != NULL){
        // frog bytes = 0, escargot = 1
        printf("%s\n", ptr->candy ? "escargot": "frog bites");
        ptr = ptr->next;// same as ptr->next
    }
    printf("\n");
}

// print what is currently in belt
void printupdate(Link head)
{
    int p_frog = candycount(FrogBite, head);
    int p_escar = candycount(Escargot, head);
    printf("Belt: %d frogs + %d escargots = %d. produced: %d\t",
         p_frog, p_escar, p_frog + p_escar, produced);
}

// prind production and consupption report
void printreport()
{
    printf("\nPRODUCTION REPORT\n");
    printf("----------------------------------------\n");
	printf("crunchy frog bite producer generated %d candies\n", CFBnum);
	printf("escargot sucker producer generated %d candies\n", EESnum);
	printf("Lucy consumed %d crunchy frog bites + %d escargot suckers = %d\n",
    lucyCFB, lucyEES, lucyCFB + lucyEES);
	printf("Ethel consumed %d crunchy frog bites + %d escargot suckers = %d\n",
    ethelCFB, ethelEES, ethelCFB + ethelEES);
}