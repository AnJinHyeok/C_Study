#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define LEN 5

typedef struct _node { struct _node* next; }node;
typedef int (*FCMP)(const void*, const void*);

int intcmp(const void* a, const void* b) {
	return (*(int*)a - *(int*)b);
}

void init_list(node** p) {
	*p = (node*)malloc(sizeof(node));
	(*p)->next = NULL;
}

void* llv_insert(void* key, node* base, int* num, int width, FCMP fcmp) {
	node* t;
	t = (node*)malloc(sizeof(node) + width);
	memcpy(t + 1, (int*)key, width);
	t->next = base->next;
	base->next = t;
	(*num)++;
	return t;
}

void* llv_search(void* key, node* base, int* num, int width, FCMP fcmp) {
	node* t;
	t = base;
	while (fcmp(t + 1, (int*)key) != 0 && t != NULL) {
		t = t->next;
		(*num)--;
	}
	return (t == NULL ? NULL : t + 1);
}

int main() {
	void* p;
	node* t, * head;
	int size = 0, key = 9, num, result;
	int data[LEN] = { 3,1,9,7,5 };

	init_list(&head);

	for (int i = 0; i < LEN; i++) llv_insert(data + i, head, &size, sizeof(int), intcmp);
	t = head->next;
	while (t != NULL) {
		memcpy(&num, t + 1, sizeof(int));
		printf("%d ", num);
		t = t->next;
	}

	num = size;
	p = llv_search(&key, head, &num, sizeof(int), intcmp);
	memcpy(&result, p, sizeof(int));
	printf("\n%d는 %d 위치에 있다.", result, num);
}