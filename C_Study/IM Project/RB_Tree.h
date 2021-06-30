#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef int(*FCMP)(const void*, const void*);

typedef struct _node {
	int red;
	struct _node* left;
	struct _node* right;
}node;

node* head;

void init_tree(node** p) {
	*p = (node*)calloc(1, sizeof(node));
	(*p)->left = (*p)->right = NULL;
	(*p)->red = 0;
}

void* rotate(void* key, node* pivot, node* base, int width, FCMP fcmp) {
	node* child, * gchild;
	if ((fcmp(key, pivot + 1) < 0) || pivot == base) 
		child = pivot->left;
	else 
		child = pivot->right;
	if (fcmp(key, child + 1) < 0) {
		gchild = child->left;
		child->left = gchild->right;
		gchild->right = child;
	}
	else {
		gchild = child->right;
		child->right = gchild->left;
		gchild->left = child;
	}
	if ((fcmp(key, pivot + 1) < 0) || pivot == base) 
		pivot->left = gchild;
	else 
		pivot->right = gchild;
	return gchild;
}

void* rbti_insert(void* key, node* base, int* num, int width, FCMP fcmp) {
	node* t, * parent, * gparent, * ggparent;
	ggparent = gparent = parent = base;
	t = base->left;
	while (t != NULL) {
		if (fcmp(key, t + 1) == 0) return NULL;
		if (t->left && t->right && t->left->red && t->right->red) {
			t->red = 1;
			t->left->red = t->right->red = 0;
			if (parent->red) {
				gparent->red = 1;
				if ((fcmp(key, gparent + 1) < 0) != (fcmp(key, parent + 1) < 0))
					parent = (node*)rotate(key, gparent, base, width, fcmp);
				t = (node*)rotate(key, ggparent, base, width, fcmp);
				t->red = 0;
			}
			base->left->red = 0;
		}
		ggparent = gparent;
		gparent = parent;
		parent = t;
		if (fcmp(key, t + 1) < 0) t = t->left;
		else t = t->right;
	}
	t = (node*)malloc(sizeof(node) + width);
	memcpy(t + 1, key, width);
	t->left = t->right = NULL;
	if ((fcmp(key, parent + 1) < 0) || parent == base) parent->left = t;
	else parent->right = t;
	(*num)++;
	t->red = 1;
	if (parent->red) {
		gparent->red = 1;
		if ((fcmp(key, gparent + 1) < 0) != (fcmp(key, parent + 1) < 0))
			parent = (node*)rotate(key, gparent, base, width, fcmp);
		t = (node*)rotate(key, ggparent, base, width, fcmp);
		t->red = 0;
	}
	base->left->red = 0;

	return t;
}

void br_sort_list(node* p, void (*fptr)(void*, void*)) {
	int i;
	static int x = 0;

	if (p != NULL) {
		x += 2;
		br_sort_list(p->right, fptr);
		for (i = 2; i < x; i++) printf("  ");
		fptr(p + 1, p);
		br_sort_list(p->left, fptr);
		x -= 2;
	}
}