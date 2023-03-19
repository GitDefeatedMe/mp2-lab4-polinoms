#include "polinom.h"

int real_degree(int degree)
{
	return degree / 100 + (degree / 10) % 10 + degree % 10;
}

List::List()
{
	monom* A = new monom();
	A->k = 0;
	A->degree = 0;
	head = A;
}



List::~List()
{
	if (head->next == nullptr)
	{
		delete head;
	}
	else
	{
		monom* last = head;
		monom* next = head->next;
		while (next->next != nullptr)
		{
			delete last;
			last = next;
			next = next->next;
		}
		delete next;
	}
}

void List::Push(double k, int degree)
{
	try
	{
		monom m(k, degree);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}

	monom* position = head;


	while (position->next != nullptr && real_degree(degree) > real_degree(position->next->degree))
	{
		position = position->next;
	}

	if (position->next == nullptr)
	{
		monom* A = new monom();
		A->k = k;
		A->degree = degree;
		position->next = A;
	}
	else
	{
		if (degree == position->next->degree)
		{
			position->next->k += k;
		}
		else
		{
			monom* next = position->next;

			monom* A = new monom();
			A->k = k;
			A->degree = degree;

			position->next = A;
			position = position->next;
			position->next = next;
		}
	}
}



void List::Push(monom& m)
{
	monom* position = head;


	while (position->next != nullptr && m > *(position->next))
	{
		position = position->next;
	}

	if (position->next == nullptr)
	{
		monom* A = new monom(m.k, m.degree);
		position->next = A;
	}
	else
	{
		if (m == *(position->next))
		{
			*(position->next) += m.k;
		}
		else
		{
			monom* next = position->next;

			monom* A = new monom(m.k, m.degree);

			position->next = A;
			position = position->next;
			position->next = next;
		}
	}
}















List::List(const List& right)
{
	monom* A = new monom();
	A->k = right.head->k;
	A->degree = right.head->degree;
	head = A;

	if (right.head->next != nullptr)
	{
		monom* tmp = right.head->next;
		monom* pos = head;
		while (tmp != nullptr)
		{
			monom* A = new monom();
			A->k = tmp->k;
			A->degree = tmp->degree;
			pos->next = A;
			pos = pos->next;
			tmp = tmp->next;
		}
	}
}


void polinom::add(double k, int degree)
{
	try
	{
		data.Push(k, degree);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}


void polinom::add(monom m)
{
	try
	{
		data.Push(m);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}


std::ostream& operator<<(std::ostream& os, const List& p)
{
	monom* tmp = p.head->next;
	for (; tmp->next != nullptr; tmp = tmp->next)
	{
		std::cout << *tmp << " + ";
	}

	std::cout << *tmp << "\n";

	return os;
}


std::ostream& operator<<(std::ostream& os, const polinom& p)
{
	std::cout << p.data;
	return os;
}

List List::operator=(const List& right)
{
	if (head != right.head)
	{
		this->~List();

		monom* A = new monom();
		A->k = right.head->k;
		A->degree = right.head->degree;
		head = A;

		if (right.head->next != nullptr)
		{
			monom* tmp = right.head->next;
			monom* pos = head;
			while (tmp != nullptr)
			{
				monom* A = new monom();
				A->k = tmp->k;
				A->degree = tmp->degree;
				pos->next = A;
				pos = pos->next;
				tmp = tmp->next;
			}
		}
	}
	return *this;
}

List List::operator*(double a)
{
	List returnList(*this);
	monom* pos = returnList.head;
	while (pos->next != nullptr)
	{
		pos->k *= a;
		pos = pos->next;
	}
	pos->k *= a;

	return returnList;
}


polinom polinom::operator *(const polinom& right) 
{
	polinom rPolinom;
	auto left = data.begin();

	while (left != nullptr)
	{
		auto right_ = right.data.begin();

		while (right_ != nullptr)
		{
			if ((*left).k != 0 && (*right_).k != 0)
			{
				int degree1 = (*left).degree, degree2 = (*right_).degree, res_degree = degree1 + degree2;
				if (res_degree / 100 > 9)
					throw std::exception("degree overflow");
				if (res_degree % 100 / 10 < degree1 % 100 / 10 && res_degree % 100 / 10 < degree2 % 100 / 10)
					throw std::exception("degree overflow");
				if (res_degree % 10 < degree1 % 10 && res_degree % 10 < degree2 % 10)
					throw std::exception("degree overflow");
				rPolinom.add((*left).k * (*right_).k, degree1 + degree2);
			}
			right_++;
		}
		left++;
	}




	return rPolinom;
};


polinom polinom::operator+(const polinom& right)
{
	List retPolinom;
	auto pos = retPolinom.begin();
	auto left = data.begin();
	auto right_ = right.data.begin();


	while (left != nullptr && right_ != nullptr)
	{
		if (*left > *right_) // real degree
		{
			if ((*right_).k != 0)
			{
				monom* A = new monom();
				A->k = (*right_).k;
				A->degree = (*right_).degree;
				(*pos).next = A;
				pos++;
			}
			right_ ++;
		}
		else if (*left < *right_) // real degree
		{
			if ((*left).k != 0)
			{
				monom* A = new monom();
				A->k = (*left).k;
				A->degree = (*left).degree;
				(*pos).next = A;
				pos++;
			}
			left++;
		}
		else if (*left == *right_) // degree
		{
			if ((*left).k + (*right_).k != 0)
			{
				monom* A = new monom();
				A->k = (*left).k + (*right_).k;
				A->degree = (*left).degree;
				(*pos).next = A;
				pos++;
			}
			left++;
			right_++;

		}
		else // real degree1 == real degree2, but degree1 != degree2 (123 321) 
		{
			if ((*right_).k != 0)
			{
				monom* A = new monom();
				A->k = (*right_).k;
				A->degree = (*right_).degree;
				(*pos).next = A;
				pos++;
			}
			right_++;

			if ((*left).k != 0)
			{
				monom* A = new monom();
				A->k = (*left).k;
				A->degree = (*left).degree;
				(*pos).next = A;
				pos++;
			}
			left++;
		}
	}

	if (left == nullptr)
	{
		while (right_ != nullptr)
		{
			monom* A = new monom();
			A->k = (*right_).k;
			A->degree = (*right_).degree;
			right_++;
			(*pos).next = A;
			pos++;
		}
	}
	else
	{
		while (left != nullptr)
		{
			monom* A = new monom();
			A->k = (*left).k;
			A->degree = (*left).degree;
			left++;
			(*pos).next = A;
			pos++;
		}
	}
	(*pos).next = nullptr;
	return retPolinom;
}