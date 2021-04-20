#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define STDNUM 96

void ex1() {
	int fi;
	int std[STDNUM] = { 0, }; //{0,}�� Ȱ���Ͽ� ������ �迭 ��ü�� 0���� �ʱ�ȭ���ش�.
	srand((unsigned)time(NULL)); //srand �Լ��� ���� �߻��Լ��� �õ带 �����ϵ��� �����ϴ� �Լ��̴�.

	printf("sizeof(std[0]) = %d\n", sizeof(std[0])); //������ �迭���� �ϳ��� ���� ������ �̹Ƿ� int ������� �����ϴ�.
	printf("sizeof(std) = %d\n", sizeof(std)); //������ �迭 ��ü ����� ����ϴ� ���̹Ƿ� int ����� 96���� ���� ���� 384�� ������ �ȴ�.
	printf("sizeof(std)/sizeof(std[0]) = %d\n", sizeof(std) / sizeof(std[0])); //��ü ���̸� int�� ������� ���������Ƿ� STDNUM�� ������ �ȴ�.

	for (fi = 0; fi < STDNUM; fi++) {
		std[fi] = rand() % 101; //rand()�Լ����� ���Ƿ� ������ ���ڸ� 101�� �������� �������ν� 0���� 100���� ������ �Լ��� std �迭�� �����ϰ� �ȴ�.
		printf("student %2d's grade is %3d\n", fi, std[fi]); //������ std �迭�� �ϳ��� ����ϴ� �Լ��̴�.
	}
}

void ex2() {
	char str[100];
	printf("Plz input your text : ");
	scanf("%[^\n]s", str); //%[^\n]s�� \n�� �����ϰ� ��� ���ڸ� ������� �ǹ��̴�. ���� ������ scanf�� ������ ���� �� �������� �� �Լ��� �����ϸ� ���鵵 �����ؼ� ���� �� �ִ�.
	printf("your text is : %s", str); //str �� ���
}

void ex3() {
	int a = 10;
	double b = 7.25;

	int* pt_a; //������ ������
	double* pt_b; //�Ǽ��� ������

	pt_a = &a; //a�� �ּҸ� pt_a�� ����
	pt_b = &b; //b�� �ּҸ� pt_b�� ����

	printf("sizeof(pt_a) = %d\n", sizeof(pt_a)); //ũ��� 4����Ʈ�� ���´�.
	printf("sizeof(pt_b) = %d\n\n", sizeof(pt_b)); //���� ������ 4����Ʈ�̴�.
	printf("int a = %d\n", a); 
	printf("double b = %lf\n\n", b);

	printf("a's address = %p\n", pt_a); //pt_a�� �ּ� ���
	printf("b's address = %p\n\n", pt_b); //pt_b�� �ּ� ���

	a = 12; 
	*pt_a = 15;
	b = 8.5;
	*pt_b = 10.75;
	//a�� 12�� �ٲ����� a�� �ּҸ� ������ �ִ� pt_a�� 15�� �ٲ���� ������ 15�� ���������� �ٲ�
	//b�� 8.5�� �ٲ����� b�� �ּҸ� ������ �ִ� pt_b�� 10.75�� �ٲ���� ������ 10.75�� ���������� �ٲ�

	printf("int a = %d\n", a);
	printf("double b = %lf\n\n", b);
}

void ex4() {
	int arr[100];
	int* ptr_arr;
	int fi;

	srand((unsigned)time(NULL)); //srand �Լ��� ���� �߻��Լ��� �õ带 �����ϵ��� �����ϴ� �Լ��̴�.

	ptr_arr = &arr[0]; //������ ptr_arr�� arr�� ù��° �� �ּҸ� �����Ѵ�.

	printf("address of arr[0] is %p\n", &arr[0]);
	printf("arr if pointing %p\n", arr);
	printf("ptr_arr is pointing %p\n", ptr_arr);
	printf("\n");
	//arr[0]�� �ּҴ� arr�� ���� �ּҿ� �����ϰ� ptr_arr�� arr�� �ּҸ� ������ ������ �̹Ƿ� 3�� ��� ������ �ּҸ� ����ϰ� �ȴ�.

	printf("address of arr[1] is %p\n", &arr[1]);
	printf("arr+1 if pointing %p\n", arr+1);
	printf("ptr_arr+1 is pointing %p\n", ptr_arr+1);
	printf("\n");
	//�� �迭�� int�� �迭�̹Ƿ� ���̴� 4�̰� ���� ���� arr�� �ּҺ��� 4 �� �ռ��ִ� �ּҰ� ��µȴ�.

	for (fi = 0; fi < 100; fi++) arr[fi] = rand() % 101;
	printf("arr[0] = %d\n", arr[0]);
	printf("*arr = %d\n", *arr);
	printf("*ptr_arr = %d\n", *ptr_arr);
	//for���� Ȱ���Ͽ� ���� ���� arr �迭�� �ְ� arr[0]�� ���� ����ϴ� ���̹Ƿ� ��� ������ ���� ������ �ȴ�.

	printf("\n");
	
	printf("arr[20] = %d\n", arr[20]);
	printf("*(arr+20) = %d\n", *(arr + 20));
	printf("*(ptr_arr+20) = %d\n", *(ptr_arr + 20));
	printf("*arr+20 = %d\n", *arr + 20);
	printf("*ptr_arr+20 = %d\n", *ptr_arr + 20);
	//ó�� 3���� 20��°�� ����� ���� ���� ��µǰ� ������ 4��° �ڵ�� ���� ù��° �ּҿ� ����ִ� ���� 20�� ���Ѱ��� ������ �ǰ� 5��° �ڵ� ���� ���������̴�.
}

void addNmul(int a, int b, int* a_add_b, int* a_mul_b) {
	*a_add_b = a + b;
	*a_mul_b = a * b;
	//���� �����ͷ� �޾� ���� ���������ش�. �̴� �������� �����̱� ������ �Լ��� �������� �����ȴ�.
}

void inc_CBV(int a) {
	a++;
	//�������� a�� ������Ų��.
}

void inc_CBR(int* a) {
	(*a)++;
	//�޾ƿ� �ּҸ� ���������� ��ȭ��Ų��.
}

void ex5() {
	int a, b;
	int add, mul;
	printf("input a : ");
	scanf("%d", &a);
	printf("input b : ");
	scanf("%d", &b);
	//a�� b�� ���� �޾ƿ��� �Լ����̴�.

	printf("a is %d and b is %d\n\n", a, b);

	inc_CBV(a);
	inc_CBR(&b);
	//inc_CBV�� �μ��� �״�� �����ؼ� a++���ִ� �Լ��̱� ������ a�� �������� ��ȭ�� ������ ���Ѵ�.
	//������ inc_CBR�� �����ͷ� ���޹ޱ� ������ b�ּҿ� ���� �����ؼ� ���� �ٲ��ش�.

	printf("Now a is %d and b is %d\n\n", a, b);
	//���� a�� �״�� 10�̰� b�� �ϳ� ������ 20�� �ȴ�.

	addNmul(a, b, &add, &mul);
	//���� �����ְ� ���ؼ� �������ִ� �Լ��̴�.

	printf("add : %d\n", add);
	printf("mul : %d\n", mul);
}

int main() {
	//ex1();
	ex2();
	//ex3();
	//ex4();
	//ex5();
}