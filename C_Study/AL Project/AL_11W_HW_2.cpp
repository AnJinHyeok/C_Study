#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
FILE* fp;

typedef struct _head {
	int count;
	int vertex;
	struct _head* next;
}head;

head *network[MAX_NODE];
int stack[MAX_NODE];
int top;

void init_stack() {
	top = 0;
}

char int2name(int n) {
	return n + 'A';
}

int name2int(char c) {
	return c - 'A';
}

void set_list(int *V, int *E) {
	char vertex[3];
	head* t;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (int i = 0; i < *V; i++) {
		network[i] = (head*)calloc(1, sizeof(head));
		network[i]->next = NULL;
	}
	for (int i = 0; i < *E; i++) {
		printf("\nInput two nodes consisting of edge -> ");
		fscanf(fp, "%s", vertex);
		t = (head*)calloc(1, sizeof(head));
		t->vertex = name2int(vertex[1]);
		t->next = network[name2int(vertex[0])]->next;
		network[name2int(vertex[0])]->next = t;
	}
}

void set_count_indegree(head *net[], int V) {
	int i, j;
	int count;
	head* t;
	for (i = 0; i < V; i++) {
		count = 0;
		for (j = 0; j < V; j++)
			for (t = net[j]->next; t; t = t->next)
				if (t->vertex == i) count++;
		net[i]->count = count;
	}
}

void push(int i) {
	stack[++top] = i;
}

int pop() {
	return stack[top--];
}

int stack_empty() {
	return !top;
}

void topsort(head *net[], int V) {
	int i, j, k;
	head* ptr;
	init_stack();

	set_count_indegree(net, V);

	printf("\n");
	for (i = 0; i < V; i++)
		if (!net[i]->count) push(i);
	for (i = 0; i < V; i++) {
		if (stack_empty()) break;
		else{
			j = pop();
			printf("%c ", int2name(j));
			for (ptr = net[j]->next; ptr; ptr = ptr->next) {
				k = ptr->vertex;
				net[k]->count--;
				if (!net[k]->count)
					push(k);
			}
		}
	}
}

int main() {
	int V, E;
	fp = fopen("graph.txt", "r");
	set_list(&V, &E);
	topsort(network, V);
}