#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define NUMBER  3
// NUMBER ��� ������ ���������ν� �޾ƾ��ϴ� ����� ���� �ѹ��� ������ �� �ִ�.

typedef struct Report {
	char name[20], number[20];
	float nat, eng, math, tot, avg;
	int grade;
}Report;

//Report��� ����ü�� �����Ѵ�. �� �� char�� name�� number�� �̸��� �й��� �������ְ� float ���� nat, eng, math, tot, avg�� ���� ������ �����Ѵ�. �׸��� ������ ����� ����Ͽ� �����Ѵ�.
//�׸��� int�� grade�� ���߿� ������ �Է��� �� ����ϰ� �ȴ�.

int main() {
	char name[20], number[20];
	float nat, eng, math, tot = 0, avg, grade;
	Report cases[100];
	//Report��� ����ü�� ������ �� 100���� �������ν� 100���� ������ ����� �� �ְ��Ѵ�.
	float grades[100];
	//grades�� ������ �����ϱ� ���ؼ� ���Ǵ� float�� �迭�̴�.
	int max;
	//max�� ���� ����� ���Ǵ� �����̴�.
	for (int i = 0; i < NUMBER; i++) {
		printf("������ �Է��Ͻÿ� : ");
		scanf("%s %s %f %f %f", name, number, &nat, &eng, &math);
		//�̸�, �й�, ������ ������ �Է¹޴´�.
		strcpy(cases[i].name, name);
		strcpy(cases[i].number, number);
		//strcpy�� Ȱ���Ͽ� ���ڿ� name�� number�� �����Ѵ�.
		cases[i].nat = nat;
		cases[i].eng = eng;
		cases[i].math = math;
		//������ ������ �Է��Ѵ�.
		cases[i].tot = nat + eng + math;
		cases[i].avg = cases[i].tot / 3;
		//������ ����� ���� ���� �� �̸� ����ü�� �ְ� �ȴ�.
		grades[i] = cases[i].avg;
		//��հ��� �Ű� ������ ������ �� ����ϰ� �ȴ�.
	}
	for (int j = 0; j < NUMBER; j++) {
		max = j;
		for (int k = 0; k < NUMBER; k++) if (grades[max] < grades[k]) max = k;
		//ó���� ���� ū ���� ���� ��ġ�� ����ϴ� ���� max�̴�.
		cases[max].grade = j + 1;
		//����� ��ġ�� ���� �ֵ� �� ���� ���� ����� �ű��.
		grades[max] = -1;
		//���� ���� ���� ��ġ�� -1�� �ٲپ� ��󿡼� �����Ѵ�.
	}
	for (int l = 0; l < NUMBER; l++) printf("�̸� : %s �й� : %s ���� : %f ���� : %f ���� : %f ��� : %f �հ� : %f ��� : %d\n", cases[l].name, cases[l].number, cases[l].nat, cases[l].eng, cases[l].math, cases[l].avg, cases[l].tot, cases[l].grade);
	//���� ����ϴ� �Լ��̴�.
}