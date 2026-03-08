#include <stdio.h>
#include "../include/queue.h"

#define CAP 5

void status(Queue *q)
{
    printf("SIZE=%d  EMPTY=%d  FULL=%d\n",
           size(q), isEmpty(q), isFull(q));
}

int main()
{
    Queue q = createqueue(CAP);

    printf("\n===== CIRCULAR QUEUE TEST SUITE =====\n");

    printf("\nINITIAL STATE\n");
    showqueue(&q);
    status(&q);

    /* ---------- CYCLE 1 : PARTIAL FILL ---------- */

    printf("\nCYCLE 1 : PARTIAL FILL\n");

    printf("ENQUEUE 10\n");
    enqueue(&q,10); showqueue(&q); status(&q);

    printf("ENQUEUE 20\n");
    enqueue(&q,20); showqueue(&q); status(&q);

    printf("ENQUEUE 30\n");
    enqueue(&q,30); showqueue(&q); status(&q);

    printf("PEEK\n");
    printf("FRONT %d\n", peek(&q));
    showqueue(&q); status(&q);


    /* ---------- CYCLE 2 : PARTIAL CLEAR ---------- */

    printf("\nCYCLE 2 : PARTIAL CLEAR\n");

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q); status(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q); status(&q);


    /* ---------- CYCLE 3 : WRAP AROUND ---------- */

    printf("\nCYCLE 3 : WRAP AROUND TEST\n");

    printf("ENQUEUE 40\n");
    enqueue(&q,40); showqueue(&q); status(&q);

    printf("ENQUEUE 50\n");
    enqueue(&q,50); showqueue(&q); status(&q);

    printf("ENQUEUE 60\n");
    enqueue(&q,60); showqueue(&q); status(&q);


    /* ---------- CYCLE 4 : FILL COMPLETELY ---------- */

    printf("\nCYCLE 4 : FILL TO CAPACITY\n");

    printf("ENQUEUE 70\n");
    enqueue(&q,70); showqueue(&q); status(&q);

    printf("ENQUEUE 80 (EXPECT FULL)\n");
    enqueue(&q,80); showqueue(&q); status(&q);


    /* ---------- CYCLE 5 : MIXED OPERATIONS ---------- */

    printf("\nCYCLE 5 : MIXED OPERATIONS\n");

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q); status(&q);

    printf("ENQUEUE 90\n");
    enqueue(&q,90); showqueue(&q); status(&q);

    printf("PEEK\n");
    printf("FRONT %d\n", peek(&q));
    showqueue(&q); status(&q);


    /* ---------- CYCLE 6 : CLEAR COMPLETELY ---------- */

    printf("\nCYCLE 6 : CLEAR ALL\n");

    while(!isEmpty(&q))
    {
        printf("DEQUEUE\n");
        printf("REMOVED %d\n", dequeue(&q));
        showqueue(&q); status(&q);
    }


    /* ---------- CYCLE 7 : UNDERFLOW ---------- */

    printf("\nCYCLE 7 : UNDERFLOW TEST\n");

    printf("DEQUEUE (EXPECT UNDERFLOW)\n");
    dequeue(&q);
    showqueue(&q); status(&q);


    /* ---------- CYCLE 8 : REFILL AFTER EMPTY ---------- */

    printf("\nCYCLE 8 : REFILL AFTER EMPTY\n");

    printf("ENQUEUE 100\n");
    enqueue(&q,100); showqueue(&q); status(&q);

    printf("ENQUEUE 200\n");
    enqueue(&q,200); showqueue(&q); status(&q);

    printf("ENQUEUE 300\n");
    enqueue(&q,300); showqueue(&q); status(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q); status(&q);

    printf("\n===== TEST COMPLETE =====\n");

    return 0;
}