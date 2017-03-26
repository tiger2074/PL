///////////////////////////////////////////////////////////////////////
// File: dllmain.cpp
// Date: 03/14/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////

#include "dllAPI.h"

// dllmain.cpp : Defines the entry point for the DLL application.

int x;

// entryFunction : Called by caller app at dll loadup, sets initial positions and object startup creation data
int entryFunction(int* val)
{
	x = *val;

	*val = x + 1; // Pass value to caller by reference example
	dllCallback(*val + 1); // Pass value to caller through callback function example
	return x; // Pass value to caller through function return value example
}

// update : Called by called app at every loop
bool update()
{
	return true;
}