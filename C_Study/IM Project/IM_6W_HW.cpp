#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	char equ;
	struct _node *next;
}node;

node* head, * tail;

void init_stack() {
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	tail->next = tail;
	head->next = tail;
}

char pop() {
	node *t;
	char c;
	t = head->next;
	if (t == tail)
		return -1;
	else
	{
		head->next = t->next;
		c = t->equ;
		free(t);
		return c;
	}
}

void push(char c) {
	node* t;
	t = (node*)calloc(1, sizeof(node));
	t->equ = c;
	t->next = head->next;
	head->next = t;
}

void postfix(char* dst, char* src) {
	char c;
	init_stack();

	while (*src) {
		if (*src == ')') {
			*dst++ = pop();
			*dst++ = ' ';
			src++;
		}
		else if (*src == '+' || *src == '-' || *src == '*' || *src == '/') {
			push(*src);
			src++;
		}
		else if (*src >= '0' && *src <= '9') {
			do {
				*dst++ = *src++;
			} while (*src >= '0' && *src <= '9');
			*dst++ = ' ';
		}
		else
			src++;
	}
	*dst = 0;
}

void main() {
	char exp[256];
	char src[256] = "(1+(2*3))";

	postfix(exp, src);
	printf("Postfix representation : %s\n", exp);
}