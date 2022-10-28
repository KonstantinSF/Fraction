#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n-----------------------------------\n"

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
	Fraction& operator*=(Fraction other)
	{
		this->to_improper();
		other.to_improper();
		set_numerator(get_numerator() * other.get_numerator());
		set_denominator(get_denominator() * other.get_denominator());
		this->to_proper();
		return *this;
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


//#define CONSTRUCTORS_CHECK

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

	Fraction A(0, 45, 15); 
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
	Fraction C=B;
	A.reduce(); cout << A << endl; 
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