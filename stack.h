#ifndef _STACK_H_
#define _STACK_H_

#include "item.h"

typedef struct _stack Stack;

Stack *stInit(int);
int push(Item, Stack *);
Item pop(Stack *);
Item peek(Stack *);
int stIsEmpty(Stack *);
int stIsFull(Stack *);
void stFree(Stack *);
void stFreeItems(Stack *);

#endif

