/* -----------------------------------------------------------------------------
FILE:              Polynomial.hpp
DESCRIPTION:       Header file of Polynomial class
COMPILER:          GCC

MODIFICATION HISTORY:
Author                  Date               Version
---------------         ----------         --------------
Edgaras Fiodorovas      2016-04-14         1.0
----------------------------------------------------------------------------- */
#pragma once
#include <iostream>
#include <vector>
#include <string>

class Polynomial {
  private:
    std::vector<int> coefficents;
  public:
    Polynomial();
    Polynomial( const std::initializer_list<int> coefficents );
    Polynomial( const std::vector<int> coefficents );
    Polynomial( const Polynomial &P );
    //~Polynomial();

    int GetDegree() const;
    int GetCoefficent( int pwr ) const;
    std::string GetExpression() const;
    int Eval(int x) const;

    void operator= ( const Polynomial &P );
    int& operator[] ( int val );
    Polynomial operator+ ( const Polynomial &P ) const;
    Polynomial operator- ( const Polynomial &P ) const;
    Polynomial operator* ( const Polynomial &P ) const;
    bool operator== ( const Polynomial &P ) const;

    friend std::ostream &operator<<( std::ostream &output, const Polynomial &P );
    friend std::istream &operator>>( std::istream  &input, Polynomial &P );
};
