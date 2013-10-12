/*
 * Expression_Tree.cc
 */
#include "Expression_Tree.h"
// INKLUDERA FÖR DET SOM KOMMER ATT ANVÄNDAS I DENNA FIL!
using namespace std;
#include <iostream>

// SEPARATA DEFINITIONER FÖR FÖR EXPRESSION_TREE-KLASSERNA DEFINIERAS HÄR.

void Assign::print(ostream& os) const
{
  os << str() << endl;
}

Assign* Assign::clone() const
{

  return new Assign(*this);
}



Plus* Plus::clone() const
{
  return new Plus(*this);
}

long double Plus::evaluate() const
{
  return left_->evaluate()+right_->evaluate();
}

Minus* Minus::clone() const
{
  return new Minus(*this);
}

Times* Times::clone() const
{
  return new Times(*this);
}
void Times::print(ostream& os) const
{
  os << str() << endl;
}

Divide* Divide::clone() const
{
  return new Divide(*this);
}

Power* Power::clone() const
{
  return new Power(*this);
}


Integer* Integer::clone() const
{
  return new Integer(*this);
}

void Integer::print(std::ostream& os) const
{
  os << int_ << endl;
}

