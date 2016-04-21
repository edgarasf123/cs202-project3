/* -----------------------------------------------------------------------------

FILE:              Account.cpp

DESCRIPTION:       Account class member definitions.

COMPILER:          Visual Studio 2013

NOTES:             Used to handle individual accounts of bankacct application.

MODIFICATION HISTORY:

Author                  Date               Version
---------------         ----------         --------------
Edgaras Fiodorovas      2016-03-18         1.0

----------------------------------------------------------------------------- */


#include "Account.h"

using std::cout;
using std::endl;

/* -----------------------------------------------------------------------------
FUNCTION:          Account::Account()
DESCRIPTION:       Account constructor. Creates empty object.
----------------------------------------------------------------------------- */
Account::Account(){}

// ==============  Validation ======================
/* -----------------------------------------------------------------------------
FUNCTION:          Account::validate_name(  char * str )
DESCRIPTION:       Validates first/last name. (e.g. Williams)
ARGUMENTS:         str: the string to validate.
RETURNS:           Returns true if the name is valid.
----------------------------------------------------------------------------- */
bool Account::validate_name(const char * str) {
	int i = 0;
	for (; str[i] != 0; ++i)
		if (!isalpha(str[i]) || (i == 0 ? !isupper(str[i]) : !islower(str[i])) || i > 31)
			return false;
	return i >= 3;
}
/* -----------------------------------------------------------------------------
FUNCTION:          Account::validate_middle_initial(  char c )
DESCRIPTION:       Validates middle initial. (e.g. W)
ARGUMENTS:         c: the character to validate.
RETURNS:           Returns true if the middle initial is valid.
----------------------------------------------------------------------------- */
bool Account::validate_middle_initial(const char c) {
	return (isalpha(c) && isupper(c)) || c == 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Account::validate_ssn(  char * str )
DESCRIPTION:       Validates social security number. (e.g. 333224444)
ARGUMENTS:         str: the string to validate.
RETURNS:           Returns true if the ssn is valid.
----------------------------------------------------------------------------- */
bool Account::validate_ssn(const char * str) {
	int i = 0;
	for (; str[i] != 0; ++i)
		if (!isdigit(str[i]) || i > 9)
			return false;
	return i == 9;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Account::validate_phone_area_code(  char * str )
DESCRIPTION:       Validates phone area code. (e.g. 800)
ARGUMENTS:         str: the string to validate.
RETURNS:           Returns true if the phone area code is valid.
----------------------------------------------------------------------------- */
bool Account::validate_phone_area_code(const char * str) {
	int i = 0;
	for (; str[i] != 0; ++i)
		if (!isdigit(str[i]) || i > 3)
			return false;
	return i == 3;
}
/* -----------------------------------------------------------------------------
FUNCTION:          Account::validate_phone_number  char * str )
DESCRIPTION:       Validates phone number. (e.g. 3334444)
ARGUMENTS:         str: the string to validate.
RETURNS:           Returns true if the phone number is valid.
----------------------------------------------------------------------------- */
bool Account::validate_phone_number(const char * str) {
	int i = 0;
	for (; str[i] != 0; ++i)
		if (!isdigit(str[i]) || i > 7)
			return false;
	return i == 7;
}
/* -----------------------------------------------------------------------------
FUNCTION:          Account::validate_account_number(  char * str )
DESCRIPTION:       Validates account number. (e.g. AB1CD)
ARGUMENTS:         str: the string to validate.
RETURNS:           Returns true if the account number is valid.
----------------------------------------------------------------------------- */
bool Account::validate_account_number(const char * str) {
	int i = 0;
	for (; str[i] != 0; ++i)
		if ((!(isalpha(str[i]) && isupper(str[i])) && !isdigit(str[i])) || i>5)
			return false;
	return i == 5;
}
/* -----------------------------------------------------------------------------
FUNCTION:          Account::validate_account_password(  char * str )
DESCRIPTION:       Validates account password. (e.g. AB1CD2)
ARGUMENTS:         str: the string to validate.
RETURNS:           Returns true if the password is valid.
----------------------------------------------------------------------------- */
bool Account::validate_account_password(const char * str) {
	int i = 0;
	for (; str[i] != 0; ++i)
		if ((!(isalpha(str[i]) && isupper(str[i])) && !isdigit(str[i])) || i>6)
			return false;
	return i == 6;
}

/* -----------------------------------------------------------------------------
FUNCTION:          Account::print_info()
DESCRIPTION:       Prints out account information.
RETURNS:           Void function.
----------------------------------------------------------------------------- */
void Account::print_info() const{
	std::cout << std::left
		<< "Account Information:" << endl
		<< std::setw(18) << "First Name: " << first_name << endl
		<< std::setw(18) << "Last Name: " << last_name << endl
		<< std::setw(18) << "Middle Initial: " << middle_initial << endl
		<< std::setw(18) << "SSN: " << social_securty_number << endl
		<< std::setw(18) << "Phone number: " << "(" << phone_area_code << ")" << phone_number << endl
		<< std::setw(18) << "Account Balance:" << "$" << std::fixed << std::setprecision(2) << account_balance << endl
		<< std::setw(18) << "Account Number: " << account_number << endl
		<< std::setw(18) << "Account Password: " << account_password << endl;
}


/* -----------------------------------------------------------------------------
FUNCTION:          Account::is_valid() const
DESCRIPTION:       Checks if object has all correct information.
RETURNS:           Returns true if all information is correct.
----------------------------------------------------------------------------- */
bool Account::is_valid() const{
	return
		validate_name(last_name) &&
		validate_name(first_name) &&
		validate_middle_initial(middle_initial) &&
		validate_ssn(social_securty_number) &&
		validate_phone_area_code(phone_area_code) &&
		validate_phone_number(phone_number) &&
		validate_account_number(account_number) &&
		validate_account_password(account_password);
}

/* -----------------------------------------------------------------------------
FUNCTION:          Account::validate_credentials() const
DESCRIPTION:       Checks if provided password match with the account.
RETURNS:           Returns true if password is correct.
----------------------------------------------------------------------------- */
bool Account::validate_credentials(char * account_password) const{
	return strcmp(this->account_password, account_password) == 0;
}


/* -----------------------------------------------------------------------------
FUNCTION:          Account::is_getline( std::istream * stream, char * buf, int length)
DESCRIPTION:       Custom function for reading streams, reads every line, regardless of
                   whitespace.
ARGUMENTS:         stream: stream object
                   buf: buffer to read the line to
                   length: the size of the buffer
RETURNS:           Void function
----------------------------------------------------------------------------- */
void Account::is_getline(std::istream * stream, char * buf, int length){
	char c;
	int i = 0;
	while (true){
		c = stream->get();
		if (c == '\n' || c == '\r' || c == -1)
			break;
		if (i<length)
			buf[i++] = c;
	}
	buf[i] = 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator<< (std::ostream& os, const Account& account)
DESCRIPTION:       Operator overloading for <<, writes account information into a stream.
RETURNS:           ostream object
----------------------------------------------------------------------------- */
std::ostream& operator<< (std::ostream& os, const Account& account){
	os << account.last_name << std::endl
		<< account.first_name << std::endl
		<< account.middle_initial << std::endl
		<< account.social_securty_number << std::endl
		<< account.phone_area_code << std::endl
		<< account.phone_number << std::endl
		<< std::fixed << std::setprecision(2) << account.account_balance << std::endl
		<< account.account_number << std::endl
		<< account.account_password << std::endl
		<< std::endl;
	return os;
}

/* -----------------------------------------------------------------------------
FUNCTION:          operator>> (std::istream& is, Account& account)
DESCRIPTION:       Operator overloading for >>, reads account information from a stream.
RETURNS:           istream object
----------------------------------------------------------------------------- */
std::istream& operator>> (std::istream& is, Account& account){
	char line[40];
	while (!is.eof()){
		account.is_getline(&is, line, 32);
		if (Account::validate_name(line)){
			strcpy(account.last_name, line);
			account.is_getline(&is, account.first_name, 32);
			account.is_getline(&is, line, 2);  account.middle_initial = line[0];
			account.is_getline(&is, account.social_securty_number, 10);
			account.is_getline(&is, account.phone_area_code, 4);
			account.is_getline(&is, account.phone_number, 8);
			account.is_getline(&is, line, 32); account.account_balance = strtof(line, NULL);
			account.is_getline(&is, account.account_number, 6);
			account.is_getline(&is, account.account_password, 7);
			break;
		}
	}
	return is;
}

