#include "main.h"
#include "libs.h"

int main()
{
	int timer = 24;

	//SetTimer(NULL, 0, timer, (TIMERPROC)BetterCallSaul);
	display_bomb(timer);
	return 0;
}

void display_bomb(int timer)
{
	
	HANDLE bufferConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND console = GetConsoleWindow();
	//PlaySound(MAKEINTRESOURCE(101), GetModuleHandle(NULL), SND_RESOURCE);
	HMODULE myApp = GetModuleHandleA("bomb.exe");
	PlaySound(MAKEINTRESOURCE(101), myApp, SND_RESOURCE | SND_ASYNC);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	RECT r = { 250,250,0,0 };
	MoveWindow(console, r.left, r.top, 130, 200, TRUE);
	GetConsoleScreenBufferInfo(bufferConsole, &csbi);
	csbi.dwSize.X = csbi.dwMaximumWindowSize.X;
	csbi.dwSize.Y = csbi.dwMaximumWindowSize.Y;
	SetConsoleScreenBufferSize(bufferConsole, csbi.dwSize);
	ShowScrollBar(console, SB_BOTH, FALSE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(bufferConsole, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(bufferConsole, &cursorInfo);
	//mciSendString(L"open \"song.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	//mciSendString(L"play mp3", NULL, 0, NULL);
	for (int i = 0; i < timer; ++i) {
		SetConsoleCursorPosition(bufferConsole, { 0,0 });
		std::cout << "\n #########";
		std::cout << "\n ##-" << format_number(timer-i) << "-##";
		std::cout << "\n #########";
		std::cout << "\n ##~123~##";
		std::cout << "\n ##~456~##";
		std::cout << "\n ##~789~##";
		std::cout << "\n ###~0~###";
		std::cout << "\n #########";
		Sleep(1000);
	}
	kaboom(true);
}

std::string format_number(int number) {
	std::string formatted_number = "";

	if (number < 100) {
		formatted_number = " " + std::to_string(number);
	}
	else if (number < 10) {
		formatted_number = "  " + std::to_string(number);
	}else formatted_number = std::to_string(number);
	return formatted_number;
}

void kaboom(bool riko)
{
	if (riko == true) {
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;
		OpenProcessToken(GetCurrentProcess(),TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,&tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1; 
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES)NULL, 0);
		ExitWindows(EWX_POWEROFF | EWX_FORCE,SHTDN_REASON_MINOR_OTHER);
		//ExitWindows(EWX_LOGOFF, EWX_FORCE);
	}
}