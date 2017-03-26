///////////////////////////////////////////////////////////////////////
// File: dllAPI.h
// Date: 03/16/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#ifdef PLPE_EXPORTS
#define PLE_API __declspec(dllexport)
#else
#define PLE_API __declspec(dllimport)
#endif

// Local callback function to send message to caller app
void(*dllCallback)(int);

// Exported entry function
extern "C" PLE_API int entryFunction(int* val);

// Exported Callback function
extern "C" PLE_API void setCallback(void(*callback)(int))
{
	dllCallback = callback;
}

// Exported Update function
extern "C" PLE_API bool update();