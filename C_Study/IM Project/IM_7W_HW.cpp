#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct _node {
	char data;
	struct _node *left;
	struct _node* right;
}node;

node* head, * tail;
node* stack[MAX];
int top;
node s;

void init_stack() {
	top = -1;
}

void init_tree() {
	head = (node*)calloc(1, sizeof(node));
	tail = (node*)calloc(1, sizeof(node));
	head->left = tail;
	head->right = tail;
	tail->left = tail;
	tail->right = tail;
}

int push(node *tree) {
	if (top >= MAX - 1) {
		printf("overflow");
		return -1;
	}
	stack[++top] = tree;
	return 1;
}

node* pop() {
	node* t;
	if (top <= -1) {
		printf("underflow");
		return NULL;
	}
	t = stack[top--];
	return t;
}

node* make_tree(char *str) {
	while (1) {
		node* t;
		t = (node*)calloc(1, sizeof(node));
		if (*str == '+' || *str == '-' || *str == '*' || *str == '/') {
			t->right = pop();
			t->left = pop();
			t->data = *str;
			push(t);
			str++;
		}
		else if (*str >= 'A' && *str <= 'Z') {
			t->data = *str;
			t->left = tail;
			t->right = tail;
			push(t);
			str++;
		}
		else {
			str++;
			free(t);
		}
		if (*str == NULL)
			return pop();
	}
}

node* queue[MAX];
int front, rear;

void init_queue() {
	front = rear = 0;
}

int is_queue_empty() {
	return (front == rear);
}

node *put(node* t) {
	queue[rear] = t;
	rear = ++rear % MAX;
	return t;
}

node* get() {
	node* t;
	t = queue[front];
	front = ++front % MAX;
	return t;
}

void visit(node* t) {
	printf("-> %c ", t->data);
}

void levelorder_traverse(node* t) {
	put(t);

	while (!is_queue_empty()) {
		t = get();
		visit(t);

		if (t->left != tail)
			put(t->left);
		if (t->right != tail)
			put(t->right);
	}
}

int main() {
	char str[200];
	gets_s(str);

	if (*str == NULL) return -1;
	init_stack();
	init_tree();
	init_queue();
	head->right = make_tree(str);

	levelorder_traverse(head->right);
}