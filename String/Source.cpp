#include<iostream>
using namespace std;
#define tab "\t"

class String
{
	size_t size; //размер строки в Байтах
	char* str; //указатель на строку в динамич памяти
public:
	const char* get_str()const
	{
		return str; 
	}
				/*constructors*/
	explicit String(size_t size =80)
	{
	this->size = size; 
	this->str = new char[size] {}; 
	cout << "DefConstructor:\t" << this << endl; 
	}
	String(const char str[])
	{
		this->size = strlen(str) + 1; //длина строки с терминатором
		this->str = new char[size] {}; 
		for (int i = 0; i < size; i++)
			this->str[i] = str[i]; 
		cout << "constructor:\t" << endl; 
	}
	String(const String& other)
	{
		this->size = other.size; 
		this->str = new char [size] {}; 
		for (int i = 0; i < size; i++)
		{
			this->str[i] = other.str[i]; 
		}
		cout << "CopyConstrucror: \t" << this << endl; 
	}

	~String()
	{
		delete[] this->str; 
		cout << "Destructor:\t" << this << endl; 
	}
	//			Operators
	String& operator = (const String& other)
	{
		this->size = other.size; 
		this->str = new char [size] {}; 
		for (int i = 0; i < size; i++)
			this->str[i] = other.str[i]; 
		cout << "CopyAssigmtn:\t" << this << endl; 
		return *this; 
	}
	//			Methods

	void print()const
	{
		cout << "size:\t"<< size << endl;
		cout << "str:\t" << str << endl;
	}
};

ostream& operator << (ostream& os, const String&obj)
{
	return os << obj.get_str();
}

void main()
{
	setlocale(LC_ALL, ""); 
	String str1; // пустая строка размером 80Байт
	str1.print(); 
	cout << str1 << endl; 

	String str2 (22); 
	str2.print(); 

	String str3 = "Hello"; 
	str3.print(); 

	String str4 = str3;//CopyConstructor
	cout << str4 << endl; 

	String str5; //Default constructor
	str5 = str4; //Copy assignement
	cout << str5 << endl; 
}
