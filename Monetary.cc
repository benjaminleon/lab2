 /*
 * FILNAMN:       Monetary.cc
 * LABORATION:    Klass, operator;verlagring, undantag Lab2
 * PROGRAMMERARE: Minh Le Tran  920218-1237 Y3b
 *                Benjamin Lind 910506-1999 Y3b
 * DATUM:         2013-10-06
 */

#include "Monetary.h"
#include <stdexcept>
#include <iostream>
#include <sstream> 
using namespace std;


namespace monetary
{
  //*********************** Constructors *******************************

  Money::Money(std::string currency, int units,  int centimer): currency_{currency}, units_{units}, centimer_{centimer}
  {
    if(!currency.empty() && currency.size()!=3)
      throw monetary_error{"Trebokstäversvaluta, por favor!"};
    if(units<0)
      throw monetary_error{"positiva värden, tack!"};
    if(centimer<0 || centimer>99)
      throw monetary_error{"Hundradelarsvärden mellan 0 och 99, tack!"};
  }
    
  Money::Money(int units, int centimer):currency_{""}, units_{units}, centimer_{centimer}
  {
    if(units<0)
      throw monetary_error{"positiva värden, tack!"};
    if(centimer<0 || centimer>99)
      throw monetary_error{"Hundradelarsvärden mellan 0 och 99 tack!"};
  }

  //*********************** Print **************************************

  void Money::print(ostream& os) const
  {
    if (currency_.empty())
      os << get_units() << "." <<  get_centimer() << endl;
    else 
      os << currency() << " " << get_units() << "." <<  get_centimer() << endl;
  }

  ostream& operator<<(ostream& os, const Money& cash)
  {
    cash.print(os);
    return os ;
  }

  //*********************** Assignment *********************************
 
  Money& Money::operator=(const Money& rhs)
  {
    if (rhs.currency_=="" || currency_ == rhs.currency_ )
      {
	units_=rhs.units_;
	centimer_=rhs.centimer_;
      }
    else if (currency_=="")
      {
	currency_=rhs.currency_;
	units_=rhs.units_;
	centimer_=rhs.centimer_;
      }
    else
      {
	throw monetary_error("Fel, en specifierad valuta får ej ändras");
      }
    return (*this);
  }

  //*********************** Addition  **********************************

  Money Money::operator+(const Money& m1) 
  { 
    Money temp {*this}; 
    
    if (temp.currency_ ==  m1.currency_ || temp.currency_ == "" || m1.currency_ == "") 
      { 
      temp.units_ = temp.units_ + m1.units_; 
      temp.centimer_ = temp.centimer_ + m1.centimer_; 
      if (temp.centimer_ >= 100) 
        { 
	  temp.centimer_ = temp.centimer_ - 100; 
	  temp.units_ = temp.units_ + 1; 
        } 
      } 
    else
      { 
        throw monetary_error("Fel! Olika valuta får ej adderas!"); 
      } 
    return temp; 
  }


  //*********************** Subtraktion  **********************************

  Money Money::operator-(const Money& m1)
  {
    Money temp {*this};
    if(m1.currency_ == this->currency_ || m1.currency_ == "" || this->currency_ == "")
      {
	temp.centimer_ = temp.centimer_ - m1.centimer_;
	if (temp.centimer_<0)
	  {
	    temp.centimer_ = 100 + temp.centimer_;
	    temp.units_ = temp.units_ - 1; 
	  }
	temp.units_ = temp.units_ - m1.units_;
	if (temp.units_<0)
	  throw monetary_error("Fel, negativt value big boi!!!");
      }
    else
      throw monetary_error("Fel! Olika valuta får ej subtraheras!");

    return temp;
  }
  




  //*********************** Compare ************************************

  bool Money::operator==(const Money& money) 
  { 
    if(currency_ != money.currency_ && currency_ != "" && money.currency_ != "") 
      { 
	throw monetary_error("Fel! Det går ej att jämnföra två olika valutor!"); 
      } 
    return ((currency_ == money.currency_) && (units_ == money.units_) && (centimer_ == money.centimer_)); 
  } 
  
  bool Money::operator<(const Money& money) 
  { 
    if(currency_ != money.currency_ && currency_ != "" && money.currency_ != "") 
      { 
        throw monetary_error("Fel! Det går ej att jämnföra två olika valutor!"); 
      } 
    else if(units_ == money.units_) 
      { 
        return (centimer_ < money.centimer_); 
      } 
    return (units_ < money.units_) ; 
  } 
  
  bool Money::operator>(const Money& money) 
  { 
    return !(*this < money || *this == money); 
  } 
  
  bool Money::operator<=(const Money& money) 
  { 
    return (*this < money || *this == money); 
  } 
  
  bool Money::operator>=(const Money& money) 
  { 
    return (*this > money || *this == money); 
  } 
  
  bool Money::operator!=(const Money& money) 
  { 
    return !(*this == money); 
  } 
  
  //*********************** Increment  *********************************

  Money& Money::operator++() 
  { 
    centimer_ = centimer_ + 1; 
    if (centimer_ > 99) 
      { 
        centimer_ = 0; 
        units_ = units_ + 1; 
      } 
    return *this; 
  } 
  
  Money Money::operator++(int) 
  {  
    Money tmp {*this};
    tmp.centimer_= centimer_; 
    centimer_ = centimer_ + 1; 
    if (centimer_ > 99) 
      { 
	centimer_ = 0; 
        units_ = units_ + 1; 
      } 
    return tmp; 
  } 
  


  //*********************** Plus-assignement **************************

  Money Money::operator+=(const Money& m1)
  {
    *this = *this + m1;
    return *this;
  }

  //*********************** Minus-assignement *************************
  Money Money::operator-=(const Money& m1)
  {
    *this = *this - m1;
    return *this;
  }

  //*********************** Decrement *********************************
  Money& Money::operator--()
  {
    centimer_ = centimer_ -1 ;
    if (centimer_ < 0)
      {
	centimer_ = centimer_ + 100;
	units_ = units_ - 1;
      }
    if (units_ < 0)
      throw monetary_error("negativt värde ej tillåtet, du stegar för lååångt");
    return *this;
  }

  Money Money::operator--(int)
  {
    Money tmp {*this};
    centimer_ = centimer_ - 1;
    if(centimer_ < 0)
      {
	centimer_ = centimer_ + 100;
	units_ = units_ - 1;
      }
    if (units_ < 0)
      throw monetary_error("negativt värde ej tillåtet, du stegar för lååångt");
    return tmp;
  }
	    

  //*********************** Get private members  ***********************

  string Money::get_units() const
  {
    string Result;
    ostringstream convert;
    convert << units_;
    Result = convert.str();
    return Result;
  }
  
  string Money::get_centimer() const
  {
    string Result;
    ostringstream convert;
    convert << centimer_;
    Result = convert.str();
    return Result;
  }
  

  //*********************** Input  ***********************

  
 
  istream& operator>>(istream& is, Money& cash)
  {
    is>>ws;
    char c;
    is.get(c);

    //======= 1st char alpha =======
     
    if(isalpha(c))
      {
	string str_curr;
	stringstream ss;
	ss << c;
	ss >> str_curr; 
	is.get(c);
	while(!isspace(c))
	  {     
	    if(isalpha(c))
	      {
		string str;
		stringstream ss;
		ss << c;
		ss >> str;
		str_curr.append(str);
		is.get(c);
	      }
	    else
	      throw monetary_error("Fel inmatning");
	  }
	if(isspace(c))
	  {
	    is>>ws;
	    is.get(c);
	    // digit after currency
	    if(isdigit(c))
	      {
		string str_unit; 
		stringstream ss;
		ss << c;
		ss >> str_unit;
		is.get(c);
		while(c!='.' && !isspace(c))
		  {
		    if(isdigit(c))
		      {
			string str2;
			stringstream ss;
			ss << c;
			ss >> str2;
			str_unit.append(str2);
			is.get(c);
		      }
		    else 
		      throw monetary_error("Fel inmatning");
		  }
		
		// cents
		if(c=='.')
		  {
		    string str_cent;
		    is.get(c);
		    while(isdigit(c))
		      {
			string str2;
			stringstream ss;
			ss << c;
			ss >> str2;
			str_cent.append(str2);
			is.get(c);
		      }
		    if(isspace(c))
		      {
			int unit;
			int centimer;

			stringstream convert_unit(str_unit); //because str_unit is of wrong data type 
			if ( !(convert_unit >> unit) )
			  unit = 0;//if that fails set unit to 0

			stringstream convert_cent(str_cent); //because str_cent is of wrong data type
			if ( !(convert_cent >> centimer) )
			  centimer = 0;//if that fails set centimer to 0
	 
			Money temp{str_curr,unit,centimer};
			cash=temp;
			return is;
		      }
		    else
		      throw monetary_error("Fel inmatning");
		  }
		if(isspace(c))
		  {
		    int unit;
		    stringstream convert(str_unit); //because str_unit is of  wrong data type
		    if ( !(convert >> unit) )
		      unit = 0;//if that fails set Result to 0
		    Money temp{str_curr,unit};
		    cash=temp;
		    return is;
		  }
		else
		  throw monetary_error("Fel inmatning");
	      }
	    else
	      throw monetary_error("Fel inmatning");
	    
	  }
      }
    
    // ============= 1st char is a digit =======

    if(isdigit(c))
      {
	string str_unit;
	stringstream ss;
	ss << c;
	ss >> str_unit;
	is.get(c);
	while(c!='.' && !isspace(c) ) 
	  {
	    if(isdigit(c)) 
	      {
		string str1;
		stringstream ss;
		ss << c;
		ss >> str1;
		str_unit.append(str1);
		is.get(c);
	      }
	    else
	      throw monetary_error("Fel inmatning");
	  }
	//cents
	if(c=='.')
	  {
	    string str_cent;
	    is.get(c);
	    while(!isspace(c)) 
	      {
		if(isdigit(c)) 
		  {
		    string str1;
		    stringstream ss;
		    ss << c;
		    ss >> str1;
		    str_cent.append(str1);
		    is.get(c);
		  }
		else
		  throw monetary_error("Fel inmatning");
	      }
	    if(isspace(c))
	      {
		int unit;
		int centimer;
		stringstream convert_unit(str_unit);//because str_unit is of wrong data type
		if ( !(convert_unit >> unit) )
		  unit = 0;//if that fails set unit to 0
		
		stringstream convert_cent(str_cent);//because str_cent is of wrong data type
		if ( !(convert_cent >> centimer) )
		  centimer = 0;//if that fails set centimer to 0
		Money temp{unit,centimer};
		cash = temp;
		return is;
	      }
	    else
	      throw monetary_error("Fel inmatning");
	  }
	else
	  {
	    int unit;
	    stringstream convert_unit(str_unit);//because str_unit is of wrong data type
	    if ( !(convert_unit >> unit) )
	      unit = 0;//if that fails set unit to 0
	    Money temp{unit};
	    cash = temp;
	    return is;
	  }	
      }
    else
      {
	throw monetary_error("Fel inmatning");
      }
    return is;
    
  }



}
