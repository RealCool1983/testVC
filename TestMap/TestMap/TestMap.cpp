// TestMap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TestMap.h"

using namespace std; 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;
template <typename T> class Demo_A{
public:
	T sum(T a , T b){
		return a + b;
	};
	Demo_A(){

	};
};

template <typename T> class Demo {
    public:
        Demo(const T &a, const T &b) {
            this->a = a;
            this->b = b;
        } 
         
        T do_something() {
            return a + b;
        }
     
    private:
        T a;
        T b;
};

int TestTemplate(){
    Demo<int> d1(20, 25);
    std::cout << d1.do_something() << std::endl;
//	printf("%d", d1.do_something());

    Demo<double> d2(5.2, 3.95);
    std::cout << d2.do_something() << std::endl;
//	printf("%f", d2.do_something());

    Demo<char> d3('1', '2');
    std::cout << d3.do_something() << std::endl;
//	printf("%d", d3.do_something());
	
	Demo_A<int> Demo_A_Test;
	cout << Demo_A_Test.sum(10,1) << endl;

	Demo_A<double> Demo_A_Test1;
	cout << Demo_A_Test1.sum(10.2,1.1) << endl;


	system("pause");
	return 0;
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
	TestTemplate();
	return nRetCode;
}
