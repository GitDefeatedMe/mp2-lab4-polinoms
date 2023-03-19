#include "polinom.h"
#include <iostream>


void input_polinom(int n, polinom& p)
{
	int i = 0;
	while (i < n)
	{
		double k; int degree;
		std::cout << i + 1 << " : ";
		std::cin >> k; std::cin >> degree;
		try
		{
			monom m(k, degree);
			p.add(m);
			i++;
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}
	}
}

int main()
{
	int n1, n2;
	polinom p1, p2;
	std::cout << "enter the number of monomials in the first polynomial : ";
	std::cin >> n1;
	std::cout << "enter monomials in the form of 2 numbers corresponding to the coefficient and degree, for example, the monomial 3.4*x^1*y^2*z^3 correspond to 3.4 123\n";
	input_polinom(n1, p1);
	
	
	std::cout << "enter the number of monomials in the second polynomial : ";
	std::cin >> n2;
	input_polinom(n2, p2);


	std::cout << "\n\npolynom 1 : " << p1 << "polynom 2 : " << p2;

	std::cout << "\n\n\select the operation : \n\t1 - addition  \n\t2 - subtraction \n\t3 - multiplication\n";
	int select = 0;
	do
	{
		std::cin >> select;
	} while (select <= 0 || select > 3);
	
	polinom res;
	switch (select)
	{
	case 1:
		res = p1 + p2;
		std::cout << "polynom1 + polynom2 = "<< res;
		break;
	
	case 2:
		res = p1 - p2;
		std::cout << "polynom1 - polynom2 = " << res;
		break;
	
	case 3:
		try
		{
			res = p1 * p2;
			std::cout << "polynom1 * polynom2 = " << res;
		}
		catch (const std::exception&ex)
		{
			std::cout << ex.what();
		}
		break;
	}
	return 1;
}
