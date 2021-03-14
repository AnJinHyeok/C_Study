#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char *dice_name[6] = {"ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX" };

int main() {
	int* dice = (int*)calloc(6, sizeof(int));
	int count, number;
	scanf("%d", &count);
	for (int i = 1; i <= count; i++) {
		number = rand() % 6;
		(*(dice + number))++;
	}
	for (int j = 0; j < 6; j++) {
		printf("%s는 %d번 나왔습니다.\n", dice_name[j], *(dice + j));
	}
	free(dice);
}