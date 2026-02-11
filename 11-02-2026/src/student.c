#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	int roll;
	int age;
	float marks;
	char gender;
	char *name;
	char *course;
	char *email;
	
	struct Node *next;	
};


// Output Utilities
char *centertext(char* source, int size) {
	int ssize = strlen(source);
	char* output = malloc(size + 1);
	if (!output) {
		printf("NO SPACE IN RAM");
		return NULL;
		
	}
	//printf("Size: %d, ss:%d, s-s/2: %d, s+s/2: %d\n", size, ssize, (size-ssize)/2, (size+ssize)/2);

	for(int i = 0; i < (size - ssize) / 2; i++)
		output[i] = ' ';

	for (int i =  (size - ssize) / 2; i <  (size + ssize) / 2; i++)
		output[i] = source[i -  (size - ssize) / 2];


	for(int i = (size + ssize) / 2; i < size; i++)
		output[i] = ' ';

	output[size] = '\0';
	return output;
} 

void printline() {
	printf("+--------+---------------+-----+---------+---------+--------+--------------------+\n");
}

void printheader() {
	char *rollc, *namec, *agec, *genderc, *coursec, *marksc, *emailc;

	rollc = centertext("Roll", 8);
	namec = centertext("Name", 15);
	agec = centertext("Age", 5);
	genderc = centertext("Gender", 9);
	coursec = centertext("Course", 9);
	marksc = centertext("Marks", 8);
	emailc = centertext("Email", 20);

	printf("+%s+%s+%s+%s+%s+%s+%s+\n", rollc, namec, agec, genderc, coursec, marksc, emailc);
}

void printrecord(struct Node* record) {
	char rolls[10], ages[10], genders[5], markss[10], *rollc, *namec, *agec, *genderc, *coursec, *marksc, *emailc;
	
	sprintf(rolls, "%d", record -> roll);
	sprintf(ages, "%d", record -> age);
	sprintf(genders, "%c", record -> gender);
	sprintf(markss, "%f", record -> marks);

	
	rollc = centertext(rolls, 8);
	namec = centertext(record -> name, 15);
	agec = centertext(ages, 5);
	genderc = centertext(genders, 9);
	coursec = centertext(record -> course, 9);
	marksc = centertext(markss, 8);
	emailc = centertext(record -> email, 20);

		
	printf("|%s|%s|%s|%s|%s|%s|%s|\n", rollc, namec, agec, genderc, coursec, marksc, emailc);
}


struct Node *create() {
	struct Node *temp = NULL;
	temp = malloc(sizeof(struct Node));
	if (!temp) {
		fprintf(stderr, "ERROR!! No space in RAM.");
	}

	printf("Roll: ");
	scanf("%d", &temp -> roll);

	printf("Name: ");
	temp->name = malloc(50);
	scanf("%s", temp -> name);

	printf("Age: ");
	scanf("%d", &temp -> age);

	char buf[3];
	printf("Gender: ");
	scanf("%s", buf);
	temp -> gender = buf[0];

	printf("Course: ");
	temp -> course = malloc(10);
	scanf("%s", temp -> course);

	printf("Marks: ");
	scanf("%f", &temp -> marks);

	printf("Email: ");
	temp->email = malloc(1024);
	scanf("%s", temp -> email);
	
	temp -> next = NULL;
	return temp;
}


// Insertion Functions

struct Node *insert_sorted(struct Node *HEAD, struct Node *new) {
	struct Node *temp = HEAD, *next;

	if (!HEAD) return new;
	
	while (temp->next && temp->roll < new->roll)
		temp = temp -> next;

	next = temp -> next;
	temp -> next = new;
	new -> next = next;
	return HEAD;
}


void search_roll(struct Node *temp) {
	int roll, count = 0;
	int flag = 0;
	printf("Enter Roll number to Search: ");
	scanf("%d", &roll);
	while (temp != NULL) {
		if (temp -> roll == roll) {
			count++;
			if (!flag) {
				flag = 1;
				printline();
				printheader();
				printline();
			}
			printrecord(temp);
		}
		temp = temp -> next;	
	} 
	if (!flag) printf("Not Found!");
	else {
		printline();
		printf("Found %d records. \n\n", count);
	}
}
// Program Flow Functions

void gc (struct Node *n) {
	if (n == NULL)
		return;

	struct Node* next = n -> next;
	while (n) {
		free(n);
		n = next;
		if (n)
			next = n -> next;
	}
}


#ifndef _IGNORE_MAIN

const char* MESSAGE = "Enter Option:\n\
\n\t(1) Insert Student record.\
\n\t(2) Search.\
\n\t(3) Display All Records.\n\
\n\t(0) Exit.\
\n\nOption: ";

const char *SEARCH_MSG = "Enter Search Parameter:\n\
\n\t(1) Roll\
\n\t(2) Name\
\n\t(3) Course\
\n\t(4) Marks RANGE\
\n\tOption: ";

int main() {
	int t;
	struct Node *HEAD = NULL, *temp;
	
	int flag = 1;
	while (flag) {
		fputs(MESSAGE, stdout);
		scanf("%d", &t);

		switch (t) {
			case 0:
				gc(HEAD);
				flag = 0;
				break;
			case 1:
				temp = create();
				HEAD = insert_sorted(HEAD, temp);
				printf("Record Inserted Successfully!\n");
				break;
			case 2:
				search_roll(HEAD);
		}
	}
}

#endif



