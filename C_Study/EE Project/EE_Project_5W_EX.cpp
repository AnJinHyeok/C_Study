#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#define WIDTHBYTES(bits) (((bits)+31)/32*4) // ��Ʈ�� ���� �԰ݿ���, ���ι��� ������ ũ��� 4�� ���(����Ʈ����)�� �Ѵ�.
//������ �ü�������� ��Ʈ�� ������ ��Ʈ���� ������ ó���ϴ� ��� ������ 4�� ����� ��� ó���ϴ� Ư¡�� ������.
#define BYTE unsigned char

FILE* file;// ���� ������ ����
int rwsize, rwsize2;// ���� ���� �� ����Ʈ ��
BYTE* lpImg;// �Է� �����Ͱ� ����Ǵ� �޸� �ּҸ� �����ϴ� ������
BYTE* lpOutImg;// ��� �����Ͱ� ����Ǵ� �޸� �ּҸ� �����ϴ� ������
RGBQUAD* pRGB;// Lookup Table
BITMAPFILEHEADER hf;// ��Ʈ�� ���� �ش�
BITMAPINFOHEADER hinfo;// ��Ʈ�� ���� ���

void bitof24_to_8bit_gray(void);
void egdt(void); // ����!!
void rgbdis();
void paletteswap();
int crop();
void clearinputbuffer();
// ���α׷� ���� �Լ��� ���� ����

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
//sebel ����ũ�� ���� ����� �� �� �����ڸ� �µθ������� ��� ����� ������ �ʵ��� ����� ���� �Լ��̴�.
//�����ڸ��� ��� 0�� ��ȯ�Ͽ� if���� �پ�Ѱ� �����ڸ��� �ƴҰ�� if���� �� ����� �����Ѵ�.

void egdt(void)
{
	int i, j;
	int Y = 0, X = 0;
	double result_box[816][1232] = {};
	//���� ���� 2���� �迭�� �����Ѵ�. double **result_box�� ������ �����Ҵ����� �����ص� ����� ����.
	double max = 0;
	int x_label[3][3] = { {1,0,-1},{2,0,-2},{1,0,-1} };
	int y_label[3][3] = { {1,1,1},{0,0,0},{-1,-2,-1} };
	//sobel ������ ���� ����ũ�� �����ϴ� �������̴�.
	BITMAPFILEHEADER ohf;
	BITMAPINFOHEADER ohinfo;
	//��Ʈ�� �̹����� �������� ��� ���� �����̴�.

	file = fopen("ori.bmp", "rb");
	//ori ���� ����
	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	//���� ���� ���н� ���� ���� ���

	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);
	//��Ʈ������ �˱� ���ؼ� fread�� ���� �ϳ� �о�ͼ� �Ǵ��Ѵ�.
	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	//���� ��Ʈ���� �ƴϸ� ���� ���� ���
	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	//��Ʈ���� ������ �޾ƿ´�.

	ohf = hf;
	ohinfo = hinfo;
	//�о���� ������ ohf�� ohinfo�� �������ش�.

	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(8 * ohinfo.biWidth);
	//������ ������� ��Ʈ�� ���� ��ü ����� �����ش�.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//���� ��ġ�� �����Ѵ�.
	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	//�̹��� ���� �޾ƿ� ������ �����Ѵ�.

	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	//���Ϸκ��� �̹��� ���� �޾ƿ´�.
	fclose(file);
	//������ �ݴ´�.

	//lpOutImg_x = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);
	//lpOutImg_y = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);

	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);
	//����� ������� �����ϱ� ���� �����̴�.

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
			//edge_cut �Լ��� Ȱ���Ͽ� ���� �����ڸ��� �ƴҰ�� ����ũ�� ���Ͽ� ����� �ϰ� �� ���� Y�� X�� ���������� �����Ѵ�.

			result_box[i][j] = sqrt(pow(X, 2) + pow(Y, 2));
			//���� ������ X���� Y���� �����ϰ� ���ؼ� ��Ʈ�� ���� ���� result_box�� ����ִ´�.

			if (result_box[i][j] > max) max = result_box[i][j];
			//result_box�� �� �߿� ���� ū ���� ã�� �����̴�.

			X = 0;
			Y = 0;
			//X�� Y�� �ʱ�ȭ���ش�.
		}
	}

	for (int i = 0; i < hinfo.biHeight; i++) {
		for (int j = 0; j < hinfo.biWidth; j++) {
			result_box[i][j] = (result_box[i][j] / max) * 255;
			//result_box�� ����Ǿ� �ִ� ������ 0���� 255���� �ٽ� �����ϴ� ������ �����Ѵ�.
			lpOutImg[i * rwsize2 + j] = (BYTE)result_box[i][j];
			//�� �Ŀ� BYTE �ڷ������� �ٲ� �� lpOutImg�� ���� �������ش�.
		}
	}

	ohf.bfOffBits += 1024;
	//OffBits�� �����Ѵ�. ���� ��鿡�� �ڷḦ ���ð�쿡�� �� ���� �ǵ� �ʿ䰡 ����.

	ohinfo.biBitCount = 8;
	//bitcount ���� �������ش�.

	pRGB = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
	//RGBQUAD�� �����ϱ� ���� ������ �����Ѵ�.

	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
		pRGB[i].rgbReserved = i;
	}
	//����� �����̹Ƿ� 0���� 255���� ���� �־��ش�.

	file = fopen("EDGE.bmp", "wb");

	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(pRGB, sizeof(RGBQUAD), 256, file);
	fwrite(lpOutImg, sizeof(char), rwsize2 * hinfo.biHeight, file);
	//bmf ����, bmf ����, RGBQUAD, �̹��� �� ������� ���Ͽ� �����Ͽ� BMF ������ �����Ѵ�.
	fclose(file);
	
	free(lpImg);
	free(lpOutImg);
	free(pRGB);
	//�����Ҵ��� �����Ѵ�.
	

	printf("Check EDGE.bmp!!\n\n");
}

void bitof24_to_8bit_gray(void)
{
	int i, j;
	BYTE R, G, B, GRAY;

	BITMAPFILEHEADER ohf; // ��� ������ ���� ��Ʈ�� ���� ���
	BITMAPINFOHEADER ohinfo; // ��� ������ ���� ��Ʈ�� ���� ���� ���

	printf("RUN bitof24_to_8bit_gray()\n\n");

	file = fopen("ori.bmp", "rb");// ������ �б� ���� ��

	if (file == NULL)// ���� ���⿡ �����ϸ�
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file); // ������ ���� ������ BITMAPFILEHEADER��ŭ�� hf�� ����

	if (hf.bfType != 0x4D42) // 0X4D42 == BM(�ƽ�Ű �ڵ�), ��Ʈ�������� �� ó�� ������ BM�̴�. ���� ù �κ��� �а�, �� �κ��� �м��ؼ� ��Ʈ���� �ƴϸ�...
	{
		printf("File is NOT BMP\n");
		exit(1);
	}

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file); // ������ ���� ������ BITMAPINFOHEADER��ŭ�� hinfo�� ����

	printf("File size : %d\n", hf.bfSize); // �Է¹��� ��Ʈ�� ������ ũ�⸦ ȭ�鿡 �����
	printf("offset : %d\n", hf.bfOffBits); // �Է¹��� ��Ʈ�� ���Ͽ��� ���� �����Ͱ� �����ϴ� ������
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight); // �Է¹��� ��Ʈ�� ������ �ȼ� ������ ȭ�鿡 �����
	printf("%d BPP \n", hinfo.biBitCount); // �Է¹��� ��Ʈ�� ������ �ȼ��� ��Ʈ���� ���

	ohf = hf;
	ohinfo = hinfo;
	// ���� ���ϰ� ��� ������ ���� �����ϹǷ� ��������� �����ؼ� ����Ѵ�.
	// ��, �Ϻ� ���� �ٲ�� �͵��� �����Ƿ�, ���߿� �ݵ�� ��������� �Ѵ�.(bfOffBits, biBitCount ��...)

	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(8 * ohinfo.biWidth);
	//�Է� ���ϰ� ��� ���Ͽ��� ���� �� �ٴ� �����Ͱ� ���Ʈ���� �����Ѵ�
	//�̶� �Է����Ͽ��� ��������(=�������� �ִ� �� �ȼ� ����)
	//�� �ȼ��� ����Ʈ ���� ���ϸ�, �� ���� �� ��Ʈ�� �����ϴ��� �� �� �ִ�.
	//rwsize2�� ����� ���� �Է� ���ϰ� ��� ������ �ȼ� ������� �����ϱ� ������ �Է� ������ �������� �״�� ����
	//8BPP ������ �ȼ��� ��Ʈ���� 8��Ʈ�̹Ƿ� 8�� ���Ѵ�.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//��Ʈ�� ���Ͽ��� ���� ������ ����� �ִ� ��ġ�� �����͸� �̵��Ѵ�

	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	//�Է� ���� ������ ���� �޸𸮸� �Ҵ��Ѵ�

	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	//�����ʹ� ���� ���� ������ ���� ����� ���� �� ó������ �̵��� ��Ȳ�̴�. �̶� �̹����� ��������(=�������� �ִ� �� �ȼ� ����)
	//�� �ٴ� ��Ʈ���� ���ϸ�, ��ü �������� ũ�Ⱑ ���´�. fread�Լ��� �̿��� �̹����� �����͸� char������ ũ�⸸ŭ
	//������ �����Ѵ�.

	fclose(file);
	//���ϻ���� �Ϸ�Ǿ����Ƿ� �ݴ´�.

	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);
	//����� ������ ���� �޸𸮸� �Ҵ��Ѵ�

	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			B = lpImg[i * rwsize + 3 * j + 0];
			G = lpImg[i * rwsize + 3 * j + 1];
			R = lpImg[i * rwsize + 3 * j + 2];
			//�ռ� ����ߵ� rwsize�� ���� ������ ������ ũ���. ���� ���⿡ i�� ���Ѵٴ°��� i+1��° ���� �����͸�
			//������� �ǹ��Ѵ�. ���� �÷����� �� �ȼ��� �����ʹ� 3����Ʈ�� �ʿ��ϹǷ� 3*j�� �ؼ� j+1��° �ȼ��� �̵��Ѵ�.
			//�� ���� ������ ����  i+1��° ���� j+1��°ĭ�� �ȼ��� �����͸� ������ �迭�� ���� Ȯ���ϰ� �ȴ�.
			//�̶� �迭�� ��ġ�� +0,+1,+2�� �ؼ� �������� B G R���� ���� �����Ѵ�.

			GRAY = (BYTE)(0.299 * R + 0.587 * G + 0.114 * B);
			//���� ������ R,G,B���� ������ ���� ���ϰ� ���ؼ� ��Ⱚ�� �����
			//�� ������ ��� ���������ΰ�? -> ã�Ƽ� ����Ʈ ÷��
			lpOutImg[i * rwsize2 + j] = GRAY;
			//���� ��Ⱚ�� lpOutImg�� i+1��° ���� j+1��°ĭ�� �ȼ��� �����͸� ������ �迭�� �����Ѵ�.
		}
	}
	ohf.bfOffBits += 1024;
	//bfOffBits�� ���� ������ ȭ�� �����Ͱ� ���۵Ǵ� ���� ��ġ�̴�.
	//��Ʈ�����Ͽ��� ��Ʈ���� ������(1 ~ 8BPP)
	//��Ʈ���� ���� ����(8BPP �ʰ�) �޸� ColorTable�� ������ ȭ�� �����;տ� �ִ�.
	//���� bfOffBits�� 1024��ŭ �ڷ� �о�� �Ѵ�.
	//1024�� RGBQUAD�� ũ��(4����Ʈ) * 256�� �ȷ�Ʈ = 1024��.

	ohinfo.biBitCount = 8;
	//8BPP�̴ϱ� 8�̴�.

	pRGB = (RGBQUAD*)malloc(sizeof(RGBQUAD) * 256);
	//�ռ� ���� ColorTable�� ���� �޸𸮸� �����Ѵ�.

	for (i = 0; i < 256; i++)
	{
		pRGB[i].rgbBlue = i;
		pRGB[i].rgbGreen = i;
		pRGB[i].rgbRed = i;
		pRGB[i].rgbReserved = i;
	}
	//����̴ϱ� �׳� 0���� 255���� ���������� �����Ѵ�.

	file = fopen("BW.bmp", "wb");
	//���� ����� ������ ������� ����.

	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(pRGB, sizeof(RGBQUAD), 256, file);
	//��Ʈ�� ������ �����ϴ� BITMAPFILEHEADER, BITMAPINFOHEADER,RGBQUAD�� ����Ѵ�.
	fwrite(lpOutImg, sizeof(char), rwsize2 * hinfo.biHeight, file);
	//�ռ� �츮�� ���� ��� �����͸� ����Ѵ�.
	fclose(file);
	//������ �ݴ´�.

	free(lpImg);
	free(lpOutImg);
	free(pRGB);
	//�޸𸮸� ��ȯ�Ѵ�.

	printf("Check BW.bmp!!\n\n");
}

void rgbdis(void)
{
	int i, j;
	printf("RUN rgbdis()\n\n");
	file = fopen("rgbdis.bmp", "rb");
	//������ �����Ѵ�.

	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	//���� ���¿� ������ ��� ���� ������ ����Ѵ�.
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);
	//bmf���� Ȯ���Ѵ�.

	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	//bmf������ �ƴҰ�� ���� ������ ����Ѵ�.

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	//���� ������ �޾ƿ´�.

	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	//���� ������ ����Ѵ�.

	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	//������ ������ ũ�⸦ ���ؼ� �����Ѵ�.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//���� ������ġ ����

	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	//�̹��� ������ �޾ƿ��� ���� ���� ����

	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	//�����͸� �о�� lpImg�� �����Ѵ�.

	fclose(file);
	//���� �ݱ�

	lpOutImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	//����� �̹����� ������ ���� ����

	for (i = 0; i < hinfo.biHeight; i++)
	{
		for (j = 0; j < hinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize + 3 * j + 0] = lpImg[i * rwsize + 3 * j + 0];  // B
			lpOutImg[i * rwsize + 3 * j + 1] = 0;  // G
			lpOutImg[i * rwsize + 3 * j + 2] = 0;  // R
		}
	}
	//BGR �߿��� B�� ���� �����ؼ� IpOutImg�� �����Ѵ�.

	hinfo.biBitCount = 24;
	//bitcount�� 24�� �����Ѵ�.

	file = fopen("blue.bmp", "wb");
	//������ �����Ѵ�.

	fwrite(&hf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&hinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(lpOutImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	//bmf ����, ����, �̹��� ���� ������ �� ������ �ݴ´�.

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
	//���� �Ȱ��� ������ �ݺ��ϴµ� ���⿡���� BGR �߿� G�� ���� ����ϰ� ������ ���� ��� 0���� ���� �̹����� ����Ѵ�.

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
	//���� �Ȱ��� ���������� BGR�� R�� ���� ����ϰ� �������� ���� 0���� ���� �̹����� ����Ѵ�.

	free(lpImg);
	free(lpOutImg);
	//���� �Ҵ��� �����Ѵ�.
	
	printf("Check blue.bmp, green.bmp, red.bmp!!!\n\n");
}

void paletteswap()
{
	int i, j;
	BYTE R, G, B, GRAY;
	RGBQUAD* oripal;
	RGBQUAD* swappal;
	//RGBQUAD �����͸� 2�� �����ؼ� �ϳ��� ���� RGB, ������ �ϳ��� �ٲ� RGB�� �����Ѵ�.

	BITMAPFILEHEADER ohf;
	BITMAPINFOHEADER ohinfo;

	printf("RUN paletteswap()\n\n");

	file = fopen("logo.bmp", "rb");

	if (file == NULL)
	{
		printf("Error At File open!!!\n");
		exit(1);
	}
	//���� ���� ���н� ���� ���� ���

	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);

	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	//������ bmf�� �ƴҽ� ���� ���� ���

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);
	//info�� �о�´�.

	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	printf("Palette has %d color \n", hinfo.biClrUsed);
	//info�� ���ؼ� ����Ѵ�.

	ohf = hf;
	ohinfo = hinfo;
	//����� �̹����� �޾ƿ� �̹����� �����ϰ� �����Ѵ�.

	oripal = (RGBQUAD*)malloc(sizeof(RGBQUAD) * hinfo.biClrUsed);
	fread(oripal, sizeof(RGBQUAD), hinfo.biClrUsed, file);
	//RGBQUAD �����Ҵ� �� ���Ϸκ��� ���� �޾ƿ´�.

	for (i = 0; i < hinfo.biClrUsed; i++)
	{
		printf("Original palette %d B : %d\n", i, oripal[i].rgbBlue);
		printf("Original palette %d G : %d\n", i, oripal[i].rgbGreen);
		printf("Original palette %d R : %d\n\n", i, oripal[i].rgbRed);
	}
	//���Ͽ��� �о�� ���� for���� Ȱ���� ����Ѵ�.


	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(ohinfo.biBitCount * ohinfo.biWidth);
	//bmf �̹��� ���� ������ ���� rwsize�� ��ü ������ �������� rwsize2�� �����Ѵ�.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//������ ��ġ�� �����Ѵ�.

	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);

	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	//�̹��� �����͸� �ҷ��´�.

	fclose(file);

	lpOutImg = lpImg;
	//����� �̹����� �ҷ��� �̹����� �����Ѵ�.

	swappal = (RGBQUAD*)malloc(sizeof(RGBQUAD) * hinfo.biClrUsed);
	int buf;
	for (i = 0; i < hinfo.biClrUsed; i++)
	{
		printf("input palette %d B : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbBlue = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		//Blue�� ���� ���� ���� �Ŀ� 255�� 0 ������ ������ �ٲ� rbgBlue�� �־��ش�.
		printf("input palette %d G : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbGreen = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		// Green�� ���� ���� ���� �Ŀ� 255�� 0 ������ ������ �ٲ� rbgBlue�� �־��ش�.
		printf("input palette %d R : ", i);
		scanf("%d", &buf);
		clearinputbuffer();
		swappal[i].rgbRed = buf > 255 ? (unsigned char)255 : buf < 0 ? 0 : (unsigned char)buf;
		// Red�� ���� ���� ���� �Ŀ� 255�� 0 ������ ������ �ٲ� rbgBlue�� �־��ش�.
		printf("\n");
	}

	file = fopen("logo_swap.bmp", "wb");

	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(swappal, sizeof(RGBQUAD), hinfo.biClrUsed, file);
	fwrite(lpOutImg, sizeof(char), rwsize2 * hinfo.biHeight, file);
	fclose(file);
	//�ȷ�Ʈ ���� �޾� ������ �� bmf ���� ����, ����, �ȷ�Ʈ, �̹��� ������ �����ؼ� ������ �ϼ��Ѵ�.

	free(lpImg);
	free(oripal);
	free(swappal);
	//���� �Ҵ��� �����Ѵ�.
	printf("logo_swap.bmp!!\n\n");
}

void clearinputbuffer() // �Է� ���� Ŭ����
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
	//������ ����� ���µ��� �ʾ��� ��� ���� ���� ���
	fread(&hf, sizeof(BITMAPFILEHEADER), 1, file);

	if (hf.bfType != 0x4D42)
	{
		printf("File is NOT BMP\n");
		exit(1);
	}
	//��Ʈ�� ������ �ƴҰ�� ���� ���� ���

	fread(&hinfo, sizeof(BITMAPINFOHEADER), 1, file);

	printf("File size : %d\n", hf.bfSize);
	printf("offset : %d\n", hf.bfOffBits);
	printf("Image Size : (%dX%d)\n", hinfo.biWidth, hinfo.biHeight);
	printf("%d BPP \n", hinfo.biBitCount);
	//���Ͽ� ���� ���� ���

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
	//p1x, p1y, p2x, p2y�� �ܼ� â���� ���� �޾ƿ´�.

	if (p1x<0 || p1x>hinfo.biWidth || p1y<0 || p1y>hinfo.biHeight || p2x<0 || p2x>hinfo.biWidth || p2y<0 || p2y>hinfo.biHeight)
	{
		printf(" check your input!!! \n");
		return -1;
	}
	//���� �� ������ ������ ����� ���� �Էµ��� ��� �ٽ� �Է��϶�� ���� ������ ����Ѵ�.

	if (p1x > p2x)
	{
		fi = p1x;
		p1x = p2x;
		p2x = fi;
	}
	//p1x�� p2x���� Ŭ ��쿡�� ���� ����Ī���ش�.

	if (p1y > p2y)
	{
		fi = p1y;
		p1y = p2y;
		p2y = fi;
	}
	//p1y�� p2y���� �� Ŭ ��� ���� ����Ī���ش�.

	ohf = hf;
	ohinfo = hinfo;

	ohinfo.biWidth = p2x - p1x + 1;
	ohinfo.biHeight = p2y - p1y + 1;
	//biWidth�� biHeight�� �Է� �޾Ҵ� ���鿡�� �����Ͽ� �����Ѵ�.

	rwsize = WIDTHBYTES(hinfo.biBitCount * hinfo.biWidth);
	rwsize2 = WIDTHBYTES(ohinfo.biBitCount * ohinfo.biWidth);
	//������ ������ ������� ��ü ������ ����� ���ؼ� �����Ѵ�.

	ohf.bfSize = rwsize2 * ohinfo.biHeight + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//��Ʈ�� ������ ��ü ����� ���Ѵ�.

	fseek(file, hf.bfOffBits, SEEK_SET);
	//���� ��ġ ����
	lpImg = (BYTE*)malloc(rwsize * hinfo.biHeight);
	fread(lpImg, sizeof(char), rwsize * hinfo.biHeight, file);
	fclose(file);
	//lpImg�� ���� �Ҵ����� �Ŀ� fread�� ���� �����Ѵ�.

	lpOutImg = (BYTE*)malloc(rwsize2 * ohinfo.biHeight);

	//����� �̹����� ���� ������ ���� �Ҵ��Ѵ�.

	for (i = 0; i < ohinfo.biHeight; i++)
	{
		for (j = 0; j < ohinfo.biWidth; j++)
		{
			lpOutImg[i * rwsize2 + 3 * j + 0] = lpImg[(i + p1y) * rwsize + 3 * (j + p1x) + 0];
			lpOutImg[i * rwsize2 + 3 * j + 1] = lpImg[(i + p1y) * rwsize + 3 * (j + p1x) + 1];
			lpOutImg[i * rwsize2 + 3 * j + 2] = lpImg[(i + p1y) * rwsize + 3 * (j + p1x) + 2];
		}
	}
	//���� �̹������� p1y��ŭ y������ �а� p1x��ŭ x������ �о ���� �������ִ� ������ ��ģ��.

	file = fopen("crop.bmp", "wb");
	fwrite(&ohf, sizeof(char), sizeof(BITMAPFILEHEADER), file);
	fwrite(&ohinfo, sizeof(char), sizeof(BITMAPINFOHEADER), file);
	fwrite(lpOutImg, sizeof(char), rwsize2 * ohinfo.biHeight, file);
	fclose(file);
	//����� ���� ������� �����Ͽ� ������ �����Ѵ�.
	free(lpImg);
	free(lpOutImg);
	//���� �Ҵ��� �����Ѵ�.
	printf("Check crop.bmp!!!\n\n");
}