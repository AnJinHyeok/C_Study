#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float CtoF(int tem) {
	return 1.8 * tem + 32;
}
//공식을 활용하여 섭씨에서 화씨로 변환해주는 함수

float FtoC(int tem) {
	return (tem - 32) * 5 / 9.0;
}
//공식을 활용하여 화씨에서 섭씨로 변환해주는 함수

int len(char str[]) {
	return strlen(str);
}
//문자열의 길이 출력하는 함수, string 헤더를 사용

void switching() {
	int cho, num;
	printf("CtoF면 1, FtoC이면 2를 선택하세요 : ");
	scanf("%d", &cho);
	printf("숫자를 입력하세요 : ");
	scanf("%d", &num);
	if (cho == 1) printf("화씨 %f", CtoF(num));
	else if (cho == 2) printf("섭씨 %f", FtoC(num));
}
//화씨에서 섭씨로 바꾸는지, 섭씨에서 화씨로 바꾸는지 선택한 후 함수를 활용해 출력하는 함수이다.

void length() {
	char str[1000];
	rewind(stdin);
	gets_s(str);
	printf("문자열의 길이는 %d입니다.", len(str));
}
//rewind로 버퍼를 비운 후에 gets_s로 문자열을 받고 len함수로 길이는 반환한다.

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
//어떤 연산을 할지 전달 받고 1번이면 덧셈 출력, 2번이면 곱셈 출력, 그리고 3번이면 종료된다.

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
	
	printf("문장 개수 : %d, 단어 개수 : %d, 문자 개수 : %d", str_num, ++word_num, char_num);
}
//rewind로 버퍼를 비우고 gets_s로 문자열을 전달받고 while문을 활용하여 '\0'로 종료되기 전까지 반복문을 돌게 되고 .,?,!을 찾으면 문장을 마친것으로 간주한다.
//그리고 ' '을 만났을 때 단어임을 알게 되면 단어 개수를 하나 더하고 매 반복문을 돌때마다 char_num을 더해서 최종 출력하게 된다.

int main() {
	int menu;
	printf("Menu1 : 화씨 섭씨 변환\nMenu2 : 문자열의 길이\nMenu3 : 간단한 계산기\nMenu4 : 문장의 수, 단어 수, 문자 수 세기\nMenu를 선택하세요 : ");
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