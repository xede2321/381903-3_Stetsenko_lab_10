#ifndef _TMONOM_
#define _TMONOM_

#include "List.h"

class TMonomData
{
public:
  double* data;
  double K;
  int dim;

  TMonomData(int t);
  TMonomData(double* _data = 0, int _dim = 0, double _K = 0);
  TMonomData(TMonomData& _v);
  ~TMonomData();
};

class TMonom : public TListElem<TMonomData>
{
protected:

public:
  TMonom(TMonomData _data);
  TMonom(double* _data = 0, int _dim = 0, double _K = 0);
  TMonom(TMonom& _v);
  ~TMonom();

  bool operator == (const TMonom& _v);
  bool operator != (const TMonom& _v);

  TMonomData& operator *();
  TMonomData& operator *(int);

  double GetK();
  void SetK(double _K);

  int GetDim();
  void SetDim(int _dim);

  virtual TMonom* Clone();

  double& operator[] (int i);
  TMonom& operator= (const TMonom& _v);
  TMonom  operator* (const TMonom& _v);
  TMonom  operator/ (const TMonom& _v);
  TMonom* operator+ (const TMonom& _v);
  TMonom* operator- (const TMonom& _v);

  bool operator> (const TMonom& _v);
  bool operator< (const TMonom& _v);

  friend ostream& operator<< (ostream& ostr, const TMonom& A);
  friend istream& operator>> (istream& istr, TMonom A);
};

#endif 