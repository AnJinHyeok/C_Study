#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE 100
#define INFINITE 1000

int distance[MAX_NODE], parent[MAX_NODE], check[MAX_NODE];
FILE* fp;
int a[MAX_NODE][MAX_NODE] = {};

char int2name(int i) {
	return i + 'A';
}

int name2int(char c) {
	return c - 'A';
}

void adjmatrix(int* V, int* E) {
	char vertex[3];
	int i, j, w;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			if(i != j) 
				a[i][j] = INFINITE;
	for (j = 0; j < *E; j++) {
		printf("\nInput two nodes of edge and weight -> ");
		fscanf(fp, "%s %d", vertex, &w);
		a[name2int(vertex[0])][name2int(vertex[1])] = w;
		a[name2int(vertex[1])][name2int(vertex[0])] = w;
	}
}

void print_distance(int* distance, int s, int V) {
	printf("\n");
	for (int i = 0; i < V; i++)
		printf("%d\t", distance[i]);
}

void dijkstra(int s, int V) {
	int x = 0, y, d;
	int i, checked = 0;
	for (x = 0; x < V; x++) {
		distance[x] = a[s][x];
		if (x != s) parent[x] = s;
	}
	check[s] = 1;
	checked++;

	print_distance(distance, s, V);

	while (checked < V) {
		x = 0;
		while (check[x]) x++;
		for (i = x; i < V; i++)
			if (check[i] == 0 && distance[i] < distance[x]) 
				x = i;
		check[x] = 1;
		checked++;

		for (y = 0; y < V; y++) {
			if (x == y || a[x][y] >= INFINITE || check[y]) continue;
			d = distance[x] + a[x][y];
			if (d < distance[y]) {
				distance[y] = d;
				parent[y] = x;
			}
		}
		print_distance(distance, x, V);
	}
}

void print_parent(int V) {
	for (int i = 0; i < V; i++)
		printf("\n%c", int2name(parent[i]));
}

int main() {
	int V, E;
	fp = fopen("graph.txt", "rt");
	adjmatrix(&V, &E);
	dijkstra(5, V);
	print_parent(V);
}