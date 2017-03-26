///////////////////////////////////////////////////////////////////////
// File: Plugins.h
// Date: 03/17/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <iostream>
#include <Windows.h>


typedef int(__cdecl *DLLentryFunc)(int*);
typedef bool(__cdecl *DLLupdateFunc)(void);
typedef void(__cdecl *DLLCallbackFn)(int);
typedef void(__cdecl *DLLSetCallbackFn)(DLLCallbackFn);


class Plugins
{
private:
	
	struct DLL
	{
		DLLentryFunc entryFunction;
		DLLupdateFunc update;
		DLLSetCallbackFn setCallback;
		HINSTANCE DLLID;
		const char* filepath;
		bool state = true;
	};

	std::vector<DLL> DLLs;
	std::vector<const char*> filepaths;

public:
	bool loadAll();
	bool load(const char*);
	void entryFunctions();
	void updateAll();

	void freeAllDLLs();

	Plugins(std::vector<const char*> &filepaths);

};

void callback(int message);