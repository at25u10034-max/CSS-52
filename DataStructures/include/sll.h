#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct LinkedList {
    int size;
    int *LINK;
    int *DATA;
    int AVAIL;
    int HEAD;
} List;

extern const char ERRORS[20][100];

List create(int n);
void freelist(List *l);

int next(List *l, int nidx);
int isNull(int i);

int isEmpty(List *l);
int isFull(List *l);
int len(List *l);

void avail(List *l, int idx);

int node(List *l, int val);

void set(List *l, int nidx, int val);
int get(List *l, int nidx);

void link(List *l, int curr, int next);

int insert(List *l, int pos, int val);
int insertStart(List *l, int val);
int insertEnd(List *l, int val);

int delete(List *l, int pos);
int deleteStart(List *l);
int deleteEnd(List *l);

void show(List *l);

#endif