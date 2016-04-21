/* -----------------------------------------------------------------------------

FILE:              bankacct.h

DESCRIPTION:       Header for bankacct application

COMPILER:          Visual Studio 2013

MODIFICATION HISTORY:

Author                  Date               Version
---------------         ----------         --------------
Edgaras Fiodorovas      2016-03-18         1.0

----------------------------------------------------------------------------- */


#define _CRT_SECURE_NO_WARNINGS
#ifndef BANKACCT_H
#define BANKACCT_H

#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>

#include "Account.h"

struct Arg_Data {
	char A[3 + 1]; // Phone area code
	char D[32]; // Database file name
	char F[32]; // First name
	char H[7 + 1]; // Phone number
	char L[32];  // Last Name
	char M; // Middle initial
	char N1[5 + 1]; // First account number
	char N2[5 + 1]; // Second account number
	char P1[6 + 1]; // First account password
	char P2[6 + 1]; // Second account password
	char R[32]; // Report file name
	char S[9 + 1]; // SSN
	float T; // Transfer amount
	char W[6 + 1]; // New password
};

void cmdln_parse_arguments(int, char **, char*, Arg_Data*);
void cmdln_process_arguments(char *, Arg_Data*);
void cmdln_invalid_arg(char *);

void cmdln_show_help();

std::vector<Account*> & database();

void database_load(char *);
void database_save(char *);
bool database_find(char *, Account ** = NULL);
bool database_report(char *);

bool validate_file_name(char *);

void str_sort(char *);

#endif
