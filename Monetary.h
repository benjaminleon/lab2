 /*
 * FILNAMN:       Monetary.h
 * LABORATION:    Klass, operator;verlagring, undantag Lab2
 * PROGRAMMERARE: Minh Le Tran  920218-1237 Y3b
 *                Benjamin Lind 910506-1999 Y3b
 * DATUM:         2013-10-06
 */

#ifndef MONETARY_H
#define MONETARY_H

#include<string>
#include <stdexcept>


namespace monetary 
{

/*
 * Klassen Money lagrar penningbelopp f;r valutor
 * d'r hundradelar av valutaenheten anv'nds, 
 * till exempel kronor/oren eller euro/centimes.
 */
  
  class Money
  {
  public:   
    
    //---------Constructors------------
    // Money() = default; //testa ta bort om raden under racker
    
    Money(std::string currency="", int units=0, int centimer=0);
    Money(int units, int centimer=0);
  Money(Money& money): currency_{money.currency_}, units_{money.units_}, centimer_{money.centimer_}{}
    
    ~Money() = default;

    //---------Print-------------------
    
    void print(std::ostream& os) const;

    
    //--------Assignment---------------

    Money& operator=(const Money& rhs);



    //--------Addition-----------------
    Money operator+(const Money& m1);


    //------- Subtraktion -------------
    
    Money operator-(const Money& m1);


    //-------Sammansatt tilldelning----
    
    Money operator+=(const Money& m1);
    Money operator-=(const Money& m1);
    
  
   

  
    //-------Compare------------------
    bool operator==(const Money& money); 
    bool operator<(const Money& money);
    bool operator<=(const Money& money);
    bool operator>(const Money& money);
    bool operator>=(const Money& money);
    bool operator!=(const Money& money);

    //-------Increment----------------

    //---prefix--
    Money& operator++();

    //---postfix--
    Money operator++(int);

    //-------Decrement----------------
    
    //---prefix--
    Money& operator--();

    //---postfix--
    Money operator--(int);

    //-------Functions----------------

    std::string currency() const {return currency_;}

    std::string get_units() const;
    std::string get_centimer() const;
 

    


  private:
    
    std::string currency_;
    int units_;
    int centimer_;
    

  };

  
  /*
   * Klassen monetary_error 'r en undantagsklass
   * h'rledd fr[n logic_error i exception-hierarkin.
   */
   
  
  class monetary_error : public std::logic_error
    {
  public:
    explicit monetary_error(const std::string& what_arg) noexcept : std::logic_error{what_arg} {}

    explicit monetary_error(const char* what_arg) noexcept : std::logic_error{what_arg} {}
    }; 


  
  //-------Output------------------
  
  std::ostream& operator<<(std::ostream& os, const Money& cash);
  
  //-------Input------------------

  std::istream& operator>>(std::istream& is, Money& cash);
} 



#endif
