#include <stdio.h>
#include <string.h>

int count(char str[]) {
	int num = 0, i = 0;
	for (i = 0; i < strlen(str); i++) str[i] == ' ' ? num++ : NULL;
	//while (str[i++] != '\0') str[i] == ' ' ? num++ : NULL;
	return num;
}

int main() {
	char str[1001];
	gets_s(str);
	printf("%d", count(str));
}