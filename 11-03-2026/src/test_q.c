#include <stdio.h>
#include "./2stackq.c"

#define CAP 5

int main()
{
    Queue q = createqueue(CAP);

    printf("\n===== LINEAR QUEUE TEST SUITE =====\n");

    printf("\nINITIAL STATE\n");
    showqueue(&q);

    /* -------- TEST 1 : BASIC ENQUEUE -------- */

    printf("\nTEST 1 : BASIC ENQUEUE\n");

    printf("ENQUEUE 10\n");
    enqueue(&q,10); showqueue(&q);

    printf("ENQUEUE 20\n");
    enqueue(&q,20); showqueue(&q);

    printf("ENQUEUE 30\n");
    enqueue(&q,30); showqueue(&q);


    /* -------- TEST 2 : BASIC DEQUEUE -------- */

    printf("\nTEST 2 : BASIC DEQUEUE\n");

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q));
    showqueue(&q);


    /* -------- TEST 3 : ENQUEUE AFTER PARTIAL CLEAR -------- */

    printf("\nTEST 3 : ENQUEUE AFTER PARTIAL CLEAR\n");

    printf("ENQUEUE 40\n");
    enqueue(&q,40); showqueue(&q);

    printf("ENQUEUE 50\n");
    enqueue(&q,50); showqueue(&q);

    /* -------- TEST 4 : OVERFLOW AT ARRAY END -------- */

    printf("\nTEST 4 : OVERFLOW WHEN REAR REACHES END\n");

    printf("ENQUEUE 20\n");
    enqueue(&q,20); showqueue(&q);

    printf("ENQUEUE 30\n");
    enqueue(&q,30); showqueue(&q);

    printf("ENQUEUE 60 (EXPECT OVERFLOW)\n");
    enqueue(&q,60); showqueue(&q);


    /* -------- TEST 5 : EMPTY THE QUEUE -------- */

    printf("\nTEST 5 : CLEAR COMPLETELY\n");

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q)); showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q)); showqueue(&q);

    printf("DEQUEUE\n");
    printf("REMOVED %d\n", dequeue(&q)); showqueue(&q);


    /* -------- TEST 6 : UNDERFLOW -------- */

    printf("\nTEST 6 : UNDERFLOW\n");

    printf("DEQUEUE (EXPECT UNDERFLOW)\n");
    dequeue(&q); showqueue(&q);


    /* -------- TEST 7 : SPACE REUSE -------- */

    printf("\nTEST 7 : SPACE EXISTS AND IS NOW AVAILABLE\n");

    printf("ENQUEUE 100 (EXPECT OVERFLOW IF REAR AT END)\n");
    enqueue(&q,100); showqueue(&q);


    /* -------- TEST 8 : PEEK -------- */

    printf("\nTEST 8 : PEEK\n");

    printf("PEEK\n");
    printf("FRONT %d\n", peekq(&q));
    showqueue(&q);


    printf("\n===== TEST SUITE COMPLETE =====\n");

    return 0;
}