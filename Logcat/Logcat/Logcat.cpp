// Logcat.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logcat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;




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
	system("pause");
	return nRetCode;
}

bool run()
{
	bool b_wait_fastboot = false;
	int nLimitTime = 0 ;
	int m_nConnectRetry = 10;
	// wait for adb 
	while ( !b_wait_fastboot){
		if (!ExecAdb(L"devices",L"device"))
		{
	//		TraceLog(MSG_INFO, _T("runRebootWaitADB get adb  fail "));
			Sleep(1000);
		}
		else 
		{
			b_wait_fastboot = true;
	//		TraceLog(MSG_INFO, _T("runRebootWaitADB get adb  OK"));
		}

		nLimitTime ++;
		if ( nLimitTime > m_nConnectRetry ) break; //time out
	}

	ExecAdb(L"remount", L"NULL");

	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	CString currDate;
	currDate.Format(_T("%04d%02d%02d_%02d%02d"), systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute);
	
	CString csLogcat;
	csLogcat.Format(L" logcat -v time -d  > %s.txt", currDate);
	if (!ExecAdb(csLogcat.GetBuffer(0), L"NULL"))
		{
	//		TraceLog(MSG_INFO, _T("runRebootWaitADB get adb  fail "));
			Sleep(1000);
		}	
	csLogcat.ReleaseBuffer();

	return true;
}

//bool ExecAdb(CString csAdbCmd,  CString csParameter, char* output)
//bool ExecAdb(const std::wstring &cmd, char* output)
bool ExecAdb(const std::wstring &cmd, std::wstring findString)
{
	bool isOk = false;
	CString csCmd;
	//std::string m_Adbcommand;
	std::wstring wst_adbcmd;
	wst_adbcmd = cmd;



	DWORD nPipeSize = 1024 * 1024; //1M pipeline

	CString pthToolDir;
	::GetModuleFileName(NULL, pthToolDir.GetBuffer(MAX_PATH), MAX_PATH);
	pthToolDir.ReleaseBuffer();
	pthToolDir = pthToolDir.Left(pthToolDir.ReverseFind('\\'));
	CString pathExe = pthToolDir + _T("\\adb.exe");
	if (_taccess(pathExe, 0) == -1)
	{
		strcpy(ErrorCode, "ERROR: No verify_tool.exe exist!");
		return false;
	}

	HANDLE hRead, hWrite;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(&hRead, &hWrite, &sa, nPipeSize))
	{
		strcpy(ErrorCode, "ERROR: CreatePipe fail!");
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

//	csCmd.Format(_T("%s %s"), pathExe, chCmd );
	csCmd.Format(_T("%s %s"), pathExe, wst_adbcmd.c_str() );
	//csCmd.Format(_T("/C adb logcat -v > a.txt"), wst_adbcmd.c_str() );
	CString cs1;
	cs1.Format(_T(" %s"), wst_adbcmd.c_str() );
	TRACE(_T("Cmd: %s\n"), csCmd);
	if (::CreateProcess(NULL, csCmd.GetBuffer(0), NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInfo))
	//if (::CreateProcess(pathExe.GetBuffer(0), cs1.GetBuffer(0), NULL, NULL, TRUE, 0, NULL, NULL, &startupInfo, &processInfo))
	{
		DWORD TimeOutSignal = WaitForSingleObject(processInfo.hProcess, 50 * 1000); // timeout in 10 seconds

		CloseHandle(hWrite);
		hWrite = NULL;
		//if timeout then exit the process
		if (TimeOutSignal == WAIT_TIMEOUT)
		{
			isOk = false;
			TerminateProcess(processInfo.hProcess, 0);
			strcpy(ErrorCode, "ERROR: ExecVerifyTool timeout");
		}
		else
		{

			isOk = true;
			DWORD bytesRead;
			std::wstring	std_out = L"";
			std::wstring std_find_string = L"pass";
			char* message = new char[nPipeSize];
			wchar_t* msg = new wchar_t[nPipeSize];
			memset(message, 0, sizeof(message));
			memset(msg, 0, sizeof(msg));

			::ReadFile(hRead, message, nPipeSize, &bytesRead, NULL);
			message[bytesRead] = '\0';

			size_t newsize = strlen(message) + 1;

			size_t convertedChars = 0;
			mbstowcs_s(&convertedChars, msg, newsize, message, _TRUNCATE);
		 
			std_out = msg;
			if ( findString.find(L"NULL") == string::npos){
					if ( std_out.find( findString )  == string::npos) 
					{
						isOk = false;
						strcpy(ErrorCode, "ERROR: ExecAdb fail!");
					}
					else
					{
						isOk = true;
					//	strncpy(output, message, 4096);
						//strcpy(ErrorCode, "ExecVerifyTool command ok");
					}
		}
			delete [] message;
			delete []msg;
		}
	}
	else
	{
		isOk = false;
		strcpy(ErrorCode, "ERROR: Execute ExecAdb fail!");
	}
	csCmd.ReleaseBuffer();
	CloseHandle(hRead);
	if (hWrite)CloseHandle(hWrite);
	//CloseHandle(hProcess);

	CloseHandle(processInfo.hProcess);
	CloseHandle(processInfo.hThread);
	//hProcess = NULL;

	return isOk;
}




bool ExecAndroidLogcat(bool isPass)
{
	std::string g_str_station = "T1";
	std::string	g_str_modelName =  "T2";
	std::string g_strPicasso="T3";

	SYSTEMTIME systemTime;
	GetLocalTime(&systemTime);
	CString currDate;
	currDate.Format(_T("%04d%02d%02d"), systemTime.wYear, systemTime.wMonth, systemTime.wDay);
	CString csLogPath;
	csLogPath.Format(_T("C:\\LOG\\%s\\%s\\%s\\Logcat"), g_str_modelName.c_str(), g_str_station.c_str(), currDate);

	_wmkdir(csLogPath.GetBuffer());
	csLogPath.ReleaseBuffer();

	CString csPicasso = _T("RD");
	if (!g_strPicasso.empty())
		csPicasso = g_strPicasso.c_str();

	CString csPassFail = isPass ? _T("PASS") : _T("FAIL");
	CString msg;
	CString command;

		CString csDevice;
	//	if (m_pIPhone->m_devices.size() > 1)
		csDevice="";
		command.Format(_T("/C adb %s logcat -v time -d > %s\\%s_logcat_%s_%s_%s_%04d%02d%02d_%02d%02d%02d.txt"),
			csDevice, csLogPath, csPassFail, g_str_modelName.c_str(), g_str_station.c_str(), csPicasso,
			systemTime.wYear, systemTime.wMonth, systemTime.wDay,
			systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
		SHELLEXECUTEINFO ShExecInfo = {0};
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = L"open";
		ShExecInfo.lpFile = L"cmd";
		ShExecInfo.lpParameters = command;
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_HIDE;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess, 3000);

	//	msg.Format(_T("Execute: %s"), command);
		//TraceLog(MSG_INFO, std::string(CT2A(msg)));
	return true;

}