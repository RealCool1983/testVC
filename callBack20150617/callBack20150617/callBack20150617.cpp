// callBack20150617.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;
struct MSGMAP_ENTRY
{
   int nMessage;
 //  LONG (*pfn)(HWND,UINT,WPARAM,LPARAM);
};


class CallBackTest
{
	// 宣告回呼函式的原型;
	typedef void (*CBFun)( int k );
	// 宣告//一個回呼函式指標;
	CBFun pCBFun;

	public:
		CallBackTest() { 
			pCBFun= NULL; 
		}	// 初始化為 NULL;

	//void SetCallBack( CBFun fun ) { 
	void SetCallBack( CBFun fun ) { 
		pCBFun= fun; 
	}	// 註冊回呼函式;

	void run() { // 當我執行到第0,50或50的倍數迴圈時,會呼叫回呼函式;

		for( int i= 0; i< 151; i++ ) {
			printf( "%d\t", i );
			if( ( 0 == ( i%50 ) ) && ( NULL != pCBFun ) )	// 第50個倍數了,並且有註冊回呼函式;
				(*pCBFun)( i );
		}
	}
};

void myCBFun( int k )
{
	printf("\n我被呼叫了,這是第 %d 個!\n", k );
}

class Base{
public :
	int val;
	Base(){ val = 1;};
};

class Derive:public Base{
public:
	int val;
	Derive(int i){ val = Base::val + i;};

};



void playVector(){
	vector<int> v(10);
	v[5] = 5;

	for (int i = 0 ; i < 10 ; i ++){
		cout << "NO." << i << " = " << v[i] << endl;
	}
}

unsigned int oct2dec( unsigned int oct){
	//return (oct / 10 * 8 + oct % 10);
	cout << "oct = " << oct << endl;
	if ( oct / 10 > 0 ){
		return (  8 * oct2dec(oct/10));
	}
	else if (  oct / 10 == 0 ) 	 return ( oct% 10);
}

int _tmain(int argc, _TCHAR* argv[])
{
	CallBackTest cbt;
	cbt.SetCallBack( myCBFun );	// 註冊 callback function;
	//cbt.run();

	//***playVector
	//playVector();

	//** oct2dec
	cout <<  "oct2dec = " << oct2dec(26) << endl ;

	//*******************


	Derive d(10);
	cout << d.Base::val << endl << d.val << endl;

	string s("abcd");
	string& st = s;
	cout << st.data() << endl;
	//********************
	int y;
	std::cin >> y ;


	
	//SLEEP(5000);
	return 0;
}


