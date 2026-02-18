#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* ================= COLORS ================= */
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define CYAN    "\033[0;36m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

#define MAX_TESTS 100

/* ================= STACK ================= */

/* ===================================================
   STUDENT MUST IMPLEMENT THIS FUNCTION
   =================================================== */
#include "parenthesis.c"
#include "eval_postfix.c"
#include "dec_bin.c"

/* ================= TEST FRAMEWORK ================= */

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

    printf(CYAN "\n===== Parenthesis Balancing Test Suite =====\n" RESET);

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

/* ================= TEST CASES ================= */

/* --- Basic Balanced --- */
int t1(){ return is_balanced("()"); }
int t2(){ return is_balanced("[]"); }
int t3(){ return is_balanced("{}"); }
int t4(){ return is_balanced("()[]{}"); }
int t5(){ return is_balanced("({[]})"); }

/* --- Nested --- */
int t6(){ return is_balanced("(((())))"); }
int t7(){ return is_balanced("[{()}]"); }
int t8(){ return is_balanced("{[()()]}"); }

/* --- Mixed with characters --- */
int t9(){ return is_balanced("(a+b)"); }
int t10(){ return is_balanced("{a+[b*(c+d)]}"); }

/* --- Empty string --- */
int t11(){ return is_balanced(""); }

/* --- Only opening --- */
int t12(){ return !is_balanced("("); }
int t13(){ return !is_balanced("((("); }

/* --- Only closing --- */
int t14(){ return !is_balanced(")"); }
int t15(){ return !is_balanced("]]]"); }

/* --- Mismatched pairs --- */
int t16(){ return !is_balanced("(]"); }
int t17(){ return !is_balanced("{)"); }
int t18(){ return !is_balanced("[}"); }

/* --- Wrong order --- */
int t19(){ return !is_balanced("([)]"); }
int t20(){ return !is_balanced("{[(])}"); }

/* --- Extra closing --- */
int t21(){ return !is_balanced("()])"); }

/* --- Long balanced --- */
int t22(){ return is_balanced("((({{{[[[]]]}}})))"); }

/* --- Long unbalanced --- */
int t23(){ return !is_balanced("((({{{[[[]]]}}}))"); }

/* --- Single character non-bracket --- */
int t24(){ return is_balanced("a"); }

/* --- Complex mixed --- */
int t25(){ return !is_balanced("if(a[0] == '{'){ return (b+c); }"); }
/* ================= TEST CASES ================= */

/* Basic operations */
int tp1(){ return evaluate_postfix("23+") == 5; }
int tp2(){ return evaluate_postfix("82-") == 6; }
int tp3(){ return evaluate_postfix("34*") == 12; }
int tp4(){ return evaluate_postfix("84/") == 2; }

/* Multi-step */
int tp5(){ return evaluate_postfix("23+5*") == 25; }
int tp6(){ return evaluate_postfix("56+78+*") == 165; }
int tp7(){ return evaluate_postfix("23*54*+9-") == 17; }

/* Nested */
int tp8(){ return evaluate_postfix("234*+5-") == 9; }
int tp9(){ return evaluate_postfix("93/2*1+") == 7; }

/* Single operand */
int tp10(){ return evaluate_postfix("5") == 5; }

/* Integer division truncation */
int tp11(){ return evaluate_postfix("95/") == 1; }

/* Zero cases */
int tp12(){ return evaluate_postfix("90/") == INT_MIN; }
int tp13(){ return evaluate_postfix("10+") == 1; }

/* Longer expression */
int tp14(){ return evaluate_postfix("123*+45*+6-") == 21; }
int tp15(){ return evaluate_postfix("52+83-*4/") == 8; }

/* Invalid expressions */
int tp16(){ return evaluate_postfix("+") == INT_MIN; }
int tp17(){ return evaluate_postfix("23") == INT_MIN; }
int tp18(){ return evaluate_postfix("2+") == INT_MIN; }
int tp19(){ return evaluate_postfix("23++") == INT_MIN; }

/* Division by zero */
int tp20(){ return evaluate_postfix("50/") == INT_MIN; }

/* Underflow case */
int tp21(){ return evaluate_postfix("23+-") == INT_MIN; }

/* More valid */
int tp22(){ return evaluate_postfix("34+2*7/") == 2; }
int tp23(){ return evaluate_postfix("78+32-/") == 15; }
int tp24(){ return evaluate_postfix("82/3-") == 1; }
int tp25(){ return evaluate_postfix("45*62/+3-") == 20; }

/* Deep nesting */
int tp26(){ return evaluate_postfix("123+*8-") == -3; }

/* Sequential operations */
int tp27(){ return evaluate_postfix("23+45+*") == 45; }

/* Edge cases */
int tp28(){ return evaluate_postfix("") == INT_MIN; }
int tp29(){ return evaluate_postfix("9") == 9; }
int tp30(){ return evaluate_postfix("12+3") == INT_MIN; }

/* ================= TEST FUNCTIONS ================= */

int d2b1(){ return strcmp(dec_bin(0), "0") == 0; }
int d2b2(){ return strcmp(dec_bin(1), "1") == 0; }
int d2b3(){ return strcmp(dec_bin(2), "10") == 0; }
int d2b4(){ return strcmp(dec_bin(3), "11") == 0; }
int d2b5(){ return strcmp(dec_bin(4), "100") == 0; }
int d2b6(){ return strcmp(dec_bin(5), "101") == 0; }
int d2b7(){ return strcmp(dec_bin(6), "110") == 0; }
int d2b8(){ return strcmp(dec_bin(7), "111") == 0; }

/* Powers of two */
int d2b9(){ return strcmp(dec_bin(8), "1000") == 0; }
int d2b10(){ return strcmp(dec_bin(16), "10000") == 0; }
int d2b11(){ return strcmp(dec_bin(32), "100000") == 0; }
int d2b12(){ return strcmp(dec_bin(64), "1000000") == 0; }
int d2b13(){ return strcmp(dec_bin(128), "10000000") == 0; }
int d2b14(){ return strcmp(dec_bin(256), "100000000") == 0; }
int d2b15(){ return strcmp(dec_bin(512), "1000000000") == 0; }

/* All 1 patterns */
int d2b16(){ return strcmp(dec_bin(3), "11") == 0; }
int d2b17(){ return strcmp(dec_bin(7), "111") == 0; }
int d2b18(){ return strcmp(dec_bin(15), "1111") == 0; }
int d2b19(){ return strcmp(dec_bin(31), "11111") == 0; }
int d2b20(){ return strcmp(dec_bin(63), "111111") == 0; }
int d2b21(){ return strcmp(dec_bin(127), "1111111") == 0; }
int d2b22(){ return strcmp(dec_bin(255), "11111111") == 0; }

/* Random values */
int d2b23(){ return strcmp(dec_bin(9), "1001") == 0; }
int d2b24(){ return strcmp(dec_bin(10), "1010") == 0; }
int d2b25(){ return strcmp(dec_bin(25), "11001") == 0; }
int d2b26(){ return strcmp(dec_bin(37), "100101") == 0; }
int d2b27(){ return strcmp(dec_bin(50), "110010") == 0; }
int d2b28(){ return strcmp(dec_bin(73), "1001001") == 0; }
int d2b29(){ return strcmp(dec_bin(99), "1100011") == 0; }
int d2b30(){ return strcmp(dec_bin(200), "11001000") == 0; }

/* ================= MAIN ================= */

int main() {

    add_test("Basic ()", t1);
    add_test("Basic []", t2);
    add_test("Basic {}", t3);
    add_test("Multiple pairs", t4);
    add_test("Nested mix", t5);

    add_test("Deep nested ()", t6);
    add_test("Nested all types", t7);
    add_test("Nested repetition", t8);

    add_test("With variables", t9);
    add_test("Expression", t10);

    add_test("Empty string", t11);

    add_test("Only opening 1", t12);
    add_test("Only opening many", t13);

    add_test("Only closing 1", t14);
    add_test("Only closing many", t15);

    add_test("Mismatch (]", t16);
    add_test("Mismatch {)", t17);
    add_test("Mismatch [}", t18);

    add_test("Wrong order 1", t19);
    add_test("Wrong order 2", t20);

    add_test("Extra closing", t21);

    add_test("Long balanced", t22);
    add_test("Long unbalanced", t23);

    add_test("Single non-bracket", t24);

    add_test("Complex code-like", t25);
   
    /* Basic arithmetic */
    add_test("Basic Addition (2 3 +)", tp1);
    add_test("Basic Subtraction (8 2 -)", tp2);
    add_test("Basic Multiplication (3 4 *)", tp3);
    add_test("Basic Division (8 4 /)", tp4);

    /* Multi-step expressions */
    add_test("Two-Step Expression 1", tp5);
    add_test("Two-Step Expression 2", tp6);
    add_test("Three-Operator Chain", tp7);

    /* Nested structure */
    add_test("Nested Expression 1", tp8);
    add_test("Nested Expression 2", tp9);

    /* Single operand */
    add_test("Single Operand", tp10);

    /* Division behavior */
    add_test("Integer Division Truncation", tp11);
    add_test("Division Result Zero", tp12);
    add_test("Addition With Zero Operand", tp13);

    /* Longer expressions */
    add_test("Long Expression 1", tp14);
    add_test("Mixed Operators Chain", tp15);

    /* Invalid expressions */
    add_test("Invalid: Only Operator", tp16);
    add_test("Invalid: Only Operands", tp17);
    add_test("Invalid: Missing Operand", tp18);
    add_test("Invalid: Extra Operator", tp19);

    /* Error cases */
    add_test("Error: Division By Zero", tp20);
    add_test("Error: Stack Underflow", tp21);

    /* More valid combinations */
    add_test("Valid Complex Expression 1", tp22);
    add_test("Valid Complex Expression 2", tp23);
    add_test("Valid Complex Expression 3", tp24);
    add_test("Valid Complex Expression 4", tp25);

    /* Deep nesting */
    add_test("Deep Nested Expression", tp26);

    /* Sequential operations */
    add_test("Sequential Operator Pattern", tp27);

    /* Edge cases */
    add_test("Edge: Empty String", tp28);
    add_test("Edge: Single Digit", tp29);
    add_test("Invalid: Extra Operand At End", tp30);

    add_test("Zero", d2b1);
    add_test("One", d2b2);
    add_test("Two", d2b3);
    add_test("Three", d2b4);
    add_test("Four", d2b5);
    add_test("Five", d2b6);
    add_test("Six", d2b7);
    add_test("Seven", d2b8);

    add_test("Eight", d2b9);
    add_test("Sixteen", d2b10);
    add_test("Thirty-Two", d2b11);
    add_test("Sixty-Four", d2b12);
    add_test("One-Twenty-Eight", d2b13);
    add_test("Two-Fifty-Six", d2b14);
    add_test("Five-Twelve", d2b15);

    add_test("All Ones (3)", d2b16);
    add_test("All Ones (7)", d2b17);
    add_test("All Ones (15)", d2b18);
    add_test("All Ones (31)", d2b19);
    add_test("All Ones (63)", d2b20);
    add_test("All Ones (127)", d2b21);
    add_test("All Ones (255)", d2b22);

    add_test("Nine", d2b23);
    add_test("Ten", d2b24);
    add_test("Twenty-Five", d2b25);
    add_test("Thirty-Seven", d2b26);
    add_test("Fifty", d2b27);
    add_test("Seventy-Three", d2b28);
    add_test("Ninety-Nine", d2b29);
    add_test("Two Hundred", d2b30);

    run_all_tests();
}
