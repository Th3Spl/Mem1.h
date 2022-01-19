//Author: Th3Spl
//Date: 18/01/2022
//myDiscord: https://discord.gg/635ysHGDG6 (pls join us ù_ù)

///////////////////////////////////////////////////////////|
#include "Mem1.h" /////// You only need my header :) //////|
///////////////////////////////////////////////////////////|

int main()
{
	LPCSTR WindowName = "AssaultCube"; // The name of the Window
	const wchar_t* moduleBaseName = L"ac_client.exe"; // this can be the .exe or the .dll part where there is the value
	DWORD ptrAddress = 0x00187C0C; //  <--- This should be your game pointer
	vector<DWORD> offsets{ 0xEC }; // <--- here you should insert your pointers
	int newValue = 999; // The new Value 
	GetByName(WindowName); //Attach the window
	DWORD finalPtrAddr = GetPtrAddr(moduleBaseName, ptrAddress, offsets); //Get the final ptr address
	WriteMem(finalPtrAddr, newValue); // Write on the process
}