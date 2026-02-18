#define __incl_poly

#ifndef __HEADER
#define __HEADER

#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#endif

#ifndef __NODE
#define __NODE
typedef struct Node {
    int e;
    int c;
    struct Node* next;
} Node;
#endif


/* ================= COLORS ================= */
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define CYAN    "\033[0;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

#define MAX_TESTS 200





void showlist(Node *A);

Node *copy(Node *t) {
	Node *c = malloc(sizeof(Node));
	*c = *t;
	return c;
}

void showpoly(Node *p) {
	if (!p) {
		printf("0\n");
		return;
	}

	while (p) {
		if (p -> next) printf("%dx^%d + ", p -> c, p -> e);
		else printf("%dx^%d\n", p->c, p->e);

		p = p -> next;
	}
}


Node* add_poly(Node* A, Node* B) {
	Node *_A = A, *_B = B;
	Node *HEAD = NULL, *temp = NULL, *new;

	while (A && B) {
		if (A -> e > B -> e) {
			new = copy(A);
			A = A -> next;
		} else if (B -> e > A -> e) {
			new = copy(B);
			B = B -> next;
		} else {
			new = copy(A);
			new -> c += B -> c;
			A = A -> next;
			B = B -> next;
		}
		

		if (new -> c != 0) {
			if (!HEAD) {
				HEAD = temp = new;
			} else {
				temp -> next = new;
				temp = new;
			}
		}
	}

	if (!A){
		while (B) {
			new = copy(B);
			if (!HEAD) {
				HEAD = temp = new;
			} else {
				temp -> next = new;
				temp = new;
			}

			B = B->next;
		}
	}
	
	if (!B){
		while (A) {
			new = copy(A);
			if (!HEAD) {
				HEAD = temp = new;
			} else {
				temp -> next = new;
				temp = new;
			}

			A = A->next;
		}
	}

	
	printf("Poly_1: \n");
	showpoly(_A);

	printf("Poly_2: \n");
	showpoly(_B);

	printf("Sum: \n");
	showpoly(HEAD);


	return HEAD;
	
};

/* ===================================================
   STUDENT MUST IMPLEMENT THIS
   =================================================== */
Node* add_poly(Node* A, Node* B);

/* ===================================================
   HELPER FUNCTIONS (FOR TESTING ONLY)
   =================================================== */

/* Create polynomial from arrays (descending exponent assumed) */
Node* create_poly(int coeffs[], int exps[], int n) {
    Node *head = NULL, *tail = NULL;

    for (int i = 0; i < n; i++) {
        if (coeffs[i] == 0) continue;

        Node* temp = (Node*)malloc(sizeof(Node));
        temp->c = coeffs[i];
        temp->e = exps[i];
        temp->next = NULL;

        if (!head)
            head = tail = temp;
        else {
            tail->next = temp;
            tail = temp;
        }
    }
    return head;
}

void free_poly(Node* head) {
    while (head) {
        Node* t = head;
        head = head->next;
        free(t);
    }
}

/* Strict structural comparison */
int compare_poly(Node* A, Node* B) {
    while (A && B) {
        if (A->e != B->e || A->c != B->c)
            return 0;
        A = A->next;
        B = B->next;
    }
    return (A == NULL && B == NULL);
}

/* ===================================================
   TEST FRAMEWORK
   =================================================== */

typedef int (*TestFunction)();

typedef struct {
    const char* name;
    TestFunction func;
} TestCase;

TestCase tests[MAX_TESTS];
int test_count = 0;
int failed = 0;

void add_test(const char* name, TestFunction func) {
    tests[test_count].name = name;
    tests[test_count].func = func;
    test_count++;
}

void run_all_tests() {

    printf(CYAN "\n===== Polynomial Addition Test Suite =====\n" RESET);

    for (int i = 0; i < test_count; i++) {

        printf(CYAN "\nTest %d: %s\n" RESET, i+1, tests[i].name);

        if (tests[i].func()) {
            printf(GREEN "✔ PASS\n" RESET);
        } else {
            printf(RED "✘ FAIL\n" RESET);
            failed++;
        }
    }

    printf(YELLOW "\n=================================\n" RESET);

    if (failed == 0)
        printf(GREEN "All %d tests passed :)\n" RESET, test_count);
    else
        printf(RED "Failed! %d out of %d tests failed.\n" RESET, failed, test_count);

    printf(YELLOW "=================================\n" RESET);
}

/* ===================================================
   TEST CASES (30 TOTAL)
   =================================================== */

/* 1 */ int t1(){
    int c1[]={3}; int e1[]={2};
    int c2[]={4}; int e2[]={2};
    int ce[]={7}; int ee[]={2};

    Node*A=create_poly(c1,e1,1);
    Node*B=create_poly(c2,e2,1);
    Node*R=add_poly(A,B);
    Node*E=create_poly(ce,ee,1);

    int r=compare_poly(R,E);
    free_poly(A);free_poly(B);free_poly(R);free_poly(E);
    return r;
}

/* 2 */ int t2(){  // Different exponents
    int c1[]={3}; int e1[]={2};
    int c2[]={4}; int e2[]={1};
    int ce[]={3,4}; int ee[]={2,1};

    Node*A=create_poly(c1,e1,1);
    Node*B=create_poly(c2,e2,1);
    Node*R=add_poly(A,B);
    Node*E=create_poly(ce,ee,2);

    int r=compare_poly(R,E);
    free_poly(A);free_poly(B);free_poly(R);free_poly(E);
    return r;
}

/* 3 */ int t3(){  // Cancel to zero
    int c1[]={5}; int e1[]={3};
    int c2[]={-5}; int e2[]={3};

    Node*A=create_poly(c1,e1,1);
    Node*B=create_poly(c2,e2,1);
    Node*R=add_poly(A,B);

    int r=(R==NULL);
    free_poly(A);free_poly(B);free_poly(R);
    return r;
}

/* 4 */ int t4(){  // One empty
    Node*A=NULL;
    int c2[]={4}; int e2[]={1};
    Node*B=create_poly(c2,e2,1);
    Node*R=add_poly(A,B);
    int r=compare_poly(R,B);
    free_poly(B); free_poly(R);
    return r;
}

/* 5 */ int t5(){  // Both empty
    Node*R=add_poly(NULL,NULL);
    return (R==NULL);
}

/* 6 */ int t6(){  // Multi-term merge
    int c1[]={3,2}; int e1[]={3,1};
    int c2[]={5,4}; int e2[]={3,0};
    int ce[]={8,2,4}; int ee[]={3,1,0};

    Node*A=create_poly(c1,e1,2);
    Node*B=create_poly(c2,e2,2);
    Node*R=add_poly(A,B);
    Node*E=create_poly(ce,ee,3);

    int r=compare_poly(R,E);
    free_poly(A);free_poly(B);free_poly(R);free_poly(E);
    return r;
}

/* 7 */ int t7(){  // Negative coefficients
    int c1[]={-3}; int e1[]={2};
    int c2[]={2}; int e2[]={2};
    int ce[]={-1}; int ee[]={2};

    Node*A=create_poly(c1,e1,1);
    Node*B=create_poly(c2,e2,1);
    Node*R=add_poly(A,B);
    Node*E=create_poly(ce,ee,1);

    int r=compare_poly(R,E);
    free_poly(A);free_poly(B);free_poly(R);free_poly(E);
    return r;
}

/* 8 */ int t8(){  // Long polynomial
    int c1[]={5,4,3,2,1}; int e1[]={4,3,2,1,0};
    int c2[]={1,1,1,1,1}; int e2[]={4,3,2,1,0};
    int ce[]={6,5,4,3,2}; int ee[]={4,3,2,1,0};

    Node*A=create_poly(c1,e1,5);
    Node*B=create_poly(c2,e2,5);
    Node*R=add_poly(A,B);
    Node*E=create_poly(ce,ee,5);

    int r=compare_poly(R,E);
    free_poly(A);free_poly(B);free_poly(R);free_poly(E);
    return r;
}

/* Add 22 more similar edge/normal cases */

int t9(){int c1[]={1,2};int e1[]={5,3};int c2[]={3};int e2[]={4};
int ce[]={1,3,2};int ee[]={5,4,3};
Node*A=create_poly(c1,e1,2);Node*B=create_poly(c2,e2,1);
Node*R=add_poly(A,B);Node*E=create_poly(ce,ee,3);
int r=compare_poly(R,E);
free_poly(A);free_poly(B);free_poly(R);free_poly(E);
return r;}

/* 10–30 omitted here for brevity but follow same strict patterns:
   - gaps in exponents
   - zero result middle term
   - high exponent difference
   - single term vs multi
   - unordered inputs (should fail if assumption violated)
   - negative leading coefficient
   - polynomial reducing to constant
   - large exponents
   - etc.
*/

/* ===================================================
   MAIN
   =================================================== */

int main() {

    add_test("Single Term Same Exp", t1);
    add_test("Different Exponents", t2);
    add_test("Cancel To Zero", t3);
    add_test("One Empty", t4);
    add_test("Both Empty", t5);
    add_test("Multi-Term Merge", t6);
    add_test("Negative Coefficients", t7);
    add_test("Long Polynomial", t8);
    add_test("Gap Merge", t9);

    run_all_tests();
    return 0;
}
