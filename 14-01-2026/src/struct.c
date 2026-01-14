#include <stdlib.h>
#include <string.h>

#define __main__
#include "bsort_gen.c"
#define N_STUDENTS 3

typedef struct {
	int roll;
	char* name;
	int marks;
} Student;


Student students[N_STUDENTS] = {
	{101, "Amit", 78},
	{103, "Neha", 85},
	{102, "Rahul", 85}
};

int comp(void* e1, void* e2) {
	Student *s1 = (Student*) e1;
	Student *s2 = (Student*) e2;
	if (s1->marks != s2->marks)
		return s1->marks - s2->marks;

	return strcmp(s1->name, s2->name);
};

int main() {
	
	Student **pointerarr = malloc(sizeof(Student *) * 3);
	pointerarr[0] = &students[0];
	pointerarr[1] = &students[1];
	pointerarr[2] = &students[2];
	 
	bsort(N_STUDENTS, (void**) pointerarr, comp);

	printf("Roll		Name		Marks\n");
	for (int i = 0; i < N_STUDENTS; i++) {
		printf("%d\t\t%s\t\t%d\n", pointerarr[i]->roll, pointerarr[i]->name, pointerarr[i]->marks);
	}
}
