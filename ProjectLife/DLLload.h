///////////////////////////////////////////////////////////////////////
// File: DLLload.h
// Date: 03/14/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////

#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>

typedef int(__cdecl *DLLentryFunc)(int*);
typedef bool(__cdecl *DLLupdateFunc)(void);
typedef void(__cdecl *DLLCallbackFn)(int);
typedef void(__cdecl *DLLSetCallbackFn)(DLLCallbackFn);

class DLLload
{
private:	
	bool OpenDLL(const char* filepath);

public:
	DLLentryFunc entryFunction;
	DLLupdateFunc update;
	HINSTANCE DLLID;
	const char* filepath;
	bool state = true;

	DLLload(const char* filepath);
	~DLLload();
};


void callback(int message);
bool addDll(const char*, std::vector<DLLload*> &DLLs);
void freeDlls(std::vector<DLLload*> &DLLs);