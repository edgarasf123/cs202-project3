/* -----------------------------------------------------------------------------

FILE:              bankacct.cpp

DESCRIPTION:       Main code for command-line bankacct application

COMPILER:          Visual Studio 2013

MODIFICATION HISTORY:

Author                  Date               Version
---------------         ----------         --------------
Edgaras Fiodorovas      2016-03-18         1.0

----------------------------------------------------------------------------- */

#include "bankacct.h"
#include "math.h"

using std::cout;
using std::endl;
using std::vector;

/* -----------------------------------------------------------------------------
FUNCTION:          main(int argc, char *argv[])
DESCRIPTION:       Initiates bankacct application
ARGUMENTS:         argc: Argument count passed trough command line.
                   argv: Pointer array, which points to each c-string of the argument.
RETURNS:           Returns 0 on succesful execution
----------------------------------------------------------------------------- */
int main(int argc, char *argv[]){
	char argi[32] = {};
	Arg_Data argd = {};
	cmdln_parse_arguments(argc, argv, argi, &argd);
	cmdln_process_arguments(argi, &argd);
	return 0; // 0=success
}

/* -----------------------------------------------------------------------------
FUNCTION:          cmdln_parse_arguments(int argc, char ** argv, char * argi, Arg_Data * argd)
DESCRIPTION:       Parses the command line, which then parsed information is
                   stored in argi and argd arguments
ARGUMENTS:         argc: Argument count argument passed trough main() function.
                   argv: Argument var argument passed trough main() function.
				   argd: c-string of argument initials. Writes each initial of argument.
                   argd: Pointer to a Arg_Data struct variable. Writes data values
                         of each argument.
RETURNS:           Void functions
----------------------------------------------------------------------------- */
void cmdln_parse_arguments(int argc, char ** argv, char * argi, Arg_Data * argd){
	for (int i = 1; i < argc; ++i){
		char * arg_line = argv[i];
		if (arg_line[0] != '/')
			cmdln_invalid_arg(arg_line);
		char arg_char = toupper(arg_line[1]);
		argi[i - 1] = arg_char;
		switch (arg_char){
			case '?':
				if (arg_line[2] != 0)
					cmdln_invalid_arg(arg_line);
				break;
			case 'I':
				if (arg_line[2] != 0)
					cmdln_invalid_arg(arg_line);
				break;
			case 'F':
				if (Account::validate_name(arg_line + 2))
					strcpy(argd->F, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'L':
				if (Account::validate_name(arg_line + 2))
					strcpy(argd->L, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'D':
				if (validate_file_name(arg_line + 2))
					strcpy(argd->D, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'R':
				if (validate_file_name(arg_line + 2))
					strcpy(argd->R, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'A':
				if (Account::validate_phone_area_code(arg_line + 2))
					strcpy(argd->A, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'H':
				if (Account::validate_phone_number(arg_line + 2))
					strcpy(argd->H, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'M':
				if (Account::validate_middle_initial(*(arg_line + 2)) && strlen(arg_line) <= 3)
					argd->M = *(arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'N':
				if (Account::validate_account_number(arg_line + 2))
					strcpy(argd->N1[0] == 0 ? argd->N1 : argd->N2, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'P':
				if (Account::validate_account_password(arg_line + 2))
					strcpy(argd->P1[0] == 0 ? argd->P1 : argd->P2, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'S':
				if (Account::validate_ssn(arg_line + 2))
					strcpy(argd->S, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			case 'T':
				if (sscanf(arg_line + 2, "%f", &argd->T) == 0 || argd->T <= 0)
					cmdln_invalid_arg(arg_line);
				argd->T = roundf(argd->T * 100) / 100;
				break;
			case 'W':
				if (Account::validate_account_password(arg_line + 2))
					strcpy(argd->W, arg_line + 2);
				else
					cmdln_invalid_arg(arg_line);
				break;
			default:
				cmdln_invalid_arg(arg_line);
				break;
		}
	}
	str_sort(argi);
}

void cmdln_invalid_arg(char * arg){
	cout << "Invalid argument '" << arg << "'" << endl
		<< "Type 'bankacct /?' for help." << endl;
	exit(1);
}

/* -----------------------------------------------------------------------------
FUNCTION:          cmdln_process_arguments(char * argi, Arg_Data * argd)
DESCRIPTION:       Executes provided arguments
ARGUMENTS:         argd: c-string of argument initials.
ARGUMENTS:         argd: Pointer to a Arg_Data struct variable. Holds data values
                         of each argument.
RETURNS:           Void functions
----------------------------------------------------------------------------- */
void cmdln_process_arguments(char * argi, Arg_Data * argd) {
	if(strchr(argi, '?') != NULL || argi[0] == 0){ // Show Help
		cmdln_show_help();
	}else if( strcmp(argi, "DINP") == 0){ // Show account information
		Account * account;
		database_load(argd->D);
		if (!database_find(argd->N1, &account) || !account->validate_credentials(argd->P1)){
			cout << "Access Denied!" << endl;
			exit(1);
		}
		account->print_info();
	}else if (strcmp(argi, "DFNP") == 0) { // Change first name
		Account * account;
		database_load(argd->D);
		if (!database_find(argd->N1, &account) || !account->validate_credentials(argd->P1)){
			cout << "Access Denied!" << endl;
			exit(1);
		}
		strcpy(account->first_name, argd->F);
		database_save(argd->D);
		cout << "Account(" << argd->N1 << ") first name was updated to '" << argd->F << "'" << endl;
	}else if (strcmp(argi, "DLNP") == 0) { // Change last name
		Account * account;
		database_load(argd->D);
		if (!database_find(argd->N1, &account) || !account->validate_credentials(argd->P1)){
			cout << "Access Denied!" << endl;
			exit(1);
		}
		strcpy(account->last_name, argd->L);
		database_save(argd->D);
		cout << "Account(" << argd->N1 << ") last name was updated to '" << account->last_name << "'" << endl;
	}else if (strcmp(argi, "DMNP") == 0) { // Change middle initial
		Account * account;
		database_load(argd->D);
		if (!database_find(argd->N1, &account) || !account->validate_credentials(argd->P1)){
			cout << "Access Denied!" << endl;
			exit(1);
		}
		account->middle_initial = argd->M;
		database_save(argd->D);
		cout << "Account(" << argd->N1 << ") middle initial was updated to '" << account->middle_initial << "'" << endl;
	}else if (strcmp(argi, "DNPS") == 0) { // Change ssn
		Account * account;
		database_load(argd->D);
		if (!database_find(argd->N1, &account) || !account->validate_credentials(argd->P1)){
			cout << "Access Denied!" << endl;
			exit(1);
		}
		strcpy(account->social_securty_number, argd->S);
		database_save(argd->D);
		cout << "Account(" << argd->N1 << ") SSN was updated to '" << account->social_securty_number << "'" << endl;
	}else if (strcmp(argi, "ADNP") == 0) { // Change phone area code
		Account * account;
		database_load(argd->D);
		if (!database_find(argd->N1, &account) || !account->validate_credentials(argd->P1)){
			cout << "Access Denied!" << endl;
			exit(1);
		}
		strcpy(account->phone_area_code, argd->A);
		database_save(argd->D);
		cout << "Account(" << argd->N1 << ") phone area code was updated to '" << argd->A << "'" << endl;
	}else if (strcmp(argi, "DHNP") == 0) { // Change phone number
		Account * account;
		database_load(argd->D);
		if (!database_find(argd->N1, &account) || !account->validate_credentials(argd->P1)){
			cout << "Access Denied!" << endl;
			exit(1);
		}
		strcpy(account->phone_number, argd->H);
		database_save(argd->D);
		cout << "Account(" << argd->N1 << ") phone number was updated to '" << argd->H << "'" << endl;
	}else if (strcmp(argi, "DNNPPT") == 0) { // Transfer funds
		Account * sender, * receiver;
		database_load(argd->D);

		if (!database_find(argd->N1, &sender) || !sender->validate_credentials(argd->P1)){
			cout << "(sender)Access Denied!" << endl;
			exit(1);
		}
		if (!database_find(argd->N2, &receiver) || !receiver->validate_credentials(argd->P2)){
			cout << "(receiver)Access Denied!" << endl;
			exit(1);
		}
		if (argd->T == 0){
			cout << "You can't transfer $0.00." << endl;
			exit(1);
		}
		if (argd->T > sender->account_balance){
			cout << "You can't transfer more funds than the sender has." << endl;
			exit(1);
		}
		sender->account_balance -= argd->T;
		receiver->account_balance += argd->T;
		database_save(argd->D);
		cout << "Transfered $" << argd->T << " from " << argd->N1 << " to " << argd->N2;
	}else if (strcmp(argi, "DNPW") == 0) { // Change password
		Account * account;
		database_load(argd->D);
		if (!database_find(argd->N1, &account) || !account->validate_credentials(argd->P1)){
			cout << "Access Denied!" << endl;
			exit(1);
		}
		strcpy(account->account_password, argd->W);
		database_save(argd->D);
		cout << "Account(" << argd->N1 << ") password was updated to '" << argd->W << "'" << endl;
	}else if (strcmp(argi, "DR") == 0) { // Write report
		database_load(argd->D);
		if (database_report(argd->R)){
			cout << "Report was written to " << argd->R << endl;
		}else{
			cout << "Unable to write report to " << argd->R << endl;
			exit(1);
		}
	}else {
		cout << "Invalid combination of arguments '" << argi << "'" << endl
			<< "Type 'bankacct /?' for help." << endl;
		exit(1);
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          cmdln_show_help()
DESCRIPTION:       Prints out help screen in console.
RETURNS:           Void function
----------------------------------------------------------------------------- */
void cmdln_show_help() {
	cout
		<< "bankacct help : " << endl
		<< "" << endl
		<< "Control Arguments:" << endl

		<< "\t/?\t\tShows this message." << endl
		<< "" << endl

		<< "\t/I\t\tShows account information. " << endl
		<< "\t\t\tMust be used with following arguments /D, /N, and /P." << endl
		<< "" << endl
		<< "\t\t\tExample: bankacct /DBankDB.Txt /NA123B /PA23B42 /I" << endl
		<< "" << endl

		<< "\t/Ffirstname\tChange first name of an account." << endl
		<< "\t\t\tMust be used with following arguments /D, /N, and /P." << endl
		<< "" << endl
		<< "\t\t\tExample:  bankacct /DBankDB.Txt /NA123B /PA23B42" << endl
		<< "\t\t\t\t/FSteven" << endl
		<< "" << endl

		<< "\t/Llastname\tChange last name of an account." << endl
		<< "\t\t\tMust be used with following arguments /D, /N, and /P." << endl
		<< "" << endl
		<< "\t\t\tExample:  bankacct /DBankDB.Txt /NA123B /PA23B42" << endl
		<< "\t\t\t\t/LRichards" << endl
		<< "" << endl

		<< "\t/Minitial\tChange middle initial of an account." << endl
		<< "\t\t\tMust be used with following arguments /D, /N, and /P." << endl
		<< "" << endl
		<< "\t\t\tExample:  bankacct /DBankDB.Txt /NA123B /PA23B42 /MA" << endl
		<< "" << endl

		<< "\t/Sssn\t\tChange SSN of an account. " << endl
		<< "\t\t\tMust be used with following arguments /D, /N, and /P." << endl
		<< "" << endl
		<< "\t\t\tExample: bankacct /DBankDB.Txt /NA123B /PA23B42" << endl
		<< "\t\t\t /S123894321" << endl
		<< "" << endl

		<< "\t/Aareacode\tChange phone area code of an account." << endl
		<< "\t\t\tMust be used with following arguments /D, /N, and /P." << endl
		<< "" << endl
		<< "\t\t\tExample: bankacct /DBankDB.Txt /NA123B" << endl
		<< "\t\t\t/PA23B42 /A775" << endl
		<< "" << endl

		<< "\t/Hphonenumber\tChange phone number of an account." << endl
		<< "\t\t\tMust be used with following arguments /D, /N, and /P." << endl
		<< "" << endl
		<< "\t\t\tExample: bankacct /DBankDB.Txt /NA123B" << endl
		<< "\t\t\t/PA23B42 /H3324581" << endl
		<< "" << endl

		<< "\t/Wnewpassword\tChange password of an account. " << endl
		<< "\t\t\tMust be used with following arguments /D, /N," << endl
		<< "\t\t\tand (old password)/P." << endl
		<< "" << endl
		<< "\t\t\tExample: bankacct /DBankDB.Txt /NA123B /PA23B42" << endl
		<< "\t\t\t/WZZSTOP" << endl
		<< "" << endl

		<< "\t/Rfilename\tWrite database report to a file." << endl
		<< "\t\t\tMust be used with /D argument." << endl
		<< "" << endl
		<< "\t\t\tExample: bankacct /DBankDB.Txt /RBankRpt.Txt" << endl
		<< "\t\t\t" << endl
		<< "" << endl

		<< "\t/Tammount\tTransfer funds between two accounts. " << endl
		<< "\t\t\tMust be used with following arguments" << endl
		<< "\t\t\tin following order /D, (sender)/N, (sender)/P," << endl
		<< "\t\t\t(recipient)/N, and (recipient)/P." << endl
		<< "" << endl
		<< "\t\t\tExample: bankacct /DBankDB.Txt /NA123B" << endl
		<< "\t\t\t /PA23B42 /NC123A /PZ52C42 /T76809.20" << endl
		<< "" << endl

		<< "Specifiers:" << endl
		<< "\t/Dfilename\tSpecifies database file." << endl
		<< "\t/Nnumber\tSpecifies account number." << endl
		<< "\t/Ppassword\tSpecifies account password." << endl;

}

// ============== DataBase Management ======================

/* -----------------------------------------------------------------------------
FUNCTION:          database()
DESCRIPTION:       Holds the vector of accounts in static variable.
RETURNS:           Database vector reference
----------------------------------------------------------------------------- */

vector<Account*> & database(){
	static vector<Account*> accounts;
	return accounts;
}
/* -----------------------------------------------------------------------------
FUNCTION:          database_load( char * db_file_name )
DESCRIPTION:       Populates database vector from a file.
ARGUMENTS:         db_file_name: The filename of database file.
RETURNS:           Void function
----------------------------------------------------------------------------- */
void database_load(char * db_file_name){
	database().clear();

	std::ifstream db_file(db_file_name);

	if (db_file.is_open()){
		while (!db_file.eof()){
			Account * tmp_account = new Account();
			db_file >> *tmp_account;
			if (tmp_account->is_valid())
				database().push_back(tmp_account);
			else
				delete tmp_account;
		}
		db_file.close();
	}else{
		printf("Unable to load database from %s!\n", db_file_name);
		db_file.close();
		exit(1);
	}

}

/* -----------------------------------------------------------------------------
FUNCTION:          database_save( char * db_file_name )
DESCRIPTION:       Stores database vector to a file.
ARGUMENTS:         db_file_name: The filename of database file.
RETURNS:           Void function
----------------------------------------------------------------------------- */
void database_save(char * db_file_name) {
	std::ofstream db_file(db_file_name);
	if (!db_file.is_open()){
		printf("Unable to save database to %s!\n", db_file_name);
		db_file.close();
		exit(1);
	}

	for (Account* const& account : database())
		db_file << *account;

	db_file.close();
}

/* -----------------------------------------------------------------------------
FUNCTION:          database_find( char * account_number, struct Account ** account )
DESCRIPTION:       Searches the database array by given account_number, once
                   found, updates the Account pointer.
ARGUMENTS:         account_number: Account number to search for.
                   account: The pointer of Account pointer variable.
RETURNS:           Returns true if the account was found.
----------------------------------------------------------------------------- */
bool database_find(char * account_number, Account ** account){
	for (Account* const& acc : database()){
		if (strcmp(acc->account_number, account_number) == 0){
			*account = acc;
			return true;
		}
	}
	*account = NULL;
	return false;
}
/* -----------------------------------------------------------------------------
FUNCTION:          database_report(  char * report_file_name )
DESCRIPTION:       Writes database report to specified file.
ARGUMENTS:         report_file_name: the name of a report file
RETURNS:           Returns true if file was written.
----------------------------------------------------------------------------- */
bool database_report(char * report_file_name){
	std::ofstream report_file(report_file_name);
	if (!report_file.is_open())
		return false;

	report_file
		<< "-------    ----        -----     --    ---------    ------------    -------" << std::endl
		<< "Account    Last        First     MI    SS           Phone           Account" << std::endl
		<< "Number     Name        Name            Number       Number          Balance" << std::endl
		<< "-------    ----        -----     --    ---------    ------------    -------" << std::endl;

	for (Account* const& acc : database()){
		report_file << std::left
			<< std::setw(11) << acc->account_number
			<< std::setw(12) << acc->last_name
			<< std::setw(10) << acc->first_name
			<< std::setw(6) << (acc->middle_initial == 0 ? ' ' : acc->middle_initial)
			<< std::setw(13) << acc->social_securty_number
			<< std::setw(1) << "(" << std::setw(3) << acc->phone_area_code << std::setw(1) << ")" << std::setw(11) << acc->phone_number
			<< std::setw(11) << std::fixed << std::setprecision(2) << acc->account_balance
			<< std::endl;
	}
	report_file.close();
	return true;
}


// ==============  Validation ======================
/* -----------------------------------------------------------------------------
FUNCTION:          validate_file_name(  char * str )
DESCRIPTION:       Validates file name. (e.g. Report.txt)
ARGUMENTS:         str: the string to validate.
RETURNS:           Returns true if the name is valid.
----------------------------------------------------------------------------- */
bool validate_file_name(char * str) {
	/*int i = 0;
	for (; str[i] != 0; ++i)
	if (!isalnum(str[i]) && str[i] != '.' && str[i] != '_' && str[i] != '-')
		return false;
	return i >= 3;*/
	return str[0]!=0;
}

// ============== Helper Functions ======================
/* -----------------------------------------------------------------------------
FUNCTION:          str_sort( char * str )
DESCRIPTION:       Sorts the characters by ASCII in given c-string.
RETURNS:           Void function
----------------------------------------------------------------------------- */
void str_sort( char * str) {
	int i = 0;
	while (str[i] != 0 && str[i + 1] != 0){
		if (str[i] > str[i + 1]){
			char tmp = str[i];
			str[i] = str[i + 1];
			str[i + 1] = tmp;
			if (i>0)
				--i;
		}else
			++i;
	}
}
