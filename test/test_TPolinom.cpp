#include <../Polinom/Polinom.h>
#include <../gtest/gtest.h>

TEST(Polinom, can_create_polinomial)
{
  ASSERT_NO_THROW(TPolinomial P1);
}

TEST(Polinom, can_copy_polinomial)
{
  TPolinomial P1;
  ASSERT_NO_THROW(TPolinomial P2(P1));
}

TEST(Polinom, operator_plus_equally)
{
  TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
  TPolinomial P1;
  ASSERT_NO_THROW(P1 += a);
}

TEST(Polinom, operator_multiplication)
{
  TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);
  TPolinomial P1, P2, P3;
  P1 += a;
  P2 += b;

  ASSERT_NO_THROW(P1 * P2);
}

TEST(Polinom, operator_plus)
{
  TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);
  TPolinomial P1, P2, P3;
  P1 += a;
  P2 += b;

  ASSERT_NO_THROW(P2 + P1);
}

TEST(Polinom, operator_minus)
{
  TMonom a(new double[3]{ 1, 2, 3 }, 3, 1);
  TMonom b(new double[3]{ 3, 2, 1 }, 3, 1);
  TPolinomial P1, P2, P3;
  P1 += a;
  P2 += b;

  ASSERT_NO_THROW(P2 - P1);
}

TEST(Polinom, DOP_fractional_powers_DOP)
{
  TMonom a(new double[3]{ 1.55, 2.75, 3.95 }, 3, 1);
  TPolinomial P1;

  ASSERT_NO_THROW(P1 += a);
}

TEST(Polinom, DOP_number_of_variables_K_DOP)
{
  TMonom a(new double[5]{ 1, 2, 3, 4, 5 }, 5, 1);
  TMonom b(new double[6]{ 1, 2, 3, 4, 5, 6 }, 10, 1);
  TPolinomial P1;
  P1 += a;
  ASSERT_NO_THROW(P1 += b);
}

TEST(Polinom, DOP_save_data_in_file_DOP)
{
  TMonom a(new double[1]{ 3 }, 1, 1);
  TMonom b(new double[1]{ 1 }, 1, 1);
  TMonom c(new double[1]{ 2 }, 1, 1);
  TPolinomial P1;
  P1 += a;
  P1 += b;
  P1 += c;

  ASSERT_NO_THROW(P1.File(););
}