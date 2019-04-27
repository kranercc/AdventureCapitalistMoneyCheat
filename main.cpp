#include <windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h> 
#include <tchar.h>


DWORD pid;



DWORD off1, off2, off3, off4, off5;
DWORD baseAddress;
char moduleName[] = "mono.dll";

int valueHealth;

//scan modules find server and copy addrs
DWORD dwGetModuleBaseAddr(TCHAR *lpszModuleName, DWORD procid) {
	//temporary holder
	DWORD baseAddrNow = 0;
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, procid);
	MODULEENTRY32 moduleEntry32 = { 0 };
	moduleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapShot, &moduleEntry32)) {

		do {
			if (_tcscmp(moduleEntry32.szModule, lpszModuleName) == 0) {

				baseAddrNow = (DWORD)moduleEntry32.modBaseAddr;
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
	DWORD clientBase = dwGetModuleBaseAddr(_T(moduleName), pid);
	

	//reading memory

	
	DWORD moneyAddress;
	DWORD newMoney, currentMoney;
	
	cout << "How much money do you want to have: ";
	cin >> newMoney;
	while (1) {
		//offset health
		ReadProcessMemory(pHandle, (LPCVOID)(clientBase + 0x001F50AC), &baseAddress, sizeof(baseAddress), NULL);
		ReadProcessMemory(pHandle, (LPCVOID)(baseAddress + 0xc4), &off1, sizeof(off1), NULL);
		ReadProcessMemory(pHandle, (LPCVOID)(off1 + 0x50), &off2, sizeof(off2), NULL);
		ReadProcessMemory(pHandle, (LPCVOID)(off2 + 0x2c), &off3, sizeof(off3), NULL);
		ReadProcessMemory(pHandle, (LPCVOID)(off3 + 0x28), &off4, sizeof(off4), NULL);

		moneyAddress = off4 + 0x18;

		ReadProcessMemory(pHandle, (LPCVOID)(moneyAddress), &currentMoney, sizeof(currentMoney), NULL);

		cout << currentMoney;

		WriteProcessMemory(pHandle, (LPVOID)(moneyAddress), &newMoney, sizeof(newMoney), 0);
		ReadProcessMemory(pHandle, (LPCVOID)(moneyAddress), &currentMoney, 4, NULL);

		cin.get();
	}
	
	return 0;

}
