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
	ASSERT_NO_THROW(List list);
	List list1;
	ASSERT_NO_THROW(List list2(list1));
}

TEST(List, can_push_monom)
{
	List list;
	monom m(1, 100);
	ASSERT_NO_THROW(list.Push(m));
	ASSERT_NO_THROW(list.Push(1, 100));
}

TEST(List, can_cout_list)
{
	List list;
	monom m(1, 100);
	list.Push(m);
	ASSERT_NO_THROW(std::cout << list);
}

TEST(List, can_be_equated)
{
	List list, list1;
	monom m(1, 100);
	list.Push(m);
	ASSERT_NO_THROW(list1 = list);
}




TEST(polinom, can_create_polinom)
{
	ASSERT_NO_THROW(polinom pol);
	polinom pol1;
	ASSERT_NO_THROW(polinom pol2(pol1));
	List list;
	ASSERT_NO_THROW(polinom pol3(list));
}

TEST(polinom, can_be_equated)
{
	polinom p1;
	ASSERT_NO_THROW(polinom p2 = p1);
}

TEST(polinom, can_add_monom)
{
	polinom p1; monom m(1, 100);
	ASSERT_NO_THROW(p1.add(m));
	ASSERT_NO_THROW(p1.add(1, 123));
}

TEST(polinom, can_subtract_polynoms)
{
	polinom p1; polinom p2;
	p1.add(1, 123); p2.add(1, 123);
	ASSERT_NO_THROW(p1 - p2);
}

TEST(polinom, can_multøply_polynoms_by_number)
{
	polinom p1;
	p1.add(1, 123); p1.add(1, 323);
	ASSERT_NO_THROW(p1 * 2);
}

TEST(polinom, can_multøply_polynoms_by_polynom)
{
	polinom p1; polinom p2;
	p1.add(1, 123); p2.add(1, 123);
	ASSERT_NO_THROW(p1 * p2);
}