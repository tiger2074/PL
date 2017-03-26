///////////////////////////////////////////////////////////////////////
// File: Plugins.cpp
// Date: 03/17/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////

#include "Plugins.h"

Plugins::Plugins(std::vector<const char*> &filepaths)
{
	for (int i(0); i < filepaths.size(); i++)
	{
		this->filepaths.push_back(filepaths[i]);
	}
}

bool Plugins::loadAll()
{
	// Loads all DLLs for amount of known filepaths
	for (int i(0); i < filepaths.size(); i++)
	{
		if (load(filepaths[i]))
		{
			return 1;
		}
	}
}

bool Plugins::load(const char* filepath)
{
	// Already-existing check
	for (int i(0); i < DLLs.size(); i++)
	{
		if (DLLs[i].filepath == filepath)
		{
			std::cout << "DLL is already loaded!" << std::endl;
			return 1;
		}
		else
		{
			continue;
		}
	}

	// Creates and loads new DLL obejct
	DLL newDLL;
	newDLL.filepath = filepath;
	// Load DLL into memory
	std::cout << "Loading " << filepath << ". . . " << std::endl;
	newDLL.DLLID = LoadLibrary(filepath);
	if (!newDLL.DLLID)
	{
		std::cout << "DLL not found!" << std::endl;
		return 1;
	}
	// Import entry function from DLL
	newDLL.entryFunction = (DLLentryFunc)GetProcAddress(newDLL.DLLID, "entryFunction");
	if (!newDLL.entryFunction)
	{
		FreeLibrary(newDLL.DLLID);
		std::cout << "Could not locate entry function!" << std::endl;
		return 1;
	}
	// Import update function from DLL
	newDLL.update = (DLLupdateFunc)GetProcAddress(newDLL.DLLID, "update");
	if (!newDLL.update)
	{
		FreeLibrary(newDLL.DLLID);
		std::cout << "Could not locate update function!" << std::endl;
		return 1;
	}
	// Import setCallback function from DLL
	newDLL.setCallback = (DLLSetCallbackFn)GetProcAddress(newDLL.DLLID, "setCallback");
	if (!newDLL.setCallback) {
		FreeLibrary(newDLL.DLLID);
		std::cout << "Could not locate callback function!" << std::endl;
		return 1;
	}

	newDLL.setCallback(callback);
	DLLs.push_back(newDLL);
	
	std::cout << newDLL.filepath << " successfully loaded and callback set!" << std::endl;
	return 0;
}

void Plugins::entryFunctions()
{
	int x(2);

	for (int i(0); i < DLLs.size(); i++)
	{
		DLLs[i].entryFunction(&x);
	}
}

void Plugins::updateAll()
{
	// Calls all update functions
	for (int i(0); i < DLLs.size(); i++)
	{
		DLLs[i].update();
	}
}

void Plugins::freeAllDLLs()
{
	for (int i(0); i < DLLs.size(); i++)
	{
		FreeLibrary(DLLs[i].DLLID);
	}
}

void callback(int message)
{
	std::cout << "Callback called! value= " << message << std::endl;
}