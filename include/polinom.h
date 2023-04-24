#include <iostream>
#include <exception>



struct monom
{
	int real_degree(int degree)
	{
		return degree / 100 + (degree / 10) % 10 + degree % 10;
	}

	int degree = 0;
	double k = 0;



	monom() { degree = 0; k = 0; };
	monom(double k, int pow) { 
		this->k = k, degree = pow; 
		if (degree >= 1000 || degree < 0)
			throw std::exception("incorrect degree\n");
	};

	bool operator>(const monom& right) { return real_degree(degree) > real_degree(right.degree);};
	bool operator<(const monom& right) { return real_degree(degree) < real_degree(right.degree); };
	bool operator==(const monom& right) { return degree == right.degree; };
	const monom& operator=(const monom& m) { this->k = m.k; this->degree = m.degree; return *this; };
	monom operator+=(double a) {
		this->k += a;
		return *this;
	};
	monom operator+=(monom a) {
		this->k += a.k;
		return *this;
	};

	monom operator*(double a) { monom rMonom; rMonom.degree = degree; rMonom.k = k * a; return rMonom; };
	friend std::ostream& operator<<(std::ostream& os, const monom& m){
		int x = m.degree / 100;
		int y = m.degree % 100 / 10;
		int z = m.degree % 10;
		std::cout << m.k << " " << m.degree;
		return os;
	};
};






template <class T>
class List
{
private:

public:

	struct Node
	{
		T data;
		Node* next = nullptr;


		Node() :data(), next(nullptr) {};
		Node(T obj, Node* next_ = nullptr)
		{
			data = obj;
			next = next_;
		};
		Node(Node& n)
		{
			data = n.data;
			next = nullptr;
		}

		bool operator >(T& right) { return data > right; };
		bool operator <(T& right) { return data < right; };
		Node operator *=(T& right) { data *= right; return *this; };
		bool operator==(Node& right) { return data == right.data; };
		bool operator!=(Node& right) { return data != right.data; };
		const Node& operator=(const Node& m) { this->data = m.data; return *this; };
	};


	Node* head = nullptr;





	List() 
	{
		Node* A = new Node();
		head = A;
	};


	~List()
	{
		if (head->next == nullptr)
		{
			delete head;
		}
		else
		{
			Node* last = head;
			Node* next = head->next;
			while (next->next != nullptr)
			{
				delete last;
				last = next;
				next = next->next;
			}
			delete next;
		}
	}


	List(List<T>& right)
	{
		if (head != nullptr)
		{
			std::cout << "Not nullptr!\n";
		}

		Node* A = new Node();
		head = A;
		if (right.head->next != nullptr)
		{
			Node* tmp = right.head->next;
			Node* pos = head;
			while (tmp != nullptr)
			{
				Node* A = new Node();
				A->data = tmp->data;
				pos->next = A;
				pos = pos->next;
				tmp = tmp->next;
			}
		}
		
	}



	void Push(T& m)
	{
		Node* position = head;

		while (position->next != nullptr && m > position->next->data)
		{
			position = position->next;
		}

		if (position->next == nullptr)
		{
			Node* A = new Node(m);
			position->next = A;
		}
		else
		{
			if (m == position->next->data)
			{
				(position->next->data) += m;
			}
			else
			{
				Node* next = position->next;

				Node* A = new Node(m);

				position->next = A;
				position = position->next;
				position->next = next;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const List& p)
	{
		Node* tmp = p.head->next;
		for (; tmp != nullptr; tmp = tmp->next)
		{
			std::cout << tmp->data << " + ";
		}

		return os;
	}




	List operator=(List& right)
	{
		if (head != right.head)
		{
			this->~List();

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
};





class PolynomList : private List<monom>
{
	using List<monom>::head;
	using List<monom>::Node;
public:
	PolynomList() :List<monom>() {};
	PolynomList(const PolynomList& right) :List<monom>() 
	{
		if (right.head->next != nullptr)
		{
			Node* tmp = right.head->next;
			Node* pos = head;
			while (tmp != nullptr)
			{
				Node* A = new Node();
				A->data = tmp->data;
				pos->next = A;
				pos = pos->next;
				tmp = tmp->next;
			}
		}
	};


	PolynomList operator=(const PolynomList& right)
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



	void add(double k, int degree)
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
	void add(monom m)
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
	PolynomList operator +(PolynomList& right)
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
					pos++;
				}
				right_++;
			}
			else if (left->data < right_->data) // real degree
			{
				if (left->data.k != 0)
				{
					List<monom>::Node* A = new List<monom>::Node(left->data);
					pos->next = A;
					pos++;
				}
				left = left->next;
			}
			else if (left->data == right_->data) // degree
			{
				if (left->data.k + right_->data.k != 0)
				{
					monom sum = left->data;
					sum += right_->data;
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


	PolynomList operator *(double a)
	{
		PolynomList returnPolinom(*this);
		Node* pos = returnPolinom.head->next;
		while (pos != nullptr)
		{
			pos->data.k *= a;
			pos = pos->next;
		}

		return returnPolinom;
	};


	PolynomList operator -(PolynomList& right)
	{
		PolynomList new_right_polynom = right * (-1.0);
		PolynomList new_polynom = new_right_polynom + *this; return new_polynom;
	};



	PolynomList operator *(PolynomList& right)
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
	};




	friend std::ostream& operator<<(std::ostream& os, const PolynomList& p)
	{
		Node* tmp = p.head->next;
		if (tmp != nullptr)
		{
			for (; tmp->next != nullptr; tmp = tmp->next)
			{
				std::cout << tmp->data << " + ";
			}
			std::cout << tmp->data;

		}
		return os;
	}
};