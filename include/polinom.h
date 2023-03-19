#include <iostream>
#include <exception>



struct monom
{
	int real_degree(int degree)
	{
		return degree / 100 + (degree / 10) % 10 + degree % 10;
	}

	monom* next = nullptr;
	int degree = 0;
	double k = 0;



	monom() {};
	monom(double k, int pow) { 
		this->k = k, degree = pow;  next = nullptr; 
		if (degree >= 1000 || degree < 0)
			throw std::exception("incorrect degree\n");
	};
	monom(double k, int pow, monom* mon) : k(k), degree(degree) { next = mon; };
	bool operator>(const monom& right) { return real_degree(degree) > real_degree(right.degree);};
	bool operator<(const monom& right) { return real_degree(degree) < real_degree(right.degree); };
	bool operator==(const monom& right) { return degree == right.degree; };
	const monom& operator=(const monom& m) { this->k = m.k; this->degree = m.degree; return *this; };
	monom operator+=(double a) {
		this->k += a;
		return *this;
	};
	monom operator*(double a) { monom rMonom; rMonom.degree = degree; rMonom.k = k * 2; return rMonom; };
	friend std::ostream& operator<<(std::ostream& os, const monom& m){
		int x = m.degree / 100;
		int y = m.degree % 100 / 10;
		int z = m.degree % 10;
		std::cout << m.k << " " << m.degree;
		return os;
	};
};


class List
{
private:
	monom* head = nullptr;
public:
	List();
	List(const List& right);
	~List();
	void Push(double a, int xyz);
	void Push(monom& m);
	friend std::ostream& operator<<(std::ostream& os, const List& p);
	List operator=(const List& right);
	List operator*(double a);

	class iterator
	{
	private:
		monom* pos;
	public:
		iterator(monom* node) : pos(node) {}

		bool operator ==(iterator i) {
			return pos == i.pos;
		}
		bool operator !=(iterator i) {
			return pos != i.pos;
		}
		monom& operator*() {
			return *pos;
		}

		iterator& operator++(int) {
			pos = pos->next;
			return *this;
		}
	};

	iterator begin() const {
		return iterator(head);
	}

	iterator end() const {
		return iterator(nullptr);
	}
};

class polinom
{
private:
	List data;
public:
	polinom() :data() {};
	~polinom() {};
	polinom(const polinom& right) :data(right.data) {};
	polinom(const List& right) :data(right) {};

	const polinom& operator =(const polinom& right) { data = right.data; return *this; };
	void add(double a, int xyz);
	void add(monom m);

	
	polinom operator +(const polinom& right);


	polinom operator *(double a) { List new_List = this->data * a; polinom new_polinom(new_List); return new_polinom; };
	polinom operator -(polinom& right) { polinom new_polinom = *this + (right * -1.); return new_polinom; };
	polinom operator *(const polinom& right);

	friend std::ostream& operator<<(std::ostream& os, const polinom& p);
};



