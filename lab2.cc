 
 /*
 * FILNAMN:       lab2.cc
 * LABORATION:    Klass, operator;verlagring, undantag Lab2
 * PROGRAMMERARE: Minh Le Tran  920218-1237 Y3b
 *                Benjamin Lind 910506-1999 Y3b
 * DATUM:         2013-10-06
 */


#include <iostream>
#include <string>

#include "Monetary.h"

using namespace monetary;
using namespace std;

int main()
{
try 
  {

    //------ Initialize-----
    Money m1;
    Money m2{100};
    Money m3{10, 50};
    Money m4{"SEK"};
    Money m5{"SEK", 10};
    Money m6{"FFR", 100, 50};
    Money m7{m6};
    Money m8{m1};

    m5.print(cout);
    
    cout << m5 << endl;
    cout << m3 << endl;
    cout << m4 << endl;


    //------ Assignment -----
    m4=m5;
    cout << m4 << endl;

    m4=m3;
    cout << m4 << endl;

    m1=m6;
    cout << m1 << endl;

    //m4 + m6; // Olika valutor
    
    //------ Addition -----
    m4 + m5;
    m1 + m2;
    
    //------ compare -----
    
    m4 < m5;
    m4 != m3;
     
   
    //m4 <= m6;  // G[r ej att j'mf;ra olika valutor
    

    //------ stegning -----
    ++m4;
   

    //------ sammansatt tilldelning -----
    m4 += m5;
   
    
    //------ subtraktion -----
    Money majs;
    Money banan{"SEK"};
    majs  = m4-banan;
    

    
  }
 catch(const monetary_error& e)
   {
     cout << e.what() << endl;
   }

 try
   {
     Money m1;
     cout << "Tilldela m1: ";
     cin >> m1;
     cout << "m1: "; 
     m1.print(cout);
     
   }
 catch(const monetary_error& e)
   {
     cout<< e.what() << endl;
   }

 


}


