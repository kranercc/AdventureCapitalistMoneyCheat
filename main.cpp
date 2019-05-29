#include <windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h> 
#include <tchar.h>


DWORD pid;



DWORD64 off1, off2, off3, off4, off5;
DWORD64 baseAddress;
char moduleName[] = "mono-2.0-bdwgc.dll";

int valueHealth;

//scan modules find server and copy addrs
DWORD64 dwGetModuleBaseAddr(TCHAR *lpszModuleName, DWORD64 procid) {
	//temporary holder
	DWORD64 baseAddrNow = 0;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procid);
	MODULEENTRY32 moduleEntry32 = { 0 };
	moduleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapShot, &moduleEntry32)) {

		do {
			if (_tcscmp(moduleEntry32.szModule, lpszModuleName) == 0) {

				baseAddrNow = (DWORD64)moduleEntry32.modBaseAddr;
				break;

			}

		} while (Module32Next(hSnapShot, &moduleEntry32));


	}
	CloseHandle(hSnapShot);
	return baseAddrNow;

}


using namespace std;
int main() {

	HWND hwnd = FindWindowA(0, ("AdCap!"));

	// get the pid of the window and place it in pid
	GetWindowThreadProcessId(hwnd, &pid);

	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	//get client base addr
	DWORD64 clientBase = dwGetModuleBaseAddr(_T(moduleName), pid);


	double newMoney = 0;
	DWORD64 moneyAddress;
	double currentMoney = 0;

	cout << "How much money do you want to add to your current balance: ";
	cin >> newMoney;

	//offset health
	ReadProcessMemory(pHandle, (LPCVOID)(clientBase + 0x0039CC58), &baseAddress, sizeof(double), NULL);
	ReadProcessMemory(pHandle, (LPCVOID)(baseAddress + 0x80), &off1, sizeof(double), NULL);
	ReadProcessMemory(pHandle, (LPCVOID)(off1 + 0x708), &off2, sizeof(double), NULL);
	ReadProcessMemory(pHandle, (LPCVOID)(off2 + 0xc8), &off3, sizeof(double), NULL);
	ReadProcessMemory(pHandle, (LPCVOID)(off3 + 0x28), &off4, sizeof(double), NULL);

	moneyAddress = off4 + 0x18;

	//logic : get the amount we currently have, and then add the new money to it
	ReadProcessMemory(pHandle, (LPCVOID)(moneyAddress), &currentMoney, sizeof(double), NULL);
	cout << currentMoney;

	newMoney += currentMoney;
	WriteProcessMemory(pHandle, (LPVOID)(moneyAddress), &newMoney, sizeof(newMoney), 0);
	

	return 0;

}
