#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100
int GM[MAX_NODE][MAX_NODE];
int* check, *stack;
int top;

int name2int(char c) {
	return c - 'A';
}

char int2name(int i) {
	return i + 'A';
}

void input_adjmatrix(int a[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int i, j, k;
	printf("\nInput number of node & edge\n");
	scanf("%d %d", V, E);
	check = (int*)calloc(*V, sizeof(int));
	for (i = 0; i < *V; i++) for (j = 0; j < *V; j++) a[i][j] = 0;
	for (i = 0; i < *V; i++) a[i][i] = 1;
	for (k = 0; k < *E; k++) {
		printf("\nINnput two node consist of edge ->");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		a[i][j] = 1;
		a[j][i] = 1;
	}
}

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

node* GL[MAX_NODE];

void input_adjlist(node* a[], int* V, int* E) {
	char vertex[3];
	int i, j;
	node* t;
	printf("\nInput number of node & edge\n");
	scanf("%d %d", V, E);
	for (i = 0; i < *V; i++) a[i] = NULL;
	for (j = 0; j < *E; j++) {
		printf("\nInput two node consist of edge ->");
		scanf("%s", vertex);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->next = a[i];
		a[i] = t;
		i = name2int(vertex[1]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->next = a[i];
		a[i] = t;
	}
}

void print_adjmatrix(int a[][MAX_NODE], int V) {
	int i, j;
	printf("%3c", ' ');
	for (i = 0; i < V; i++) printf("%3c", int2name(i));
	printf("\n");
	for (i = 0; i < V; i++) {
		printf("%3c", int2name(i));
		for (j = 0; j < V; j++) printf("%3d", a[i][j]);
		printf("\n");
	}
}

void print_adjlist(node* a[], int V) {
	for (int i = 0; i < V; i++) {
		node* t = NULL;
		printf("%c", int2name(i));
		do {
			t = a[i];
			int data = t->vertex;
			a[i] = t->next;
			free(t);
			printf(" -> %c", int2name(data));
		} while (a[i] != NULL);
		printf("\n");
	}
}

void visit(int i) {
	printf(" -> %c", int2name(i));
}

void DFS_recur_matrix(int a[][MAX_NODE], int V, int i) {
	int j;
	check[i] = 1;
	visit(i);
	for (j = 0; j < V; j++)
		if (a[i][j] != 0)
			if (check[j] == 0)
				DFS_recur_matrix(a, V, j);
}

void DFS_adjmatrix(int a[][MAX_NODE], int V) {
	int i;
	printf("A");
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++)
		if (check[i] == 0) DFS_recur_matrix(a, V, i);
}

void init_stack() {
	top = -1;
}

int push(int i) {
	if (top >= MAX_NODE - 1) {
		printf("stack is overflow");
		return -1;
	}
	else {
		stack[++top] = i;
		return i;
	}
}

int stack_empty() {
	if (top <= -1)
		return 1;
	else return 0;
}

int pop() {
	if (stack_empty()) {
		printf("stack is empty");
		return -1;
	}
	else return stack[top--];
}

void nrDFS_adjmatrix(int a[][MAX_NODE], int V) {
	int i, j;
	stack = (int*)calloc(V, sizeof(int));
	check = (int*)calloc(V, sizeof(int));
	init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++) {
		if (check[i] == 0) {
			push(i);
			check[i] = 1;
			while (!stack_empty()) {
				i = pop();
				visit(i);
				for(j=0;j<V;j++)
					if(a[i][j]!=0)
						if (check[j] == 0) {
							push(j);
							check[j] = 1;
						}
			}
		}
	}
}

void DFS_recur_list(node* a[], int V, int i) {
	node* t;
	check[i] = 1;
	visit(i);
	for (t = a[i]; t != NULL; t = t->next)
		if (check[t->vertex] == 0)
			DFS_recur_list(a, V, t->vertex);
}

void DFS_adjlist(node* a[], int V) {
	int i;
	printf("A");
	check = (int*)calloc(V, sizeof(int));
	for (i = 0; i < V; i++) check[i] = 0;
	for (i = 0; i < V; i++)
		if (check[i] == 0) DFS_recur_list(a, V, i);
}

void nrDFS_adjlist(node* a[], int V) {
	int i, j = 0;
	node* t;
	stack = (int*)calloc(V, sizeof(int));
	check = (int*)calloc(V, sizeof(int));
	init_stack();
	for (i = 0; i < V; i++) check[i] = 0;
	while (j != V) {
		if (check[j] == 0) {
			push(j);
			check[j] = 1;
			while (!stack_empty()) {
				i = pop();
				visit(i);
				t = a[i];
				while (t != NULL) {
					if (check[t->vertex] == 0) {
						push(t->vertex);
						check[t->vertex] = 1;
					}
					t = t->next;
				}
			}
		}
		j++;
	}
}

int main() {
	int V, E;

	//input_adjmatrix(GM, &V, &E);
	//print_adjmatrix(GM, V);

	input_adjlist(GL, &V, &E);
	//print_adjlist(GL, V);

	//DFS_adjmatrix(GM, V);
	//nrDFS_adjmatrix(GM, V);

	//DFS_adjlist(GL, V);
	nrDFS_adjlist(GL, V);
}