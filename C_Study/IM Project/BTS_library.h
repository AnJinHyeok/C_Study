#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef int(*FCMP)(const void*, const void*);

typedef struct _node {
	struct _node* left;
	struct _node* right;
}node;

void init_tree(node** p) {
	*p = (node*)calloc(1, sizeof(node));
	(*p)->left = (*p)->right = NULL;
}

void* btv_search(void* key, node* base, int* num, int width, FCMP fcmp) {
	node* s;
	s = base->left;
	while (s != NULL && fcmp(key, s + 1) != 0) {
		if (fcmp(key, s + 1) < 0) s = s->left;
		else s = s->right;
	}
	if (s == NULL) return NULL;
	else return s + 1;
}

void* btv_insert(void* key, node* base, int* num, int width, FCMP fcmp) {
	node* p, * s;
	p = base;
	s = base->left;
	while (s != NULL) {
		p = s;
		if (fcmp(key, s + 1) < 0) s = s->left;
		else s = s->right;
	}
	if ((s = (node*)malloc(sizeof(node) + width)) == NULL) return NULL;
	memcpy(s + 1, key, width);
	s->left = s->right = NULL;
	if (fcmp(key, p + 1) < 0 || p == base) p->left = s;
	else p->right = s;
	(*num)++;
	return s + 1;
}

void btv_sort_list(node* p, void (*fptr)(void*)) {
	int i;
	static int x = 0;

	if (p != NULL) {
		x += 2;
		btv_sort_list(p->right, fptr);
		for (i = 2; i < x; i++) printf("  ");
		fptr(p + 1);
		btv_sort_list(p->left, fptr);
		x -= 2;
	}
}