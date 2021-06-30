#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node {
	int key;
	struct _node* left;
	struct _node* right;
}node;

node* base;

void init_tree(){
	base = (node*)calloc(1, sizeof(node));
	base->left = base->right = NULL;
}

char int2name(int n) {
	return n + 'A';
}

int name2int(char c) {
	return c - 'A';
}

node* bti_search(int key, node* base, int* num) {
	node* s;
	s = base->left;
	while (key != s->key && s != NULL) {
		if (key < s->key) s = s->left;
		else s = s->right;
	}
	if (s == NULL) return NULL;
	else return s;
}

node* bti_insert(int key, node* base, int* num) {
	node* p, * s;
	p = base;
	s = base->left;
	while (s != NULL) {
		p = s;
		if (key < s->key) s = s->left;
		else s = s->right;
	}
	s = (node*)malloc(sizeof(node));
	s->key = key;
	s->left = s->right = NULL;
	if (key < p->key || p == base) p->left = s;
	else p->right = s;
	(*num)++;
	return s;
}

void bti_sort(node* p, int* a, int* index) {
	if (p != NULL) {
		bti_sort(p->left, a, index);
		a[(*index)++] = p->key;
		bti_sort(p->right, a, index);
	}
}

node* _balance(int N, int* a, int *index) {
	int nl, nr;
	node* p;
	if (N > 0) {
		nl = (N - 1) / 2;
		nr = N - nl - 1;
		p = (node*)malloc(sizeof(node));
		p->left = _balance(nl, a, index);
		p->key = a[(*index)++];
		p->right = _balance(nr, a, index);

		return p;
	}
	else return NULL;
}

char stack[100] = {};
int top = -1;

void clear() {
	top = -1;
	printf("\n\n");
}

void push(char c) {
	stack[++top] = c;
}

char pop() {
	return stack[top--];
}

void print(node* sorting) {
	if (sorting != NULL) {
		push('L');
		print(sorting->left);

		for (int i = 0; i <= top; i++)
			printf("%c", stack[i]);
		if (top == -1) printf("ROOT");
		printf("에 위치한 노드입니다 -> %c\n\n", int2name(sorting->key));

		push('R');
		print(sorting->right);
		pop();
	}
	else
		pop();
}

int main() {
	int num = 0, index = 0;
	int* a;
	node* sorting;
	char tree[13] = "FBADCOLGHKMN";
	a = (int*)calloc(strlen(tree), sizeof(int));
	init_tree();
	for(int i = 0; i < 12; i++)
		bti_insert(name2int(tree[i]), base, &num);
	print(base->left);
	bti_sort(base, a, &index);
	index = 0;
	sorting = _balance(strlen(tree), a, &index);
	clear();
	print(sorting);
}