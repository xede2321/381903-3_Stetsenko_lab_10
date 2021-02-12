#ifndef _POLINOMIAL_
#define _POLINOMIAL_

#include <iostream>
#include <fstream>
#include "../Polinom/TMonom.h"
#include "List.h"


using namespace std;

class TPolinomial : public TList<TMonomData>
{
public:
  TPolinomial();
  TPolinomial(TPolinomial& _v);
  ~TPolinomial();

  TPolinomial& operator+= (TMonom& _v);

  TPolinomial operator* (TPolinomial& _v);
  TPolinomial operator+ (TPolinomial& _v);
  TPolinomial operator- (TPolinomial& _v);


  void File();
};
#endif 