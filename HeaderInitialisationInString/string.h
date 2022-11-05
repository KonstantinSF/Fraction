#include<iostream>
using namespace std;
#define tab "\t"
using std::cout;
using std::cin;
using std::cout;
using std::size_t;
/////////////////////////////////////////////////////////
/////////////////CLASS DECLARATION START/////////////////

class String;
String operator + (const String& left, const String& right);
ostream& operator << (ostream& os, const String& obj);
int StringLength(const char str[]);

class String
{
	size_t size; //размер строки в Байтах size_t это unsigned int
	char* str; //указатель на строку в динамич памяти
public:
	size_t get_size()const;

	const char* get_str()const;
	char* get_str();

	/*constructors*/

	explicit String(size_t size = 80);
	String(const char str[]);
	String(const String& other);
	String(String&& other);
	~String();
	//			Operators

	String& operator = (const String& other);
	String& operator = (String&& other);
	String& operator += (const String& other);
	char operator [] (int index)const;
	char& operator [] (int index);
	//			Methods

	void print()const;
};

/////////////////CLASS DECLARATION END/////////////
///////////////////////////////////////////////////