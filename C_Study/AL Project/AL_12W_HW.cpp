#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100

int* check;
int order = 0, top = 0;

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

node* g[MAX_NODE];
int stack[MAX_NODE];
FILE* fp;

int name2int(char s) {
	return s - 'A';
}

char int2name(int num) {
	return num + 'A';
}

void init_stack() {
	top = -1;
}

void push_list(int num, int s) {
	node* t;
	t = (node*)calloc(1, sizeof(node));
	t->vertex = s;
	t->next = g[num];
	g[num] = t;
}

void push(int i) {
	stack[++top] = i;
}

int pop() {
	return stack[top--];
}

void init_node(int V) {
	for (int i = 0; i < V; i++) g[i] = NULL;
}

void input_node(int* V, int* E) {
	char edge[3];
	node* t;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	init_node(*V);
	check = (int*)calloc(*V, sizeof(int));
	for (int i = 0; i < *E; i++) {
		printf("input Edge : ");
		fscanf(fp, "%s", edge);
		push_list(name2int(edge[0]), name2int(edge[1]));
	}
	printf("\n");
}

int strong_recur(node* g[], int i) {
	int m, min, k, flag;
	node* t;
	check[i] = min = ++order;
	push(i);
	for (t = g[i]; t != NULL; t = t->next) {
		if (check[t->vertex] == 0)
			m = strong_recur(g, t->vertex);
		else
			m = check[t->vertex];
		if (m < min) min = m;
	}
	if (min == check[i]) {
		flag = 0;
		while ((k = pop()) != i) {
			printf("%c ", int2name(k));
			check[k] = MAX_NODE + 1;
			flag = 1;
		}
		if (flag) printf("%c\n", int2name(k));
	}
	return min;
}

void strong(node* g[], int V) {
	int x, y;
	for (y = 0; y < V; y++)
		check[y] = 0;
	for (y = 0; y < V; y++) {
		if (check[y] == 0)
			strong_recur(g, y);
	}
}

int main() {
	int V, E;
	fp = fopen("graph.txt", "r");
	input_node(&V, &E);
	init_stack();
	strong(g, V);
}