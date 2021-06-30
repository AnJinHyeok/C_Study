#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "BTS_library.h"

typedef struct _wcount {
	int count;
	char word[20];
}wcount;

node* head;
const char delim[] = " \t\r\n,.-";

int wcount_cmp(const void *a, const void *b){
	return strcmp(((wcount*)a)->word, ((wcount*)b)->word);
}

void print_wcount(void* a) {
	printf("%s : %d\n", ((wcount*)a)->word, ((wcount*)a)->count);
}

void main() {
	int i, num = 0, cnt = 0;

	char* tok;
	char str[256];
	wcount wc, * wcp;

	init_tree(&head);

	FILE* fp;
	fp = fopen("test.txt", "r");

	fgets(str, 256, fp);
	while (!feof(fp)) {
		tok = strtok(str, delim);
		while (tok) {
			strcpy(wc.word, tok);
			wcp = (wcount*)btv_search(&wc, head, &num, sizeof(wcount), wcount_cmp);

			if (wcp == NULL) {
				wc.count = 1;
				btv_insert(&wc, head, &num, sizeof(wcount), wcount_cmp);
			}
			else
				(wcp->count)++;
			tok = strtok(NULL, delim);
		}
		fgets(str, 256, fp);
	}
	printf("\n");
	btv_sort_list(head->left, print_wcount);
}