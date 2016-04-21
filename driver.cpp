/* -----------------------------------------------------------------------------
FILE:              driver.cpp
DESCRIPTION:       C++ file containing main() function to test Polynomial class
COMPILER:          GCC

MODIFICATION HISTORY:
Author                  Date               Version
---------------         ----------         --------------
Edgaras Fiodorovas      2016-04-14         1.0
----------------------------------------------------------------------------- */
#include <iostream>
#include <iomanip>
#include "Polynomial.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::setw;

#define PRINT_POLYNOMIAL(p,x) (\
  cout << std::left << endl\
    << setw(12) << "Variable:" << #p << endl\
    << setw(12) << "Degree:"  << (p).GetDegree() << endl\
    << setw(12) << "Expression:" << (p).GetExpression() << endl\
    << setw(12) << "Out-Stream:" << (p) << endl\
    << #p"(" << x << ") = " << p.Eval(x) << endl\
)
#define CLEAR_INPUT() while (getchar() != '\n') {}

/* -----------------------------------------------------------------------------
FUNCTION:          main()
DESCRIPTION:       Entry point of program, multiple tests with output of
                   Polynomial class
RETURNS:           Void function
----------------------------------------------------------------------------- */
int main(){
  int x;
  cout << "x=";
  cin >> x;
  CLEAR_INPUT()

  Polynomial p_construct_default;
  PRINT_POLYNOMIAL(p_construct_default,x);

  cout << endl << "================" << endl;

  Polynomial p_construct_overloaded{0,3, 0, 0, 0, 5, -17};
  PRINT_POLYNOMIAL(p_construct_overloaded,x);

  cout << endl << "================" << endl;

  Polynomial p_construct_copy(p_construct_overloaded);
  cout << "Removing 5th degree of p_construct_copy" << endl;
  p_construct_copy[5] = 0;
  PRINT_POLYNOMIAL(p_construct_overloaded,x);
  PRINT_POLYNOMIAL(p_construct_copy,x);

  cout << endl << "================" << endl;

  Polynomial p_asignment = p_construct_copy;
  PRINT_POLYNOMIAL(p_asignment,x);

  cout << endl << "================" << endl;
  Polynomial p_input;
  cout << "Enter new polynomial: ";
  cin >> p_input;
  PRINT_POLYNOMIAL(p_input,x);
  cout << endl;
  cout << "p_asignment == p_input\t"
    << (p_asignment==p_input?"true":"false") << endl;
  cout << "p_asignment + p_input = ("
    << p_asignment.GetExpression() << ") + (" << p_input.GetExpression() << ") = "
    << (p_asignment+p_input).GetExpression() << endl;
  cout << "p_asignment - p_input = ("
    << p_asignment.GetExpression() << ") - (" << p_input.GetExpression() << ") = "
    << (p_asignment-p_input).GetExpression() << endl;
  cout << "p_asignment * p_input = ("
    << p_asignment.GetExpression() << ") * (" << p_input.GetExpression() << ") = "
    << (p_asignment*p_input).GetExpression() << endl;
  CLEAR_INPUT()
  return 0;
}
