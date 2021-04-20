#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define NUMBER  3
// NUMBER 라는 변수를 정의함으로써 받아야하는 사람의 수를 한번에 조절할 수 있다.

typedef struct Report {
	char name[20], number[20];
	float nat, eng, math, tot, avg;
	int grade;
}Report;

//Report라는 구조체를 선언한다. 이 때 char형 name과 number는 이름과 학번을 저장해주고 float 형의 nat, eng, math, tot, avg는 각각 성적을 저장한다. 그리고 총점과 평균을 계산하여 저장한다.
//그리고 int형 grade는 나중에 성적을 입력할 때 사용하게 된다.

int main() {
	char name[20], number[20];
	float nat, eng, math, tot = 0, avg, grade;
	Report cases[100];
	//Report라는 구조체의 개수를 총 100개를 만듬으로써 100명의 학적을 기록할 수 있게한다.
	float grades[100];
	//grades는 성적을 산출하기 위해서 사용되는 float형 배열이다.
	int max;
	//max는 성적 산출시 사용되는 변수이다.
	for (int i = 0; i < NUMBER; i++) {
		printf("정보를 입력하시오 : ");
		scanf("%s %s %f %f %f", name, number, &nat, &eng, &math);
		//이름, 학번, 국영수 성적을 입력받는다.
		strcpy(cases[i].name, name);
		strcpy(cases[i].number, number);
		//strcpy를 활용하여 문자열 name과 number를 복사한다.
		cases[i].nat = nat;
		cases[i].eng = eng;
		cases[i].math = math;
		//국영수 성적을 입력한다.
		cases[i].tot = nat + eng + math;
		cases[i].avg = cases[i].tot / 3;
		//총점과 평균을 각각 구한 후 이를 구조체에 넣게 된다.
		grades[i] = cases[i].avg;
		//평균값을 옮겨 성적을 산출할 때 사용하게 된다.
	}
	for (int j = 0; j < NUMBER; j++) {
		max = j;
		for (int k = 0; k < NUMBER; k++) if (grades[max] < grades[k]) max = k;
		//처음에 가장 큰 값을 가진 위치를 기억하는 것이 max이다.
		cases[max].grade = j + 1;
		//기억한 위치를 남은 애들 중 가장 높은 등수로 매긴다.
		grades[max] = -1;
		//가장 높은 점수 위치를 -1로 바꾸어 대상에서 제외한다.
	}
	for (int l = 0; l < NUMBER; l++) printf("이름 : %s 학번 : %s 국어 : %f 영어 : %f 수학 : %f 평균 : %f 합계 : %f 등수 : %d\n", cases[l].name, cases[l].number, cases[l].nat, cases[l].eng, cases[l].math, cases[l].avg, cases[l].tot, cases[l].grade);
	//값을 출력하는 함수이다.
}