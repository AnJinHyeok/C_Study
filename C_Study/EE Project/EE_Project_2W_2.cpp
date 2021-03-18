#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*void change(int i, int j, char **str) {
	char temp[10];
	strcpy(temp, *(str+i));
	strcpy(*(str + i), *(str + j));
	strcpy(*(str + j), temp);
}*/

void change(int i, int j, char** str) {
	char temp[10];
	strcpy(temp, str[i]);
	strcpy(str[i], str[j]);
	strcpy(str[j], temp);
}

//(*str)[10]
void sort_al(int number, char **str) {
	for (int i = 0; i < number - 1; i++) for (int j = i + 1; j < number; j++) if (strcmp(str[i], str[j]) > 0) change(i, j, str);
	printf("\n정리된 단어는\n");
	for (int j = 0; j < number; j++) printf("%s\n", str[j]);
}

int main() {
	int number;
	char** str;
	printf("개수를 입력하시오. : ");
	scanf("%d", &number);

	//char str[100][10];
	str = (char**)calloc(number, sizeof(char*));
	for (int i = 0; i < number; i++) str[i] = (char*)calloc(10, sizeof(char));

	for (int i = 0; i < number; i++) scanf("%s", str[i]);
	sort_al(number, str);
	free(str);
}