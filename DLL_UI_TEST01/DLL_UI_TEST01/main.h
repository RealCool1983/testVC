

extern "C" {  
__declspec(dllexport) double AddNumbers(double a, double b);  
}  

#ifdef DLL_UI_TEST01_EXPORTS

#define DLL_EXPORT __declspec(dllexport)

#else

//#define DLL_EXPORT __declspec(dllimport)
#define DLL_EXPORT 

#endif



class DLL_EXPORT SimpleDLLClass
{
	public:

	SimpleDLLClass();

	virtual ~SimpleDLLClass();

	virtual int getValue() { return m_nValue;};

	private:

	static int m_nValue;
};