#include <Windows.h>
#include <iostream>
#include "MemMan.h"

struct myOffsets_t
{
	DWORD money = 0x18;


}myOffsets;

struct myPlayer_t
{
	double money;


}myPlayer;



MemMan mem;


using namespace std;

void info()
{
	cout << "\n\t\t\tPress Space for Info" << endl;
	cout << "\n\nControls:\n";
	cout << "\tPress INSERT to select an option !\n";
	cout << "\tPress 1 => change money \n";



}

void addSome(DWORD address, double toWhat)
{
	double newAmmount;
	cout << "Add ammount => ";
	cin >> newAmmount;

	system("cls");
	cout << "Added " << newAmmount << endl;


	mem.writeMem<double>(address, toWhat + newAmmount);
}
int main()
{
	system("color 9");
	cout << "\n\t\t\tPress Space for Info" << endl;


	DWORD pid;
	DWORD gameModule;

	double baseAddr, off1, off2, off3;



	pid = mem.getProcess("adventure-capitalist.exe");
	gameModule = mem.getModule(pid, "mono-2.0-bdwgc.dll");

	baseAddr = mem.readMem<DWORD>(gameModule + 0x0039CC30);
	off1 = mem.readMem<DWORD>(baseAddr + 0x100);
	off2 = mem.readMem<DWORD>(off1 + 0x6D0);
	off3 = mem.readMem<DWORD>(off2 + 0x28);




	char userInput[2];
	while (1)
	{
		myPlayer.money = mem.readMem<double>(off3 + myOffsets.money);

		if (GetAsyncKeyState(VK_SPACE))
		{
			system("cls");
			info();

		}
		
		if (GetAsyncKeyState(VK_INSERT))
		{
			cout << "\nSelect: ";
			cin >> userInput;
			switch (userInput[0])
			{
			case '1':
				addSome(off3 + myOffsets.money, myPlayer.money);
				break;

			}

		}
		


	}


	return 0;
}
