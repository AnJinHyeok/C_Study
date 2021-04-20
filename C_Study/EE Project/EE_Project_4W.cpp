#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>

int main()
{
	char str[30] = "";
	//실시간 좌표값을 출력하기 위한 문자열이다.
	char str_num[10];
	//숫자를 문자열로 바꿔주기 위한 변수이다.
	char c;
	//값을 읽어오기 위한 변수이다.
	HANDLE hSerial, hIn, hOut;
	INPUT_RECORD rec;
	DWORD dw;
	//핸들하기 위한 hSerial, hIn, hOut을 선언하고 INPUT_RECORD로 rec를, DWORD로 dw를 선언한다.

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//각각 hIn과 hOut에 핸들을 선언한다.

	DWORD Mode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hIn, Mode)) printf("ERROR\n");
	Mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hIn, Mode)) printf("ERROR\n");
	//오류가 발생하지 않도록 선언해주는 부분이다.

	unsigned long bytes_written;
	unsigned long bytes_read;
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };
	//읽고 쓰기를 위해 bytes_written과 bytes_read를 선언해준다.

	POINT p;
	//위치를 받아오기 위한 포인트 변수이다.

	int count = 0;
	int number_x = 0;
	int number_y = 0;
	//x값과 y값을 받아오기 위한 카운트를 담는 변수이다.

	hSerial = CreateFile(L"COM2", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("ERROR!! COM2 PORT NOT FOUND\n");
		}
		printf("ERROR!! FAIIED TO ACCESS TO COM2 SUCCESSFULLY\n");
	}
	//hSerial 선언과 그 오류 발생시 에러 값 출력을 위한 함수이다.

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	//사이즈 값을 DCBlength에 넣어주는 코드이다.

	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR!! FAIIED TO GET SERIAL PARAMETERS\n");
	}
	//에러 문자를 출력하는 함수이다.

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.Parity = NOPARITY;
	dcbSerialParams.StopBits = ONESTOPBIT;
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR, Setting serial port state");
	}
	//파라미터 설정을 위한 선언들이다.

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;\
	//타임아웃 설정을 위한 코드이다.

	if (!SetCommTimeouts(hSerial, &timeouts))
	{
		printf("ERROR!! Time Out\n");
		return 1;
	}
	else
	{
		while (1)
		{
			ReadConsoleInput(hIn, &rec, 1, &dw);
			if (rec.EventType == MOUSE_EVENT) {
				//마우스 이벤트 발생시 들어오게 된다.
				if (rec.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK) {
					//더블클릭이 발생하면
					WriteFile(hSerial, "DoubleClick!!", 13, &bytes_written, NULL);
					WriteFile(hSerial, "\n\r", strlen("\n\r"), &bytes_written, NULL);
					WriteFile(hSerial, "Xpos : ", 7, &bytes_written, NULL);
					//DoubleClick을 출력하고 Xpos값을 받는다.
					while (1)
					{
						ReadFile(hSerial, &c, 1, &bytes_read, NULL);
						//Xpos값을 받아온다.
						if (bytes_read == 1) {
							WriteFile(hSerial, &c, 1, &bytes_written, NULL);
							number_x += atoi(&c) * pow(10, (3 - count));
							count++;
							//만약 받아오게 되면 그 값을 출력하고 number_x에 값을 정수로 넣어준다. 그 후 count를 증가시켜 4번 값을 받으면 밖으로 나오게 된다.
						}
						if (count == 4) {
							break;
						}
					}
					WriteFile(hSerial, "\n\r", strlen("\n\r"), &bytes_written, NULL);
					WriteFile(hSerial, "Ypos : ", 7, &bytes_written, NULL);
					//Ypos를 출력하고 값을 받는다.
					count = 0;
					while (1)
					{
						ReadFile(hSerial, &c, 1, &bytes_read, NULL);
						//Ypos값을 받아온다.
						if (bytes_read == 1) {
							WriteFile(hSerial, &c, 1, &bytes_written, NULL);
							number_y += atoi(&c) * pow(10, (3 - count));
							count++;
							//만약 받아오게 되면 그 값을 출력하고 number_y에 값을 정수로 넣어준다. 그 후 count를 증가시켜 4번 값을 받으면 밖으로 나오게 된다.
						}
						if (count == 4) {
							break;
						}
					}
					WriteFile(hSerial, "\n\r", strlen("\n\r"), &bytes_written, NULL);
					SetCursorPos(number_x, number_y);
					//커서의 위치를 number_x와 number_y로 옮긴다.
				}
			}
			GetCursorPos(&p);
			strcat(str, "Xpos : ");
			sprintf(str_num, "%04d", p.x);
			strcat(str, str_num);
			strcat(str, " Ypos : ");
			strcpy(str_num, "");
			sprintf(str_num, "%04d", p.y);
			strcat(str, str_num);
			WriteFile(hSerial, str, strlen(str), &bytes_written, NULL);
			WriteFile(hSerial, "\n\r", strlen("\n\r"), &bytes_written, NULL);
			strcpy(str_num, "");
			strcpy(str, "");
			//실시간으로 좌표값을 출력하는 코드로 GetCursorPos를 통해 값을 불러오고 sprintf와 strcat, strcpy를 활용해 하나의 문자열로 만들고 한번에 출력해준다.
			Sleep(100);
		}
	}

	CloseHandle(hSerial);
	//시리얼을 닫는다.
	return 0;
}