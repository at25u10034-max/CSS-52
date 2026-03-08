#include <stdio.h>
#include "sll.h"

void report(const char *op, int code)
{
    printf("%s -> %s\n", op, ERRORS[code]);
}

void step_show(List *l)
{
    printf("Current list:\n");
    show(l);
}

/* ---------- CREATE ---------- */

void test_create()
{
    printf("\n===== CREATE TEST =====\n");

    List l = create(5);

    step_show(&l);

    printf("Empty: %d\n", isEmpty(&l));
    printf("Length: %d\n", len(&l));

    freelist(&l);
}

/* ---------- EMPTY LIST BREAK ---------- */

void test_empty_break()
{
    printf("\n===== EMPTY LIST TEST =====\n");

    List l = create(5);

    step_show(&l);

    int r;

    r = deleteStart(&l);
    report("deleteStart", r);
    step_show(&l);

    r = deleteEnd(&l);
    report("deleteEnd", r);
    step_show(&l);

    r = delete(&l,0);
    report("delete(0)", r);
    step_show(&l);

    freelist(&l);
}

/* ---------- INSERT BOUNDARIES ---------- */

void test_insert_boundaries()
{
    printf("\n===== INSERT BOUNDARY TEST =====\n");

    List l = create(5);

    int r;

    r = insertStart(&l,10);
    report("insertStart 10", r);
    step_show(&l);

    r = insertEnd(&l,20);
    report("insertEnd 20", r);
    step_show(&l);

    r = insert(&l,1,15);
    report("insert pos1 15", r);
    step_show(&l);

    freelist(&l);
}

/* ---------- INVALID INDEX ---------- */

void test_invalid_index()
{
    printf("\n===== INVALID INDEX TEST =====\n");

    List l = create(5);

    int r;

    r = insertStart(&l,5);
    report("insertStart 5", r);
    step_show(&l);

    r = insert(&l,100,50);
    report("insert pos100 50", r);
    step_show(&l);

    r = delete(&l,50);
    report("delete pos50", r);
    step_show(&l);

    freelist(&l);
}

/* ---------- FULL LIST ---------- */

void test_full()
{
    printf("\n===== FULL LIST TEST =====\n");

    List l = create(3);
    show(&l);

    int r;

    printf("Here\n");
    r = insertEnd(&l,1);
    report("insertEnd 1", r);
    step_show(&l);

    r = insertEnd(&l,2);
    report("insertEnd 2", r);
    step_show(&l);

    r = insertEnd(&l,3);
    report("insertEnd 3", r);
    step_show(&l);

    printf("isFull: %d\n", isFull(&l));

    r = insertEnd(&l,4);
    report("insertEnd 4", r);
    step_show(&l);

    freelist(&l);
}

/* ---------- DELETE BOUNDARIES ---------- */

void test_delete_boundaries()
{
    printf("\n===== DELETE BOUNDARY TEST =====\n");

    List l = create(5);

    int r;

    insertEnd(&l,10);
    insertEnd(&l,20);
    insertEnd(&l,30);

    step_show(&l);

    r = deleteStart(&l);
    report("deleteStart", r);
    step_show(&l);

    r = deleteEnd(&l);
    report("deleteEnd", r);
    step_show(&l);

    freelist(&l);
}

/* ---------- MIXED OPERATIONS ---------- */

void test_mixed()
{
    printf("\n===== MIXED OPERATIONS =====\n");

    List l = create(10);

    int r;

    r = insertStart(&l,1);
    report("insertStart 1", r);
    step_show(&l);

    r = insertEnd(&l,2);
    report("insertEnd 2", r);
    step_show(&l);

    r = insertEnd(&l,3);
    report("insertEnd 3", r);
    step_show(&l);

    r = insert(&l,1,99);
    report("insert pos1 99", r);
    step_show(&l);

    r = delete(&l,2);
    report("delete pos2", r);
    step_show(&l);

    r = insertStart(&l,-1);
    report("insertStart -1", r);
    step_show(&l);

    freelist(&l);
}

/* ---------- STRESS ---------- */

void test_stress()
{
    printf("\n===== STRESS TEST =====\n");

    List l = create(20);

    int r;

    for(int i=0;i<10;i++)
    {
        char op[50];
        sprintf(op,"insertEnd %d", i);

        r = insertEnd(&l,i);
        report(op, r);
        step_show(&l);
    }

    for(int i=0;i<5;i++)
    {
        r = deleteStart(&l);
        report("deleteStart", r);
        step_show(&l);
    }

    for(int i=0;i<5;i++)
    {
        char op[50];
        sprintf(op,"insertStart %d", i*10);

        r = insertStart(&l,i*10);
        report(op, r);
        step_show(&l);
    }

    freelist(&l);
}

void test_repeated_cycles()
{
    printf("\n===== REPEATED FILL/DELETE CYCLE TEST =====\n");

    List l = create(6);

    int cycles = 4;

    for(int c = 1; c <= cycles; c++)
    {
        printf("\n--- Cycle %d : Filling list ---\n", c);

        while(!isFull(&l))
        {
            int val = c * 100 + len(&l);
            int r = insertEnd(&l, val);

            printf("insertEnd %d -> %s\n", val, ERRORS[r]);
            show(&l);
        }

        printf("\nList should now be FULL\n");
        printf("isFull = %d\n", isFull(&l));
        printf("len = %d\n", len(&l));

        printf("\n--- Cycle %d : Deleting list ---\n", c);

        while(!isEmpty(&l))
        {
            int r = deleteStart(&l);

            printf("deleteStart -> %s\n", ERRORS[r]);
            show(&l);
        }

        printf("\nList should now be EMPTY\n");
        printf("isEmpty = %d\n", isEmpty(&l));
        printf("len = %d\n", len(&l));
    }

    freelist(&l);
}

/* ---------- MAIN ---------- */

int main()
{
    test_create();
    test_empty_break();
    test_insert_boundaries();
    test_invalid_index();
    test_full();
    test_delete_boundaries();
    test_mixed();
    test_stress();
    test_repeated_cycles();

    printf("\nAll tests completed\n");

    return 0;
}