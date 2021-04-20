#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100

int* check, * check_ap;
int order, son_of_root;

typedef struct _node {
	int vertex;
	struct _node* next;
}node;

node* a[MAX_NODE];

int name2int(char s) {
	return s - 'A';
}

char int2name(int num) {
	return num + 'A';
}

void init_node(int V) {
	for (int i = 0; i < V; i++) a[i] = NULL;
}

void push(int num, char s) {
	node* t;
	t = (node*)calloc(1, sizeof(node));
	t->vertex = s;
	t->next = a[num];
	a[num] = t;
}

void input_node(int *V, int *E) {
	char edge[3];
	printf("input V and E : ");
	scanf("%d %d", V, E);
	init_node(*V);
	check = (int*)calloc(*V, sizeof(int));
	check_ap = (int*)calloc(*V, sizeof(int));
	for (int i = 0; i < *E; i++) {
		printf("input Edge : ");
		scanf("%s", edge);
		push(name2int(edge[0]), name2int(edge[1]));
		push(name2int(edge[1]), name2int(edge[0]));
	}
}

void print_node(node* a[MAX_NODE], int *V) {
	node* t;
	for (int i = 0; i < *V; i++) {
		for (t = a[i]; t != NULL; t = t->next) printf("-> %c ", int2name(t->vertex));
		printf("\n");
	}
}

void visit(int ver) {
	printf("-> %c ", int2name(ver));
}

void DFS(node* a[MAX_NODE], int ver) {
	if (check[ver] == 0) check[ver] = 1;
	visit(ver);
	node* t;
	for (t = a[ver]; t != NULL; t = t->next) {
		if (check[t->vertex] == 0) {
			DFS(a, t->vertex);
		}
	}
}

int AP(node* a[MAX_NODE], int ver, int start) {
	int min;
	check_ap[ver] = min = ++order;
	node* t;
	for (t = a[ver]; t != NULL; t = t->next) {
		if (ver == start && check_ap[t->vertex] == 0)
			son_of_root++;
		if (check_ap[t->vertex] == 0) {
			int m = AP(a, t->vertex, start);
			if (m < min) min = m;
			if (m >= check_ap[ver] && ver != start) {
				printf("AP %c\n", int2name(ver));
			}
			else
				printf("Not AP %c\n", int2name(ver));
		}
		else 
			if (min > check_ap[t->vertex]) min = check_ap[t->vertex];
	}
	return min;
}

int AP_recur(node* a[], int i) {
	node* t;
	int min, m;
	check_ap[i] = min = ++order;
	for (t = a[i]; t != NULL; t = t->next) {
		if (i == 0 && check_ap[t->vertex] == 0)
			son_of_root++;
		if (check_ap[t->vertex] == 0) {
			m = AP_recur(a, t->vertex);
			if (m < min) min = m;
			if (m >= check_ap[i] && i != 0)
				printf("* %c %2d : %d\n", int2name(i), check_ap[i], m);
			else
				printf("%c %2d : %d\n", int2name(i), check_ap[i], m);
		}
		else
			if (check_ap[t->vertex] < min)
				min = check_ap[t->vertex];
	}
	return min;
}

void AP_search(node* a[], int V) {
	int i, n = 0;
	node* t;

	for (i = 0; i < V; i++)check_ap[i] = 0;
	order = son_of_root = 0;
	//AP_recur(a, 0);
	//AP(a, 0, 0);
	for (int j = 0; j < V; j++) {
		son_of_root = 0;
		if (check_ap[j] == 0) {
			AP(a, j, j);
			//AP_recur(a, j);
			if (son_of_root > 1) printf("* ");
			else printf("  ");
			printf("%c son : %d\n", int2name(j), son_of_root);
		}
	}

}
int main() {
	int V, E;
	input_node(&V, &E);
	//print_node(a, &V);
	//DFS(a, 0);
	AP_search(a, V);
	//AP_recur(a, 0);
}