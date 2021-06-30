#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char int2name(int n) {
	return n + 'A';
}

int name2int(char c) {
	return c - 'A';
}

void downheap(int* a, int N, int k) {
	int i, v;
	v = a[k];
	while (k <= N / 2) {
		i = k << 1;
		if (i < N && a[i] < a[i + 1]) i++;
		if (v >= a[i]) break;
		a[k] = a[i];
		k = i;
	}
	a[k] = v;
}

void heap_sort(int* a, int N) {
	int k, t;

	for (k = N; k >= 1; k--)
		downheap(a, N, k);

	while (N > 1) {
		t = a[1];
		a[1] = a[N];
		a[N] = t;
		downheap(a, --N, 1);
	}
}

int main() {
	//char str[] = "SORTALGORISM";
	int num[6] = { 0,4,5,7,9,3 };
	//int a[100] = {};
	//for (int i = 0; i <= 6; i++)
	//	a[i + 1] = name2int(str[i]);
	heap_sort(num, 5);
	for (int i = 1; i <= 5; i++)
		printf("%d", num[i]);
}