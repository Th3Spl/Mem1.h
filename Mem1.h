//Author: Th3Spl
//date: 29/12/2021
//Mydiscord: https://discord.gg/635ysHGDG6
//Version: Right Dist: 1.2
/*Description: 
This is a PRIVATE header for hack games better!*/

//pragma section
#pragma once
#ifndef Mem1
#define Mem1

//inclusion
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <tchar.h>
#include <fstream>
#include <vector>

using namespace std;

//World Variables    
DWORD pID = NULL;
HWND hWnd;
HANDLE pHandle = NULL;
LPCSTR procOpened;
DWORD actual;

//GetName == FindWindowA
HWND GetByName(LPCSTR procName)
{
    hWnd = FindWindowA(NULL, procName);
    procOpened = procName;
    if (hWnd == 0)
    {
        system("color 4");
        printf("Process Not Found! \nRestart this when your hWnd is open!");
        return 0;

    }
    else
    {
        system("color a");
        GetWindowThreadProcessId(hWnd, &pID);
        pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
        if (pHandle == INVALID_HANDLE_VALUE || pHandle == NULL);
        cout << "Process Attached: " << procOpened << endl << "POV of the pc: " << hWnd;
        return 0;
    }
}


//Get the base module address
uintptr_t GetModuleBaseAddress(const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pID);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}


//Get the address of the pointer
DWORD GetPointerAddress(DWORD gameBaseAddr, DWORD address, vector<DWORD> offsets)
{
    DWORD offset_null = NULL;
    ReadProcessMemory(pHandle, (LPVOID*)(gameBaseAddr + address), &offset_null, sizeof(offset_null), 0);
    DWORD pointeraddress = offset_null; // the address we need
    for (int i = 0; i < offsets.size() - 1; i++) // we dont want to change the last offset value so we do -1
    {
        ReadProcessMemory(pHandle, (LPVOID*)(pointeraddress + offsets.at(i)), &pointeraddress, sizeof(pointeraddress), 0);
    }
    return pointeraddress += offsets.at(offsets.size() - 1); // adding the last offset
}


//Function for semplify the process for find the PtrAddr for WriteMem
DWORD GetPtrAddr(const wchar_t* client_addr, DWORD pointer, vector<DWORD> offsets)
{   
    const wchar_t* client_address = client_addr;
    DWORD ptr = pointer;
    vector<DWORD> offsetsaddr = offsets;
    uintptr_t baseModuleAddress = GetModuleBaseAddress(client_address);
    DWORD finaPtr = GetPointerAddress(baseModuleAddress, ptr, offsetsaddr);
    return finaPtr;
}


//Wrtite in the memory of the selected process
DWORD WriteMem(DWORD ptrAddress, int changedValue1)
{
    DWORD ptrAddr = ptrAddress;
    int changedValue = changedValue1;
    HANDLE phandle = pHandle;
    WriteProcessMemory(phandle, (LPVOID*)(ptrAddr), &changedValue, 4, 0);
    return 0;
}

DWORD ReadProcMem(DWORD ptraDDR)
{
    int a;
    DWORD pointer = ptraDDR;
    HANDLE phandle = pHandle;
    ReadProcessMemory(phandle, (LPCVOID)(pointer), &a, sizeof(a), nullptr);
    return a;
}

DWORD Allin()
{
    return 0;
}



#endif