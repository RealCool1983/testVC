// DLL_UI_TEST_UIPART.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//#include "Main.h" 
#include <windows.h>
#include "..\DLL_UI_TEST01\main.h"

int vloadUIDLL(){

		  // Load DLL file  
    HINSTANCE hinstLib_DLL_AFX_MANAGE_STATE= LoadLibrary(TEXT("DLL_AFX_MANAGE_STATE.dll"));  
    if (hinstLib_DLL_AFX_MANAGE_STATE == NULL) {  
        printf("ERROR: unable to load DLL\n");  
        system("pause");  
        return 1;  
    }  
  
	typedef void (WINAPI * TESTDLL)();
	TESTDLL lpproc;
	lpproc = (TESTDLL)GetProcAddress (hinstLib_DLL_AFX_MANAGE_STATE,"Show");
	if(lpproc!=(TESTDLL)NULL){
		(*lpproc)();
	}
	FreeLibrary(hinstLib_DLL_AFX_MANAGE_STATE);
}

int vloadDLL(){

	// DLL function signature  
	typedef double (*importFunction) (double a, double b);  
    importFunction addNumbers;  
    double result;  
  
	
   // Load DLL file  
    HINSTANCE hinstLib = LoadLibrary(TEXT("DLL_UI_TEST01.dll"));  
    if (hinstLib == NULL) {  
        printf("ERROR: unable to load DLL\n");  
        system("pause");  
        return 1;  
    }  
  
//	printf ("test %d", m_nValue
    // Get function pointer  
    addNumbers = (importFunction)GetProcAddress(hinstLib, "AddNumbers");  
    if (addNumbers == NULL) {  
        printf("ERROR: unable to find DLL function\n");  
        FreeLibrary(hinstLib);  
        system("pause");  
        return 1;  
    }  
  
    result = addNumbers(10, 20);  
    printf("The result is %f\n", result);  
  
    // Unload DLL file  
    FreeLibrary(hinstLib);  
}
int _tmain(int argc, _TCHAR* argv[])
{
	
	//vloadUIDLL();
	vloadDLL();
    system("pause");  
	return 0;
}

