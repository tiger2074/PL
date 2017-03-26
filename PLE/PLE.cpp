// PLE.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "PLE.h"


// This is an example of an exported variable
PLE_API int nPLE=0;

// This is an example of an exported function.
PLE_API int fnPLE(void)
{
    return 42;
}

// This is the constructor of a class that has been exported.
// see PLE.h for the class definition
CPLE::CPLE()
{
    return;
}
