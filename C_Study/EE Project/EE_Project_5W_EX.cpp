#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4) // 비트맵 파일 규격에선, 가로방향 데이터 크기는 4의 배수(바이트단위)로 한다.
//윈도우 운영체제에서는 비트맵 파일의 비트정보 한줄을 처리하는 방식 때문에 4의 배수로 끊어서 처리하는 특징을 가진다.
#define BYTE unsigned char

FILE* file;// 파일 포인터 선언
int rwsize, rwsize2;// 가로 라인 당 바이트 수
BYTE* lpImg;// 입력 데이터가 저장되는 메모리 주소를 지시하는 포인터
BYTE* lpOutImg;// 출력 데이터가 저장되는 메모리 주소를 지시하는 포인터
RGBQUAD* pRGB;// Lookup Table
BITMAPFILEHEADER hf;// 비트맵 파일 해더
BITMAPINFOHEADER hinfo;// 비트맵 정보 헤더

void bitof24_to_8bit_gray(void);
void egdt(void); // 과제!!
void rgbdis();
void paletteswap();
int crop();
void clearinputbuffer();
// 프로그램 내의 함수에 대한 선언

int main()
{
	//bitof24_to_8bit_gray();
	//rgbdis();
	//crop();
	//paletteswap();
	egdt();

	return 0;
}

int edge_cut(int num_x, int num_y) {
	if (num_x == -1 || num_y == -1 || num_y == hinfo.biHeight || num_x == hinfo.biWidth) return 0;
	else return 1;
}
//sebel 마스크를 씌워 계산을 할 때 가장자리 태두리에서는 계산 결과를 더하지 않도록 만들기 위한 함수이다.
//가장자리일 경우 0을 반환하여 if문을 뛰어넘고 가장자리가 아닐경우 if문을 들어가 계산을 진행한다.

void egdt(void)
{
	int i, j;
	int Y = 0, X = 0;
	double result_box[816][1232] = {};
	//값을 담을 2차원 배열을 선언한다. double **result_box로 선언후 동적할당으로 진행해도 상관이 없다.
	double max = 0;
	int x_label[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
	int y_label[3][3] = { {1,1,1},{0,0,0},{-1,-2,-1} };
	//sobel 연산을 위한 마스크를 저장하는 변수들이다.
	BITMAPFILEHEADER ohf;
	BITMAPINFOHEADER ohinfo;
	//비트맵 이미지의 정보들을 담기 위한 변수이다.

	file = fopen("ori.bmp", "rb");
	//ori 파일 오픈
	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	//파일 오픈 실패시 에러 문구 출력

	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);
	//비트맵임을 알기 위해서 fread로 값을 하나 읽어와서 판단한다.
	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	//만약 비트맵이 아니면 에러 문구 출력
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	//비트맵의 정보를 받아온다.

	ohf = hf;
	ohinfo = hinfo;
	//읽어들어온 값들을 ohf와 ohinfo에 전달해준다.

	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(8 * ohinfo.biWidth);
	//한줄의 사이즈와 비트를 곱한 전체 사이즈를 구해준다.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//파일 위치를 고정한다.
	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	//이미지 값을 받아올 변수를 선언한다.

	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	//파일로부터 이미지 값을 받아온다.
	fclose(file);
	//파일을 닫는다.

	//lpOutImg_x = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);
	//lpOutImg_y = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);

	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);
	//출력할 결과물을 저장하기 위한 변수이다.

	/*result_box = (double**)calloc(hinfo.biHeight, sizeof(double*));
	for (int k = 0; k < hinfo.biHeight; k++) result_box[k] = (double*)calloc(hinfo.biWidth, sizeof(double));*/

	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			/*for (int y = 0; y < 3; y++) {
				for (int x = 0; x < 3; x++) {
					if (edge_cut(j + x - 1, i + y - 1)) Y += lpImg[(i + y - 1) * rwsize + (j + x - 1)] * y_label[y][x];
				}
			}
			for (int y = 0; y < 3; y++) {
				for (int x = 0; x < 3; x++) {
					if (edge_cut(j + x - 1, i + y - 1)) X += lpImg[(i + y - 1) * rwsize + (j + x - 1)] * x_label[y][x];
				}
			}*/
			for (int y = 0; y < 3; y++) for (int x = 0; x < 3; x++) if (edge_cut(j + x - 1, i + y - 1)) Y += lpImg[(i + y - 1) * rwsize + 3*(j + x - 1) + 2] * y_label[y][x];
			for (int y = 0; y < 3; y++) for (int x = 0; x < 3; x++) if (edge_cut(j + x - 1, i + y - 1)) X += lpImg[(i + y - 1) * rwsize + 3*(j + x - 1) + 2] * x_label[y][x];
			//edge_cut 함수를 활용하여 만약 가장자리가 아닐경우 마스크와 곱하여 계산을 하고 그 값을 Y와 X에 순차적으로 저장한다.

			result_box[i][j] = sqrt(pow(X, 2) + pow(Y, 2));
			//각각 저장한 X값과 Y값을 제곱하고 더해서 루트를 씌운 값을 result_box에 집어넣는다.

			if (result_box[i][j] > max) max = result_box[i][j];
			//result_box의 값 중에 가장 큰 값을 찾는 과정이다.

			X = 0;
			Y = 0;
			//X와 Y를 초기화해준다.
		}
	}

	for (int i = 0; i < hinfo.biHeight; i++) {
		for (int j = 0; j < hinfo.biWidth; j++) {
			result_box[i][j] = (result_box[i][j] / max) * 255;
			//result_box에 저장되어 있던 값들으 0부터 255까지 다시 맵핑하는 과정을 진행한다.
			lpOutImg[i * rwsize2 + j] = (BYTE)result_box[i][j];
			//그 후에 BYTE 자료형으로 바꾼 뒤 lpOutImg로 값을 저장해준다.
		}
	}

	ohf.bfOffBits += 1024;
	//OffBits를 설정한다. 만약 흑백에서 자료를 따올경우에는 이 값을 건들 필요가 없다.

	ohinfo.biBitCount = 8;
	//bitcount 수를 저장해준다.

	pRGB = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
	//RGBQUAD를 저장하기 위한 변수를 선언한다.

	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
		pRGB[i].rgbReserved = i;
	}
	//흑백의 일종이므로 0부터 255까지 값을 넣어준다.

	file = fopen("EDGE.bmp", "wb");

	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(pRGB, sizeof(RGBQUAD), 256, file);
	fwrite(lpOutImg, sizeof(char), rwsize2 * hinfo.biHeight, file);
	//bmf 형식, bmf 정보, RGBQUAD, 이미지 값 순서대로 파일에 저장하여 BMF 파일을 생성한다.
	fclose(file);
	
	free(lpImg);
	free(lpOutImg);
	free(pRGB);
	//동적할당을 해제한다.
	

	printf("Check EDGE.bmp!!\n\n");
}

void bitof24_to_8bit_gray(void)
{
	int i, j;
	BYTE R, G, B, GRAY;

	BITMAPFILEHEADER ohf; // 출력 파일을 위한 비트맵 파일 헤더
	BITMAPINFOHEADER ohinfo; // 출력 파일을 위한 비트맵 파일 정보 헤더

	printf("RUN bitof24_to_8bit_gray()\n\n");

	file = fopen("ori.bmp", "rb");// 파일을 읽기 모드로 엶

	if (file == NULL)// 파일 열기에 실패하면
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file); // 파일을 열어 파일의 BITMAPFILEHEADER만큼을 hf에 저장

	if (hf.bfType != 0x4D42) // 0X4D42 == BM(아스키 코드), 비트맵파일은 맨 처음 시작이 BM이다. 따라서 첫 부분을 읽고, 그 부분을 분석해서 비트맵이 아니면...
	{
		printf("File is NOT BMP\n");
		exit(1);
	}

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file); // 파일을 열어 파일의 BITMAPINFOHEADER만큼을 hinfo에 저장

	printf("File size : %d\n", hf.bfSize); // 입력받은 비트맵 파일의 크기를 화면에 출력함
	printf("offset : %d\n", hf.bfOffBits); // 입력받은 비트맵 파일에서 실제 데이터가 시작하는 오프셋
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight); // 입력받은 비트맵 파일의 픽셀 개수를 화면에 출력함
	printf("%d BPP \n", hinfo.biBitCount); // 입력받은 비트맵 파일의 픽셀당 비트수를 출력

	ohf = hf;
	ohinfo = hinfo;
	// 원본 파일과 출력 파일은 거의 유사하므로 헤더파일을 복사해서 사용한다.
	// 단, 일부 값이 바뀌는 것들이 있으므로, 나중에 반드시 수정해줘야 한다.(bfOffBits, biBitCount 등...)

	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(8 * ohinfo.biWidth);
	//입력 파일과 출력 파일에서 가로 한 줄당 데이터가 몇비트인지 저장한다
	//이때 입력파일에서 가로폭과(=가로폭에 있는 총 픽셀 갯수)
	//한 픽셀당 바이트 수를 곱하면, 한 줄이 몇 비트를 차지하는지 알 수 있다.
	//rwsize2를 계산할 때는 입력 파일과 출력 파일의 픽셀 사이즈는 동일하기 때문에 입력 파일의 가로폭을 그대로 쓰며
	//8BPP 파일의 픽셀당 비트수는 8비트이므로 8을 곱한다.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//비트맵 파일에서 실제 값들이 저장돼 있는 위치로 포인터를 이동한다

	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	//입력 받은 파일을 위한 메모리를 할당한다

	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	//포인터는 현재 실제 데이터 값이 저장된 곳의 맨 처음으로 이동한 상황이다. 이때 이미지의 세로폭과(=가로폭에 있는 총 픽셀 갯수)
	//한 줄당 비트수를 곱하면, 전체 데이터의 크기가 나온다. fread함수를 이용해 이미지의 데이터를 char변수의 크기만큼
	//나눠서 저장한다.

	fclose(file);
	//파일사용이 완료되었으므로 닫는다.

	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);
	//출력한 파일을 위한 메모리를 할당한다

	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			B = lpImg[i * rwsize + 3 * j + 0];
			G = lpImg[i * rwsize + 3 * j + 1];
			R = lpImg[i * rwsize + 3 * j + 2];
			//앞서 언급했듯 rwsize는 가로 한줄의 데이터 크기다. 따라서 여기에 i를 곱한다는것은 i+1번째 줄의 데이터를
			//사용함을 의미한다. 한편 컬러에서 한 픽셀당 데이터는 3바이트가 필요하므로 3*j를 해서 j+1번째 픽셀로 이동한다.
			//즉 앞의 과정을 통해  i+1번째 줄의 j+1번째칸의 픽셀의 데이터를 저장한 배열의 값을 확인하게 된다.
			//이때 배열의 위치를 +0,+1,+2를 해서 데이터의 B G R값을 각각 저장한다.

			GRAY = (BYTE)(0.299 * R + 0.587 * G + 0.114 * B);
			//각각 저장한 R,G,B값에 적당한 값을 곱하고 더해서 밝기값을 만든다
			//이 값들은 어떻게 정해진것인가? -> 찾아서 레포트 첨부
			lpOutImg[i * rwsize2 + j] = GRAY;
			//만든 밝기값을 lpOutImg의 i+1번째 줄의 j+1번째칸의 픽셀의 데이터를 저장한 배열에 저장한다.
		}
	}
	ohf.bfOffBits += 1024;
	//bfOffBits는 실제 파일의 화면 데이터가 시작되는 곳의 위치이다.
	//비트맵파일에서 비트수가 낮으면(1 ~ 8BPP)
	//비트수가 높을 때와(8BPP 초과) 달리 ColorTable이 파일의 화면 데이터앞에 있다.
	//따라서 bfOffBits를 1024만큼 뒤로 밀어야 한다.
	//1024는 RGBQUAD의 크기(4바이트) * 256개 팔레트 = 1024다.

	ohinfo.biBitCount = 8;
	//8BPP이니까 8이다.

	pRGB = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
	//앞서 말한 ColorTable을 위한 메모리를 설정한다.

	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
		pRGB[i].rgbReserved = i;
	}
	//흑백이니까 그냥 0부터 255까지 순차적으로 저장한다.

	file = fopen("BW.bmp", "wb");
	//이제 출력할 파일을 쓰기모드로 연다.

	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(pRGB, sizeof(RGBQUAD), 256, file);
	//비트맵 파일을 구성하는 BITMAPFILEHEADER, BITMAPINFOHEADER,RGBQUAD를 기록한다.
	fwrite(lpOutImg, sizeof(char), rwsize2 * hinfo.biHeight, file);
	//앞서 우리가 만든 출력 데이터를 기록한다.
	fclose(file);
	//파일을 닫는다.

	free(lpImg);
	free(lpOutImg);
	free(pRGB);
	//메모리를 반환한다.

	printf("Check BW.bmp!!\n\n");
}

void rgbdis(void)
{
	int i, j;
	printf("RUN rgbdis()\n\n");
	file = fopen("rgbdis.bmp", "rb");
	//파일을 오픈한다.

	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	//파일 오픈에 실패할 경우 에러 문구를 출력한다.
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);
	//bmf인지 확인한다.

	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	//bmf파일이 아닐경우 에러 문구를 출력한다.

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	//파일 정보를 받아온다.

	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	//파일 정보를 출력한다.

	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	//한줄의 데이터 크기를 구해서 저장한다.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//파일 시작위치 설정

	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	//이미지 데이터 받아오기 위한 변수 선언

	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	//데이터를 읽어와 lpImg에 저장한다.

	fclose(file);
	//파일 닫기

	lpOutImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	//출력할 이미지를 저장할 공간 선언

	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize + 3 * j + 0] = lpImg[i * rwsize + 3 * j + 0];  // B
			lpOutImg[i * rwsize + 3 * j + 1] = 0;  // G
			lpOutImg[i * rwsize + 3 * j + 2] = 0;  // R
		}
	}
	//BGR 중에서 B만 먼저 추출해서 IpOutImg에 저장한다.

	hinfo.biBitCount = 24;
	//bitcount를 24로 설정한다.

	file = fopen("blue.bmp", "wb");
	//파일을 오픈한다.

	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(lpOutImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	//bmf 파일, 정보, 이미지 값을 저장한 후 파일을 닫는다.

	file = fopen("green.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize + 3 * j + 0] = 0;  // B
			lpOutImg[i * rwsize + 3 * j + 1] = lpImg[i * rwsize + 3 * j + 1];  // G
			lpOutImg[i * rwsize + 3 * j + 2] = 0;  // R
		}
	}
	fwrite(lpOutImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	//위와 똑같은 과정을 반복하는데 여기에서는 BGR 중에 G의 값만 출력하고 나머지 값은 모두 0으로 만들어서 이미지를 출력한다.

	file = fopen("red.bmp", "wb");
	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize + 3 * j + 0] = 0;  // B
			lpOutImg[i * rwsize + 3 * j + 1] = 0;  // G
			lpOutImg[i * rwsize + 3 * j + 2] = lpImg[i * rwsize + 3 * j + 2];  // R
		}
	}

	fwrite(lpOutImg, sizeof(char), rwsize * hinfo.biHeight, file);

	fclose(file);
	//위와 똑같은 과정이지만 BGR중 R의 값만 출력하고 나머지의 값은 0으로 만들어서 이미지를 출력한다.

	free(lpImg);
	free(lpOutImg);
	//동적 할당을 해제한다.
	
	printf("Check blue.bmp, green.bmp, red.bmp!!!\n\n");
}

void paletteswap()
{
	int i, j;
	BYTE R, G, B, GRAY;
	RGBQUAD* oripal;
	RGBQUAD* swappal;
	//RGBQUAD 포인터를 2개 선언해서 하나는 기존 RGB, 나머지 하나는 바뀐 RGB를 저장한다.

	BITMAPFILEHEADER ohf;
	BITMAPINFOHEADER ohinfo;

	printf("RUN paletteswap()\n\n");

	file = fopen("logo.bmp", "rb");

	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	//파일 오픈 실패시 에러 문구 출력

	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);

	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	//파일이 bmf가 아닐시 에러 문구 출력

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	//info를 읽어온다.

	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	printf("Palette has %d color \n", hinfo.biClrUsed);
	//info에 대해서 출력한다.

	ohf = hf;
	ohinfo = hinfo;
	//출력할 이미지를 받아온 이미지와 동일하게 설정한다.

	oripal = (RGBQUAD*)malloc(sizeof(RGBQUAD) * hinfo.biClrUsed);
	fread(oripal, sizeof(RGBQUAD), hinfo.biClrUsed, file);
	//RGBQUAD 동적할당 후 파일로부터 값을 받아온다.

	for (i = 0; i < hinfo.biClrUsed; i++)
	{
		printf("Original palette %d B : %d\n", i, oripal[i].rgbBlue);
		printf("Original palette %d G : %d\n", i, oripal[i].rgbGreen);
		printf("Original palette %d R : %d\n\n", i, oripal[i].rgbRed);
	}
	//파일에서 읽어온 값을 for문을 활용해 출력한다.


	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(ohinfo.biBitCount * ohinfo.biWidth);
	//bmf 이미지 한줄 데이터 값인 rwsize와 전체 데이터 사이즈인 rwsize2를 선언한다.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//파일의 위치를 고정한다.

	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);

	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	//이미지 데이터를 불러온다.

	fclose(file);

	lpOutImg = lpImg;
	//출력할 이미지에 불러온 이미지를 저장한다.

	swappal = (RGBQUAD*)malloc(sizeof(RGBQUAD) * hinfo.biClrUsed);
	int buf;
	for (i = 0; i < hinfo.biClrUsed; i++)
	{
		printf("input palette %d B : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbBlue = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		//Blue에 대한 값을 받은 후에 255와 0 사이의 값으로 바꿔 rbgBlue에 넣어준다.
		printf("input palette %d G : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbGreen = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		// Green에 대한 값을 받은 후에 255와 0 사이의 값으로 바꿔 rbgBlue에 넣어준다.
		printf("input palette %d R : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbRed = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		// Red에 대한 값을 받은 후에 255와 0 사이의 값으로 바꿔 rbgBlue에 넣어준다.
		printf("\n");
	}

	file = fopen("logo_swap.bmp", "wb");

	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(swappal, sizeof(RGBQUAD), hinfo.biClrUsed, file);
	fwrite(lpOutImg, sizeof(char), rwsize2 * hinfo.biHeight, file);
	fclose(file);
	//팔레트 값을 받아 저장한 후 bmf 파일 형식, 정보, 팔레트, 이미지 순으로 저장해서 파일을 완성한다.

	free(lpImg);
	free(oripal);
	free(swappal);
	//동적 할당을 해제한다.
	printf("logo_swap.bmp!!\n\n");
}

void clearinputbuffer() // 입력 버퍼 클리어
{
	while (getchar() != '\n');
}

int crop()
{
	int p1x, p1y, p2x, p2y, fi;
	int i, j;

	BITMAPFILEHEADER ohf;
	BITMAPINFOHEADER ohinfo;

	printf("RUN crop()\n\n");

	file = fopen("ori.bmp", "rb");

	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	//파일이 제대로 오픈되지 않았을 경우 에러 문구 출력
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);

	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	//비트맵 파일이 아닐경우 에러 문구 출력

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);

	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	//파일에 대한 정보 출력

	printf("P1 x : ");
	scanf("%d", &p1x);
	clearinputbuffer();

	printf("P1 y : ");
	scanf("%d", &p1y);
	clearinputbuffer();

	printf("P2 x : ");
	scanf("%d", &p2x);
	clearinputbuffer();

	printf("P2 y : ");
	scanf("%d", &p2y);
	clearinputbuffer();

	printf("P1 : %4d, %4d\n", p1x, p1y);
	printf("P2 : %4d, %4d\n", p2x, p2y);
	//p1x, p1y, p2x, p2y를 콘솔 창에서 직접 받아온다.

	if (p1x<0 || p1x>hinfo.biWidth || p1y<0 || p1y>hinfo.biHeight || p2x<0 || p2x>hinfo.biWidth || p2y<0 || p2y>hinfo.biHeight)
	{
		printf(" check your input!!! \n");
		return -1;
	}
	//만약 그 값들이 범위를 벗어나는 값이 입력됐을 경우 다시 입력하라는 에러 문구를 출력한다.

	if (p1x > p2x)
	{
		fi = p1x;
		p1x = p2x;
		p2x = fi;
	}
	//p1x가 p2x보다 클 경우에는 둘을 스위칭해준다.

	if (p1y > p2y)
	{
		fi = p1y;
		p1y = p2y;
		p2y = fi;
	}
	//p1y가 p2y보다 더 클 경우 둘을 스위칭해준다.

	ohf = hf;
	ohinfo = hinfo;

	ohinfo.biWidth = p2x - p1x + 1;
	ohinfo.biHeight = p2y - p1y + 1;
	//biWidth와 biHeight을 입력 받았던 값들에서 연산하여 저장한다.

	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(ohinfo.biBitCount * ohinfo.biWidth);
	//한줄의 데이터 사이즈와 전체 데이터 사이즈를 구해서 저장한다.

	ohf.bfSize = rwsize2 * ohinfo.biHeight + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//비트맵 파일의 전체 사이즈를 구한다.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//파일 위치 고정
	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	//lpImg를 동적 할당해준 후에 fread로 값을 저장한다.

	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);

	//출력할 이미지를 담을 공간을 동적 할당한다.

	for (i = 0; i < ohinfo.biHeight; i++)
	{
		for (j = 0; j < ohinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize2 + 3 * j + 0] = lpImg[(i + p1y) * rwsize + 3 * (j + p1x) + 0];
			lpOutImg[i * rwsize2 + 3 * j + 1] = lpImg[(i + p1y) * rwsize + 3 * (j + p1x) + 1];
			lpOutImg[i * rwsize2 + 3 * j + 2] = lpImg[(i + p1y) * rwsize + 3 * (j + p1x) + 2];
		}
	}
	//기존 이미지에서 p1y만큼 y축으로 밀고 p1x만큼 x축으로 밀어서 값을 저장해주는 과정을 거친다.

	file = fopen("crop.bmp", "wb");
	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(lpOutImg, sizeof(char), rwsize2 * ohinfo.biHeight, file);
	fclose(file);
	//저장된 값을 순서대로 저장하여 파일을 생성한다.
	free(lpImg);
	free(lpOutImg);
	//동적 할당을 해제한다.
	printf("Check crop.bmp!!!\n\n");
}