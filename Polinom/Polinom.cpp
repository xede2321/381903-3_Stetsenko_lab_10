#include "Polinom.h"
#include "../Polinom/TMonom.h"

TPolinomial::TPolinomial() : TList<TMonomData>()
{
}

TPolinomial::TPolinomial(TPolinomial& _v) : TList<TMonomData>(_v)
{
}

TPolinomial::~TPolinomial()
{

}

TPolinomial& TPolinomial::operator+=(TMonom& _v)
{
  if (this->root == 0)
  {
    this->root = _v.Clone();
    this->end = this->root;
  }
  else
  {
    TMonom* temp = static_cast<TMonom*>(this->root);

    while (temp != 0)
    {
      if (*temp == _v)
      {
        temp->SetK(temp->GetK() + _v.GetK());
      }
      else
      {
        TMonom* temp2 = _v.Clone();
        if (*temp < _v)
        {
          temp2->SetPrev(temp->GetPrev());
          temp2->SetNext(temp);

          if (temp->GetPrev() != 0)
          {
            temp->GetPrev()->SetNext(temp2);
          }
          else
          {
            this->root = temp2;
          }

          temp->SetPrev(temp2);
          return *this;
        }
        else
        {
          if (temp->GetNext() == 0)
          {
            temp2->SetPrev(temp);
            temp->SetNext(temp2);
            this->end = temp2;
            return *this;
          }
          else
          {
            temp = static_cast<TMonom*>(temp->GetNext());
          }
        }
      }
    }
  }
  return *this;
}

TPolinomial TPolinomial::operator*(TPolinomial& _v)
{
  TPolinomial res;
  TMonom* tmp1 = static_cast<TMonom*>(root);

  if (root == 0 && _v.root)
  {
    throw "Oshibka";
  }

  while (tmp1 != 0)
  {
    TMonom* tmp2 = static_cast<TMonom*>(_v.root);

    while (tmp2 != 0)
    {
      TMonom tmp3;
      tmp3 = (static_cast<TMonom&>(*tmp2)) * (static_cast<TMonom&>(*tmp1));
      res += tmp3;
      tmp2 = static_cast<TMonom*>(tmp2->GetNext());
    }
    tmp1 = static_cast<TMonom*>(tmp1->GetNext());
  }
  return res;
}

TPolinomial TPolinomial::operator+(TPolinomial& _v)
{
  if (_v.root == 0 || root == 0)
  {
    throw "Oshibka";
  }

  TPolinomial res;
  TMonom* temp = static_cast<TMonom*>(_v.root);
  TMonom* temp2 = static_cast<TMonom*>(root);
  TMonom* r = 0;

  while (temp != 0 && temp2 != 0)
  {
    TMonom temp3;
    if (*temp == *temp2)
    {
      temp3 = ((*temp) + (*temp2))[0];
      temp = static_cast<TMonom*>(temp->GetNext());
      temp2 = static_cast<TMonom*>(temp2->GetNext());
    }
    else if (*temp < *temp2)
    {
      temp3 = *temp2;
      temp2 = static_cast<TMonom*>(temp2->GetNext());
    }
    else
    {
      temp3 = *temp;
      temp = static_cast<TMonom*>(temp->GetNext());
    }

    if (r == 0)
    {
      res += temp3;
      r = static_cast<TMonom*>(res.root);
    }
    else
    {
      r->SetNext(temp3.Clone());
      r->GetNext()->SetPrev(static_cast<TMonom*>(r));
      r = static_cast<TMonom*>(r->GetNext());
    }
  }
  if (temp != 0)
  {
    while (temp != 0)
    {
      r->SetNext(new TMonom(*temp));
      r->GetNext()->SetPrev(r);
      r = static_cast<TMonom*>(r->GetNext());
      temp = static_cast<TMonom*>(temp->GetNext());
    }
  }
  else if (temp2 != 0)
  {
    while (temp2 != 0)
    {
      r->SetNext(new TMonom(*temp2));
      r->GetNext()->SetPrev(r);
      r = static_cast<TMonom*>(r->GetNext());
      temp = static_cast<TMonom*>(temp2->GetNext());
    }
  }
  return res;
}

TPolinomial TPolinomial::operator-(TPolinomial& _v)
{
  {
    if (_v.root == 0 || root == 0)
    {
      throw "Oshibka";
    }

    TPolinomial res;
    TMonom* temp = static_cast<TMonom*>(_v.root);
    TMonom* temp2 = static_cast<TMonom*>(root);
    TMonom* r = 0;

    while (temp != 0 && temp2 != 0)
    {
      TMonom temp3;
      if (*temp == *temp2)
      {
        temp3 = ((*temp) - (*temp2))[0];
        temp = static_cast<TMonom*>(temp->GetNext());
        temp2 = static_cast<TMonom*>(temp2->GetNext());
      }
      else if (*temp > *temp2)
      {
        temp3 = *temp;
        temp = static_cast<TMonom*>(temp->GetNext());
      }
      else
      {
        temp3 = *temp2;
        temp2 = static_cast<TMonom*>(temp2->GetNext());
      }

      if (r == 0)
      {
        res += temp3;
        r = static_cast<TMonom*>(res.root);
      }
      else
      {
        r->SetNext(temp3.Clone());
        r->GetNext()->SetPrev(static_cast<TMonom*>(r));
        r = static_cast<TMonom*>(r->GetNext());
      }
    }
    if (temp != 0)
    {
      while (temp != 0)
      {
        r->SetNext(new TMonom(*temp));
        r->GetNext()->SetPrev(r);
        r = static_cast<TMonom*>(r->GetNext());
        temp = static_cast<TMonom*>(temp->GetNext());
      }
    }
    else if (temp2 != 0)
    {
      while (temp2 != 0)
      {
        r->SetNext(new TMonom(*temp2));
        r->GetNext()->SetPrev(r);
        r = static_cast<TMonom*>(r->GetNext());
        temp = static_cast<TMonom*>(temp2->GetNext());
      }
    }
    return res;
  }
}

void TPolinomial::File()
{
  ofstream outf("Data.txt");
  if (!outf)
  {
    throw "Oshibka file";
  }
  if (this->root == 0)
  {
    return;
  }

  TMonom* temp = static_cast<TMonom*>(this->root);

  while (temp != NULL)
  {
    outf << temp[0] << endl;
    TMonom* temp2 = static_cast<TMonom*>(temp->GetNext());
    if (temp2 != NULL)
    {
      outf << temp2[0] << endl;
      temp = static_cast<TMonom*>(temp2->GetNext());
    }
    else
    {
      return;
    }
  }
}