#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>

LARGE_INTEGER freq, start, stop;
double diff;

int larusse(int A, int B) {
	int C, sum = 0;
	while (A != 0) {
		if (A % 2 == 1) {
			C = B;
			sum += C;
		}
		A /= 2;
		B *= 2;
	}
	return sum;
}

int larusse_shift(int A, int B) {
	int C, sum = 0;
	while (A != 0) {
		if (A % 2 == 1) {
			C = B;
			sum += C;
		}
		A >>= 1;
		B <<= 1;
	}
	return sum;
}

int main() {
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	int num1, num2;
	scanf("%d %d", &num1, &num2);
	/*for (int i = 1; i < 100000000; i++)
		larusse(num1, num2);
		larusse_shift(num1, num2);*/
	printf("%d", larusse(num1, num2));
	printf("%d", larusse_shift(num1, num2));

	QueryPerformanceCounter(&stop);
	diff = (double)(stop.QuadPart - start.QuadPart) / freq.QuadPart;
	printf("\n%lf", diff);
}