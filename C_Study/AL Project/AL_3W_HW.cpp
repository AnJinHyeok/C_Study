#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int from = 1, by = 2, to = 3;

void move(int from, int to) {
	printf("\nMove from %d to %d", from, to);
}

typedef struct Hanoi_Node {
	int from;
	int by;
	int to;
	int n;
	struct Hanoi_Node* next;
}Hanoi_Node;

typedef struct {
	Hanoi_Node* Top;
}LinkedStackType;

void init(LinkedStackType* s) {
	s->Top = NULL;
}

int empty(LinkedStackType* s) {
	return (s->Top == NULL);
}

void push(LinkedStackType* s, int from, int by, int to, int n) {
	Hanoi_Node* temp = (Hanoi_Node*)malloc(sizeof(Hanoi_Node));
	temp->from = from;
	temp->by = by;
	temp->to = to;
	temp->n = n;
	temp->next = s->Top;
	s->Top = temp;
}

int pop(LinkedStackType* s) {
	if (empty(s)) {
		printf("-1");
		exit(1);
	}
	else {
		Hanoi_Node* temp = s->Top;
		from = temp->from;
		by = temp->by;
		to = temp->to;
		int n = temp->n;
		s->Top = s->Top->next;
		free(temp);
		move(from, to);
		return n;
	}
}

void nor_hanoi() {
	int j = 0, temp;
	printf("\nIf you want to quit, input -1:");
	while (1) {
		printf("\nInput the height of hanoi tower:");
		scanf("%d", &j);
		if (j == -1) break;
		else {
			LinkedStackType Hanoi;
			init(&Hanoi);
			while (1) {
				while (j > 1) {
					push(&Hanoi, from, by, to, j);
					j--;
					temp = to;
					to = by;
					by = temp;
				}
				move(from, to);
				if (!empty(&Hanoi)) {
					j = pop(&Hanoi);
					j--;
					temp = from;
					from = by;
					by = temp;
				}
				else break;
			}
		}
	}
}

void hanoi(int n, int from, int by, int to) {
	if (n == 1) move(from, to);
	else {
		hanoi(n - 1, from, to, by);
		move(from, to);
		hanoi(n - 1, by, from, to);
	}
}

void re_hanoi() {
	int j = 0;
	printf("\nIf you want to quit, input -1:");
	while (1) {
		printf("\nInput the height of hanoi tower:");
		scanf("%d", &j);
		if (j == -1) break;
		else {
			hanoi(j, 1, 2, 3);
		}
	}
}

int main() {
	re_hanoi();
	nor_hanoi();
}