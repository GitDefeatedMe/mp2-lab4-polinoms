#include <gtest.h>
#include "polinom.h"

TEST(monom, can_create_monom)
{
	ASSERT_NO_THROW(monom m);
	monom m1;
	ASSERT_NO_THROW(monom m2(m1));
	ASSERT_NO_THROW(monom m3(1, 123));
}

TEST(monom, throws_when_create_monom_with_incorract_degree)
{
	ASSERT_ANY_THROW(monom m3(1, 1230));
	ASSERT_ANY_THROW(monom m3(1, -1));
}


TEST(monom, can_compare_monomes)
{
	monom m1(1, 123), m2(2, 234), m3(3, 321), m4(m1);
	EXPECT_EQ(m1 < m2, true);
	EXPECT_EQ(m2 < m3, false);
	EXPECT_EQ(m1 > m2, false);
	EXPECT_EQ(m2 > m3, true);
	EXPECT_EQ(m1 == m2, false);
	EXPECT_EQ(m1 == m4, true);
}

TEST(monom, can_be_equated)
{
	monom m1(1, 100), m2;
	ASSERT_NO_THROW(m2 = m1);
	EXPECT_EQ(m1 == m2, true);
}

TEST(monom, can_add_monom)
{
	monom m1(1, 100), m2(3, 100);
	ASSERT_NO_THROW(m1 += 2);
	EXPECT_EQ(m1 == m2, true);
}

TEST(monom, can_multøply_monom_by_number)
{
	monom m1(1, 100), m2(3, 100);
	ASSERT_NO_THROW(m1 = m1 * 3);
	EXPECT_EQ(m1 == m2, true);
}



TEST(List, can_create_list)
{
	ASSERT_NO_THROW(List<monom> list);
	List<monom> list1;
	ASSERT_NO_THROW(List<monom> list2(list1));
}

TEST(List, can_push_monom)
{
	List<monom> list;
	monom m(1, 100);
	ASSERT_NO_THROW(list.Push(m));
}

TEST(List, can_cout_list)
{
	List<monom> list;
	monom m(1, 100);
	list.Push(m);
	ASSERT_NO_THROW(std::cout << list);
}

TEST(List, can_be_equated)
{
	List<monom> list, list1;
	monom m(1, 100);
	list.Push(m);
	ASSERT_NO_THROW(list1 = list);
}




TEST(polinom, can_create_polinom)
{
	ASSERT_NO_THROW(PolynomList pol);
	PolynomList pol1;
	ASSERT_NO_THROW(PolynomList pol2(pol1));
}

TEST(polinom, can_be_equated)
{
	PolynomList p1;
	ASSERT_NO_THROW(PolynomList p2 = p1);
}

TEST(polinom, can_add_monom)
{
	PolynomList p1; monom m(1, 100);
	ASSERT_NO_THROW(p1.add(m));
	ASSERT_NO_THROW(p1.add(1, 123));
}

TEST(polinom, can_subtract_polynoms)
{
	PolynomList p1; PolynomList p2;
	p1.add(1, 123); p2.add(1, 123);
	ASSERT_NO_THROW(p1 - p2);
}

TEST(polinom, can_multøply_polynoms_by_number)
{
	PolynomList p1;
	p1.add(1, 123); p1.add(1, 323);
	ASSERT_NO_THROW(p1 * 2);
}

TEST(polinom, can_multøply_polynoms_by_polynom)
{
	PolynomList p1; PolynomList p2;
	p1.add(1, 123); p2.add(1, 123);
	ASSERT_NO_THROW(p1 * p2);
}