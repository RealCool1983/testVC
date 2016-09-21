// DLL_UI_TEST01.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "main.h"


__declspec(dllexport) double AddNumbers(double a, double b) {return a+b;}  