#include "string.h"

//#define CONSTRUCTORS_CHECK
#define OPERATOR_PLUS_CHECK

void main()
{
	setlocale (LC_ALL, ""); 
#ifdef CONSTRUCTORS_CHECK
	String str1; // пустая строка размером 80Байт
	str1.print();
	cout << str1 << endl;

	String str2(22);
	str2.print();

	String str3 = "Hello";
	str3.print();

	String str4 = str3;//CopyConstructor
	cout << str4 << endl;

	String str5; //Default constructor
	str5 = str4; //Copy assignement
	cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATOR_PLUS_CHECK
	String str1 = "Hello!";
	//cout << str1 << endl; 
	String str2 = "World";
	//cout << str2 << endl; 
	String str3;
	str3 = str1 + str2;
	cout << str3 << endl;
#endif // OPERATOR_PLUS_CHECK

}

int StringLength(const char str[])
{
	//Принимает строку, и возвращает размер строки в символах
	int i = 0;
	for (; str[i]; i++);
	return i;
}
