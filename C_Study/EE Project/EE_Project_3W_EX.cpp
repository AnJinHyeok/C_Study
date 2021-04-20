#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 100
//���� ����� �����Ͽ� ���Ƿ� �ٲ� �� �ְ� �� ���̴�.

/*struct student {
	char grade;
	int mid_term;
	int final_term;
	int attendance;
};*/
//student��� ����ü�� �����ϰ� char�� grade, int�� �߰�, �⸻ ������ attendance�� �����ϰ� �ȴ�.

typedef struct student {
	char grade;
	int mid_term;
	int final_term;
	int attendance;
}STD;
//student ����ü�� STD�� ª�� �����ϰ� �ȴ�.

void ex1() {
	struct student std1;
	//student ����ü�� std1�̶�� �̸����� �����ϰ� �ȴ�.

	std1.grade = 'A';
	std1.mid_term = 97;
	std1.final_term = 92;
	std1.attendance = 10;
	//���� ����ü �����鿡 ������ �����ϰ� �ȴ�.

	printf("std1's grade is %c\n", std1.grade);
	printf("std1's mid_term is %d\n", std1.mid_term);
	printf("std1's final_term is %d\n", std1.final_term);
	printf("std1's attendance is %d\n", std1.attendance);
	//printf�Լ��� Ȱ���ؼ� std1�� ����ִ� ����ü �������� ������ ����ϰ� �ȴ�.
}

//typedef struct student STD;
//student ����ü�� STD �̸� ���̱�

void ex2() {
	STD std1;
	//��κ��� �ڵ�� ex1()�� ���������� STD�� struct student�� ��ü�Ͽ� ���� �ȴ�.

	std1.grade = 'A';
	std1.mid_term = 97;
	std1.final_term = 92;
	std1.attendance = 10;

	printf("std1's grade is %c\n", std1.grade);
	printf("std1's mid_term is %d\n", std1.mid_term);
	printf("std1's final_term is %d\n", std1.final_term);
	printf("std1's attendance is %d\n", std1.attendance);
}

void ex3() {
	STD std1;
	//�ڵ�� ex2()�� ���������� �ѹ��� ����ü���� �� ���ο� �̸��� ���̰� �ȴ�.

	std1.grade = 'A';
	std1.mid_term = 97;
	std1.final_term = 92;
	std1.attendance = 10;

	printf("std1's grade is %c\n", std1.grade);
	printf("std1's mid_term is %d\n", std1.mid_term);
	printf("std1's final_term is %d\n", std1.final_term);
	printf("std1's attendance is %d\n", std1.attendance);
}

void ex4() {
	STD student[10];
	//STD ����ü�� student��� �̸��� 10�� ����ü�� �����Ѵ�.
	int fi;
	int sum;

	srand((unsigned)time(NULL));
	//���� �Լ��� ����ϱ� ���� ����

	for (fi = 0; fi < 10; fi++) {
		student[fi].mid_term = rand() % 46;
		student[fi].final_term = rand() % 46;
		student[fi].attendance = rand() % 11;
		sum = student[fi].mid_term + student[fi].final_term + student[fi].attendance;
		//�����Լ��� ���ؼ� mid_term ������ final_term ������ �Է��ϰ� attendance�� �Է��ϰ� �ȴ�. �� ���� sum ���� �� 3������ ��� ���� ���� ����ִ´�.

		if (sum > 80) student[fi].grade = 'A';
		else if (sum > 70) student[fi].grade = 'B';
		else if (sum > 60) student[fi].grade = 'C';
		else if (sum > 50) student[fi].grade = 'D';
		else student[fi].grade = 'F';
		//if else ���� Ȱ���� �հ谡 80�� �̻��� A, 10�� ���� B, C, D ������ �ޱ�� 50�� ���� F ������ �ޱ�� �ȴ�.

		printf("student %d's grade is %c\n", fi, student[fi].grade);
		printf("student %d's total grade is %d\n\n", fi, sum);
		//�� ���� ����Ѵ�.
	}
}

void ex5(int argc, char* argv[]) {
	int fi;
	printf("main function get %d argv\n", argc);
	for (fi = 0; fi < argc; fi++) printf("argv[%d] : %s\n", fi, argv[fi]);
	//argv ���� argc ���� Ȱ���� for���� �����ϰ� argv ���� ��� ����ϰ� �ȴ�.
}

int ex6() {
	int fi;
	int* ptr = NULL;
	int size = 0;

	srand((unsigned)time(NULL));
	//���� �Լ� Ȱ���� ���� ����

	while (size <= 0) {
		printf("size for memory : ");
		scanf("%d", &size);
		if (size <= 0) printf("\n size must be bigger than 0\n");
	}
	//size�� �Է¹޴� while�� �̰� ����� �� size ���� �ԷµǸ� while���� �����Ѵ�.

	ptr = (int*)malloc(size * sizeof(int));
	//int�� ������ ptr�� size ũ���� int�� ���� �Ҵ��� �ϴ� �ڵ��̴�.

	if (ptr == NULL) {
		printf("FAIL : CANNOT ASSIGN!!\n");
		return -1;
	}
	//ptr�� �״�� NULL�� ��� ������ ������ �˸���.
	for (fi = 0; fi < size; fi++) {
		ptr[fi] = rand() % 101;
		printf("ptr[%3d] = %3d\n", fi, ptr[fi]);
	}
	//ptr �迭�� rand �Լ��� Ȱ���� ���� ����ְ� �̸� ����Ѵ�.
	free(ptr);
	//�����Ҵ��� �����ϴ� �Լ�
	return 0;
}

int ex7() {
	FILE* fp;
	//���� �����͸� �����Ѵ�.
	const char* str = "The Key to realizing a dream is to focus not on success but significance - and then even the small steps and little victories along your path will take on greater meaning.";
	char buf[200];
	int fi;

	fp = fopen("test_text.txt", "wt");
	//������ ���� ���� �����Ѵ�.
	if (fp == NULL) {
		printf("Fail to open file\n");
		return -1;
	}
	//���� ���� ���¿� �������� ��� �˷��ִ� �Լ�

	fputc('T', fp);
	fputc('E', fp);
	fputc('S', fp);
	fputc('T', fp);
	fputc('\n', fp);
	//fputc�� Ȱ���Ͽ� �۾��� ���Ͽ� �����Ѵ�.

	fputs(str, fp);
	//fputs �Լ��� Ȱ���� ���� �����ص� str �迭�� �����Ѵ�.

	fclose(fp);
	//������ �ݴ´�.

	fp = fopen("test_text.txt", "rt");
	//������ �б���� �����Ѵ�.

	for (fi = 0; fi < 5; fi++) printf("%c", fgetc(fp));
	//5�� fp�� �ҷ��´�.
	fgets(buf, 200, fp);
	//buf ���ڿ��� fgets�� ������ �ҷ��´�.
	printf("%s", buf);
	fclose(fp);
	return 0;
}

int ex8() {
	FILE* fp;
	const char* str = "The Key to realizing a dream is to focus not on success but significance - and then even the small steps and little victories along your path will take on greater meaning.";
	char buf[200];
	int fi;

	fp = fopen("test_text.txt", "wt");
	if (fp == NULL) {
		printf("Fail to open file\n");
		return -1;
	}

	fputc('T', fp);
	fputc('E', fp);
	fputc('S', fp);
	fputc('T', fp);
	fputc('\n', fp);

	fputs(str, fp);

	fclose(fp);
	//���� 7���̶� ����

	fp = fopen("test_text.txt", "wt");
	//rt�� ���°� �ƴ� �ٽ� ������� ����. �̶� test_text ������ ���������� �׾ȿ� �ƹ��͵� �������� �ʴ�.

	fclose(fp);
	return 0;
}

int ex9() {
	FILE* fp;
	STD st;
	fp = fopen("student.txt", "wt");
	if (fp == NULL) printf("Fail to open file\n");
	//student.txt��� ������ ���� �������� ���� �ȴ�.

	st.grade = 'B';
	st.mid_term = 56;
	st.final_term = 72;
	st.attendance = 10;
	//����ü�� ������ ��Ҹ� �Է��Ѵ�.

	fprintf(fp, "grade is %c\n", st.grade);
	fprintf(fp, "mid_term is %d\n", st.grade);
	fprintf(fp, "final_term is %d\n", st.grade);
	fprintf(fp, "attendance is %d\n", st.attendance);
	//������ ��Ҹ� fprintf�� Ȱ���Ͽ� ���Ͽ� �����Ѵ�.

	fclose(fp);
	//������ �ݴ´�.

	return 0;
}

int ex10() {
	FILE* ori;
	FILE* cp;
	char buffer[BUF_SIZE];
	int count;

	ori = fopen("student.txt", "rb");
	cp = fopen("copy.txt", "wb");
	//ori�� �б� ���·� ������ ������ cp�� ���� ���·� ������ ������.

	if (ori == NULL || cp == NULL) {
		printf("Fail to open file\n");
		return -1;
	}
	//������ ������ ��� �������� �˷��ִ� �Լ�

	while (1) {
		count = fread(buffer, 1, BUF_SIZE, ori);
		//ori���� fread�� Ȱ���� ���� �о���� �ȴ�.
		if (count < BUF_SIZE) {
			if (feof(ori) != 0) {
				fwrite(buffer, 1, count, cp);
				printf("Copy success!!\n");
				break;
			}
			else {
				printf("Copy FAIL!!\n");
				break;
			}
		}
		//count�� buf_size���� ���� ��� ori�� ������� ������ fwrite�� Ȱ���� cp�� �ű�� ����ִٸ� copy�� ���������� �˸���.
		else fwrite(buffer, 1, BUF_SIZE, cp);
		//fwite�� Ȱ���ؼ� cp�� ���� �����Ѵ�.
	}
	fclose(ori);
	fclose(cp);
	//�ΰ��� ������ �����Ѵ�.
	return 0;
}

int main(int argc, char *argv[]) {
	//ex1();
	//ex2();
	//ex3();
	//ex4();
	//ex5(argc, argv);
	//ex6();
	//ex7();
	//ex8();
	//ex9();
	ex10();
}