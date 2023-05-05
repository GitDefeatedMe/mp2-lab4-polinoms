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
	monom(monom& m) {
		this->k = m.k, degree = m.degree;
	};
	bool operator>(const monom& right) { return real_degree(degree) > real_degree(right.degree); };
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
	friend std::ostream& operator<<(std::ostream& os, const monom& m) {
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
			position->next->next = nullptr;
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
			pos->next = nullptr;
		}
	};

	void add(double k, int degree);
	void add(monom m);

	PolynomList operator=(const PolynomList& right);
	PolynomList operator +(PolynomList& right);
	PolynomList operator *(double a);
	PolynomList operator -(PolynomList& right);
	PolynomList operator *(PolynomList& right);

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