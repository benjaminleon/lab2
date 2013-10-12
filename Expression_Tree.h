/*
 * Expression_Tree.h
 */
#ifndef EXPRESSIONTREE_H
#define EXPRESSIONTREE_H
#include <iosfwd>
#include <string>
#include <stdexcept>

/*
 * expression_error: kastas om ett fel inträffar i en Expression-operation;
 * ett diagnostiskt meddelande ska skickas med.
 */
// ATT GÖRA!


// OBSERVERA: NEDANSTÅENDE ÄR ENDAST KODSKELETT - MODIFIERA OCH KOMPLETTERA!

/*
 * Expression_Tree: Abstrakt, polymorf basklass för alla trädnodklasser.
 */
class Expression_Tree
{
 public:
  virtual long double      evaluate() const = 0;
  virtual std::string      get_postfix() const = 0;
  virtual std::string      str() const = 0;
  virtual void             print(std::ostream&) const = 0;
  virtual Expression_Tree* clone() const = 0;
  virtual ~Expression_Tree() = default;

 protected:

};


/*
 * Binary_Operator.
 */

class Binary_Operator : public Expression_Tree
{
 public:
  virtual ~Binary_Operator() = default;

protected:
  Expression_Tree* left_;
  Expression_Tree* right_;
 Binary_Operator(const Binary_Operator& other): left_{other.left_}, right_{other.right_} {} 

};



class Operand : public Expression_Tree
{
 public:
  virtual ~Operand() = default;
  virtual std::string get_postfix() const {return "hejsan";} 
  
 protected:
  double operand;
};




class Assign : public Binary_Operator
{ 
  long double evaluate() const override; 
  Assign* clone() const override;
  std::string get_postfix() const;
  void print(std::ostream&) const;
  std::string str() const {return "=";}
  ~Assign() = default;
 private:
  Assign(const Assign&) = default;
  
  
};

class Plus : public Binary_Operator
{ 
 public:
  Plus* clone() const override;
  std::string get_postfix() const;
  void print(std::ostream&) const;
  ~Plus() = default;  
  long double evaluate() const;
  std::string get_postfix();
  std::string str() const {return "+";}
  Plus(const Expression_Tree* left, const Expression_Tree* right);
  
 private:
  Plus(const Plus&);
  
  
};

class Minus : public Binary_Operator 
{
 public:
  Minus* clone() const override;
  std::string get_postfix() const;
  void print(std::ostream&) const;
  ~Minus() = default;
  long double evaluate() const;
  std::string str() const {return "-";}
  
 private:
  Minus(const Minus&);
  
  
};

class Times : public Binary_Operator
{
 public:
  Times* clone() const override;
  std::string get_postfix() const;
  void print(std::ostream& os) const; 
  ~Times() = default;
  long double evaluate() const;
  std::string str() const {return "*";}
 private:
  Times(const Times&);
 
   
};

class Divide : public Binary_Operator
{
 public:
  Divide* clone() const override;
  std::string get_postfix() const;
  void print(std::ostream&) const;
  ~Divide() = default;
  long double evaluate() const;
  std::string str() const {return "/";}
 private:
  Divide(const Divide&);
  
  
};

class Power: public Binary_Operator
{
 public:
  Power* clone() const override;
  std::string get_postfix() const;
  void print(std::ostream&) const;
  ~Power() = default; 
  long double evaluate() const;
  std::string str() const {return "^";}
 private:
  Power(const Power&);
  
   
};

class Integer : public Operand
{
 public:
  ~Integer()=default;
  Integer* clone() const override;
  void print(std::ostream&) const;
  long double evaluate() const {return int_;}
  std::string str() const {return std::to_string(int_);}
 Integer(int digits): int_{digits}{}
  

 private:
  Integer(const Integer&); // kopieringskonstruktor
  int int_;
  
  
};

class Real : public Operand
{
 public:
  ~Real()=default; 
  Real* clone() const override;
  void print(std::ostream&) const;
  long double evaluate() const {return real_;}
  std::string str() const {return std::to_string(real_);}

 Real(float digits): real_{digits}{}  
  
 private:
  Real(const Real&);  //kopieringskonstruktor
  float real_;

};

class Variable : public Operand
{
 public:
  void set_value();
  double long get_value() const;
  Variable* clone() const override;
  void print(std::ostream&) const;
  ~Variable() = default;
  std::string str() const {return std::to_string(get_value());}
  
 private:
  Variable(const Variable&);
  char variable_;
};

#endif
