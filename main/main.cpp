#include <iostream>
#include "../Polinom/Polinom.h"
#include "List.h"
#include "../Polinom/TMonom.h"
using namespace std;

int main()
{
  TMonom a(new double[1]{ 3 }, 1, 1);
  TMonom b(new double[1]{ 1 }, 1, 1);
  TMonom c(new double[1]{ 2 }, 1, 1);
  TPolinomial P1;
  P1 += a;
  P1 += b;
  P1 += c;
  P1.File();


  return 0;
}