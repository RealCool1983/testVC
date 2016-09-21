// DLL_UI_TEST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DLL_UI_TEST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
void run(){
	printf("HELOO\n");
	system("pause");
	//return 0;
}
void runMain(){
	bool bRes = false;;
	//std::string st_readId = "";
	CString csTmp;
	 wchar_t  sz_cmd_in[FTD_BUF_SIZE] =L"";
	 wchar_t  sz_cmd_out[FTD_BUF_SIZE] =L"";
	 wchar_t  sz_cmd_errcode[FTD_BUF_SIZE] =L"";
	 wchar_t  *sz_value = new  wchar_t [ID_SIZE_BUFFER]  ;
	std::string  ErrMsg;

	wcscpy(sz_cmd_in, L"shell getprop ro.build.oemversion.main");
	if ( !ExecAdbOut(sz_cmd_in, sz_cmd_out, sz_cmd_errcode) ){
	//	ErrMsg = (_T("adb shell getprop ro.build.oemversion.main fail"));
	//	AfxMessageBox( ErrMsg.c_str(),0, 0 );
//		goto  Exit_ShowResult;
	}	

}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
	}
	
	run();
	runMain();
	return nRetCode;
}

bool ExecAdbOut(CString Command, wchar_t* output, wchar_t* ErrorCode)
{
	bool isOk = false;
	DWORD nPipeSize = 1024 * 1024; //1M pipeline

	CString pthToolDir;
	::GetModuleFileName(NULL, pthToolDir.GetBuffer(MAX_PATH), MAX_PATH);
	pthToolDir.ReleaseBuffer();
	pthToolDir = pthToolDir.Left(pthToolDir.ReverseFind('\\'));
	CString path_adb = pthToolDir + _T("\\adb.exe");
	if (_taccess(path_adb, 0) == -1)
	{
//		strcpy(ErrorCode, "ERROR: No adb.exe exist!");
		return false;
	}

	HANDLE hRead, hWrite;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, nPipeSize))
	{
//		strcpy(ErrorCode, "ERROR: CreatePipe fail!");
		return false;
	}

	//HANDLE hProcess = NULL;
	PROCESS_INFORMATION processInfo;
	STARTUPINFO startupInfo;
	::ZeroMemory(&startupInfo, sizeof(startupInfo));
	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	startupInfo.wShowWindow	= SW_HIDE;
	startupInfo.hStdError = hWrite;
	startupInfo.hStdOutput = hWrite;

	Command = _T("\"") + path_adb + _T("\" ") + Command;
	TRACE(_T("Cmd: %s\n"), Command);
	if (::CreateProcess(NULL, Command.GetBuffer(), NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInfo))
	{
		DWORD TimeOutSignal = WaitForSingleObject(processInfo.hProcess, 10 * 1000); // timeout in 10 seconds

		CloseHandle(hWrite);
		hWrite = NULL;
		//if timeout then exit the process
		if (TimeOutSignal == WAIT_TIMEOUT)
		{
			isOk = false;
			TerminateProcess(processInfo.hProcess, 0);
	//		strcpy(ErrorCode, "ERROR: Adb timeout");
		}
		else
		{

			isOk = true;
			DWORD bytesRead;
			std::string	std_out = "";
			std::string std_find_string = "error";
			char* message = new char[nPipeSize];
			memset(message, 0, sizeof(message));
			::ReadFile(hRead, message, nPipeSize, &bytesRead, NULL);
			message[bytesRead] = '\0';

			std_out = message;
			if ( std_out.find( std_find_string )  != string::npos) 
			{
				isOk = false;
	//			strcpy(ErrorCode, "ERROR: adb com fail!");
			}
			else
			{
	//			strncpy(output, message, 4096);
		//		strcpy(ErrorCode, "Adb command ok");
			}
			delete [] message;

		}
	}
	else
	{
		isOk = false;
//		strcpy(ErrorCode, "ERROR: Execute adb.exe fail!");
	}
	Command.ReleaseBuffer();
	CloseHandle(hRead);
	if (hWrite)CloseHandle(hWrite);
	//CloseHandle(hProcess);

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	//hProcess = NULL;

	return isOk;
}
