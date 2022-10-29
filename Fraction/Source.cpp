#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-----------------------------------\n"
class Fraction; //объявление класса
Fraction operator* (Fraction left, Fraction right); 

int Maximal_common_divider(int a, int b);

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
		this->denominator=1; 
		cout << "Def.Constructor:" << this << endl;
	}
	Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator=1; 
		cout << "1Arg.Constructor:" << this << endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator (denominator); 
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
		numerator%= denominator; 
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
		int divider = Maximal_common_divider(this->numerator, this->denominator);
		this->numerator = numerator / divider;
		this->denominator = denominator / divider;
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
	int a = A;
	cout << a << endl;

	double b = A;
	cout << b << endl;

	Fraction B = 2.75;
	cout << B << endl;
#endif // HOME_WORK_1
}

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