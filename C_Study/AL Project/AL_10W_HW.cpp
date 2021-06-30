#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
#define UNSEEN (-INT_MAX)

typedef struct node {
	int vertex;
	int weight;
	struct node* next;
}node;

node* G[MAX_NODE];
int check[MAX_NODE];
int parent[MAX_NODE];
FILE* fp;
int nheap = 0;
int heap[MAX_NODE];

void pq_init() {
	nheap = 0;
}

void upheap(int h[], int k) {
	int v;
	v = h[k];
	while (check[h[k / 2]] <= check[v] && k / 2 > 0) {
		h[k] = h[k / 2];
		k /= 2;
	}
	h[k] = v;
}

void downheap(int h[], int k) {
	int i, v;
	v = h[k];
	while (k <= nheap / 2) {
		i = k << 1;
		if (i < nheap && check[h[i]] < check[h[i + 1]]) i++;
		if (check[v] >= check[h[i]]) break;
		h[k] = h[i];
		k = i;
	}
	h[k] = v;
}

void adjust_heap(int h[], int n) {
	int k;
	for (k = n / 2; k >= 1; k--) downheap(h, k);
}

int pq_empty() {
	if (nheap == 0) return 1;
	return 0;
}

int pq_extract(int h[]) {
	int v = h[1];
	h[1] = h[nheap--];
	downheap(h, 1);
	return v;
}

char int2name(int i) {
	return i + 'A';
}

int name2int(char c) {
	return c - 'A';
}

void print_adjlist(node* g[], int V) {
	int i;
	node* t;
	for (i = 0; i < V; i++) {
		printf("\n%c : ", int2name(i));
		for (t = g[i]; t != NULL; t = t->next) {
			printf("-> %c:%d ", int2name(t->vertex), t->weight);
		}
	}
}

void print_heap(int h[]) {
	int i;
	printf("\n");
	for (i = 1; i <= nheap; i++)
		printf("%c:%d ", int2name(h[i]), check[h[i]]);
}

int pq_update(int h[], int v, int p) {
	if (check[v] == UNSEEN) {
		h[++nheap] = v;
		check[v] = p;
		upheap(h, nheap);
		return 1;
	}
	else {
		if (check[v] < p) {
			check[v] = p;
			adjust_heap(h, nheap);
			return 1;
		}
		else
			return 0;
	}
}

void input_adjlist(node* g[], int* V, int* E) {
	char vertex[3];
	int i, j, w;
	node* t;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		g[i] = NULL;
	for (j = 0; j < *E; j++) {
		printf("\nInput two nodes of edge and weight -> ");
		fscanf(fp, "%s %d", vertex, &w);
		t = (node*)calloc(1, sizeof(node));
		t->vertex = name2int(vertex[0]);
		t->weight = w;
		t->next = g[name2int(vertex[1])];
		g[name2int(vertex[1])] = t;
		t = (node*)calloc(1, sizeof(node));
		t->vertex = name2int(vertex[1]);
		t->weight = w;
		t->next = g[name2int(vertex[0])];
		g[name2int(vertex[0])] = t;
	}
}

void visit(int i) {
	printf("-> %c ", int2name(i));
}

void shortest_adjlist(node* g[], int V) {
	int i;
	node* t;
	pq_init();
	for (i = 0; i < V; i++) {
		check[i] = UNSEEN;
		parent[i] = 0;
	}
	for (i = 0; i < V; i++) {
		if (check[i] == UNSEEN) {
			parent[i] = -1;
			pq_update(heap, i, 0);

			while (!pq_empty()) {
				print_heap(heap);
				i = pq_extract(heap);
				check[i] = -check[i];
				visit(i);
				for (t = g[i]; t != NULL; t = t->next) {
					if (check[t->vertex] < 0)
						if (pq_update(heap, t->vertex, -t->weight-check[i]))
							parent[t->vertex] = i;
				}
			}
		}
	}
}

void print_cost() {
	printf("%d\n", check[name2int('K')]);
}

int print_path(int N) {
	if (N == 0)
		return 0;
	else {
		int num = print_path(parent[N]);
		printf("%c ", int2name(num));
		return N;
	}
}

int main() {
	int V, E;
	fp = fopen("graph.txt", "rt");

	input_adjlist(G, &V, &E);
	printf("\nOriginal graph\n");
	print_adjlist(G, V);
	printf("\n");
	shortest_adjlist(G, V);
	printf("\n\nGraph path : ");
	printf("%c",int2name(print_path(name2int('K'))));
	printf("\n\nMinimum Cost is ");
	print_cost();
	fclose(fp);
}