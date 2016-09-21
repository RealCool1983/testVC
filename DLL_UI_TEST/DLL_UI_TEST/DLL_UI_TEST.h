#pragma once

#include "resource.h"
#include <direct.h>
#include <windows.h>
#include <string>

#define FTD_BUF_SIZE 4096
#define ID_SIZE_BUFFER 512
using namespace std;

bool ExecAdbOut(CString Command, wchar_t* output, wchar_t* ErrorCode);
void runMain();