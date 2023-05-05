#include "polinom.h"

PolynomList PolynomList::operator=(const PolynomList& right)
{
	if (head != right.head)
	{
		this->~PolynomList();

		Node* A = new Node(*(right.head));
		head = A;

		if (right.head->next != nullptr)
		{
			Node* tmp = right.head->next;
			Node* pos = head;
			while (tmp != nullptr)
			{
				Node* A = new Node(tmp->data);
				pos->next = A;
				pos = pos->next;
				tmp = tmp->next;
			}
		}
	}
	return *this;
}

void PolynomList::add(double k, int degree)
{
	try
	{
		monom m(k, degree);
		Push(m);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

void PolynomList::add(monom m)
{
	try
	{
		Push(m);
	}
	catch (const std::exception& ex)
	{
		throw ex;
	}
}

PolynomList PolynomList::operator +(PolynomList& right)
{
	PolynomList retPolynom;

	Node* pos = retPolynom.head;
	Node* left = head->next;
	Node* right_ = right.head->next;

	while (left != nullptr && right_ != nullptr)
	{
		if (left->data > right_->data) // real degree
		{
			if (right_->data.k != 0)
			{
				List<monom>::Node* A = new List<monom>::Node(right_->data);
				pos->next = A;
				pos = pos->next;
			}
			right_ = right_->next;
		}
		else if (left->data < right_->data) // real degree
		{
			if (left->data.k != 0)
			{
				List<monom>::Node* A = new List<monom>::Node(left->data);
				pos->next = A;
				pos = pos->next;
			}
			left = left->next;
		}
		else if (left->data == right_->data) // degree
		{
			if (left->data.k + right_->data.k != 0)
			{
				monom sum(left->data.k + right_->data.k, right_->data.degree);
				List<monom>::Node* A = new List<monom>::Node(sum);
				pos->next = A;
				pos = pos->next;
			}
			left = left->next;
			right_ = right_->next;

		}
		else // real degree1 == real degree2, but degree1 != degree2 (123 321) 
		{
			if (right_->data.k != 0)
			{
				List<monom>::Node* A = new List<monom>::Node(right_->data);
				pos->next = A;
				pos = pos->next;
			}
			right_ = right_->next;

			if (left->data.k != 0)
			{
				List<monom>::Node* A = new List<monom>::Node(left->data);
				pos->next = A;
				pos = pos->next;
			}
			left = left->next;
		}
	}

	if (left == nullptr)
	{
		while (right_ != nullptr)
		{
			List<monom>::Node* A = new List<monom>::Node(right_->data);
			pos->next = A;
			pos = pos->next;
			right_ = right_->next;
		}
	}
	else
	{
		while (left != nullptr)
		{
			List<monom>::Node* A = new List<monom>::Node(left->data);
			pos->next = A;
			pos = pos->next;
			left = left->next;
		}
	}
	pos->next = nullptr;
	return retPolynom;
}


PolynomList PolynomList::operator *(double a)
{
	PolynomList returnPolinom(*this);
	Node* pos = returnPolinom.head->next;
	while (pos != nullptr)
	{
		pos->data.k *= a;
		pos = pos->next;
	}
	return returnPolinom;
}

PolynomList PolynomList::operator -(PolynomList& right)
{
	PolynomList new_right_polynom = right * (-1.0);
	PolynomList new_polynom = new_right_polynom + *this; return new_polynom;
}


PolynomList PolynomList::operator *(PolynomList& right)
{
	PolynomList rPolinom;
	Node* left = head->next;

	while (left != nullptr)
	{
		Node* right_ = right.head->next;

		while (right_ != nullptr)
		{
			if (left->data.k != 0 && right_->data.k != 0)
			{
				int degree1 = left->data.degree, degree2 = right_->data.degree, res_degree = degree1 + degree2;
				if (res_degree / 100 > 9)
					throw std::exception("degree overflow");
				if (res_degree % 100 / 10 < degree1 % 100 / 10 && res_degree % 100 / 10 < degree2 % 100 / 10)
					throw std::exception("degree overflow");
				if (res_degree % 10 < degree1 % 10 && res_degree % 10 < degree2 % 10)
					throw std::exception("degree overflow");
				rPolinom.add(left->data.k * right_->data.k, res_degree);
			}
			right_ = right_->next;
		}
		left = left->next;
	}
	return rPolinom;
}
