#include "main.h"
#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

double try_gx(){
	double d_n1 = 0 ;
	d_n1 = sqrt(9.0);

	return d_n1;
}


class IniArray{
public:

private:
	void init(int sz, int *array);
	IniArray(int sz){ init(sz, 0);}
	IniArray(int sz, int szb);
};
void IniArray::init(int sz, int *array){
	
}
//IniArray::init(int sz, int *array)
IniArray::IniArray(int sz , int szb){ init(sz, 0);}

void vactor_test(){
	int ia[10] = {10, 11, 12, 13, 14, 15, 16, 17, 18 ,19};
	vector<int> vec(ia, ia+10);
	sort(vec.begin(), vec.end());
}

void char_test(){
	const char* st = "today is happyday";
	int n_count = 0 ;

	while (*st++){
		n_count++;
	}
	
}

class AbstractCircle {
public:
    void radius(double radius) {
        _radius = radius;
    }
    double radius() {
        return _radius;
    }
    // 宣告虛擬函式
    virtual void render() = 0;
 
protected:
    double _radius;
};

class HollowCircle : public AbstractCircle {
public:
    void render() {
        cout << "畫一個半徑 " 
             << _radius 
             << " 的空心圓"
             << endl;
    }
};

class ConcreteCircle : public AbstractCircle {
public:
    void render() {
        cout << "畫一個半徑 " 
             << _radius 
             << " 的實心圓"
             << endl;
    }
};

void render(AbstractCircle &circle) {
    circle.render();
}

#pragma pack(1)
typedef struct {
	double Data1;
	short Data2;
	short Data3;
	char Data4[9];
} EFI_GUID;
#pragma pack()

#pragma pack(1)
struct EFI_GUID_II{
	double Data1;
	short Data2;
	short Data3;
	char Data4[9];
} ;
#pragma pack()

void custom_for_each( int *pArray, unsigned int size, int (*op)( int ) )
{
  for( unsigned int i = 0; i < size; ++ i )
    pArray[i] = (*op)( pArray[i] );
}
 

int main()
{
	int ival = 1024;
	void *pv;
	int *pi = &ival;
	const char *pc = "a casting";
	pc = static_cast<char*>(pv);

	EFI_GUID g;
	printf("sizeof %d\n", sizeof(g));

	EFI_GUID_II g2;
	printf("sizeof %d\n", sizeof(g2));

    ConcreteCircle concrete;
    concrete.radius(10.0);
	concrete.render();
    render(concrete);
 
    HollowCircle hollow;
    hollow.radius(20.0);
	hollow.render();
   render(hollow);
 
   // return 0;


  std::cout << "Hello World!" << std::endl;

  int arr[10], arrb[10];
  int *in;
  in= arrb;
  for(int i = 0 ; i < 10 ; i++) arrb[i] = i +10;
	
  for(int i = 0 ; i < 10 ; i++)
  cout <<  "invalue" << *(in++) << endl; 
  cin >> arr[0];
  return 0;
}

