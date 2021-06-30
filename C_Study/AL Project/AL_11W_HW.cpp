#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODE 100
#define INFINITE 1000
FILE* fp;
int g[MAX_NODE][MAX_NODE];

char int2name(int n) {
	return n + 'A';
}

int name2int(char c) {
	return c - 'A';
}

void input_adjmatrix(int g[][MAX_NODE], int* V, int* E) {
	char vertex[3];
	int i, j, k, w;
	printf("\nInput number of nodes & edges\n");
	fscanf(fp, "%d %d", V, E);
	for (i = 0; i < *V; i++)
		for (j = 0; j < *V; j++)
			g[i][j] = INFINITE;
	for (i = 0; i < *V; i++)
		g[i][i] = 0;
	for (k = 0; k < *E; k++) {
		printf("\nInput two nodes consisting of edge -> ");
		fscanf(fp, "%s %d", vertex, &w);
		i = name2int(vertex[0]);
		j = name2int(vertex[1]);
		g[i][j] = w;
	}
}

void floyd(int d[][MAX_NODE], int V) {
	int x, y, k;
	for (y = 0; y < V; y++)
		for (x = 0; x < V; x++)
			for (k = 0; k < V; k++)
				if (d[x][y] + d[y][k] < d[x][k])
					d[x][k] = d[x][y] + d[y][k];
}

int main() {
	int V, E;
	fp = fopen("graph.txt", "r");
	input_adjmatrix(g, &V, &E);
	floyd(g, V);
	for (int i = 0; i < V; i++) {
		printf("\n");
		for (int j = 0; j < V; j++)
			printf("%d\t", g[i][j]);
	}
}