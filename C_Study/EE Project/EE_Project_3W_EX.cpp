#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUF_SIZE 100
//버퍼 사이즈를 정의하여 임의로 바꿀 수 있게 한 것이다.

/*struct student {
	char grade;
	int mid_term;
	int final_term;
	int attendance;
};*/
//student라는 구조체를 선언하고 char형 grade, int형 중간, 기말 점수와 attendance를 저장하게 된다.

typedef struct student {
	char grade;
	int mid_term;
	int final_term;
	int attendance;
}STD;
//student 구조체를 STD로 짧게 정의하게 된다.

void ex1() {
	struct student std1;
	//student 구조체를 std1이라는 이름으로 선언하게 된다.

	std1.grade = 'A';
	std1.mid_term = 97;
	std1.final_term = 92;
	std1.attendance = 10;
	//각각 구조체 변수들에 값들을 대입하게 된다.

	printf("std1's grade is %c\n", std1.grade);
	printf("std1's mid_term is %d\n", std1.mid_term);
	printf("std1's final_term is %d\n", std1.final_term);
	printf("std1's attendance is %d\n", std1.attendance);
	//printf함수를 활용해서 std1에 들어있는 구조체 변수들의 값들을 출력하게 된다.
}

//typedef struct student STD;
//student 구조체에 STD 이름 붙이기

void ex2() {
	STD std1;
	//대부분의 코드는 ex1()과 동일하지만 STD로 struct student를 대체하여 쓰게 된다.

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
	//코드는 ex2()와 동일하지만 한번에 구조체선언 및 새로운 이름을 붙이게 된다.

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
	//STD 구조체로 student라는 이름의 10개 구조체를 선언한다.
	int fi;
	int sum;

	srand((unsigned)time(NULL));
	//랜덤 함수를 사용하기 위한 선언

	for (fi = 0; fi < 10; fi++) {
		student[fi].mid_term = rand() % 46;
		student[fi].final_term = rand() % 46;
		student[fi].attendance = rand() % 11;
		sum = student[fi].mid_term + student[fi].final_term + student[fi].attendance;
		//랜덤함수를 통해서 mid_term 점수와 final_term 점수를 입력하고 attendance를 입력하게 된다. 그 이후 sum 값에 그 3가지를 모두 더한 값을 집어넣는다.

		if (sum > 80) student[fi].grade = 'A';
		else if (sum > 70) student[fi].grade = 'B';
		else if (sum > 60) student[fi].grade = 'C';
		else if (sum > 50) student[fi].grade = 'D';
		else student[fi].grade = 'F';
		//if else 문을 활용해 합계가 80점 이상은 A, 10점 밑은 B, C, D 순으로 메기고 50점 밑은 F 점수를 메기게 된다.

		printf("student %d's grade is %c\n", fi, student[fi].grade);
		printf("student %d's total grade is %d\n\n", fi, sum);
		//그 값을 출력한다.
	}
}

void ex5(int argc, char* argv[]) {
	int fi;
	printf("main function get %d argv\n", argc);
	for (fi = 0; fi < argc; fi++) printf("argv[%d] : %s\n", fi, argv[fi]);
	//argv 값과 argc 값을 활용해 for문을 실행하고 argv 값을 모두 출력하게 된다.
}

int ex6() {
	int fi;
	int* ptr = NULL;
	int size = 0;

	srand((unsigned)time(NULL));
	//랜덤 함수 활용을 위한 선언

	while (size <= 0) {
		printf("size for memory : ");
		scanf("%d", &size);
		if (size <= 0) printf("\n size must be bigger than 0\n");
	}
	//size를 입력받는 while문 이고 제대로 된 size 값이 입력되면 while문을 종료한다.

	ptr = (int*)malloc(size * sizeof(int));
	//int형 포인터 ptr에 size 크기의 int형 동적 할당을 하는 코드이다.

	if (ptr == NULL) {
		printf("FAIL : CANNOT ASSIGN!!\n");
		return -1;
	}
	//ptr이 그대로 NULL일 경우 오류가 있음을 알린다.
	for (fi = 0; fi < size; fi++) {
		ptr[fi] = rand() % 101;
		printf("ptr[%3d] = %3d\n", fi, ptr[fi]);
	}
	//ptr 배열에 rand 함수를 활용해 값을 집어넣고 이를 출력한다.
	free(ptr);
	//동적할당을 해제하는 함수
	return 0;
}

int ex7() {
	FILE* fp;
	//파일 포인터를 선언한다.
	const char* str = "The Key to realizing a dream is to focus not on success but significance - and then even the small steps and little victories along your path will take on greater meaning.";
	char buf[200];
	int fi;

	fp = fopen("test_text.txt", "wt");
	//파일을 쓰기 모드로 오픈한다.
	if (fp == NULL) {
		printf("Fail to open file\n");
		return -1;
	}
	//만약 파일 오픈에 실패했을 경우 알려주는 함수

	fputc('T', fp);
	fputc('E', fp);
	fputc('S', fp);
	fputc('T', fp);
	fputc('\n', fp);
	//fputc를 활용하여 글씨를 파일에 저장한다.

	fputs(str, fp);
	//fputs 함수를 활용해 위에 선언해둔 str 배열을 저장한다.

	fclose(fp);
	//파일을 닫는다.

	fp = fopen("test_text.txt", "rt");
	//파일을 읽기모드로 오픈한다.

	for (fi = 0; fi < 5; fi++) printf("%c", fgetc(fp));
	//5번 fp를 불러온다.
	fgets(buf, 200, fp);
	//buf 문자열에 fgets로 문장을 불러온다.
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
	//예제 7번이랑 동일

	fp = fopen("test_text.txt", "wt");
	//rt로 여는게 아닌 다시 쓰기모드로 연다. 이때 test_text 파일은 형성되지만 그안에 아무것도 적혀있지 않다.

	fclose(fp);
	return 0;
}

int ex9() {
	FILE* fp;
	STD st;
	fp = fopen("student.txt", "wt");
	if (fp == NULL) printf("Fail to open file\n");
	//student.txt라는 파일을 쓰기 형식으로 열게 된다.

	st.grade = 'B';
	st.mid_term = 56;
	st.final_term = 72;
	st.attendance = 10;
	//구조체에 각각의 요소를 입력한다.

	fprintf(fp, "grade is %c\n", st.grade);
	fprintf(fp, "mid_term is %d\n", st.grade);
	fprintf(fp, "final_term is %d\n", st.grade);
	fprintf(fp, "attendance is %d\n", st.attendance);
	//각각의 요소를 fprintf를 활용하여 파일에 저장한다.

	fclose(fp);
	//파일을 닫는다.

	return 0;
}

int ex10() {
	FILE* ori;
	FILE* cp;
	char buffer[BUF_SIZE];
	int count;

	ori = fopen("student.txt", "rb");
	cp = fopen("copy.txt", "wb");
	//ori는 읽기 형태로 파일을 열었고 cp는 쓰기 형태로 파일을 열었다.

	if (ori == NULL || cp == NULL) {
		printf("Fail to open file\n");
		return -1;
	}
	//문제가 생겼을 경우 오류임을 알려주는 함수

	while (1) {
		count = fread(buffer, 1, BUF_SIZE, ori);
		//ori에서 fread를 활용해 값을 읽어오게 된다.
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
		//count가 buf_size보다 작을 경우 ori가 비어있지 않으면 fwrite을 활용해 cp에 옮기고 비어있다면 copy가 실패했음을 알린다.
		else fwrite(buffer, 1, BUF_SIZE, cp);
		//fwite을 활용해서 cp에 값을 복사한다.
	}
	fclose(ori);
	fclose(cp);
	//두개의 파일을 저장한다.
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