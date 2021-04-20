#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//많은 내용이 과제 1과 겹치는 관계로 어느정도 설명을 생략하도록 하겠습니다.

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
	//buf 배열은 파일에서 값을 읽어온 후에 저장하기 위한 변수이다.
	char* count, *count_st;
	//단어를 끊어내기 위해서 선언한 변수이다.

	FILE* fp;
	//파일을 불러오기 위해서 fp 라는 포인터를 선언한다.
	fp = fopen("test.txt", "rt");
	//fp에 test.txt파일을 읽기 모드로 불러온다.
	if (fp == NULL) {
		printf("Fail to open file\n");
		return -1;
	}
	//만약 fp에 파일을 불러오는게 실패했을 경우에는 Fail to open file이라는 문장을 출력하게 해주는 if문이다.
	for (int i = 0; i < NUMBER; i++) {
		fgets(buf, 100, fp);
		//파일에서 한줄을 불러와서 buf에 저장한다.
		count_st = count = buf;
		//count_st와 count의 주소를 buf 처음 주소로 저장한다.
		while (*count != '\0') {
			//count가 널문자를 가르킬 때까지 반복한다.
			while (*count != ' ' && *count != '\n' && *count != '\0') count++;
			//count가 ' '이거나 '\n'이거나 널문자일 때는 count의 주소를 하나 증가시켜주는 함수이다.
			if (*count == ' ' && flag == 0) {
				*count = '\0';
				strcpy(cases[i].name, count_st);
				count++;
				count_st = count;
				flag++;
			}
			//만약 공백인데 flag가 0인 경우 이름이므로 strcpy를 count자리에 널 문자를 넣어준 후에 strcpy를 활용하여 name을 넣어주고 count의 주소와 flag의 주소를 증가시키고 count_st에 count의 주소를 저장해준다.
			else if (*count == ' ' && flag == 1) {
				*count = '\0';
				strcpy(cases[i].number, count_st);
				count++;
				count_st = count;
				flag++;
			}
			//flag가 1이면 number로 생각하고 똑같이 행한다.
			else if (*count == ' ' && flag == 2) {
				*count = '\0';
				cases[i].nat = atoi(count_st);
				count++;
				count_st = count;
				flag++;
			}
			//flag가 2이면 atoi 함수를 활용하여 문자열을 숫자로 바꾸고 이를 nat에 저장한다.
			else if (*count == ' ' && flag == 3) {
				*count = '\0';
				cases[i].eng = atoi(count_st);
				count++;
				count_st = count;
				flag++;
			}
			//flag가 3이면 atoi 함수를 활용하여 문자열을 숫자로 바꾸고 이를 eng에 저장한다.
			else if ((*count == '\n' || *count == '\0') && flag == 4) {
				*count = '\0';
				cases[i].math = atoi(count_st);
				count++;
				count_st = count;
				flag++;
			}
			//flag가 4이고 널 문자이거나 '\n'이면 atoi로 숫자로 바꿔 math에 저장해준다.
		}
		cases[i].tot = cases[i].nat + cases[i].eng + cases[i].math;
		cases[i].avg = cases[i].tot / 3;
		//tot과 avg를 구해주는 코드이다.
		grades[i] = cases[i].avg;
		flag = 0;
	}
	for (int j = 0; j < NUMBER; j++) {
		max = j;
		for (int k = 0; k < NUMBER; k++) if (grades[max] < grades[k]) max = k;
		cases[max].grade = j + 1;
		grades[max] = -1;
	}
	//grade 산정 방식은 1번 과제와 같다.
	fclose(fp);
	//파일 읽기모드를 종료한다.
	fp = fopen("test_text.txt", "wt");
	//파일 쓰기 모드를 시작한다.
	if (fp == NULL) {
		printf("Fail to open file\n");
		return -1;
	}
	for (int l = 0; l < NUMBER; l++) fprintf(fp, "이름 : %s 학번 : %s 국어 : %f 영어 : %f 수학 : %f 평균 : %f 합계 : %f 등수 : %d\n", cases[l].name, cases[l].number, cases[l].nat, cases[l].eng, cases[l].math, cases[l].avg, cases[l].tot, cases[l].grade);
	//파일에 쓰는 과정이다.
	fclose(fp);
}