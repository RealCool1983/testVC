#pragma once

#include "resource.h"
#include <wchar.h>
#include <direct.h>

char   ErrorCode[512];
//bool ExecVerifyTool();
//bool ExecAdb(CString csAdbCmd, char* output);
bool ExecAdb(const std::wstring &cmd, std::wstring findString);
bool run();
bool ExecAndroidLogcat(bool isPass);
