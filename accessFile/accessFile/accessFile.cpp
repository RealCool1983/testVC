// accessFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sys/types.h>
#include <dirent.h>
#include <string>
#include <vector>

#include <errno.h>
#include <iostream>

using namespace std;
//
int getdir(string dir, vector<string> &files){
    DIR *dp;//創立資料夾指標
    struct dirent *dirp;
    if((dp = opendir(dir.c_str())) == NULL){
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }
    while((dirp = readdir(dp)) != NULL){//如果dirent指標非空
        files.push_back(string(dirp->d_name));//將資料夾和檔案名放入vector
    }
    closedir(dp);//關閉資料夾指標
    return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//std::vector abc;
	std::vector<string> abc;
	//vector<string> foo;
	return 0;
}

