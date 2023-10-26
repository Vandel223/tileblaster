#ifndef _LINKLIST_H_
#define _LINKLIST_H_


typedef struct {

    int cnt;
    int color;

} ColorCnt;

typedef struct _node {

	ColorCnt cCnt;
	struct _node *next;

} Node;

#endif
