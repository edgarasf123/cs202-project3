/* -----------------------------------------------------------------------------

FILE:              Account.h

DESCRIPTION:       Account class header file.

COMPILER:          Visual Studio 2013

NOTES:             Used to handle individual accounts of bankacct application.

MODIFICATION HISTORY:

Author                  Date               Version
---------------         ----------         --------------
Edgaras Fiodorovas      2016-03-18         1.0

----------------------------------------------------------------------------- */

#pragma once

#include <cstring>
#include <iostream>
#include <iomanip>


class Account {

	private:
		void is_getline(std::istream * stream, char * buf, int length);
	public:
		static bool validate_name(const char *);
		static bool validate_middle_initial(const char);
		static bool validate_ssn(const char *);
		static bool validate_phone_area_code(const char *);
		static bool validate_phone_number(const char *);
		static bool validate_account_number(const char *);
		static bool validate_account_password(const char *);

		char last_name[32];
		char first_name[32];
		char middle_initial;
		char social_securty_number[9 + 1];
		char phone_area_code[3 + 1];
		char phone_number[7 + 1];
		float account_balance;
		char account_number[5 + 1];
		char account_password[6 + 1];

		Account();

		bool is_valid() const;
		bool validate_credentials(char *) const;

		void print_info() const;

	friend std::ostream& operator<< (std::ostream&, const Account&);
	friend std::istream& operator>> (std::istream&, Account&);
};
