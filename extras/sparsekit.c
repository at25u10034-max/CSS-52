#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define BUFFER 4000
#define MAX_TESTS 500

/* ===== ANSI COLORS ===== */
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define CYAN    "\033[0;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

/* ===== STRUCT ===== */
typedef struct Node {
    int row;
    int col;
    int value;
    struct Node* next;
} Node;

/* ===================================================
   STUDENT MUST IMPLEMENT THESE
   =================================================== */
Node* create_sparse(int matrix[][MAX], int rows, int cols);
void display_sparse(Node* head, int rows, int cols, FILE* outfile);
Node* add_sparse(Node* A, Node* B);
Node* transpose_sparse(Node* A);
Node* multiply_sparse(Node* A, Node* B, int r1, int c1, int r2, int c2);
Node* delete_element(Node* A, int row, int col);

#include "create_sparse.c"
#include "display_sparse.c"
#include "add_sparse.c"
#include "transpose_sparse.c"
#include "delete_element.c"

Node* multiply_sparse(Node* A, Node* B, int r1, int c1, int r2, int c2) {};

/* ===================================================
   TEST FRAMEWORK CORE
   =================================================== */

typedef int (*TestFunction)();

typedef struct {
    const char* name;
    TestFunction func;
} TestCase;

TestCase tests[MAX_TESTS];
int test_count = 0;
int failed_tests = 0;

void add_test(const char* name, TestFunction func) {
    tests[test_count].name = name;
    tests[test_count].func = func;
    test_count++;
}

void run_all_tests() {
    printf(CYAN "\n===== Running Sparse Matrix Test Suite =====\n" RESET);

    for (int i = 0; i < test_count; i++) {
        printf(CYAN "\nTest %d: %s\n" RESET, i+1, tests[i].name);

        int result = tests[i].func();

        if (result)
            printf(GREEN "✔ PASS\n" RESET);
        else {
            printf(RED "✘ FAIL\n" RESET);
            failed_tests++;
        }
    }

    printf(YELLOW "\n=================================\n" RESET);
    if (failed_tests == 0)
        printf(GREEN "All %d tests passed :)\n" RESET, test_count);
    else
        printf(RED "Failed! %d out of %d tests failed.\n" RESET, failed_tests, test_count);
    printf(YELLOW "=================================\n" RESET);
}

/* ===================================================
   UTILITIES
   =================================================== */

void free_list(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

void showlist(Node *A) {
	while (A) {
		printf("{a[%d][%d] = %d} -> ", A->row, A->col, A->value);
		A=A->next;
	}
	printf("NULL\n");
}

int count_nodes(Node* head) {
    int c=0; while(head){c++; head=head->next;} return c;
}

int compare_list(Node* A, Node* B) {
    while (A && B) {
        if (A->row!=B->row || A->col!=B->col || A->value!=B->value)
            return 0;
        A=A->next; B=B->next;
    }
    return (A==NULL && B==NULL);
}

int check_display(Node *head,
                      int rows,
                      int cols,
                      const char* expected_output)
{

    
    FILE *temp = fopen("temp_display.txt", "w+");

    display_sparse(head, rows, cols, temp);

    fflush(temp);

    /* --- Read captured output --- */
    char buffer[BUFFER] = {0};
    rewind(temp);
    fread(buffer, 1, BUFFER-1, temp);
    fclose(temp);

    /* --- ALSO print to stdout (as requested) --- */
    printf("Matrix Output:\n%s", buffer);

    /* --- Compare --- */
    int pass = (strcmp(buffer, expected_output) == 0);

    if (!pass) {
        printf("Expected:\n%s\n", expected_output);
    }

    return pass;
}


/* ===================================================
   CREATION TESTS (8)
   =================================================== */

int test_create_single_zero(){int m[MAX][MAX]={{0}};Node*A=create_sparse(m,1,1);int r=(A==NULL);free_list(A);return r;}
int test_create_single_nonzero(){int m[MAX][MAX]={{9}};Node*A=create_sparse(m,1,1);int r=(count_nodes(A)==1);free_list(A);return r;}
int test_create_row(){int m[MAX][MAX]={{0,5,0,7}};Node*A=create_sparse(m,1,4);int r=(count_nodes(A)==2);free_list(A);return r;}
int test_create_col(){int m[MAX][MAX]={{1},{0},{3},{0}};Node*A=create_sparse(m,4,1);int r=(count_nodes(A)==2);free_list(A);return r;}
int test_create_dense(){int m[MAX][MAX]={{1,2},{3,4}};Node*A=create_sparse(m,2,2);int r=(count_nodes(A)==4);free_list(A);return r;}
int test_create_sparse_large(){int m[MAX][MAX]={{0,0,0,8,0},{0,0,0,0,0},{5,0,0,0,0},{0,0,3,0,0},{0,0,0,0,0}};Node*A=create_sparse(m,5,5);int r=(count_nodes(A)==3);free_list(A);return r;}
int test_create_negative(){int m[MAX][MAX]={{-1,0},{0,-2}};Node*A=create_sparse(m,2,2);int r=(count_nodes(A)==2);free_list(A);return r;}
int test_create_mixed(){int m[MAX][MAX]={{0,4},{5,0}};Node*A=create_sparse(m,2,2);int r=(count_nodes(A)==2);free_list(A);return r;}

/* ===================================================
   DISPLAY TESTS (8)
   =================================================== */

int test_display_zero(){int m[MAX][MAX]={{0}};Node*A=create_sparse(m,1,1);int r=check_display(A,1,1,"0\n");free_list(A);return r;}
int test_display_single(){int m[MAX][MAX]={{5}};Node*A=create_sparse(m,1,1);int r=check_display(A,1,1,"5\n");free_list(A);return r;}
int test_display_row(){int m[MAX][MAX]={{0,2,0}};Node*A=create_sparse(m,1,3);int r=check_display(A,1,3,"0 2 0\n");free_list(A);return r;}
int test_display_col(){int m[MAX][MAX]={{1},{0},{3}};Node*A=create_sparse(m,3,1);int r=check_display(A,3,1,"1\n0\n3\n");free_list(A);return r;}
int test_display_dense(){int m[MAX][MAX]={{1,2},{3,4}};Node*A=create_sparse(m,2,2);int r=check_display(A,2,2,"1 2\n3 4\n");free_list(A);return r;}
int test_display_sparse_complex(){int m[MAX][MAX]={{0,0,7},{5,0,0},{0,0,0}};Node*A=create_sparse(m,3,3);int r=check_display(A,3,3,"0 0 7\n5 0 0\n0 0 0\n");free_list(A);return r;}
int test_display_negative(){int m[MAX][MAX]={{-1,0},{0,-2}};Node*A=create_sparse(m,2,2);int r=check_display(A,2,2,"-1 0\n0 -2\n");free_list(A);return r;}
int test_display_all_zero_3x3(){int m[MAX][MAX]={0};Node*A=create_sparse(m,3,3);int r=check_display(A,3,3,"0 0 0\n0 0 0\n0 0 0\n");free_list(A);return r;}

/* ===================================================
   ADDITION TESTS (8)
   =================================================== */

int test_add_zero(){int m[MAX][MAX]={0};Node*A=create_sparse(m,2,2);Node*B=create_sparse(m,2,2);Node*C=add_sparse(A,B);int r=(C==NULL);free_list(A);free_list(B);free_list(C);return r;}
int test_add_non_overlap(){int m1[MAX][MAX]={{1,0},{0,0}};int m2[MAX][MAX]={{0,0},{0,2}};int exp[MAX][MAX]={{1,0},{0,2}};Node*A=create_sparse(m1,2,2);Node*B=create_sparse(m2,2,2);Node*C=add_sparse(A,B);Node*E=create_sparse(exp,2,2);int r=compare_list(C,E);free_list(A);free_list(B);free_list(C);free_list(E);return r;}
int test_add_overlap(){int m1[MAX][MAX]={{2}};int m2[MAX][MAX]={{3}};int exp[MAX][MAX]={{5}};Node*A=create_sparse(m1,1,1);Node*B=create_sparse(m2,1,1);Node*C=add_sparse(A,B);Node*E=create_sparse(exp,1,1);int r=compare_list(C,E);free_list(A);free_list(B);free_list(C);free_list(E);return r;}
int test_add_cancel(){int m1[MAX][MAX]={{2}};int m2[MAX][MAX]={{-2}};Node*A=create_sparse(m1,1,1);Node*B=create_sparse(m2,1,1);Node*C=add_sparse(A,B);int r=(C==NULL);free_list(A);free_list(B);free_list(C);return r;}
int test_add_dense(){int m1[MAX][MAX]={{1,2},{3,4}};int m2[MAX][MAX]={{1,1},{1,1}};int exp[MAX][MAX]={{2,3},{4,5}};Node*A=create_sparse(m1,2,2);Node*B=create_sparse(m2,2,2);Node*C=add_sparse(A,B);Node*E=create_sparse(exp,2,2);int r=compare_list(C,E);free_list(A);free_list(B);free_list(C);free_list(E);return r;}
int test_add_negative(){int m1[MAX][MAX]={{-1,0}};int m2[MAX][MAX]={{0,2}};int exp[MAX][MAX]={{-1,2}};Node*A=create_sparse(m1,1,2);Node*B=create_sparse(m2,1,2);Node*C=add_sparse(A,B);Node*E=create_sparse(exp,1,2);int r=compare_list(C,E);free_list(A);free_list(B);free_list(C);free_list(E);return r;}
int test_add_rectangular(){int m1[MAX][MAX]={{1,0,2}};int m2[MAX][MAX]={{0,3,0}};int exp[MAX][MAX]={{1,3,2}};Node*A=create_sparse(m1,1,3);Node*B=create_sparse(m2,1,3);Node*C=add_sparse(A,B);Node*E=create_sparse(exp,1,3);int r=compare_list(C,E);free_list(A);free_list(B);free_list(C);free_list(E);return r;}
int test_add_sparse_large(){int m1[MAX][MAX]={{0,0,5},{0,0,0},{0,3,0}};int m2[MAX][MAX]={{0,0,1},{0,0,0},{0,2,0}};int exp[MAX][MAX]={{0,0,6},{0,0,0},{0,5,0}};Node*A=create_sparse(m1,3,3);Node*B=create_sparse(m2,3,3);Node*C=add_sparse(A,B);Node*E=create_sparse(exp,3,3);int r=compare_list(C,E);free_list(A);free_list(B);free_list(C);free_list(E);return r;}

/* ===================================================
   TRANSPOSE (8)
   =================================================== */

int test_transpose_single(){int m[MAX][MAX]={{5}};Node*A=create_sparse(m,1,1);Node*T=transpose_sparse(A);int r=compare_list(A,T);free_list(A);free_list(T);return r;}
int test_transpose_basic(){int m[MAX][MAX]={{0,5},{3,0}};int exp[MAX][MAX]={{0,3},{5,0}};Node*A=create_sparse(m,2,2);Node*T=transpose_sparse(A);Node*E=create_sparse(exp,2,2);int r=compare_list(T,E);free_list(A);free_list(T);free_list(E);return r;}
int test_transpose_row(){int m[MAX][MAX]={{1,2,3}};int exp[MAX][MAX]={{1},{2},{3}};Node*A=create_sparse(m,1,3);Node*T=transpose_sparse(A);Node*E=create_sparse(exp,3,1);int r=compare_list(T,E);free_list(A);free_list(T);free_list(E);return r;}
int test_transpose_col(){int m[MAX][MAX]={{1},{2},{3}};int exp[MAX][MAX]={{1,2,3}};Node*A=create_sparse(m,3,1);Node*T=transpose_sparse(A);Node*E=create_sparse(exp,1,3);int r=compare_list(T,E);free_list(A);free_list(T);free_list(E);return r;}
int test_transpose_zero(){int m[MAX][MAX]={0};Node*A=create_sparse(m,2,2);Node*T=transpose_sparse(A);int r=(T==NULL);free_list(A);free_list(T);return r;}
int test_transpose_dense(){int m[MAX][MAX]={{1,2},{3,4}};int exp[MAX][MAX]={{1,3},{2,4}};Node*A=create_sparse(m,2,2);Node*T=transpose_sparse(A);Node*E=create_sparse(exp,2,2);int r=compare_list(T,E);free_list(A);free_list(T);free_list(E);return r;}
int test_transpose_negative(){int m[MAX][MAX]={{-1,0},{0,-2}};int exp[MAX][MAX]={{-1,0},{0,-2}};Node*A=create_sparse(m,2,2);Node*T=transpose_sparse(A);Node*E=create_sparse(exp,2,2);int r=compare_list(T,E);free_list(A);free_list(T);free_list(E);return r;}
int test_transpose_sparse_large(){int m[MAX][MAX]={{0,0,5},{0,0,0},{3,0,0}};int exp[MAX][MAX]={{0,0,3},{0,0,0},{5,0,0}};Node*A=create_sparse(m,3,3);Node*T=transpose_sparse(A);Node*E=create_sparse(exp,3,3);int r=compare_list(T,E);free_list(A);free_list(T);free_list(E);return r;}

/* ===================================================
   DELETE (8)
   =================================================== */

int test_delete_head(){int m[MAX][MAX]={{1,2}};int exp[MAX][MAX]={{0,2}};Node*A=create_sparse(m,1,2);Node*D=delete_element(A,0,0);Node*E=create_sparse(exp,1,2);int r=compare_list(D,E);free_list(D);free_list(E);return r;}
int test_delete_middle(){int m[MAX][MAX]={{1,2,3}};int exp[MAX][MAX]={{1,0,3}};Node*A=create_sparse(m,1,3);Node*D=delete_element(A,0,1);Node*E=create_sparse(exp,1,3);int r=compare_list(D,E);free_list(D);free_list(E);return r;}
int test_delete_tail(){int m[MAX][MAX]={{1,2,3}};int exp[MAX][MAX]={{1,2,0}};Node*A=create_sparse(m,1,3);Node*D=delete_element(A,0,2);Node*E=create_sparse(exp,1,3);int r=compare_list(D,E);free_list(D);free_list(E);return r;}
int test_delete_nonexistent(){int m[MAX][MAX]={{1,0}};Node*A=create_sparse(m,1,2);Node*D=delete_element(A,0,1);int r=compare_list(A,D);free_list(D);return r;}
int test_delete_single(){int m[MAX][MAX]={{5}};Node*A=create_sparse(m,1,1);Node*D=delete_element(A,0,0);int r=(D==NULL);free_list(D);return r;}
int test_delete_zero_matrix(){int m[MAX][MAX]={0};Node*A=create_sparse(m,2,2);Node*D=delete_element(A,0,0);int r=(D==NULL);free_list(D);return r;}
int test_delete_negative(){int m[MAX][MAX]={{-1,2}};int exp[MAX][MAX]={{0,2}};Node*A=create_sparse(m,1,2);Node*D=delete_element(A,0,0);Node*E=create_sparse(exp,1,2);int r=compare_list(D,E);free_list(D);free_list(E);return r;}
int test_delete_sparse_large(){int m[MAX][MAX]={{0,0,5},{0,0,0},{3,0,0}};int exp[MAX][MAX]={{0,0,5},{0,0,0},{0,0,0}};Node*A=create_sparse(m,3,3);Node*D=delete_element(A,2,0);Node*E=create_sparse(exp,3,3);int r=compare_list(D,E);free_list(D);free_list(E);return r;}

/* ===================================================
   MAIN REGISTRATION
   =================================================== */

int main() {

    /* Creation */
    add_test("Create - Single Zero", test_create_single_zero);
    add_test("Create - Single NonZero", test_create_single_nonzero);
    add_test("Create - Row", test_create_row);
    add_test("Create - Column", test_create_col);
    add_test("Create - Dense", test_create_dense);
    add_test("Create - Sparse Large", test_create_sparse_large);
    add_test("Create - Negative", test_create_negative);
    add_test("Create - Mixed", test_create_mixed);

    /* Display */
    add_test("Display - Zero", test_display_zero);
    add_test("Display - Single", test_display_single);
    add_test("Display - Row", test_display_row);
    add_test("Display - Column", test_display_col);
    add_test("Display - Dense", test_display_dense);
    add_test("Display - Sparse Complex", test_display_sparse_complex);
    add_test("Display - Negative", test_display_negative);
    add_test("Display - All Zero 3x3", test_display_all_zero_3x3);

    /* Addition */
    add_test("Add - Zero", test_add_zero);
    add_test("Add - Non Overlap", test_add_non_overlap);
    add_test("Add - Overlap", test_add_overlap);
    add_test("Add - Cancel", test_add_cancel);
    add_test("Add - Dense", test_add_dense);
    add_test("Add - Negative", test_add_negative);
    add_test("Add - Rectangular", test_add_rectangular);
    add_test("Add - Sparse Large", test_add_sparse_large);

    // /* Transpose */
    // add_test("Transpose - Single", test_transpose_single);
    // add_test("Transpose - Basic", test_transpose_basic);
    // add_test("Transpose - Row", test_transpose_row);
    // add_test("Transpose - Column", test_transpose_col);
    // add_test("Transpose - Zero", test_transpose_zero);
    // add_test("Transpose - Dense", test_transpose_dense);
    // add_test("Transpose - Negative", test_transpose_negative);
    // add_test("Transpose - Sparse Large", test_transpose_sparse_large);

    /* Delete */
    add_test("Delete - Head", test_delete_head);
    add_test("Delete - Middle", test_delete_middle);
    add_test("Delete - Tail", test_delete_tail);
    add_test("Delete - Nonexistent", test_delete_nonexistent);
    add_test("Delete - Single", test_delete_single);
    add_test("Delete - Zero Matrix", test_delete_zero_matrix);
    add_test("Delete - Negative", test_delete_negative);
    add_test("Delete - Sparse Large", test_delete_sparse_large);

    run_all_tests();
    return 0;
}
