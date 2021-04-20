#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//���� ������ ���� 1�� ��ġ�� ����� ������� ������ �����ϵ��� �ϰڽ��ϴ�.

#define NUMBER  10

typedef struct Report {
	char name[20], number[20];
	float nat, eng, math, tot, avg;
	int grade;
}Report;

int main() {
	Report cases[100];
	float grades[100];
	int max, flag = 0;
	char buf[200];
	//buf �迭�� ���Ͽ��� ���� �о�� �Ŀ� �����ϱ� ���� �����̴�.
	char* count, *count_st;
	//�ܾ ����� ���ؼ� ������ �����̴�.

	FILE* fp;
	//������ �ҷ����� ���ؼ� fp ��� �����͸� �����Ѵ�.
	fp = fopen("test.txt", "rt");
	//fp�� test.txt������ �б� ���� �ҷ��´�.
	if (fp == NULL) {
		printf("Fail to open file\n");
		return -1;
	}
	//���� fp�� ������ �ҷ����°� �������� ��쿡�� Fail to open file�̶�� ������ ����ϰ� ���ִ� if���̴�.
	for (int i = 0; i < NUMBER; i++) {
		fgets(buf, 100, fp);
		//���Ͽ��� ������ �ҷ��ͼ� buf�� �����Ѵ�.
		count_st = count = buf;
		//count_st�� count�� �ּҸ� buf ó�� �ּҷ� �����Ѵ�.
		while (*count != '\0') {
			//count�� �ι��ڸ� ����ų ������ �ݺ��Ѵ�.
			while (*count != ' ' && *count != '\n' && *count != '\0') count++;
			//count�� ' '�̰ų� '\n'�̰ų� �ι����� ���� count�� �ּҸ� �ϳ� ���������ִ� �Լ��̴�.
			if (*count == ' ' && flag == 0) {
				*count = '\0';
				strcpy(cases[i].name, count_st);
				count++;
				count_st = count;
				flag++;
			}
			//���� �����ε� flag�� 0�� ��� �̸��̹Ƿ� strcpy�� count�ڸ��� �� ���ڸ� �־��� �Ŀ� strcpy�� Ȱ���Ͽ� name�� �־��ְ� count�� �ּҿ� flag�� �ּҸ� ������Ű�� count_st�� count�� �ּҸ� �������ش�.
			else if (*count == ' ' && flag == 1) {
				*count = '\0';
				strcpy(cases[i].number, count_st);
				count++;
				count_st = count;
				flag++;
			}
			//flag�� 1�̸� number�� �����ϰ� �Ȱ��� ���Ѵ�.
			else if (*count == ' ' && flag == 2) {
				*count = '\0';
				cases[i].nat = atoi(count_st);
				count++;
				count_st = count;
				flag++;
			}
			//flag�� 2�̸� atoi �Լ��� Ȱ���Ͽ� ���ڿ��� ���ڷ� �ٲٰ� �̸� nat�� �����Ѵ�.
			else if (*count == ' ' && flag == 3) {
				*count = '\0';
				cases[i].eng = atoi(count_st);
				count++;
				count_st = count;
				flag++;
			}
			//flag�� 3�̸� atoi �Լ��� Ȱ���Ͽ� ���ڿ��� ���ڷ� �ٲٰ� �̸� eng�� �����Ѵ�.
			else if ((*count == '\n' || *count == '\0') && flag == 4) {
				*count = '\0';
				cases[i].math = atoi(count_st);
				count++;
				count_st = count;
				flag++;
			}
			//flag�� 4�̰� �� �����̰ų� '\n'�̸� atoi�� ���ڷ� �ٲ� math�� �������ش�.
		}
		cases[i].tot = cases[i].nat + cases[i].eng + cases[i].math;
		cases[i].avg = cases[i].tot / 3;
		//tot�� avg�� �����ִ� �ڵ��̴�.
		grades[i] = cases[i].avg;
		flag = 0;
	}
	for (int j = 0; j < NUMBER; j++) {
		max = j;
		for (int k = 0; k < NUMBER; k++) if (grades[max] < grades[k]) max = k;
		cases[max].grade = j + 1;
		grades[max] = -1;
	}
	//grade ���� ����� 1�� ������ ����.
	fclose(fp);
	//���� �б��带 �����Ѵ�.
	fp = fopen("test_text.txt", "wt");
	//���� ���� ��带 �����Ѵ�.
	if (fp == NULL) {
		printf("Fail to open file\n");
		return -1;
	}
	for (int l = 0; l < NUMBER; l++) fprintf(fp, "�̸� : %s �й� : %s ���� : %f ���� : %f ���� : %f ��� : %f �հ� : %f ��� : %d\n", cases[l].name, cases[l].number, cases[l].nat, cases[l].eng, cases[l].math, cases[l].avg, cases[l].tot, cases[l].grade);
	//���Ͽ� ���� �����̴�.
	fclose(fp);
}