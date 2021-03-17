#include <stdio.h>

#define ROWS	4
#define COLS	3

int m[ROWS][COLS] = { {1,3,5},{9,7,3},{3,3,9},{2,8,6} };

float get_row_avg(int m[][COLS], int r) {
	int* start, * end;
	float avg = 0;

	start = *(m + r - 1);
	end = *(m + r - 1) + COLS  - 1;

	while (start <= end) {
		avg += *start;
		start++;
	}

	avg /= COLS;

	return avg;
}

int main() {
	for(int i = 1; i <= 4; i++) printf("%d¹øÂ° AVG : %f\n", i, get_row_avg(m, i));
}