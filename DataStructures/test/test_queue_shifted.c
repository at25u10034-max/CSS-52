#include <stdio.h>
#include "../include/queue.h"

#define CAPACITY 5

int main()
{
    printf("\n===== QUEUE ADT TEST KIT =====\n");

    Queue q = createqueue(CAPACITY);

    printf("\nINITIAL STATE\n");
    showqueue(&q);


    /* -------- Cycle 1 : Fill Completely -------- */

    printf("\n===== CYCLE 1 : FULL FILL =====\n");

    printf("ENQUEUE 10\n");
    enqueue(&q,10); showqueue(&q);

    printf("ENQUEUE 20\n");
    enqueue(&q,20); showqueue(&q);

    printf("ENQUEUE 30\n");
    enqueue(&q,30); showqueue(&q);

    printf("ENQUEUE 40\n");
    enqueue(&q,40); showqueue(&q);

    printf("ENQUEUE 50\n");
    enqueue(&q,50); showqueue(&q);

    printf("ENQUEUE 60 (EXPECT OVERFLOW)\n");
    enqueue(&q,60); showqueue(&q);


    /* -------- Cycle 2 : Partial Clear + Refill -------- */

    printf("\n===== CYCLE 2 : PARTIAL CLEAR =====\n");

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("PEEK\n");
    printf("FRONT %d\n", peek(&q));
    showqueue(&q);

    printf("ENQUEUE 70\n");
    enqueue(&q,70); showqueue(&q);

    printf("ENQUEUE 80\n");
    enqueue(&q,80); showqueue(&q);


    /* -------- Cycle 3 : Clear All -------- */

    printf("\n===== CYCLE 3 : CLEAR COMPLETELY =====\n");

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE (EXPECT UNDERFLOW)\n");
    dequeue(&q); showqueue(&q);


    /* -------- Cycle 4 : Small Fill -------- */

    printf("\n===== CYCLE 4 : SMALL FILL =====\n");

    printf("ENQUEUE 100\n");
    enqueue(&q,100); showqueue(&q);

    printf("ENQUEUE 200\n");
    enqueue(&q,200); showqueue(&q);

    printf("PEEK\n");
    printf("FRONT %d\n", peek(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);


    /* -------- Cycle 5 : Mixed Pattern -------- */

    printf("\n===== CYCLE 5 : MIXED OPERATIONS =====\n");

    printf("ENQUEUE 300\n");
    enqueue(&q,300); showqueue(&q);

    printf("ENQUEUE 400\n");
    enqueue(&q,400); showqueue(&q);

    printf("ENQUEUE 500\n");
    enqueue(&q,500); showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("ENQUEUE 600\n");
    enqueue(&q,600); showqueue(&q);

    printf("ENQUEUE 700\n");
    enqueue(&q,700); showqueue(&q);

    printf("ENQUEUE 800 (EXPECT OVERFLOW)\n");
    enqueue(&q,800); showqueue(&q);


    /* -------- Cycle 6 : Alternating Pattern -------- */

    printf("\n===== CYCLE 6 : ALTERNATING =====\n");

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("ENQUEUE 900\n");
    enqueue(&q,900); showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("ENQUEUE 1000\n");
    enqueue(&q,1000); showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);


    /* -------- Cycle 7 : Final Drain -------- */

    printf("\n===== CYCLE 7 : FINAL DRAIN =====\n");

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE (EXPECT UNDERFLOW)\n");
    dequeue(&q); showqueue(&q);

    printf("\n===== TEST COMPLETE =====\n");

    return 0;
}