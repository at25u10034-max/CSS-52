#include <stdio.h>
#include "../include/pqueue.h"

#define CAP 5

void status(Queue *q)
{
    printf("SIZE=%d EMPTY=%d FULL=%d\n",
           size(q), isEmpty(q), isFull(q));
}

int main()
{
    printf("\n===== PRIORITY QUEUE TEST SUITE =====\n");

    Queue q = createqueue(CAP);

    printf("\nINITIAL STATE\n");
    showqueue(&q);
    status(&q);

    /* ------------------------------------------------ */
    /* CYCLE 1 : BASIC INSERTION ORDER TEST             */
    /* ------------------------------------------------ */

    printf("\nCYCLE 1 : INSERT OUT OF ORDER\n");

    printf("ENQUEUE (10,3)\n");
    enqueue(&q,10,3);
    showqueue(&q); status(&q);

    printf("ENQUEUE (20,1)\n");
    enqueue(&q,20,1);
    showqueue(&q); status(&q);

    printf("ENQUEUE (30,2)\n");
    enqueue(&q,30,2);
    showqueue(&q); status(&q);

    printf("ENQUEUE (40,5)\n");
    enqueue(&q,40,5);
    showqueue(&q); status(&q);

    printf("ENQUEUE (50,4)\n");
    enqueue(&q,50,4);
    showqueue(&q); status(&q);

    /* expect sorted by weight */


    /* ------------------------------------------------ */
    /* CYCLE 2 : OVERFLOW TEST                          */
    /* ------------------------------------------------ */

    printf("\nCYCLE 2 : OVERFLOW\n");

    printf("ENQUEUE (60,6) EXPECT OVERFLOW\n");
    enqueue(&q,60,6);
    showqueue(&q); status(&q);


    /* ------------------------------------------------ */
    /* CYCLE 3 : DEQUEUE ORDER                          */
    /* ------------------------------------------------ */

    printf("\nCYCLE 3 : DEQUEUE IN PRIORITY ORDER\n");

    printf("DEQUEUE -> %d\n", dequeue(&q));
    showqueue(&q); status(&q);

    printf("DEQUEUE -> %d\n", dequeue(&q));
    showqueue(&q); status(&q);


    /* ------------------------------------------------ */
    /* CYCLE 4 : WRAP AROUND INSERT                     */
    /* ------------------------------------------------ */

    printf("\nCYCLE 4 : WRAP AROUND INSERT\n");

    printf("ENQUEUE (60,0)\n");
    enqueue(&q,60,0);
    showqueue(&q); status(&q);

    printf("ENQUEUE (70,7)\n");
    enqueue(&q,70,7);
    showqueue(&q); status(&q);


    /* ------------------------------------------------ */
    /* CYCLE 5 : PEEK TEST                              */
    /* ------------------------------------------------ */

    printf("\nCYCLE 5 : PEEK\n");

    printf("PEEK -> %d\n", peek(&q));
    showqueue(&q); status(&q);


    /* ------------------------------------------------ */
    /* CYCLE 6 : MIXED OPERATIONS                       */
    /* ------------------------------------------------ */

    printf("\nCYCLE 6 : MIXED OPERATIONS\n");

    printf("DEQUEUE -> %d\n", dequeue(&q));
    showqueue(&q); status(&q);

    printf("ENQUEUE (80,3)\n");
    enqueue(&q,80,3);
    showqueue(&q); status(&q);

    printf("ENQUEUE (90,8)\n");
    enqueue(&q,90,8);
    showqueue(&q); status(&q);


    /* ------------------------------------------------ */
    /* CYCLE 7 : CLEAR COMPLETELY                       */
    /* ------------------------------------------------ */

    printf("\nCYCLE 7 : CLEAR ALL\n");

    while(!isEmpty(&q))
    {
        printf("DEQUEUE -> %d\n", dequeue(&q));
        showqueue(&q); status(&q);
    }


    /* ------------------------------------------------ */
    /* CYCLE 8 : UNDERFLOW                              */
    /* ------------------------------------------------ */

    printf("\nCYCLE 8 : UNDERFLOW\n");

    printf("DEQUEUE EXPECT UNDERFLOW\n");
    dequeue(&q);
    showqueue(&q); status(&q);


    /* ------------------------------------------------ */
    /* CYCLE 9 : STABILITY TEST (SAME PRIORITY)         */
    /* ------------------------------------------------ */

    printf("\nCYCLE 9 : SAME PRIORITY TEST\n");

    printf("ENQUEUE 100, 200, 300\n");

    enqueue(&q,100,2);
    enqueue(&q,200,2);
    enqueue(&q,300,2);

    showqueue(&q); status(&q);

    printf("DEQUEUE -> %d\n", dequeue(&q)); showqueue(&q); status(&q);
    printf("DEQUEUE -> %d\n", dequeue(&q)); showqueue(&q); status(&q);
    printf("DEQUEUE -> %d\n", dequeue(&q)); showqueue(&q); status(&q);

    showqueue(&q); status(&q);


    printf("\n===== TEST COMPLETE =====\n");

    return 0;
}