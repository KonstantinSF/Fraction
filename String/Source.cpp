#include<iostream>
using namespace std;
#define tab "\t"

int StringLength(const char str[]); 

class String
{
	size_t size; //размер строки в Байтах size_t это unsigned int
	char* str; //указатель на строку в динамич памяти
public:
	size_t get_size()const
	{
		return size; 
	}

	const char* get_str()const
	{
		return str; 
	}
	char* get_str()
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
	String(String&& other)
	{
		//Shallow copy:
		this->size = other.size; 
		this->str = other.str; 
		other.str = nullptr; 
		other.size = NULL; 
		cout << "MoveConstr:" << this << endl; 
	}
	~String()
	{
		delete[] this->str; 
		cout << "Destructor:\t" << this << endl; 
	}
	//			Operators
	String& operator = (const String& other)
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
	char operator [] (int index)const
	{
		return str[index]; 
	}
	char& operator [] (int index)//если возвр по ссылке, то можем менять
	{
		return str[index];
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

//#define CONSTRUCTORS_CHECK
#define OPERATOR_PLUS_CHECK
void main()
{
	setlocale(LC_ALL, ""); 
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
	cout << str1 << endl; 
	String str2 = "World!";
	cout << str2 << endl; 
	String str3 = str1 +" "+ str2;
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
