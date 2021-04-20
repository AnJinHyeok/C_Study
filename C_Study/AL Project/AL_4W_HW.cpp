/*#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BLK 20

int recursive_line(int* canvas, int x1, int y1, int x2, int y2) {
	if (abs(x1 - x2) * abs(x1 - x2) + abs(y1 - y2) * abs(y1 - y2) < 1) return 1;
	else {
		float x = (x1 + x2) / 2.0, y = (y1 + y2) / 2.0;
		canvas[(int)y * BLK + (int)x] = 1;
		if (fabs(x1 - x) * fabs(x1 - x) + fabs(y1 - y) * fabs(y1 - y) > 1) recursive_line(canvas, x1, y1, (int)x, (int)y);
		if (fabs(x2 - x) * fabs(x2 - x) + fabs(y2 - y) * fabs(y2 - y) > 1) recursive_line(canvas, (int)x, (int)y, x2, y2);
	}
}

int main() {
	int i, j;
	int* canvas = (int*)calloc(BLK * BLK, sizeof(int));

	canvas[15 * BLK + 15] = 1;
	recursive_line(canvas, 1, 1, 15, 15);

	for (i = 0; i < BLK; i++) {
		for (j = 0; j < BLK; j++) printf("%-2d", canvas[i * BLK + j]);
		printf("\n");
	}
	free(canvas);
}*/
//직선 그리기 알고리즘

#include <stdio.h>
#include <stdlib.h>

int region_labeling(int (*seed)[7], int x, int y) {
	if (seed[y][x] == 0 || seed[y][x] == 2) return 1;
	else {
		seed[y][x] = 2;
		region_labeling(seed, x - 1, y);
		region_labeling(seed, x, y - 1);
		region_labeling(seed, x + 1, y);
		region_labeling(seed, x, y + 1);
		region_labeling(seed, x - 1, y - 1);
		region_labeling(seed, x + 1, y - 1);
		region_labeling(seed, x - 1, y + 1);
		region_labeling(seed, x + 1, y + 1);
	}
}

int main() {
	int seed[7][7] = { {0,0,0,0,0,0,0},{0,0,0,1,0,0,0},{0,0,0,1,0,0,0},{0,1,1,1,1,0,0},{0,0,0,0,0,1,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0} };

	region_labeling(seed, 3, 1);
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) printf("%-2d", seed[i][j]);
		printf("\n");
	}
}
