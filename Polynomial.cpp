/* -----------------------------------------------------------------------------
FILE:              Polynomial.cpp
DESCRIPTION:       C++ file for Polynomial class
COMPILER:          GCC

MODIFICATION HISTORY:
Author                  Date               Version
---------------         ----------         --------------
Edgaras Fiodorovas      2016-04-14         1.0
----------------------------------------------------------------------------- */
#include <sstream>
#include <math.h>

#include "Polynomial.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;
using std::istringstream;
using std::ostringstream;
using std::getline;
/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial::Polynomial()
DESCRIPTION:       Creates empty polynomial of degree -1
----------------------------------------------------------------------------- */
Polynomial::Polynomial() {}
/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial::Polynomial( const std::vector<int> _coefs )
DESCRIPTION:       Constructor for Polynomial class, fills coefficents from
                   initializer_list.
NOTES:             First element has higest power, and last element is a
                   constant
----------------------------------------------------------------------------- */
Polynomial::Polynomial( const std::initializer_list<int> _coefs ) {
  for(const int * it = _coefs.begin(); it != _coefs.end(); ++it )
    coefficents.insert( coefficents.begin(), 1, *it );
}
/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial::Polynomial( const std::vector<int> _coefs )
DESCRIPTION:       Constructor for Polynomial class, fills coefficents from
                   vector object.
NOTES:             First element is constant, and last element has highest
                   past.
----------------------------------------------------------------------------- */
Polynomial::Polynomial( const std::vector<int> _coefs ) {
  coefficents = _coefs;
}
/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial::Polynomial( const Polynomial &P  )
DESCRIPTION:       A copy constructor
----------------------------------------------------------------------------- */
Polynomial::Polynomial( const Polynomial &P  ) {
  coefficents = P.coefficents;
}
/* -----------------------------------------------------------------------------
FUNCTION:          int Polynomial::GetDegree() const
DESCRIPTION:       Finds highest non-zero coefficent's power of polynomial.
RETURNS:           Degree of polynomial
----------------------------------------------------------------------------- */
int Polynomial::GetDegree() const{
  int degree = -1;
  for(int pwr=0;pwr<(int)coefficents.size();++pwr)
    if(coefficents[pwr] != 0)
      degree = pwr;
  return degree;
}
/* -----------------------------------------------------------------------------
FUNCTION:          int Polynomial::GetCoefficent( int pwr ) const
RETURNS:           Coefficent of specified power.
----------------------------------------------------------------------------- */
int Polynomial::GetCoefficent( int pwr ) const{
  if(pwr>GetDegree())
    return 0;
  return coefficents[pwr];
}
/* -----------------------------------------------------------------------------
FUNCTION:          std::string Polynomial::getExpression() const
RETURNS:           Expression of polynomial.
----------------------------------------------------------------------------- */
std::string Polynomial::GetExpression( ) const{
  stringstream result;
  bool printed = false;

  vector<int>::const_iterator r_iter = coefficents.begin();
  for (int pwr = GetDegree(); pwr>=0; --pwr){
    int val = r_iter[pwr];
    if(val == 0)
      continue;

    if(printed){
      result << (val > 0?" + ":" - ");
      val = abs(val);
    }
    result << val;

    if(pwr > 1)
      result << "x^" << pwr;
    else if(pwr == 1)
      result << "x";

    printed = true;
  }
  if(!printed)
    result << "0";
  return result.str();
}
/* -----------------------------------------------------------------------------
FUNCTION:          int Polynomial::eval( int x ) const
DESCRIPTION:       Evaluates thy polynomial at specified x value
RETURNS:           Evaluated polynomial
----------------------------------------------------------------------------- */
int Polynomial::Eval( int x ) const{
  int result = 0;
  for(int pwr=0;pwr<=GetDegree();++pwr)
    result += GetCoefficent(pwr) * pow( x, pwr );
  return result;
}
/* -----------------------------------------------------------------------------
FUNCTION:          void Polynomial::operator= (const Polynomial &P )
DESCRIPTION:       Copies specified polynomial to itself.
RETURNS:           Void function
----------------------------------------------------------------------------- */
void Polynomial::operator= (const Polynomial &P ){
  coefficents = P.coefficents;
}
/* -----------------------------------------------------------------------------
FUNCTION:          int& Polynomial::operator[] ( int pwr )
DESCRIPTION:       Returns a reference to coefficent of specified power.
RETURNS:           Reference to coefficent
----------------------------------------------------------------------------- */
int& Polynomial::operator[] ( int pwr ){
  if(pwr >= (int)coefficents.size())
    coefficents.resize(pwr+1);
  return coefficents[pwr];
}
/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial Polynomial::operator+ ( const Polynomial &P ) const{
DESCRIPTION:       Adds both polynomial.
RETURNS:           New added polynomial
----------------------------------------------------------------------------- */
Polynomial Polynomial::operator+ ( const Polynomial &P ) const{
  Polynomial result;
  for(int pwr=0;pwr<=GetDegree() || pwr<=P.GetDegree();++pwr)
    result[pwr] = GetCoefficent(pwr) + P.GetCoefficent(pwr);
  return result;
}
/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial Polynomial::operator- ( const Polynomial &P ) const{
DESCRIPTION:       Subtracts polynomial from another.
RETURNS:           New subtracted polynomial
----------------------------------------------------------------------------- */
Polynomial Polynomial::operator- ( const Polynomial &P ) const {
  Polynomial result;
  for(int pwr=0;pwr<=GetDegree() || pwr<=P.GetDegree();++pwr)
    result[pwr] = GetCoefficent(pwr) - P.GetCoefficent(pwr);
  return result;
}
/* -----------------------------------------------------------------------------
FUNCTION:          Polynomial Polynomial::operator* ( const Polynomial &P ) const
DESCRIPTION:       Multiplies two polynomials.
RETURNS:           New multiplied Polynomial
----------------------------------------------------------------------------- */
Polynomial Polynomial::operator* ( const Polynomial &P ) const {
  Polynomial result;
  for(int pwr1=0;pwr1<=GetDegree();++pwr1)
    for(int pwr2=0;pwr2<=P.GetDegree();++pwr2)
      result[pwr1+pwr2] = result[pwr1+pwr2] + GetCoefficent(pwr1)*(P.GetCoefficent(pwr2));
  return result;
}
/* -----------------------------------------------------------------------------
FUNCTION:          bool Polynomial::operator== ( const Polynomial &P ) const
DESCRIPTION:       Compares two polynomials.
RETURNS:           Returns true if two polynomials are equal to each other.
----------------------------------------------------------------------------- */
bool Polynomial::operator== ( const Polynomial &P ) const {
  if(GetDegree()!=P.GetDegree())
    return false;
  for(int pwr=0;pwr<=GetDegree();++pwr)
    if( GetCoefficent(pwr) != P.GetCoefficent(pwr))
      return false;
  return true;
}
/* -----------------------------------------------------------------------------
FUNCTION:          std::ostream &operator<<( std::ostream &output, const Polynomial &P )
DESCRIPTION:       Output stream for Polynomial class. Outputs polynomial in
                   list of numbers.
RETURNS:           Output Stream
NOTES:             First element has higest power, and last element is a constant
----------------------------------------------------------------------------- */
std::ostream &operator<<( std::ostream &output, const Polynomial &P ){
  bool printed = false;
  ostringstream result;

  vector<int>::const_iterator r_iter = P.coefficents.begin();
  for (int pwr = P.GetDegree(); pwr>=0; --pwr){
    int val = r_iter[pwr];

    if(printed)
      result << " ";
    result << val;

    printed = true;
  }
  if(!printed)
    result << "0";
  output << result.str();
  return output;
}
/* -----------------------------------------------------------------------------
FUNCTION:          std::istream &operator>>( std::istream  &input, Polynomial &P )
DESCRIPTION:       Input Stream for Polynomial class. Reads either list of
                   numbers(1 0 2 -1).
RETURNS:           Input Stream
NOTES:             First element has higest power, and last element is a constant
----------------------------------------------------------------------------- */
std::istream &operator>>( std::istream  &input, Polynomial &P ){
  P.coefficents.clear();
  string line;
  getline(cin, line);
  istringstream line_stream(line);

  int val;
  while(!line_stream.eof()){
    line_stream >> val;
    P.coefficents.insert( P.coefficents.begin(), 1, val );
  }
  return input;
}
