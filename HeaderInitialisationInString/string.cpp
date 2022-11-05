#include "string.h"

/////////////////////////////////////////////////////////
/////////////////CLASS DEFINITION START/////////////////

size_t String::get_size()const
{
	return size;
}

const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}

/*constructors*/

String::String(size_t size) :size(size), str(new char[size] {})//Default constructor
{
	//this->size = size; 
	//this->str = new char[size] {}; //занулена и содержит 80байт памяти
	cout << "DefConstructor:\t" << this << endl;
}
String::String(const char str[]) :size(strlen(str) + 1), str(new char[size] {})
{
	//this->size = strlen(str) + 1; //длина строки с терминатором
	//this->str = new char[size] {}; 
	for (int i = 0; i < size; i++)
		this->str[i] = str[i];
	cout << "constructor:\t" << endl;
}
String::String(const String& other) :size(other.size), str(new char[size] {})
{
	/*this->size = other.size;
	this->str = new char [size] {}; */
	for (int i = 0; i < size; i++)
	{
		this->str[i] = other.str[i];
	}
	cout << "CopyConstrucror: \t" << this << endl;
}
String::String(String&& other) :size(other.size), str(other.str)
{
	//Shallow copy:
	/*this->size = other.size;
	this->str = other.str; */
	other.str = nullptr;
	other.size = NULL;
	cout << "MoveConstr:" << this << endl;
}
String::~String()//последний метод в секции конструкторов
{
	delete[] this->str;
	cout << "Destructor:\t" << this << endl;
}
//			Operators
String& String::operator = (const String& other)
{
	if (this == &other)return *this;
	delete[] this->str;
	this->size = other.size;
	this->str = new char [size] {};
	for (int i = 0; i < size; i++)
		this->str[i] = other.str[i];
	cout << "CopyAssigmtn:\t" << this << endl;
	return *this;
}
String& String::operator = (String&& other)
{
	if (this == &other)return *this;//на всяк случай, не м.б. 2 разных объекта с одним адресом
	delete[] this->str;
	this->size = other.size;
	this->str = other.str;
	other.size = 0;
	other.str = nullptr;
	cout << "MoveAssignment:\t " << this << endl;
	return *this;
}
String& String::operator += (const String& other)
{
	return *this = *this + other;
}
char String::operator [] (int index)const
{
	return str[index];
}
char& String::operator [] (int index)//если возвр по ссылке, то можем менять
{
	return str[index];
}
//			Methods

void String::print()const
{
	cout << "size:\t" << size << endl;
	cout << "str:\t" << str << endl;
}
ostream& operator << (ostream& os, const String& obj)
{
	return os << obj.get_str();
}
String operator + (const String& left, const String& right)
{
	//int length_left = strlen(left.get_str()); 
	//int length_right = strlen(right.get_str()); 
	//int size = length_left+length_right+1;
	//char* result = new char[size] {}; 

	//for (int i = 0; i < length_left; i++)
	//{
	//	result[i] = left.get_str()[i];
	//}
	//result[length_left] = {' '};
	//for (int i = length_left+1; i < size; i++)
	//{
	//	result[i] = right.get_str()[i]; 
	//}
	//String Result = result; 
	////delete[] result; 
	//return Result; 

	String cat(left.get_size() + right.get_size() - 1); //чтобы не было лишнего нуля
	for (int i = 0; i < left.get_size(); i++)
		cat[i] = left[i];
	//cat.get_str()[i] = left.get_str()[i]; //вызываем разные GET!!!констант и обычный
	for (int i = 0; i < right.get_size(); i++)
		cat[i + left.get_size() - 1] = right[i];
	//cat.get_str()[i + left.get_size() - 1] = right.get_str()[i]; 
	return cat;
}
int StringLength(const char str[])
{
	//Принимает строку, и возвращает размер строки в символах
	int i = 0;
	for (; str[i]; i++);
	return i;
}
/////////////////CLASS DEFINITION END/////////////
///////////////////////////////////////////////////