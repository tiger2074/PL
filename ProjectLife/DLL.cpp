///////////////////////////////////////////////////////////////////////
// File: DLL.cpp
// Date: 03/17/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////

#include "DLL.h"
#include <iostream>

bool DLL::load(const char* filepath)
{
	this->filepath = filepath;
	// Load DLL into memory
	std::cout << "Loading " << filepath << ". . ." << std::endl;
	DLLID = LoadLibrary(filepath);
	if (!DLLID)
	{
		std::cout << "DLL not found!" << std::endl;
		return 1;
	}
	// Import entry function from DLL
	entryFunction = (DLLentryFunc)GetProcAddress(DLLID, "entryFunction");
	if (!entryFunction)
	{
		FreeLibrary(DLLID);
		std::cout << "Could not locate entry function!" << std::endl;
		return 1;
	}
	// Import update function from DLL
	update = (DLLupdateFunc)GetProcAddress(DLLID, "update");
	if (!update)
	{
		FreeLibrary(DLLID);
		std::cout << "Could not locate update function!" << std::endl;
		return 1;
	}
	// Import setCallback function from DLL
	setCallback = (DLLSetCallbackFn)GetProcAddress(DLLID, "setCallback");
	if (!setCallback) {
		FreeLibrary(DLLID);
		std::cout << "Could not locate callback function!" << std::endl;
		return 1;
	}
}
