#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
	int key;
	struct _node* next;
}node_s;

node_s* head_s, * tail_s;

void init_list() {
	head_s = (node_s*)calloc(1, sizeof(node_s));
	tail_s = (node_s*)calloc(1, sizeof(node_s));
	head_s->next = tail_s;
	tail_s->next = tail_s;
}

node_s* insert_after(int k, node_s* t) {
	node_s* temp;
	temp = (node_s*)calloc(1, sizeof(node_s));
	temp->key = k;
	temp->next = t->next;
	t->next = temp;
	return temp;
}

int delete_next(node_s* t) {
	node_s* temp;
	if (t->next == tail_s) return 0;
	temp = t->next;
	t->next = t->next->next;
	free(temp);
	return 1;
}

node_s* find_node(int k) {
	node_s* temp;

	temp = head_s->next;
	while (temp->key != k && temp != tail_s) temp = temp->next;
	return temp;
}

int delete_node(int k) {
	node_s* s, * p;
	p = head_s;
	s = p->next;
	while (s->key != k && s != tail_s) {
		p = p->next;
		s = p->next;
	}
	if (s != tail_s) {
		p->next = s->next;
		free(s);
		return 1;
	}
	else return 0;
}

node_s* insert_node(int t, int k) {
	node_s* s, * p, * r;
	p = head_s;
	s = p->next;
	while (s->key != k && s != tail_s) {
		p = p->next;
		s = p->next;
	}
	if (s != tail_s) {
		r = (node_s*)calloc(1, sizeof(node_s));
		r->key = t;
		p->next = r;
		r->next = s;
	}
	return p->next;
}

node_s* ordered_insert(int k) {
	node_s* s, * p, * r;
	p = head_s;
	s = p->next;
	while (s->key <= k && s != tail_s) {
		p = p->next;
		s = p->next;
	}
	r = (node_s*)calloc(1, sizeof(node_s));
	r->key = k;
	p->next = r;
	r->next = s;
	return r;
}

node_s* delete_all() {
	node_s* s, * t;
	t = head_s->next;
	while (t != tail_s) {
		s = t;
		t = t->next;
		free(s);
	}
	head_s->next = tail_s;
	return head_s;
}

void print_list(node_s* t) {
	while (t != tail_s) {
		printf("%-8d", t->key);
		t = t->next;
	}
}

int finding_node(int k, node_s* t) {
	int count = 0;
	while (t->key != k && t->next != NULL) {
		count++;
		t = t->next;
	}
	return count;
}

int main() {
	node_s* t;

	init_list();
	insert_after(9, head_s);
	insert_after(3, head_s);
	insert_after(5, head_s);
	insert_after(1, head_s);
	insert_after(7, head_s);

	print_list(head_s->next);
	printf("\n5를 담고 있는 list의 위치는 %d 입니다.", finding_node(5, head_s));
	insert_node(6, 5);
	printf("\n");
	print_list(head_s->next);
	delete_node(5);
	printf("\n");
	print_list(head_s->next);
	delete_all();
}