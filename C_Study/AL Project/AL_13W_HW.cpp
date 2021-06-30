#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
#define SOURCE 'S'
#define SINK 'T'

int Capacity[MAX_NODE][MAX_NODE];
int Flow[MAX_NODE][MAX_NODE];
int Residual[MAX_NODE][MAX_NODE];
int check[MAX_NODE];
int parent[MAX_NODE];
int path[MAX_NODE];

FILE* fp;

int name2int(char c) {
	if (c == SOURCE) return 0;
	if (c == SINK) return 1;
	return c - 'A' + 2;
}

int int2name(int i) {
	if (i == 0) return SOURCE;
	if (i == 1) return SINK;
	return i + 'A' + 2;
}

int queue[MAX_NODE];
int front, rear;

void init_queue() {
	front = rear = 0;
}

int queue_empty() {
	if (front == rear) return 1;
	else return 0;
}

void put(int k) {
	queue[rear] = k;
	rear = ++rear % MAX_NODE;
}

int get() {
	int i;
	i = queue[front];
	front = ++front % MAX_NODE;
	return i;
}

void clear_matrix(int mat[][MAX_NODE], int V) {
	for (int i = 0; i < MAX_NODE; i++)
		for (int j = 0; j < MAX_NODE; j++)
			mat[i][j] = 0;
}

void input_Capacity(int a[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int w;
	fscanf(fp, "%d %d", V, E);
	clear_matrix(a, *V);
	for (int i = 0; i < *E; i++) {
		fscanf(fp, "%s %d", vertex, &w);
		a[name2int(vertex[0])][name2int(vertex[1])] = w;
	}
}

void set_path() {
	int* temp;
	int i, count = 0;
	temp = (int*)calloc(MAX_NODE, sizeof(int));
	i = name2int(SINK);
	while (i >= 0) {
		temp[count] = i;
		i = parent[i];
		count++;
	}
	for (i = 0; i < count; i++)
		path[i] = temp[count - i - 1];
	path[i] = -1;
	free(temp);
}

void construct(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V) {
	int i, j;
	for (i = 0; i < V; i++)
		for (j = 0; j < V; j++)
			r[i][j] = c[i][j] - f[i][j];
}

int get_augument_path(int a[][MAX_NODE], int V, char S, char T) {
	int i, j;
	init_queue();
	for (i = 0; i < V; i++) {
		check[i] = 0;
		parent[i] = -1;
	}
	i = name2int(S);
	if (check[i] == 0) {
		put(i);
		check[i] = 1;
		while (!queue_empty()) {
			i = get();
			if (i == name2int(T)) break;
			for (j = 0; j < V; j++) {
				if (a[i][j] != 0) {
					if (check[j] == 0) {
						put(j);
						check[j] = 1;
						parent[j] = i;
					}
				}
			}
		}
	}
	set_path();
	if (i == name2int(T)) return 1;
	else return 0;
}

void network_flow(int c[][MAX_NODE], int f[][MAX_NODE], int r[][MAX_NODE], int V, char S, char T) {
	int i, min;
	clear_matrix(f, V);
	clear_matrix(r, V);
	construct(c, f, r, V);
	while (get_augument_path(r, V, S, T)) {
		min = INT_MAX;
		for (i = 1; path[i] >= 0; i++)
			if (min > r[path[i - 1]][path[i]]) 
				min = r[path[i - 1]][path[i]];
		for (i = 1; path[i] >= 0; i++) {
			f[path[i - 1]][path[i]] = f[path[i - 1]][path[i]] + min;
			f[path[i]][path[i - 1]] = -f[path[i - 1]][path[i]];
		}
		construct(c, f, r, V);
	}
}

int main() {
	int V, E;
	fp = fopen("graph.txt", "r");
	input_Capacity(Capacity, &V, &E);
	network_flow(Capacity, Flow, Residual, V, 'S', 'T');
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++)
			printf("%d\t", Flow[i][j]);
		printf("\n");
	}
}