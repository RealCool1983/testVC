// Test0622.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "afxmt.h"
CSingleLock singleLock(&m_CritSection);

void EnterCriticalSection_A(){

}

void EnterCriticalSection_B(){

}


int _tmain(int argc, _TCHAR* argv[])
{

singleLock.Lock();  // Attempt to lock the shared resource
	return 0;
}

