#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float CtoF(int tem) {
	return 1.8 * tem + 32;
}
//������ Ȱ���Ͽ� �������� ȭ���� ��ȯ���ִ� �Լ�

float FtoC(int tem) {
	return (tem - 32) * 5 / 9.0;
}
//������ Ȱ���Ͽ� ȭ������ ������ ��ȯ���ִ� �Լ�

int len(char str[]) {
	return strlen(str);
}
//���ڿ��� ���� ����ϴ� �Լ�, string ����� ���

void switching() {
	int cho, num;
	printf("CtoF�� 1, FtoC�̸� 2�� �����ϼ��� : ");
	scanf("%d", &cho);
	printf("���ڸ� �Է��ϼ��� : ");
	scanf("%d", &num);
	if (cho == 1) printf("ȭ�� %f", CtoF(num));
	else if (cho == 2) printf("���� %f", FtoC(num));
}
//ȭ������ ������ �ٲٴ���, �������� ȭ���� �ٲٴ��� ������ �� �Լ��� Ȱ���� ����ϴ� �Լ��̴�.

void length() {
	char str[1000];
	rewind(stdin);
	gets_s(str);
	printf("���ڿ��� ���̴� %d�Դϴ�.", len(str));
}
//rewind�� ���۸� ��� �Ŀ� gets_s�� ���ڿ��� �ް� len�Լ��� ���̴� ��ȯ�Ѵ�.

void cal() {
	int num, A, B;
	while (1) {
		printf("1:ADD, 2:MUL, 3:quit\t");
		scanf("%d", &num);
		if (num == 3) break;
		scanf("%d %d", &A, &B);
		if (num == 1) printf("%d + %d = %d\n", A, B, A + B);
		else if (num == 2) printf("%d * %d = %d\n", A, B, A * B);
	}
}
//� ������ ���� ���� �ް� 1���̸� ���� ���, 2���̸� ���� ���, �׸��� 3���̸� ����ȴ�.

void count_str() {
	int str_num = 0, word_num = 0, char_num = 0, flag = 0, num = 0;
	char str[1000];
	rewind(stdin);
	gets_s(str);
	char count = str[num];
	while (count != '\0') {
		if (count == '.' || count == '?' || count == '!') str_num++;
		else if (count == ' ' && flag != 0) {
			word_num++;
			flag = 0;
		}
		if(count != ' ') char_num++;
		flag++;
		count = str[++num];
	}
	
	printf("���� ���� : %d, �ܾ� ���� : %d, ���� ���� : %d", str_num, ++word_num, char_num);
}
//rewind�� ���۸� ���� gets_s�� ���ڿ��� ���޹ް� while���� Ȱ���Ͽ� '\0'�� ����Ǳ� ������ �ݺ����� ���� �ǰ� .,?,!�� ã���� ������ ��ģ������ �����Ѵ�.
//�׸��� ' '�� ������ �� �ܾ����� �˰� �Ǹ� �ܾ� ������ �ϳ� ���ϰ� �� �ݺ����� �������� char_num�� ���ؼ� ���� ����ϰ� �ȴ�.

int main() {
	int menu;
	printf("Menu1 : ȭ�� ���� ��ȯ\nMenu2 : ���ڿ��� ����\nMenu3 : ������ ����\nMenu4 : ������ ��, �ܾ� ��, ���� �� ����\nMenu�� �����ϼ��� : ");
	scanf("%d", &menu);

	/*if (menu == 1) switching();
	else if (menu == 2) length();
	else if (menu == 3) cal();
	else if (menu == 4) count_str();*/

	switch (menu) {
	case 1:
		switching();
		break;
	case 2:
		length();
		break;
	case 3:
		cal();
		break;
	case 4:
		count_str();
		break;
	}
}