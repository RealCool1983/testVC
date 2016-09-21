// 20151202TestPoint.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <iostream>

void doublePoint(){
	int x, *p, **q;
	x = 10;
	p = &x;
	q = &p;
	
	printf("address  of p = %x \n" , p);
	printf("address  of p = %X \n" , q);
	printf("value of x = %d" , **q);
}

void initial_point(){
	int *p ;
	int n_p = 0;
	p = &n_p;
	*p = 10;

	printf("value of p = %d" , *p);
}

void intial_char_point(){
	char *p = "hello world";
	register int t;
//	printf(p);
	
	for ( t = strlen(p) - 1 ; t > -1 ; t--) printf("%c", p[t]);
}

void point_swap_a(int *x , int *y){
	int nT = 0 ;
	nT = *x;
	printf("\n point_swap_a nT = %d\n", nT);
	Sleep(2000);
	*x = *y;
	printf("point_swap_a x, y  = %d, %d\n", *x, *y);
	Sleep(2000);
	*y = nT;
}


void point_swap_b(int &x , int &y){
	int nT = 0 ;
	nT = x;
	printf("\n point_swap_b nT = %d\n", nT);
	Sleep(2000);

	x =y;
	printf("point_swap_b x, y  = %d, %d\n", x, y);
	Sleep(2000);
	y = nT;
}

enum foobar{
	a, b, c , max1};
int _tmain(int argc, _TCHAR* argv[])
{
	//foobar fb;
	int na = max1;
	std::cout << max1;
	/*test double point ok */
//	doublePoint();

	/*initial point ok */
	//initial_point();

	/*intial_char_point ok*/
	intial_char_point();


	int x, y;
	x = 10;
	y = 20;
	/*call by address   ok */
	point_swap_a( &x, &y);
	printf ( "point_swap_a %d, %d \n", x, y);
	Sleep(5000);
	/* call by reference ok */
	point_swap_b( x , y );
	printf ( "point_swap_b %d, %d \n", x, y);

	Sleep(5000);
	//cin >>  a;
	return 0;
}

