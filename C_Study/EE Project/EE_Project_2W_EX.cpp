#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define STDNUM 96

void ex1() {
	int fi;
	int std[STDNUM] = { 0, }; //{0,}을 활용하여 정수형 배열 전체를 0으로 초기화해준다.
	srand((unsigned)time(NULL)); //srand 함수는 난수 발생함수로 시드를 변경하도록 설정하는 함수이다.

	printf("sizeof(std[0]) = %d\n", sizeof(std[0])); //정수형 배열에서 하나의 항의 사이즈 이므로 int 사이즈와 동일하다.
	printf("sizeof(std) = %d\n", sizeof(std)); //정수형 배열 전체 사이즈를 출력하는 것이므로 int 사이즈에 96개의 항을 곱한 384가 나오게 된다.
	printf("sizeof(std)/sizeof(std[0]) = %d\n", sizeof(std) / sizeof(std[0])); //전체 길이를 int형 사이즈로 나누었으므로 STDNUM이 나오게 된다.

	for (fi = 0; fi < STDNUM; fi++) {
		std[fi] = rand() % 101; //rand()함수에서 임의로 나오는 숫자를 101의 나머지로 만듬으로써 0부터 100까지 랜덤한 함수를 std 배열에 저장하게 된다.
		printf("student %2d's grade is %3d\n", fi, std[fi]); //저장한 std 배열을 하나씩 출력하는 함수이다.
	}
}

void ex2() {
	char str[100];
	printf("Plz input your text : ");
	scanf("%[^\n]s", str); //%[^\n]s는 \n을 제외하고 모든 문자를 받으라는 의미이다. 따라서 기존의 scanf는 공백을 받을 수 없었으나 이 함수를 포함하면 공백도 포함해서 받을 수 있다.
	printf("your text is : %s", str); //str 값 출력
}

void ex3() {
	int a = 10;
	double b = 7.25;

	int* pt_a; //정수형 포인터
	double* pt_b; //실수형 포인터

	pt_a = &a; //a의 주소를 pt_a에 저장
	pt_b = &b; //b의 주소를 pt_b에 저장

	printf("sizeof(pt_a) = %d\n", sizeof(pt_a)); //크기는 4바이트로 나온다.
	printf("sizeof(pt_b) = %d\n\n", sizeof(pt_b)); //위와 동일한 4바이트이다.
	printf("int a = %d\n", a); 
	printf("double b = %lf\n\n", b);

	printf("a's address = %p\n", pt_a); //pt_a의 주소 출력
	printf("b's address = %p\n\n", pt_b); //pt_b의 주소 출력

	a = 12; 
	*pt_a = 15;
	b = 8.5;
	*pt_b = 10.75;
	//a를 12로 바꿨지만 a의 주소를 가지고 있는 pt_a를 15로 바꿔줬기 때문에 15로 최종적으로 바뀜
	//b를 8.5로 바꿨지만 b의 주소를 가지고 있는 pt_b를 10.75로 바꿔줬기 때문에 10.75로 최종적으로 바뀜

	printf("int a = %d\n", a);
	printf("double b = %lf\n\n", b);
}

void ex4() {
	int arr[100];
	int* ptr_arr;
	int fi;

	srand((unsigned)time(NULL)); //srand 함수는 난수 발생함수로 시드를 변경하도록 설정하는 함수이다.

	ptr_arr = &arr[0]; //포인터 ptr_arr에 arr의 첫번째 항 주소를 복사한다.

	printf("address of arr[0] is %p\n", &arr[0]);
	printf("arr if pointing %p\n", arr);
	printf("ptr_arr is pointing %p\n", ptr_arr);
	printf("\n");
	//arr[0]의 주소는 arr의 시작 주소와 동일하고 ptr_arr은 arr의 주소를 복사한 포인터 이므로 3개 모두 동일한 주소를 출력하게 된다.

	printf("address of arr[1] is %p\n", &arr[1]);
	printf("arr+1 if pointing %p\n", arr+1);
	printf("ptr_arr+1 is pointing %p\n", ptr_arr+1);
	printf("\n");
	//이 배열은 int형 배열이므로 길이는 4이고 따라서 위에 arr의 주소보다 4 더 앞서있는 주소가 출력된다.

	for (fi = 0; fi < 100; fi++) arr[fi] = rand() % 101;
	printf("arr[0] = %d\n", arr[0]);
	printf("*arr = %d\n", *arr);
	printf("*ptr_arr = %d\n", *ptr_arr);
	//for문을 활용하여 랜덤 값을 arr 배열에 넣고 arr[0]의 값을 출력하는 것이므로 모두 동일한 값이 나오게 된다.

	printf("\n");
	
	printf("arr[20] = %d\n", arr[20]);
	printf("*(arr+20) = %d\n", *(arr + 20));
	printf("*(ptr_arr+20) = %d\n", *(ptr_arr + 20));
	printf("*arr+20 = %d\n", *arr + 20);
	printf("*ptr_arr+20 = %d\n", *ptr_arr + 20);
	//처음 3개는 20번째에 저장된 랜덤 값이 출력되게 되지만 4번째 코드는 기존 첫번째 주소에 들어있던 값에 20을 더한값이 나오게 되고 5번째 코드 역시 마찬가지이다.
}

void addNmul(int a, int b, int* a_add_b, int* a_mul_b) {
	*a_add_b = a + b;
	*a_mul_b = a * b;
	//각각 포인터로 받아 값을 증가시켜준다. 이는 직접적인 대입이기 때문에 함수를 나가서도 유지된다.
}

void inc_CBV(int a) {
	a++;
	//지역변수 a를 증가시킨다.
}

void inc_CBR(int* a) {
	(*a)++;
	//받아온 주소를 직접적으로 변화시킨다.
}

void ex5() {
	int a, b;
	int add, mul;
	printf("input a : ");
	scanf("%d", &a);
	printf("input b : ");
	scanf("%d", &b);
	//a와 b의 값을 받아오는 함수들이다.

	printf("a is %d and b is %d\n\n", a, b);

	inc_CBV(a);
	inc_CBR(&b);
	//inc_CBV는 인수를 그대로 복사해서 a++해주는 함수이기 때문에 a에 직접적인 변화를 주지는 못한다.
	//하지만 inc_CBR은 포인터로 전달받기 때문에 b주소에 직접 접근해서 값을 바꿔준다.

	printf("Now a is %d and b is %d\n\n", a, b);
	//따라서 a는 그대로 10이고 b는 하나 증가한 20이 된다.

	addNmul(a, b, &add, &mul);
	//각각 더해주고 곱해서 저장해주는 함수이다.

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