#include "TMonom.h"

TMonom::TMonom(TMonomData _data) : TListElem<TMonomData>(_data)
{
}

TMonom::TMonom(double* _data, int _dim, double _K) : TListElem<TMonomData>()
{
  if (_dim < 0)
  {
    throw "error";
  }

  data.dim = _dim;
  data.K = _K;

  if (data.dim > 0)
  {
    data.data = new double[data.dim];
    for (int i = 0; i < data.dim; i++)
    {
      data.data[i] = _data[i];
    }
  }
}

TMonom::TMonom(TMonom& _v) : TListElem<TMonomData>(_v)
{
  prev = 0;
  next = 0;
}

TMonom::~TMonom()
{
}

bool TMonom::operator==(const TMonom& _v)
{
  bool f = true;

  if (data.dim != _v.data.dim)
  {
    f = false;

  }

  if (data.dim > 0)
  {
    for (int i = 0; i < data.dim; i++)
    {
      if (data.data[i] != _v.data.data[i])
      {
        f = false;
        break;
      }
    }
    return f;
  }
  else
  {
    return data.K == _v.data.K;
  }
}

bool TMonom::operator!=(const TMonom& _v)
{
  return !this->operator==(_v);
}

TMonomData& TMonom::operator*()
{
  return data;
}

TMonomData& TMonom::operator*(int)
{
  return data;
}

double TMonom::GetK()
{
  return data.K;
}

void TMonom::SetK(double _K)
{
  data.K = _K;
}

int TMonom::GetDim()
{
  return data.dim;
}

void TMonom::SetDim(int _dim)
{
  if (data.dim == _dim)
  {
    return;
  }

  if (_dim < 0)
  {
    throw "error";
  }
  else if (_dim == 0)
  {
    if (data.dim > 0)
    {
      delete[] data.data;
    }
    data.dim = 0;
    data.data = 0;
  }
  else
  {
    if (data.dim > 0)
    {
      delete[] data.data;
    }
    data.dim = _dim;
    data.data = new double[data.dim];
    for (int i = 0; i < data.dim; i++)
    {
      data.data[i] = 0;
    }
  }
}

double& TMonom::operator[](int i)
{
  return data.data[i];
}

TMonom& TMonom::operator=(const TMonom& _v)
{
  if (this == &_v)
  {
    return *this;
  }
  next = 0;
  prev = 0;
  data.K = _v.data.K;

  if (data.dim == _v.data.dim)
  {
    for (int i = 0; i < data.dim; i++)
    {
      data.data[i] = _v.data.data[i];
    }
  }

  else if (_v.data.dim == 0)
  {
    if (data.dim > 0)
    {
      delete[] data.data;
    }
    data.dim = 0;
    data.data = 0;
  }
  else
  {
    if (data.dim > 0)
    {
      delete[] data.data;
    }
    data.dim = _v.data.dim;
    data.data = new double[data.dim];
    for (int i = 0; i < data.dim; i++)
    {
      data.data[i] = _v.data.data[i];
    }
  }
  return *this;
}

TMonom TMonom::operator*(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
  {
    throw "error";
  }

  TMonom tmp(*this);
  tmp.data.K = data.K * _v.data.K;

  for (int i = 0; i < data.dim; i++)
  {
    tmp.data.data[i] = this->data.data[i] + _v.data.data[i];
  }
  return tmp;
}

TMonom TMonom::operator/(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
  {
    throw "error";
  }

  TMonom tmp(*this);
  tmp.data.K = data.K / _v.data.K;

  for (int i = 0; i < data.dim; i++)
  {
    tmp.data.data[i] = this->data.data[i] - _v.data.data[i];
  }
  return tmp;
}

TMonom* TMonom::operator+(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
  {
    throw "error";
  }

  TMonom* tmp;

  if (*this == _v)
  {
    tmp = new TMonom(*this);
    tmp->data.K = this->data.K + _v.data.K;
  }
  else
  {
    tmp = new TMonom[2];
    if (*this > _v)
    {
      tmp[0] = *this;
      tmp[1] = _v;
    }
    else
    {
      tmp[0] = _v;
      tmp[1] = *this;
    }
  }
  return tmp;
}

TMonom* TMonom::operator-(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
  {
    throw "error";
  }

  TMonom* tmp = 0;

  if (*this == _v)
  {
    tmp = new TMonom(*this);
    tmp->data.K = this->data.K - _v.data.K;
  }
  else
  {
    tmp = new TMonom[2];
    if (*this < _v)
    {
      tmp[0] = *this;
      tmp[1] = _v;
    }
    else
    {
      tmp[0] = _v;
      tmp[1] = *this;
    }
  }

  return tmp;
}

bool TMonom::operator>(const TMonom& _v)
{
  bool temp = true;
  if (data.dim != _v.data.dim)
  {
    temp = false;
  }
  else if (data.dim > 0)
  {
    for (int i = 0; i < data.dim; i++)
    {
      if (data.data[i] > _v.data.data[i])
      {
        temp = true;
      }
      else if (data.data[i] < _v.data.data[i])
      {
        temp = false;
      }
      else
      {
        continue;
      }
    }
    temp = false;
  }
  else
  {
    return data.K > _v.data.K;
  }
  return temp;
}

bool TMonom::operator<(const TMonom& _v)
{
  if (data.dim != _v.data.dim)
  {
    return false;
  }
  if (data.dim > 0)
  {
    for (int i = 0; i < data.dim; i++)
    {
      if (data.data[i] < _v.data.data[i])
      {
        return true;
      }
      else if (data.data[i] > _v.data.data[i])
      {
        return false;
      }
      else
      {
        continue;
      }
    }
    return false;
  }
  else
  {
    return data.K < _v.data.K;
  }
}

istream& operator>>(istream& istr, TMonom A)
{
  int dim = 0;
  if (A.data.dim != 0)
  {
    dim = A.data.dim;
  }
  else
  {
    istr >> dim;
    A.SetDim(dim);
  }

  istr >> A.data.K;

  for (int i = 0; i < dim; i++)
  {
    istr >> A[i];
  }

  return istr;
}

ostream& operator<<(ostream& ostr, const TMonom& A)
{
  ostr << A.data.K;
  for (int i = 0; i < A.data.dim; i++)
  {
    ostr << "* x[" << i << "]^" << A.data.data[i];
  }
  ostr << " ";
  return ostr;
}

TMonomData::TMonomData(int t)
{
  if (t < 0)
  {
    throw "error";
  }
  else if (t == 0)
  {
    dim = 0;
    data = 0;
  }
  else
  {
    data = new double[dim];
    for (int i = 0; i < dim; i++)
    {
      data[i] = 0;
    }
  }
}

TMonomData::TMonomData(double* _data, int _dim, double _K)
{
  if (_dim < 0)
  {
    throw "error";
  }

  dim = _dim;
  K = _K;

  if (dim > 0)
  {
    data = new double[dim];
    for (int i = 0; i < dim; i++)
    {
      data[i] = 0;
    }
  }
}

TMonomData::TMonomData(TMonomData& _v)
{
  dim = _v.dim;
  K = _v.K;

  if (dim > 0)
  {
    data = new double[dim];
    for (int i = 0; i < dim; i++)
    {
      data[i] = _v.data[i];
    }
  }
}

TMonomData::~TMonomData()
{
  if (data != 0)
  {
    delete[] data;
    data = 0;
    dim = 0;
    K = 0;
  }
}

TMonom* TMonom::Clone()
{
  TMonom* res = new TMonom(*this);
  return res;
}