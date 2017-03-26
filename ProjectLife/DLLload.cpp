///////////////////////////////////////////////////////////////////////
// File: DLLload.cpp
// Date: 03/16/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////

// includes <Windows.h>, <iostream> and <vector>
#include "DLLload.h"
// Additional Includes 

DLLload::DLLload(const char* filepath)
{
	if (OpenDLL(filepath))
		state = false;
	else
		state = true;

	this->filepath = filepath;
}

DLLload::~DLLload()
{
	FreeLibrary(DLLID);
	std::cout << "library: " << filepath << " freed!" << std::endl;
}

bool DLLload::OpenDLL(const char* filepath)
{
	std::cout << "Loading " << filepath << "..." << std::endl;
	DLLID = LoadLibrary(filepath);

	if (!DLLID)
		return 1;

	// Import entry function from DLL
	entryFunction = (DLLentryFunc)GetProcAddress(DLLID, "entryFunction");
	if (!entryFunction)
	{
		std::cout << "Could not locate entry function!" << std::endl;
		return 1;
	}
	// Import update function from DLL
	update = (DLLupdateFunc)GetProcAddress(DLLID, "update");
	if (!update)
	{
		std::cout << "Could not locate update function!" << std::endl;
		return 1;
	}
	return 0;
}


void callback(int message) {
	std::cout << "Callback called! value= " << message << std::endl;
}

// Adds a DLL and its functions to a provided vector of DLLload's 
bool addDll(const char* filepath, std::vector<DLLload*> &DLLs)
{
	// Create a new DLL object
	DLLload* aDll = new DLLload(filepath);
	if (!aDll->state)
	{
		std::cout << "Failed loading dll: " << aDll->filepath << "!" << std::endl;
		FreeLibrary(aDll->DLLID);
		return 1;
	}

	// Set Callback to DLL
	DLLSetCallbackFn setCallback = (DLLSetCallbackFn)GetProcAddress(aDll->DLLID, "setCallback");
	if (!setCallback) {
		FreeLibrary(aDll->DLLID);
		std::cout << "Invalid callback to: " << aDll->filepath << "!" << std::endl;
		return 1;
	}
	setCallback(callback);
	// Add DLL to vector
	DLLs.push_back(aDll);
	std::cout << aDll->filepath << " succesfully loaded and callback set!" << std::endl;
	return 0;
}

// Frees DLL's from  memory
void freeDlls(std::vector<DLLload*> &DLLs)
{
	for (int i(0); i < DLLs.size(); i++)
	{
		DLLs[i]->~DLLload();
		
	}
}