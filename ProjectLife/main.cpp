///////////////////////////////////////////////////////////////////////
// File: main.cpp
// Date: 03/14/2017
// Rev: 01
// Creator: Instantae
// Notice: (C) Copyright 2017 Kelvin Milne. All Rights reserved
///////////////////////////////////////////////////////////////////////

// includes <Windows.h>, <iostream> and <vector>
#include "Plugins.h"
// Additional Includes 
#include <iomanip>

struct worldPositions
{
	signed long long xValue;
	signed long long yValue;
	signed long long zValue;

	worldPositions(long long x , long long y , long long z)
	{
		xValue = x;
		yValue = y;
		zValue = z;
	}
};


int main()
{
	std::cout << std::setprecision(10) << std::fixed;

	std::vector<const char*> DLLfileNames;
	DLLfileNames.push_back("PLE.dll");
	DLLfileNames.push_back("PLGE.dll");
	DLLfileNames.push_back("PLPE.dll");
	

	Plugins plugins(DLLfileNames);
	DLLfileNames.~DLLfileNames();
	plugins.loadAll();

	// Values would be assigned through DLL function call
	signed long long inxValue((signed long long)9223372036854775807);
	signed long long inyValue((signed long long)9223372036854775806);
	signed long long inzValue((signed long long)-9223372036854775806);

	std::vector<worldPositions> objectPositions;
	for (int i(0); i < 10; i++)
	{
		worldPositions object(inxValue, inyValue, inzValue);
		objectPositions.push_back(object);
	}

	plugins.entryFunctions();
	plugins.updateAll();


	std::cout << "App closing..." << std::endl;
	plugins.freeAllDLLs();
	
	return 0;
}