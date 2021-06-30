#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100

typedef struct _node {
	int vertex;
	int weight;
	struct _node* next;
}node;

typedef struct _head {
	int count;
	struct _node* next;
}head;

head* network[MAX_NODE];
node* GL[MAX_NODE];
int stack[MAX_NODE], earliest[MAX_NODE], latest[MAX_NODE];
int top;
FILE* fp;

void init_stack() {
	top = -1;
}

int name2int(char s) {
	return s - 'A';
}

char int2name(int num) {
	return num + 'A';
}

void push(int i) {
	stack[++top] = i;
}

int pop() {
	return stack[top--];
}

int stack_empty() {
	return !(top + 1);
}

void input_adjlist(node* a[], int* V, int* E) {
	char vertex[3];
	int i, j, w;
	node* t;
	printf("\nInput number of node & edge\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++) a[i] = NULL;
	for (j = 0; j < *E; j++) {
		printf("\nInput two node consist of edge ->");
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		t = (node*)malloc(sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->weight = w;
		t->next = a[i];
		a[i] = t;
	}
}

void print_adjlist(node* a[], int V) {
	printf("\n");
	for (int i = 0; i < V - 1; i++) {
		node* t = NULL;
		printf("%c", int2name(i));
		t = a[i];
		do {
			int data = t->vertex;
			int weight = t->weight;
			t = t->next;
			printf(" -> %c %d", int2name(data), weight);
		} while (t != NULL);
		printf("\n");
	}
	printf("M\n");
}

void set_count_indegree(head* net[], int V) {
	int i, j;
	int count;
	node* t;
	for (i = 0; i < V; i++) {
		count = 0;
		for (j = 0; j < V; j++)
			for (t = net[j]->next; t; t = t->next)
				if (t->vertex == i) count++;
		net[i]->count = count;
	}
}

void set_count_outdegree(head *net[], int V) {
	int i, count;
	node* t;
	for (i = 0; i < V; i++) {
		count = 0; 
		for (t = net[i]->next; t; t = t->next)
			count++;
		net[i]->count = count;
	}
}

void forward_stage(head *net[], int V) {
	int i, j, k;
	node* ptr;

	init_stack();
	set_count_indegree(net, V);

	for (i = 0; i < V; i++) earliest[i] = 0;
	for (i = 0; i < V; i++)
		if (!net[i]->count) push(i);
	for (i = 0; i < V; i++) {
		if (!stack_empty()) {
			j = pop();
			for (ptr = net[j]->next; ptr; ptr = ptr->next) {
				k = ptr->vertex;
				net[k]->count--;
				if (!net[k]->count)
					push(k);
				if (earliest[k] < earliest[j] + ptr->weight)
					earliest[k] = earliest[j] + ptr->weight;
			}
		}
	}
}

void backward_stage(head *net[], int V) {
	int i, j, k, l;
	node* ptr;

	init_stack();
	set_count_outdegree(net, V);

	for (i = 0; i < V; i++)
		latest[i] = earliest[V - 1];
	for (i = 0; i < V; i++)
		if (!net[i]->count) push(i);
	for (i = 0; i < V; i++) {
		if (!stack_empty()) {
			j = pop();
			for (l = 0; l < V; l++) {
				for (ptr = net[l]->next; ptr; ptr = ptr->next) {
					if (ptr->vertex == j) {
						k = l;
						net[k]->count--;
						if (!net[k]->count)
							push(k);
						if (latest[k] > latest[j] - ptr->weight)
							latest[k] = latest[j] - ptr->weight;
					}
				}
			}
		}
	}
}

void print_critical_activity(head *net[], int V) {
	char vertex[3];
	int i, j, w, E;
	int ear, lat, cri;
	node* t;
	fscanf(fp, "%d %d", &V, &E);
	for (j = 0; j < E; j++) {
		fscanf(fp, "%s %d", vertex, &w);
		ear = earliest[name2int(vertex[0])];
		lat = latest[name2int(vertex[1])] - w;
		cri = lat - ear;
		if (cri == 0)
			printf("<%c, %c> Early = %d, Late = %d, critical YES\n", vertex[0], vertex[1], ear, lat);
		else if(cri != 0)
			printf("<%c, %c> Early = %d, Late = %d, critical NO\n", vertex[0], vertex[1], ear, lat);
	}
}

int main() {
	int k, V, E;
	fp = fopen("graph_AOE.txt", "r");

	input_adjlist(GL, &V, &E);
	print_adjlist(GL, V);

	fclose(fp);

	for (k = 0; k < V; k++) {
		network[k] = (head*)calloc(1, sizeof(head));
		network[k]->next = GL[k];
	}
		
	forward_stage(network, V);
	backward_stage(network, V);
	fp = fopen("graph_AOE.txt", "r");
	print_critical_activity(network, V);
	fclose(fp);
}