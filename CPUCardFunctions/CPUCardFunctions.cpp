// CPUCardFunctions.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CPUCardFunctions.h"


// This is an example of an exported variable
CPUCARDFUNCTIONS_API int nCPUCardFunctions=0;

// This is an example of an exported function.
CPUCARDFUNCTIONS_API int fnCPUCardFunctions(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see CPUCardFunctions.h for the class definition
CCPUCardFunctions::CCPUCardFunctions()
{
	return;
}
