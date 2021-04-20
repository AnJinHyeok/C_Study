#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

int ex1() {
	int i;
	for (i = 0; i < 500; i++) {
		SetCursorPos(i, i);
		//커서의 위치를 i,i로 이동시킨다.
		Sleep(5);
		//딜레이를 넣는다.
	}
	return 0;
}

int ex2() {
	POINT a;
	//포인트를 저장하는 a를 선언한다.
	while (1) {
		GetCursorPos(&a);
		//커서 위치를 받아온다.
		printf("X = %d, Y = %d\n", a.x, a.y);
		//받아온 커서 위치를 출력한다.
	}
	return 0;
}

void ex3() {
	HANDLE hIn, hOut;
	INPUT_RECORD rec;
	DWORD dw;
	//받아오는 것과 출력할 HANDLE을 선언하고 들어오는 값을 기록하는 INPUT_RECORD를 선언 후 DWORD를 선언한다.

	hIn = GetStdHandle(STD_INPUT_HANDLE);
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//hIN을 INPUT 핸들로 설정하고 hOut을 OUTPUT 핸들로 설정한다.

	DWORD Mode = ENABLE_EXTENDED_FLAGS;
	if (!SetConsoleMode(hIn, Mode)) printf("ERROR\n");
	Mode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hIn, Mode)) printf("ERROR\n");
	//에러가 발생하는 것을 방지하는 코드이다.

	while (1) {
		ReadConsoleInput(hIn, &rec, 1, &dw);
		//입력 이벤트에 대한 값을 읽기위해 선언하는 함수이다.
		if (rec.EventType == MOUSE_EVENT) {
			//마우스 값이 이벤트로 들어오게 되면 실행
			if (rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {
				//그 이벤트가 왼쪽 클릭일 경우 실행
				SetConsoleCursorPosition(hOut, rec.Event.MouseEvent.dwMousePosition);
				//커서 위치를 받아서 그 위치를 고정한다.
				fputc('*', stdout);
				//*표시를 콘솔창에 출력한다.
				if (rec.Event.MouseEvent.dwEventFlags & DOUBLE_CLICK) break;
				//만약 더블클릭이 들어오게 되면 코드를 종료한다.
			}
		}
	}
}

int ex4()
{
	char c;
	HANDLE hSerial;
	//hSerial이라는 핸들을 선언한다.

	unsigned long bytes_written;
	//Serial에 값을 읽고 쓰기 위해서 선언
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };

	hSerial = CreateFile(L"COM2", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//hSerial을 만드는 함수이다.
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("ERROR!! COM2 PORT NOT FOUND\n");
		}
		printf("ERROR!! FAIIED TO ACCESS TO COM2 SUCCESSFULLY\n");
	}
	//hSerial이 제대로 생성되지 않았을 경우 에러 문구를 적어둔 if문이다.

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	//dcbSerialParams의 사이즈를 DCBlength에 저장해준다.

	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR!! FAIIED TO GET SERIAL PARAMETERS\n");
	}
	//문제가 있을 경우 에러 문구를 표시한다.

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.Parity = NOPARITY;
	dcbSerialParams.StopBits = ONESTOPBIT;
	//Serial 통신을 위해서 파라미터 값들을 설정해준다.
	
	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR, Setting serial port state");
	}
	//파라미터 값에 문제가 있을 경우 에러 문구를 출력한다.

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	//타임아웃에 관련된 설정들을 지정한다.

	if (!SetCommTimeouts(hSerial, &timeouts))
	{
		printf("ERROR!! Time Out\n");
		return 1;
		//타임아웃이 발생할 경우 에러문구를 출력한다.
	}
	else
	{
		while (1)
		{
			c = getchar();
			//값을 받아온다.
			if (c == '\0')
			{
				break;
				//문장이 끝났을 경우 종료한다.
			}
			else
			{
				WriteFile(hSerial, &c, 1, &bytes_written, NULL);
				//받아온 값을 출력한다.
			}
		}
	}

	CloseHandle(hSerial);
	//hSerial을 닫는다.
	return 0;
}

int ex5()
{
	char c;
	HANDLE hSerial;
	//hSerial이라는 핸들을 선언한다.

	unsigned long bytes_read;
	//Serial에 값을 읽기 위해서 선언
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };

	hSerial = CreateFile(L"COM2", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//hSerial을 만드는 함수이다.
	if (hSerial == INVALID_HANDLE_VALUE)
	{
		if (GetLastError() == ERROR_FILE_NOT_FOUND)
		{
			printf("ERROR!! COM2 PORT NOT FOUND\n");
		}
		printf("ERROR!! FAIIED TO ACCESS TO COM2 SUCCESSFULLY\n");
	}
	//hSerial이 제대로 생성되지 않았을 경우 에러 문구를 적어둔 if문이다.

	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	//dcbSerialParams의 사이즈를 DCBlength에 저장해준다.

	if (!GetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR!! FAIIED TO GET SERIAL PARAMETERS\n");
	}
	//문제가 있을 경우 에러 문구를 표시한다.

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.Parity = NOPARITY;
	dcbSerialParams.StopBits = ONESTOPBIT;
	//Serial 통신을 위해서 파라미터 값들을 설정해준다.

	if (!SetCommState(hSerial, &dcbSerialParams))
	{
		printf("ERROR, Setting serial port state");
	}
	//파라미터 값에 문제가 있을 경우 에러 문구를 출력한다.

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	//타임아웃에 관련된 설정들을 지정한다.

	if (!SetCommTimeouts(hSerial, &timeouts))
	{
		printf("ERROR!! Time Out\n");
		return 1;
		//타임아웃이 발생할 경우 에러문구를 출력한다.
	}
	else
	{
		while (1)
		{
			ReadFile(hSerial, &c, 1, &bytes_read, NULL);
			//Serial에 입력된 값을 읽어온다.
			if (bytes_read == 1)
				printf("%c", c);
			//만약 bytes_read가 들어왔을 경우 그 값을 출력한다.
		}
	}

	CloseHandle(hSerial);
	//hSerial을 닫는다.
	return 0;
}

int main() {
	//ex1();
	//ex2();
	//ex3();
	//ex4();
	ex5();
}