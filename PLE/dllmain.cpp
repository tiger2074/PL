///////////////////////////////////////////////////////////////////////
// File: dllmain.cpp
// Date: 03/14/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////

// dllmain.cpp : Defines the entry point for the DLL application.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef PLE_EXPORTS
#define PLE_API __declspec(dllexport)
#else
#define PLE_API __declspec(dllimport)
#endif

// Exported entry function
extern "C" PLE_API int entryFunction(int*);
// Exported Callback function
extern "C" PLE_API void setCallback(void(*callback)(int));
// Exported Update function
extern "C" PLE_API bool update();

// Local callback function to send message to caller app
void(*dllCallback)(int);

// exported function.
int entryFunction(int* val)
{
	int x = *val;

	*val = x + 1;
	dllCallback(*val + 1);
	return x;
}

void setCallback(void(*callback)(int)) {
	dllCallback = callback;
}

bool update()
{
	return true;
}