#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "RB_Tree.h"

char word[20];

const char delim[] = " \t\r\n,.-";

int br_cmp(const void* a, const void* b) {
	return strcmp((char*)a, (char*)b);
}

void print_br(void* a, void* b) {
	printf("%s : %d\n", (char*)a, ((node*)b)->red);

}

void main() {
	int num = 0;

	char* tok;
	char str[256];
	char rb[20];
	
	init_tree(&head);

	FILE* fp;
	fp = fopen("test.txt", "r");

	while (!feof(fp)) {
		fgets(str, 256, fp);
		tok = strtok(str, delim);
		while (tok) {
			strcpy(rb, tok);
			rbti_insert(&rb, head, &num, sizeof(rb), br_cmp);
			tok = strtok(NULL, delim);
		}
	}
	fclose(fp);
	printf("\n");
	br_sort_list(head->left, print_br);
}