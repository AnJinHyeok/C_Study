#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <math.h>

int main()
{
	char str[30] = "";
	//�ǽð� ��ǥ���� ����ϱ� ���� ���ڿ��̴�.
	char str_num[10];
	//���ڸ� ���ڿ��� �ٲ��ֱ� ���� �����̴�.
	char c;
	//���� �о���� ���� �����̴�.
	HANDLE hSerial, hIn, hOut;
	INPUT_RECORD rec;
	DWORD dw;
	//�ڵ��ϱ� ���� hSerial, hIn, hOut�� �����ϰ� INPUT_RECORD�� rec��, DWORD�� dw�� �����Ѵ�.

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//���� hIn�� hOut�� �ڵ��� �����Ѵ�.

	DWORD Mode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hIn, Mode)) printf("ERROR\n");
	Mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hIn, Mode)) printf("ERROR\n");
	//������ �߻����� �ʵ��� �������ִ� �κ��̴�.

	unsigned long bytes_written;
	unsigned long bytes_read;
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };
	//�а� ���⸦ ���� bytes_written�� bytes_read�� �������ش�.

	POINT p;
	//��ġ�� �޾ƿ��� ���� ����Ʈ �����̴�.

	int count = 0;
	int number_x = 0;
	int number_y = 0;
	//x���� y���� �޾ƿ��� ���� ī��Ʈ�� ��� �����̴�.

	hSerial = CreateFile(L"COM2", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("ERROR!! COM2 PORT NOT FOUND\n");
		}
		printf("ERROR!! FAIIED TO ACCESS TO COM2 SUCCESSFULLY\n");
	}
	//hSerial ����� �� ���� �߻��� ���� �� ����� ���� �Լ��̴�.

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	//������ ���� DCBlength�� �־��ִ� �ڵ��̴�.

	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR!! FAIIED TO GET SERIAL PARAMETERS\n");
	}
	//���� ���ڸ� ����ϴ� �Լ��̴�.

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.Parity = NOPARITY;
	dcbSerialParams.StopBits = ONESTOPBIT;
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR, Setting serial port state");
	}
	//�Ķ���� ������ ���� ������̴�.

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;\
	//Ÿ�Ӿƿ� ������ ���� �ڵ��̴�.

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
				//���콺 �̺�Ʈ �߻��� ������ �ȴ�.
				if (rec.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK) {
					//����Ŭ���� �߻��ϸ�
					WriteFile(hSerial, "DoubleClick!!", 13, &bytes_written, NULL);
					WriteFile(hSerial, "\n\r", strlen("\n\r"), &bytes_written, NULL);
					WriteFile(hSerial, "Xpos : ", 7, &bytes_written, NULL);
					//DoubleClick�� ����ϰ� Xpos���� �޴´�.
					while (1)
					{
						ReadFile(hSerial, &c, 1, &bytes_read, NULL);
						//Xpos���� �޾ƿ´�.
						if (bytes_read == 1) {
							WriteFile(hSerial, &c, 1, &bytes_written, NULL);
							number_x += atoi(&c) * pow(10, (3 - count));
							count++;
							//���� �޾ƿ��� �Ǹ� �� ���� ����ϰ� number_x�� ���� ������ �־��ش�. �� �� count�� �������� 4�� ���� ������ ������ ������ �ȴ�.
						}
						if (count == 4) {
							break;
						}
					}
					WriteFile(hSerial, "\n\r", strlen("\n\r"), &bytes_written, NULL);
					WriteFile(hSerial, "Ypos : ", 7, &bytes_written, NULL);
					//Ypos�� ����ϰ� ���� �޴´�.
					count = 0;
					while (1)
					{
						ReadFile(hSerial, &c, 1, &bytes_read, NULL);
						//Ypos���� �޾ƿ´�.
						if (bytes_read == 1) {
							WriteFile(hSerial, &c, 1, &bytes_written, NULL);
							number_y += atoi(&c) * pow(10, (3 - count));
							count++;
							//���� �޾ƿ��� �Ǹ� �� ���� ����ϰ� number_y�� ���� ������ �־��ش�. �� �� count�� �������� 4�� ���� ������ ������ ������ �ȴ�.
						}
						if (count == 4) {
							break;
						}
					}
					WriteFile(hSerial, "\n\r", strlen("\n\r"), &bytes_written, NULL);
					SetCursorPos(number_x, number_y);
					//Ŀ���� ��ġ�� number_x�� number_y�� �ű��.
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
			//�ǽð����� ��ǥ���� ����ϴ� �ڵ�� GetCursorPos�� ���� ���� �ҷ����� sprintf�� strcat, strcpy�� Ȱ���� �ϳ��� ���ڿ��� ����� �ѹ��� ������ش�.
			Sleep(100);
		}
	}

	CloseHandle(hSerial);
	//�ø����� �ݴ´�.
	return 0;
}