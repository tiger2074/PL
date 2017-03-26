///////////////////////////////////////////////////////////////////////
// File: DLL.h
// Date: 03/17/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////


#pragma once

#include <Windows.h>

typedef int(__cdecl *DLLentryFunc)(int*);
typedef bool(__cdecl *DLLupdateFunc)(void);
typedef void(__cdecl *DLLCallbackFn)(int);
typedef void(__cdecl *DLLSetCallbackFn)(DLLCallbackFn);

struct DLL
{
	DLLentryFunc entryFunction;
	DLLupdateFunc update;
	DLLSetCallbackFn setCallback;
	HINSTANCE DLLID;
	const char* filepath;
	bool state = true;

	bool load(const char* filepath);
};