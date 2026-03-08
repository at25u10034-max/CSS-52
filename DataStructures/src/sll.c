#include <stdio.h>
#include <stdlib.h>
#include "../include/sll.h"

const char ERRORS[20][100] = {

    "SUCCESS !",
    "LIST IS FULL",
    "LIST IS EMPTY",
    "INDEX OUT OF RANGE"
};

List create(int n) {
    List l = {.size = n};
    l.LINK = malloc(sizeof(int) * n);
    l.DATA = calloc(sizeof(int), n);
    
    l.HEAD = -1;
    l.AVAIL = 0;
    
    // Create AVAIL list.
    for(int i = 0; i < n-1; i++)
        l.LINK[i] = i + 1;
    l.LINK[n-1] = -1;
    
    return l;
}


void freelist(List *l) {
    free(l -> LINK);
    free(l -> DATA);
    free(l);
}

int next(List *l, int nidx) {
     return l -> LINK[nidx];
}

void set(List *l, int nidx, int val) {
    l -> DATA[nidx] = val;
}

void link(List *l, int curr, int next) {
    l -> LINK[curr] = next;
}

int get(List *l, int nidx) {
    return l -> DATA[nidx];
}

int isNull(int i) {
    return i == -1;
}

int isEmpty(List *l) {
    return isNull(l -> HEAD);
}

int isFull(List *l) {
    return isNull(l -> AVAIL);
}


int node(List *l, int val) {
    if (isFull(l)) return 1;
    int n = l->AVAIL;
    l -> AVAIL = next(l, n);
    set(l, n, val);
    link(l, n, -1);
    
    return n;
}


void avail(List *l, int n) {
    link(l, n, l -> AVAIL);
    set(l,n,0);
    l -> AVAIL = n;
}


int len(List *l) {
    int h = l -> HEAD;
    if (isNull(h)) return 0;
    int s = 0;
    while (!isNull(h)) {
        s++; 
        h = next(l,h);
    }
    return s;
}

void show(List *l) {
    printf("HEAD: ");
    int p = l -> HEAD;
    while (!isNull(p)) {
        printf("{[%d]: %d} -> ", p, get(l,p));
        p = next(l, p);
    }
    printf("NULL\n");
    
    printf("AVAIL: ");
    p = l -> AVAIL;
    while (!isNull(p)) {
        printf("{[%d]: %d} -> ", p, get(l,p));
        p = next(l, p);
    }
    printf("NULL\n");
    
}


int insert(List *l, int idx, int val) {
    if (isFull(l)) return 1;
    int n;    
    // CASE top
    if (idx == 0) {
          n = node(l, val);
        link(l, n, l->HEAD);
        l -> HEAD = n;
        return 0;
    }
    
    int p = l -> HEAD;
    idx--;
    while (idx--) {
        p = next(l, p);
        if (isNull(p)) return 3;
    }
    n = node(l, val);
    link(l, n, next(l,p));
    link(l, p, n);
    return 0;
}

int insertStart(List *l, int val) {
    return insert(l,0,val);
}

int insertEnd(List *l, int val) {
    if (isEmpty(l)) return insertStart(l, val);

    if (isFull(l)) return 1;
    int n = node(l, val);
    
    int p = l -> HEAD;
    while ( !isNull(next(l,p)) ) {
        p = next(l, p);
    }
    
    link(l, p, n);
    return 0;
}




int delete(List *l, int idx) {
    if (isEmpty(l)) return 2;
    
    int p = l -> HEAD;
    // CASE TOP
    if (idx == 0) {
          l -> HEAD = next(l,p);
          avail(l, p);
          return 0;
    }
    
    idx--;
    while(idx--) {
        p = next(l,p);
        if (isNull(p)) return 3;
    }
    
    int n = next(l, p);
    if (isNull(n)) return 3;
    
    link(l,p,next(l,n));
    avail(l,n);
    return 0;
}


int deleteStart(List *l) {
    delete(l,0);
}

int deleteEnd(List *l) {
    if (isEmpty(l)) return 2;
    
    int p = l -> HEAD;
    
    if (isNull(next(l,p))) {
        avail(l,p);
        l -> HEAD = -1;
        return 0;
    }
    
    while ( !isNull(next(l,next(l,p))) ) {
        p = next(l, p);
    }
    
    int n = next(l, p);
    link(l, p, next(l, n));
    avail(l, n);
    return 0;
}