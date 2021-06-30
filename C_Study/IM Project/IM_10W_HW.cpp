#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void read_file(float* input, int height, int width, char filename[]) {
	int x, y;
	FILE* fp;
	fp = fopen(filename, "r");
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			fscanf(fp, "%f", &input[y * width + x]);
		}
		fscanf(fp, "\n");
	}
	fclose(fp);
}

void insert_sort(float* a, int N) {
	int i, j, t;
	for (i = 1; i < N; i++) {
		t = a[i];
		j = i;
		while (j > 0 && a[j - 1] > t) {
			a[j] = a[j - 1];
			j--;
		}
		a[j] = t;
	}
}

float median(float* a, int x, int y, float *input) {
	int cnt = 0;
	for (int i = y - 1; i < y + 2; i++) {
		for (int j = x - 1; j < x + 2; j++) {
			a[cnt++] = input[i * 45 + j];
		}
	}
	insert_sort(a, 9);
	return a[4];
}

void median_filtering(float* input, float* output, int height, int width) {
	float sort[9] = {};
	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {
			output[y * width + x] = median(sort, x, y, input);
		}
	}
}

void write_file(float* input, int height, int width, char filename[]) {
	int x, y;
	FILE* fp;
	fp = fopen(filename, "w");
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			fprintf(fp, "%d\t", (int)input[y * width + x]);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

int main() {
	int height = 44, width = 45;
	char c_in[] = "noisy_data.txt";
	char c_out[] = "median_noisy_data.txt";
	float* num, *num_out;
	num = (float*)calloc(44*45, sizeof(float));
	num_out = (float*)calloc(44 * 45, sizeof(float));
	read_file(num, height, width, c_in);
	median_filtering(num, num_out, height, width);
	write_file(num_out, height, width, c_out);
}