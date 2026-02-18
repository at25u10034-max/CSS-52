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

#define MAX_TESTS 1000

/* ================= STACK ================= */

/* ===================================================
   STUDENT MUST IMPLEMENT THIS FUNCTION
   =================================================== */
#include "parenthesis.c"
#include "eval_postfix.c"
#include "eval_prefix.c"
#include "in2post.c"

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

/* ================= PARENTHESIS BALANCE ================= */

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
/* ================= EVALUATE POSTFIX ================= */

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

/* ================= CONVERTING INFIX TO POSTFIX ================= */

/* Basic single operands */
int ti1(){ return strcmp(infix_to_postfix("A"), "A") == 0; }
int ti2(){ return strcmp(infix_to_postfix("5"), "5") == 0; }

/* Basic operators */
int ti3(){ return strcmp(infix_to_postfix("A+B"), "AB+") == 0; }
int ti4(){ return strcmp(infix_to_postfix("A-B"), "AB-") == 0; }
int ti5(){ return strcmp(infix_to_postfix("A*B"), "AB*") == 0; }
int ti6(){ return strcmp(infix_to_postfix("A/B"), "AB/") == 0; }

/* Operator precedence */
int ti7(){ return strcmp(infix_to_postfix("A+B*C"), "ABC*+") == 0; }
int ti8(){ return strcmp(infix_to_postfix("A*B+C"), "AB*C+") == 0; }
int ti9(){ return strcmp(infix_to_postfix("A+B*C-D"), "ABC*+D-") == 0; }

/* Parentheses */
int ti10(){ return strcmp(infix_to_postfix("(A+B)"), "AB+") == 0; }
int ti11(){ return strcmp(infix_to_postfix("(A+B)*C"), "AB+C*") == 0; }
int ti12(){ return strcmp(infix_to_postfix("A*(B+C)"), "ABC+*") == 0; }
int ti13(){ return strcmp(infix_to_postfix("(A+B)*(C+D)"), "AB+CD+*") == 0; }

/* Nested parentheses */
int ti14(){ return strcmp(infix_to_postfix("((A+B)*C)"), "AB+C*") == 0; }
int ti15(){ return strcmp(infix_to_postfix("A+(B*(C+D))"), "ABCD+*+") == 0; }
int ti16(){ return strcmp(infix_to_postfix("((A+B)*(C-D))/E"), "AB+CD-*E/") == 0; }

/* Multiple operators */
int ti17(){ return strcmp(infix_to_postfix("A+B+C"), "AB+C+") == 0; }
int ti18(){ return strcmp(infix_to_postfix("A*B/C"), "AB*C/") == 0; }
int ti19(){ return strcmp(infix_to_postfix("A+B*C+D"), "ABC*+D+") == 0; }

/* Mixed digits and letters */
int ti20(){ return strcmp(infix_to_postfix("3+4*5"), "345*+") == 0; }
int ti21(){ return strcmp(infix_to_postfix("(1+2)*(3+4)"), "12+34+*") == 0; }

/* Complex expressions */
int ti22(){ return strcmp(infix_to_postfix("A+B*(C-D/E)"), "ABCDE/-*+") == 0; }
int ti23(){ return strcmp(infix_to_postfix("(A+B*C)-(D/E+F)"), "ABC*+DE/F+-") == 0; }
int ti24(){ return strcmp(infix_to_postfix("A*(B+C*D)-E"), "ABCD*+*E-") == 0; }

/* Edge cases */
int ti25(){ return strcmp(infix_to_postfix(""), "") == 0; }
int ti26(){ return strcmp(infix_to_postfix("(A)"), "A") == 0; }
int ti27(){ return strcmp(infix_to_postfix("((A))"), "A") == 0; }


/* ================= EVALUATE PREFIX ================= */

/* Basic operations */
int pr1(){ return evaluate_prefix("+23") == 5; }
int pr2(){ return evaluate_prefix("-82") == 6; }
int pr3(){ return evaluate_prefix("*34") == 12; }
int pr4(){ return evaluate_prefix("/84") == 2; }

/* Multi-step */
int pr5(){ return evaluate_prefix("*+235") == 25; }          // (2+3)*5
int pr6(){ return evaluate_prefix("*+56+78") == 165; }      // (5+6)*(7+8)
int pr7(){ return evaluate_prefix("-+*235*49") == -25; }

/* Nested */
int pr8(){ return evaluate_prefix("-+2*345") == 9; }
int pr9(){ return evaluate_prefix("+*/9321") == 7; }

/* Single operand */
int pr10(){ return evaluate_prefix("5") == 5; }

/* Integer division truncation */
int pr11(){ return evaluate_prefix("/95") == 1; }

/* Zero cases */
int pr12(){ return evaluate_prefix("/90") == INT_MIN; }   // division by zero
int pr13(){ return evaluate_prefix("+10") == 1; }         // 1 + 0

/* Longer expression */
int pr14(){ return evaluate_prefix("-++1*234*56") == -19; }
int pr15(){ return evaluate_prefix("/-*+52834") == 13; }

/* Invalid expressions */
int pr16(){ return evaluate_prefix("+") == INT_MIN; }
int pr17(){ return evaluate_prefix("23") == INT_MIN; }
int pr18(){ return evaluate_prefix("+2") == INT_MIN; }
int pr19(){ return evaluate_prefix("++23") == INT_MIN; }

/* Division by zero */
int pr20(){ return evaluate_prefix("/50") == INT_MIN; }

/* Underflow case */
int pr21(){ return evaluate_prefix("-+23") == INT_MIN; }

/* More valid */
int pr22(){ return evaluate_prefix("/+34*27") == 0; }
int pr23(){ return evaluate_prefix("/+78-32") == 15; }
int pr24(){ return evaluate_prefix("-/823") == 1; }
int pr25(){ return evaluate_prefix("-+/45*623") == 9; }

/* Deep nesting */
int pr26(){ return evaluate_prefix("-*1+238") == -3; }

/* Sequential operations */
int pr27(){ return evaluate_prefix("*+23+45") == 45; }

/* Edge cases */
int pr28(){ return evaluate_prefix("") == INT_MIN; }
int pr29(){ return evaluate_prefix("9") == 9; }
int pr30(){ return evaluate_prefix("+12") == 3; }
/* ================= TRICKY PREFIX TESTS ================= */

/* Order sensitivity (subtraction & division) */
int pr31(){ return evaluate_prefix("-34") == -1; }     // 3-4
int pr32(){ return evaluate_prefix("-43") == 1; }      // 4-3
int pr33(){ return evaluate_prefix("/26") == 0; }      // 2/6
int pr34(){ return evaluate_prefix("/62") == 3; }      // 6/2

/* Deep right-heavy nesting */
int pr35(){ return evaluate_prefix("+1+2+3+45") == 15; }
int pr36(){ return evaluate_prefix("*2*3*45") == 120; }

/* Alternating operators */
int pr37(){ return evaluate_prefix("-*+2345") == 15; }
int pr38(){ return evaluate_prefix("+*-2345") == 1; }

/* Zero behavior */
int pr39(){ return evaluate_prefix("*90") == 0; }
int pr40(){ return evaluate_prefix("+09") == 9; }
int pr41(){ return evaluate_prefix("-90") == 9; }
int pr42(){ return evaluate_prefix("-09") == -9; }

/* Division inside complex */
int pr43(){ return evaluate_prefix("+9/63") == 11; }
int pr44(){ return evaluate_prefix("-*8/42+13") == 12; }

/* Large nested combination */
int pr45(){ return evaluate_prefix("+*9-82/63") == 56; }
int pr46(){ return evaluate_prefix("-+7*45/62") == 24; }

/* Stack exhaustion check */
int pr47(){ return evaluate_prefix("+*+1234") == 13; }
int pr48(){ return evaluate_prefix("*+1+234") == 24; }

/* Extra operand at end (invalid) */
int pr49(){ return evaluate_prefix("+23 4") == INT_MIN; }  // if spaces not allowed
int pr50(){ return evaluate_prefix("+234") == INT_MIN; }   // leftover operand

/* Multiple operators without enough operands */
int pr51(){ return evaluate_prefix("++23") == INT_MIN; }
int pr52(){ return evaluate_prefix("*-+") == INT_MIN; }

/* All zeros */
int pr53(){ return evaluate_prefix("+00") == 0; }
int pr54(){ return evaluate_prefix("*+00-00") == 0; }

/* Deep subtract chain (tests correct operand order) */
int pr55(){ return evaluate_prefix("-1-2-34") == -2; }

/* Complex mixed */
int pr56(){ return evaluate_prefix("+*-+12345") == 5; }
int pr57(){ return evaluate_prefix("-+*123*45") == -15; }

/* Division by zero hidden deep */
int pr58(){ return evaluate_prefix("+3/40") == INT_MIN; }
int pr59(){ return evaluate_prefix("-*5/20+13") == INT_MIN; }

/* Valid but tricky operand stacking */
int pr60(){ return evaluate_prefix("*-9+234") == 16; }



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


    /* ================= INFIX TO POSTFIX TESTS ================= */
    
    add_test("Single Operand Letter", ti1);
    add_test("Single Operand Digit", ti2);
    
    add_test("Basic Addition", ti3);
    add_test("Basic Subtraction", ti4);
    add_test("Basic Multiplication", ti5);
    add_test("Basic Division", ti6);
    
    add_test("Precedence 1", ti7);
    add_test("Precedence 2", ti8);
    add_test("Precedence 3", ti9);
    
    add_test("Parentheses 1", ti10);
    add_test("Parentheses 2", ti11);
    add_test("Parentheses 3", ti12);
    add_test("Parentheses 4", ti13);
    
    add_test("Nested 1", ti14);
    add_test("Nested 2", ti15);
    add_test("Nested 3", ti16);
    
    add_test("Multiple Operators 1", ti17);
    add_test("Multiple Operators 2", ti18);
    add_test("Multiple Operators 3", ti19);
    
    add_test("Digits Expression 1", ti20);
    add_test("Digits Expression 2", ti21);
    
    add_test("Complex Expression 1", ti22);
    add_test("Complex Expression 2", ti23);
    add_test("Complex Expression 3", ti24);
    
    add_test("Edge Empty", ti25);
    add_test("Edge Single Paren", ti26);
    add_test("Edge Double Paren", ti27);


    /* ================= ADD PREFIX TESTS TO MAIN ================= */
    
    add_test("Prefix Basic Addition (+23)", pr1);
    add_test("Prefix Basic Subtraction (-82)", pr2);
    add_test("Prefix Basic Multiplication (*34)", pr3);
    add_test("Prefix Basic Division (/84)", pr4);
    
    add_test("Prefix Two-Step Expression 1 (*+235)", pr5);
    add_test("Prefix Two-Step Expression 2 (*+56+78)", pr6);
    add_test("Prefix Three-Operator Chain (-+*2354*9)", pr7);
    
    add_test("Prefix Nested Expression 1 (-+2*345)", pr8);
    add_test("Prefix Nested Expression 2 (+*/9321)", pr9);
    
    add_test("Prefix Single Operand", pr10);
    add_test("Prefix Integer Division Truncation (/95)", pr11);
    add_test("Prefix Division Result Zero (/90)", pr12);
    add_test("Prefix Addition With Zero Operand (+10)", pr13);
    
    add_test("Prefix Long Expression 1 (-++1*234*56)", pr14);
    add_test("Prefix Mixed Operators Chain (/-*+52834)", pr15);
    
    add_test("Prefix Invalid: Only Operator (+)", pr16);
    add_test("Prefix Invalid: Only Operands (23)", pr17);
    add_test("Prefix Invalid: Missing Operand (+2)", pr18);
    add_test("Prefix Invalid: Extra Operator (++)", pr19);
    
    add_test("Prefix Error: Division By Zero (/50)", pr20);
    add_test("Prefix Error: Stack Underflow (-+23)", pr21);
    
    add_test("Prefix Valid Complex Expression 1 (/+34*27)", pr22);
    add_test("Prefix Valid Complex Expression 2 (/+78-32)", pr23);
    add_test("Prefix Valid Complex Expression 3 (-/823)", pr24);
    add_test("Prefix Valid Complex Expression 4 (-+/45*623)", pr25);
    
    add_test("Prefix Deep Nested Expression (-*1+238)", pr26);
    add_test("Prefix Sequential Operator Pattern (*+23+45)", pr27);
    
    add_test("Prefix Edge: Empty String", pr28);
    add_test("Prefix Edge: Single Digit", pr29);
    add_test("Prefix Edge: Extra Operand (+12)", pr30);
    
    /* ================= TRICKY PREFIX TESTS ================= */
    
    add_test("Prefix Order Sensitivity (-34)", pr31);
    add_test("Prefix Order Sensitivity (-43)", pr32);
    add_test("Prefix Division Order (/26)", pr33);
    add_test("Prefix Division Order (/62)", pr34);
    
    add_test("Prefix Deep Right-Heavy Nesting (+1+2+3+45)", pr35);
    add_test("Prefix Deep Right-Heavy Nesting (*2*3*45)", pr36);
    
    add_test("Prefix Alternating Operators (-*+2345)", pr37);
    add_test("Prefix Alternating Operators (+*-2345)", pr38);
    
    add_test("Prefix Zero Behavior (*90)", pr39);
    add_test("Prefix Zero Behavior (+09)", pr40);
    add_test("Prefix Zero Behavior (-90)", pr41);
    add_test("Prefix Zero Behavior (-09)", pr42);
    
    add_test("Prefix Division Inside Complex (+9/63)", pr43);
    add_test("Prefix Division Inside Complex (-*8/42+13)", pr44);
    
    add_test("Prefix Large Nested Combination (+*9-82/63)", pr45);
    add_test("Prefix Large Nested Combination (-+7*45/62)", pr46);
    
    add_test("Prefix Stack Exhaustion (+*+1234)", pr47);
    add_test("Prefix Stack Exhaustion (*+1+234)", pr48);
    
    add_test("Prefix Extra Operand at End (+23 4)", pr49);
    add_test("Prefix Extra Operand at End (+234)", pr50);
    
    add_test("Prefix Multiple Operators Without Enough Operands (++23)", pr51);
    add_test("Prefix Multiple Operators Without Enough Operands (*-+)", pr52);
    
    add_test("Prefix All Zeros (+00)", pr53);
    add_test("Prefix All Zeros (*+00-00)", pr54);
    
    add_test("Prefix Deep Subtract Chain (-1-2-34)", pr55);
    
    add_test("Prefix Complex Mixed (+*-+12345)", pr56);
    add_test("Prefix Complex Mixed (-+*123*45)", pr57);
    
    add_test("Prefix Division By Zero Hidden (+3/40)", pr58);
    add_test("Prefix Division By Zero Hidden (-*5/20+13)", pr59);
    
    add_test("Prefix Valid But Tricky Operand Stacking (*-9+234)", pr60);
    

    run_all_tests();
}
