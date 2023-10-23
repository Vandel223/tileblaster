#include <stdlib.h>                                                                               

#include "item.h" 
#include "stack.h"


struct _stack {

    Item * Arr;
    int top;
    int ssize;

};

Stack *stInit(int size) {

	Stack *st = (Stack *) malloc(sizeof(Stack));

	st->Arr = (Item *) calloc(size, sizeof(Item));
	st->top = 0;
	st->ssize = size;

	return st;

}

int push(Item it, Stack *st) {

	if (!stIsFull(st)) {

		st->Arr[(st->top)++] = it;

		return 1;

	}

	return 0;

}

Item pop(Stack *st) {

	if (!stIsEmpty(st)) {

		return st->Arr[--(st->top)];

	}

	return NULL;

}

Item peek(Stack *st) {

	if (!stIsEmpty(st)) {

		return st->Arr[st->top - 1];

	}

	return NULL;

}

int stIsEmpty(Stack *st) {

	return st->top == 0;

}

int stIsFull(Stack *st) {

	return st->top == st->ssize;

}

void stFree(Stack *st) {

	stFreeItems(st);
	free(st->Arr);
	free(st);

}

void stFreeItems(Stack *st) {

	for (int i = 0; i < st->ssize; i++) {

		if (st->Arr[i] != NULL) free(st->Arr[i]);

	}

}

