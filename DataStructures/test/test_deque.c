#include <stdio.h>
#include "../include/deque.h"

#define CAP 5

void status(Deque *d)
{
    printf("SIZE=%d EMPTY=%d FULL=%d MODE=%d\n",
           size(d), isEmpty(d), isFull(d), d->mode);
}

int main()
{
    printf("\n===== DEQUE TEST SUITE =====\n");

    /* ========================================== */
    /* UNRESTRICTED DEQUE                         */
    /* ========================================== */

    printf("\n--- UNRESTRICTED DEQUE ---\n");

    Deque d = createdeque(CAP, UNRESTRICTED);

    printf("\nINITIAL STATE\n");
    showdeque(&d);
    status(&d);


    /* CYCLE 1 */

    printf("\nCYCLE 1 : BASIC INSERTIONS\n");

    printf("ENQUEUE_FRONT 10\n");
    enqueue_front(&d,10);
    showdeque(&d); status(&d);

    printf("ENQUEUE_REAR 20\n");
    enqueue_rear(&d,20);
    showdeque(&d); status(&d);

    printf("ENQUEUE_FRONT 30\n");
    enqueue_front(&d,30);
    showdeque(&d); status(&d);

    printf("ENQUEUE_REAR 40\n");
    enqueue_rear(&d,40);
    showdeque(&d); status(&d);


    /* CYCLE 2 */

    printf("\nCYCLE 2 : READ OPERATIONS\n");

    printf("FRONT\n");
    printf("VALUE %d\n", front(&d));
    showdeque(&d); status(&d);

    printf("BACK\n");
    printf("VALUE %d\n", back(&d));
    showdeque(&d); status(&d);


    /* CYCLE 3 */

    printf("\nCYCLE 3 : FILL COMPLETELY\n");

    enqueue_rear(&d,50);
    showdeque(&d); status(&d);

    printf("EXPECT OVERFLOW\n");
    enqueue_front(&d,60);
    showdeque(&d); status(&d);


    /* CYCLE 4 */

    printf("\nCYCLE 4 : REMOVE BOTH ENDS\n");

    printf("%d\n", dequeue_front(&d));
    showdeque(&d); status(&d);

    printf("%d\n", dequeue_rear(&d));
    showdeque(&d); status(&d);


    /* CYCLE 5 */

    printf("\nCYCLE 5 : WRAP AROUND\n");

    enqueue_front(&d,70);
    showdeque(&d); status(&d);

    enqueue_rear(&d,80);
    showdeque(&d); status(&d);


    /* CYCLE 6 */

    printf("\nCYCLE 6 : MIXED OPERATIONS\n");

    dequeue_front(&d);
    showdeque(&d); status(&d);

    enqueue_rear(&d,90);
    showdeque(&d); status(&d);

    printf("BACK=%d\n", back(&d));


    /* CYCLE 7 */

    printf("\nCYCLE 7 : CLEAR COMPLETELY\n");

    while(!isEmpty(&d))
    {
        printf("REMOVED %d\n", dequeue_front(&d));
        showdeque(&d); status(&d);
    }


    /* CYCLE 8 */

    printf("\nCYCLE 8 : UNDERFLOW\n");

    dequeue_front(&d);
    showdeque(&d); status(&d);


    freedeque(&d);


    /* ========================================== */
    /* INPUT RESTRICTED DEQUE                     */
    /* ========================================== */

    printf("\n--- INPUT RESTRICTED DEQUE ---\n");

    Deque in = createdeque(CAP, INPUT_RESTRICTED);

    enqueue_rear(&in,1);
    enqueue_rear(&in,2);
    showdeque(&in);

    printf("TRY ENQUEUE_FRONT (EXPECT ERROR)\n");
    enqueue_front(&in,3);

    printf("DEQUEUE_FRONT\n");
    printf("REMOVED %d\n", dequeue_front(&in));

    printf("DEQUEUE_REAR\n");
    printf("REMOVED %d\n", dequeue_rear(&in));

    freedeque(&in);


    /* ========================================== */
    /* OUTPUT RESTRICTED DEQUE                    */
    /* ========================================== */

    printf("\n--- OUTPUT RESTRICTED DEQUE ---\n");

    Deque out = createdeque(CAP, OUTPUT_RESTRICTED);
    // printf("%d %d\n", out.FRONT, out.REAR);
    showdeque(&out);
    status(&out);

    printf("ENQUEUE_FRONT 1\n");
    enqueue_front(&out,1);
    showdeque(&out);
    status(&out);

    printf("ENQUEUE_REAR 2\n");
    enqueue_rear(&out,2);
    showdeque(&out);
    status(&out);

    printf("TRY DEQUEUE_REAR (EXPECT ERROR)\n");
    dequeue_rear(&out);
    showdeque(&out);
    status(&out);

    printf("DEQUEUE_FRONT\n");
    printf("REMOVED %d\n", dequeue_front(&out));

    freedeque(&out);

    printf("\n===== TEST COMPLETE =====\n");

    return 0;
}