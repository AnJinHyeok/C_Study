#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

int ex1() {
	int i;
	for (i = 0; i < 500; i++) {
		SetCursorPos(i, i);
		//Ŀ���� ��ġ�� i,i�� �̵���Ų��.
		Sleep(5);
		//�����̸� �ִ´�.
	}
	return 0;
}

int ex2() {
	POINT a;
	//����Ʈ�� �����ϴ� a�� �����Ѵ�.
	while (1) {
		GetCursorPos(&a);
		//Ŀ�� ��ġ�� �޾ƿ´�.
		printf("X = %d, Y = %d\n", a.x, a.y);
		//�޾ƿ� Ŀ�� ��ġ�� ����Ѵ�.
	}
	return 0;
}

void ex3() {
	HANDLE hIn, hOut;
	INPUT_RECORD rec;
	DWORD dw;
	//�޾ƿ��� �Ͱ� ����� HANDLE�� �����ϰ� ������ ���� ����ϴ� INPUT_RECORD�� ���� �� DWORD�� �����Ѵ�.

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//hIN�� INPUT �ڵ�� �����ϰ� hOut�� OUTPUT �ڵ�� �����Ѵ�.

	DWORD Mode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hIn, Mode)) printf("ERROR\n");
	Mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hIn, Mode)) printf("ERROR\n");
	//������ �߻��ϴ� ���� �����ϴ� �ڵ��̴�.

	while (1) {
		ReadConsoleInput(hIn, &rec, 1, &dw);
		//�Է� �̺�Ʈ�� ���� ���� �б����� �����ϴ� �Լ��̴�.
		if (rec.EventType == MOUSE_EVENT) {
			//���콺 ���� �̺�Ʈ�� ������ �Ǹ� ����
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
				//�� �̺�Ʈ�� ���� Ŭ���� ��� ����
				SetConsoleCursorPosition(hOut, rec.Event.MouseEvent.dwMousePosition);
				//Ŀ�� ��ġ�� �޾Ƽ� �� ��ġ�� �����Ѵ�.
				fputc('*', stdout);
				//*ǥ�ø� �ܼ�â�� ����Ѵ�.
				if (rec.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK) break;
				//���� ����Ŭ���� ������ �Ǹ� �ڵ带 �����Ѵ�.
			}
		}
	}
}

int ex4()
{
	char c;
	HANDLE hSerial;
	//hSerial�̶�� �ڵ��� �����Ѵ�.

	unsigned long bytes_written;
	//Serial�� ���� �а� ���� ���ؼ� ����
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };

	hSerial = CreateFile(L"COM2", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//hSerial�� ����� �Լ��̴�.
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("ERROR!! COM2 PORT NOT FOUND\n");
		}
		printf("ERROR!! FAIIED TO ACCESS TO COM2 SUCCESSFULLY\n");
	}
	//hSerial�� ����� �������� �ʾ��� ��� ���� ������ ����� if���̴�.

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	//dcbSerialParams�� ����� DCBlength�� �������ش�.

	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR!! FAIIED TO GET SERIAL PARAMETERS\n");
	}
	//������ ���� ��� ���� ������ ǥ���Ѵ�.

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.Parity = NOPARITY;
	dcbSerialParams.StopBits = ONESTOPBIT;
	//Serial ����� ���ؼ� �Ķ���� ������ �������ش�.
	
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR, Setting serial port state");
	}
	//�Ķ���� ���� ������ ���� ��� ���� ������ ����Ѵ�.

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	//Ÿ�Ӿƿ��� ���õ� �������� �����Ѵ�.

	if (!SetCommTimeouts(hSerial, &timeouts))
	{
		printf("ERROR!! Time Out\n");
		return 1;
		//Ÿ�Ӿƿ��� �߻��� ��� ���������� ����Ѵ�.
	}
	else
	{
		while (1)
		{
			c = getchar();
			//���� �޾ƿ´�.
			if (c == '\0')
			{
				break;
				//������ ������ ��� �����Ѵ�.
			}
			else
			{
				WriteFile(hSerial, &c, 1, &bytes_written, NULL);
				//�޾ƿ� ���� ����Ѵ�.
			}
		}
	}

	CloseHandle(hSerial);
	//hSerial�� �ݴ´�.
	return 0;
}

int ex5()
{
	char c;
	HANDLE hSerial;
	//hSerial�̶�� �ڵ��� �����Ѵ�.

	unsigned long bytes_read;
	//Serial�� ���� �б� ���ؼ� ����
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };

	hSerial = CreateFile(L"COM2", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//hSerial�� ����� �Լ��̴�.
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("ERROR!! COM2 PORT NOT FOUND\n");
		}
		printf("ERROR!! FAIIED TO ACCESS TO COM2 SUCCESSFULLY\n");
	}
	//hSerial�� ����� �������� �ʾ��� ��� ���� ������ ����� if���̴�.

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	//dcbSerialParams�� ����� DCBlength�� �������ش�.

	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR!! FAIIED TO GET SERIAL PARAMETERS\n");
	}
	//������ ���� ��� ���� ������ ǥ���Ѵ�.

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.Parity = NOPARITY;
	dcbSerialParams.StopBits = ONESTOPBIT;
	//Serial ����� ���ؼ� �Ķ���� ������ �������ش�.

	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR, Setting serial port state");
	}
	//�Ķ���� ���� ������ ���� ��� ���� ������ ����Ѵ�.

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	//Ÿ�Ӿƿ��� ���õ� �������� �����Ѵ�.

	if (!SetCommTimeouts(hSerial, &timeouts))
	{
		printf("ERROR!! Time Out\n");
		return 1;
		//Ÿ�Ӿƿ��� �߻��� ��� ���������� ����Ѵ�.
	}
	else
	{
		while (1)
		{
			ReadFile(hSerial, &c, 1, &bytes_read, NULL);
			//Serial�� �Էµ� ���� �о�´�.
			if (bytes_read == 1)
				printf("%c", c);
			//���� bytes_read�� ������ ��� �� ���� ����Ѵ�.
		}
	}

	CloseHandle(hSerial);
	//hSerial�� �ݴ´�.
	return 0;
}

int main() {
	//ex1();
	//ex2();
	//ex3();
	//ex4();
	ex5();
}