#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<ctype.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
#define delimiter "\n-----------------------------------\n"
class Fraction; //объявление класса
Fraction operator* (Fraction left, Fraction right); 

int Maximal_common_divider(int a, int b);
int Num_in_dec_fraction(double dec_fraction); 

class Fraction
{
	int integer;
	int numerator;
	int denominator;
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;//сдесь set неприменим, только так
	}
	//			Constructors
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "Def.Constructor:" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1Arg.int.Constructor:" << this << endl;
	}
	Fraction(double decimal)
	{
		integer = decimal; //сохраняем целую часть
		decimal += 1e-10; 
		denominator = 1e+9; //тк инт хранит только 9значений
		numerator = (decimal - integer) * denominator;
		reduce(); 
		cout << "Dbl.Constructor" << endl;

		/*this->integer = dec_fraction;
		int num_in_dec_fraction =pow (10,Num_in_dec_fraction(dec_fraction));
		this->numerator = (dec_fraction-(int)dec_fraction) * num_in_dec_fraction;
		this->denominator = num_in_dec_fraction;
		int maximal_common_divider = Maximal_common_divider(numerator, denominator);
		this->numerator/=maximal_common_divider;
		this->denominator/=maximal_common_divider;
		cout << "1Arg.double.Constructor:" << this << endl;*/
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "2Arg.Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;//можно писать и set везде
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyConstructor:" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor: \t" << this << endl;
	}

	//			Operators
	Fraction& operator =(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssignement:" << this << endl;
		return *this;
	}
	Fraction& operator ++()//префиксный инкремент
	{
		integer++;
		return *this; //этот объект существует и будет сущестовать
	}
	Fraction& operator++ (int)//постфиксный инкремент
	{
		Fraction old = *this;//локальный объект он исчезнет после отработки функции. 
		integer++;
		return old;
	}
	//Fraction& operator+=(const Fraction& other)
	//{
	//	//Fraction changible = *this;
	//	Fraction tmp = other; 
	//	this->to_improper(); 
	//	tmp.to_improper();
	//	set_numerator(get_numerator() * tmp.get_denominator() + get_denominator() * tmp.get_numerator());
	//	set_denominator(get_denominator() * tmp.get_denominator()); 
	//	this->to_proper();
	//	return *this;
	//}
	Fraction& operator+=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		set_numerator(get_numerator() * other.get_denominator() + get_denominator() * other.get_numerator());
		set_denominator(get_denominator() * other.get_denominator());
		this->to_proper();
		return *this;
	}
	Fraction& operator-=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		set_numerator(get_numerator() * other.get_denominator() - get_denominator() * other.get_numerator());
		set_denominator(get_denominator() * other.get_denominator());
		this->to_proper();
		return *this;
	}
	/*Fraction& operator*=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		set_numerator(get_numerator() * other.get_numerator());
		set_denominator(get_denominator() * other.get_denominator());
		this->to_proper();
		return *this;
	}*/
	Fraction& operator *= (const Fraction& other)
	{
		//a*=b; a=a*b; 
		return *this = *this * other;
	}
	Fraction& operator/=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		other.inverted();
		set_numerator(get_numerator() * other.get_numerator());
		set_denominator(get_denominator() * other.get_denominator());
		this->to_proper();
		return *this;
	}
	//			Type-cast operator

	explicit operator int()const
	{
		return integer + numerator / denominator;
	}
	explicit operator double()const
	{

		//cout << other.get_numerator() << tab << other.get_denominator() << endl;
		//double num = static_cast<double>(other.get_numerator()) / other.get_denominator();
		/*double numerator = other.get_numerator();
		double denominator = other.get_denominator();
		double num = numerator / denominator;*/
		return integer + (double)numerator / denominator;
	}

	//			Methods
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper()
	{
		integer = numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction inverted()const
	{
		Fraction inverted = *this;
		inverted.to_improper();
		/*int buffer = inverted.numerator;
		inverted.numerator = inverted.denominator;
		inverted.denominator = buffer;*/
		swap(inverted.numerator, inverted.denominator);
		return inverted;
	}
	Fraction& reduce()
	{
		/*int divider = Maximal_common_divider(this->numerator, this->denominator);
		this->numerator = numerator / divider;
		this->denominator = denominator / divider;
		return *this;*/
		if (numerator == 0) return *this; 
		int more, less, rest;
		if (numerator > denominator) more = numerator, less = denominator;
		else less = numerator, more = denominator;
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //greatest common divider
		numerator /= GCD; 
		denominator /= GCD; 
		return *this; 
	}
};

ostream& operator<< (ostream& os, const Fraction& obj)
{
	if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer()) os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;
}
//istream& operator>> (istream& is, Fraction& frac)
//{
//	char ch = cin.get();//считываем символ
//	int digit = ch - '0';//переводим в цифру
//
//	int integer_in = 0;//целое
//	int numerator_in = 0; //числитель
//	int denominator_in = 1; //порядок знаменателя
//
//	while (isdigit(ch))//а цифра ли?
//	{
//		integer_in *= 10; //увелич порядок
//		integer_in += digit;//добавляем цифру
//		ch = cin.get();//считываем след знак
//		digit = ch - '0';//преобразуем в цифру
//	}
//	if (ch == '.')//если встретили запятую
//	{
//		ch = cin.get();
//		digit = ch - '0';
//		while (isdigit(ch))
//		{
//			numerator_in *= 10;//набираем числитель
//			numerator_in += digit;
//			ch = cin.get();
//			digit = ch - '0';
//			denominator_in *= 10; //набираем порядок знаменателя
//		}
//	}
//	frac.set_integer(integer_in); 
//	frac.set_numerator(numerator_in); 
//	frac.set_denominator(denominator_in); 
//	frac.reduce(); //сокращаем дробь
//	return is;
//}
istream& operator >> (istream& is, Fraction& obj)
{
	/*int integer, numerator, denominator; 
	is >> integer >> numerator >> denominator; 
	obj = Fraction(integer, numerator, denominator); 
	return is; */
	const int SIZE = 256; 
	char buffer[SIZE]{}; 
	//is >> buffer; 
	is.getline(buffer, SIZE); 
	char delimiters[] = "()/ "; 
	int number[3] = {}; //храниться числа извлеченные из строки
	int n = 0; 
	for (char* pch = strtok(buffer, delimiters); pch; pch = strtok(NULL, delimiters))
	{
		number[n++] = atoi(pch); 
		if (n >= 3) break; 
	}
	//for (int i = 0; i < n; i++) cout << number[i] << endl; 
	obj = Fraction(); 
	switch (n)
	{
	case 1: obj.set_integer(number[0]); break; 
	case 2: obj.set_numerator(number[0]); 
		obj.set_denominator(number[1]); break; 
	case 3: obj.set_integer(number[0]);
		obj.set_numerator(number[1]);
		obj.set_denominator(number[2]); 
	}
	return is; 
}
Fraction operator* (Fraction left, Fraction right)
{
	left.to_improper(); 
	right.to_improper(); 
	/*Fraction result; 
	result.set_numerator(left.get_numerator() * right.get_numerator()); 
	result.set_denominator(left.get_denominator() * right.get_denominator());*/
	/*Fraction result
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	);
	return result; */
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator / (const Fraction& left, const Fraction& right)
{
	/*left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator(),
		right.get_numerator() * left.get_denominator()
	).to_proper(); */
	return left * right.inverted(); 
}
Fraction operator + (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper(); 
	return Fraction
	(
		left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper(); 
}

//				COMPARISON OPERATORS

bool operator == (Fraction left, Fraction right)//тк есть алгоритм вычисления, то константные значения брать нельзя
{
	left.to_improper();
	right.to_improper(); 
	return
		left.get_numerator() * right.get_denominator() ==
		right.get_numerator() * left.get_denominator(); 
}
bool operator != (const Fraction & left, const Fraction & right)
{
	return !(left == right); 
}
bool operator > (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() >
		right.get_numerator() * left.get_denominator(); 
}
bool operator < (Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	return
		left.get_numerator() * right.get_denominator() <
		right.get_numerator() * left.get_denominator();
}
bool operator >= (const Fraction & left, const Fraction & right)
{
	return left > right || left == right; 
}
bool operator <= (const Fraction& left, const Fraction& right)
{
	return !(left > right); 
}
//bool operator > (Fraction left, Fraction right)
//{
//	left.to_improper();
//	right.to_improper();
//	left.set_numerator(left.get_numerator() * right.get_denominator()); 
//	//left.set_denominator(left.get_denominator() * right.get_denominator());
//	right.set_numerator(right.get_numerator() * left.get_denominator());
//	//right.set_denominator(right.get_denominator() * left.get_denominator()); 
//	return left.get_numerator() > right.get_numerator(); 
//}
//bool operator < (Fraction left, Fraction right)
//{
//	left.to_improper();
//	right.to_improper();
//	left.set_numerator(left.get_numerator() * right.get_denominator());
//	right.set_numerator(right.get_numerator() * left.get_denominator());
//	return left.get_numerator() < right.get_numerator();
//}

//#define CONSTRUCTORS_CHECK
//#define ARITHMETICAL_OPERATORS_CHECK
//#define COMPOUND_ASSIGNMENTS_CHECK
//#define COMPARISON_OPERATORS_CHECK
//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSION_FROM_OTHER_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER_TYPES

void main()
{
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	Fraction A; //Defaul constructor
	cout << A << endl;

	double b = 5;
	Fraction B = 5; //single arg constructor
	cout << B << endl;

	Fraction C(2, 3); //нужно перегрузить конструктор
	cout << C << endl;

	Fraction D(2, 3, 4);
	cout << D << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef ARITHMETICAL_OPERATORS_CHECK
	Fraction A(1, 3, 4);
	Fraction B(3, 4, 5);
	//Fraction C; 
	/*cout << C << endl;
	cout << A / B << endl;
	cout << A + B << endl; */
	/*for (double i = 0; i < 10; i++)
	{
		cout << i << "\t" << endl;
	}*/
	/*for (Fraction i(3, 4); i.get_integer() < 10; ++i)
	{
		cout << i << "\t";
	}*/
	Fraction C(1, 4, 3);
	cout << (A < C) << endl;
	/*if (C == B) cout << "zaebumba" << endl;
	else cout << "Ups!" << endl;
	cout << C << "\t" << B << endl; */
	//A.reduce(); cout << A << endl;   
#endif // ARITHMETICAL_OPERATORS_CHECK
//cout << (Fraction(1, 2) < Fraction(5, 9)) << endl; //это не именованые объекты, он будет являться константой

#ifdef TYPE_CONVERSIONS_BASICS
			//(type)value;	//C-like notation (Ñ-ïîäîáíàÿ ôîðìà çàïèñè)
//type(value);	//Functional notation (Ôóíêöèîíàëüíàÿ ôîðìà çàïèñè)

//Warning: Conversion from 'type' to 'type', possible loss of data.

//cout << (double)8 / 5 << endl;

	int a = 2;		//No conversions
	double b = 3;	//Conversion from less to more.
	int c = b;		//Conversion from more to less with no data loss.
	int d = 2.999;	//Conversion from more to less with data loss.
	cout << d << endl;
#endif // TYPE_CONVERSIONS_BASICS

#ifdef CONVERSION_FROM_OTHER_TO_CLASS
	/*
1. From other to Class:
	Single-Argument constructor;
	Assignment operator;
2. From Class to other type;
	operator type()const
	{
		.....;
		conversion-algorithm;
		.....;
	}
	explicit
*/

	Fraction A = Fraction(5);	//Conversion from 'int' to 'Fraction'
	cout << A << endl;
	cout << delimiter << endl;
	Fraction B;		//Default constructor
	cout << delimiter << endl;
	B = (Fraction)8;
	cout << delimiter << endl;
	cout << B << endl;
#endif // CONVERSION_FROM_OTHER_TO_CLASS

#ifdef CONVERSION_FROM_CLASS_TO_OTHER_TYPES
	Fraction A(2, 3, 4);
	/*int a = (int)A;//только явно, explicit запрещает, но если double без explicit то он сделает и инт через double
	cout << a << endl;*/

	double b = (double)A;//явно преобразуем, тк неявно запрещено
	cout << b << endl;

	Fraction B = 2.75;
	cout << B << endl;

#endif // HOME_WORK_1
	Fraction A(4532,1,2);
	cout << "Введите простую дробь: "; cin >> A;
	cout << A << endl;
};

int Maximal_common_divider(int a, int b)
{
	for (; ;)
	{
		if (a != 0 && b != 0)
		{
			if (a > b)
			{
				a = a % b;
			}
			else b = b % a;
		}
		else return a + b;
	}
}//наибольший общий делитель
int Num_in_dec_fraction(double dec_fraction)
{
	int res = dec_fraction;
	int num_in_dec_fraction = 0;
	while (dec_fraction > res)
	{
		dec_fraction *= 10;
		res = dec_fraction;
		num_in_dec_fraction++;
	}
	return num_in_dec_fraction;
}