#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

#include "db_header.h"
#include "Log.cpp"
#include "user.cpp"
#include "dbfunc.cpp"

using namespace std;

int main() {

	int g = 10;

	cout << "Welcome to ABC_Banking software";

	while (true) {

		cout << "Choose the task you want to do\n";
		cout << " 1. Create new user\n";
		cout << " 2. Login as existing user\n";
		cout << " 3. Exit application\n";

		cout << "\n Enter the operation >> ";

		string ans;
		getline(cin, ans);

		if (ans.size() >= 1) {
			if (ans[0] == '1') {
				// ask for username and password and reiterate the loop
				string username;
				cout << "Enter username >> ";
				getline(cin, username);

				// check if the username already exists or not.
				if (DB_Func::username_exists(username)) {
					LOG::Log::logError("Username already exists - Restarting");
					continue;
				}

				string password;
				cout << "Enter password >> ";
				getline(cin, password);

				string name;
				cout << "Enter name >> ";
				getline(cin, name);

				string age;
				cout << "Enter age >> ";
				getline(cin, age);

				string gender;
				cout << "Enter your gender(m/f) >> ";
				getline(cin, gender);

				cout << "\n";

				int latest = DB_Func::getLatestAccNo();
				User::Customer c(name , stoi(age), gender, username, password, 1000, latest+1);
				DB_Func::addCustomerToDBv2(c);

				continue;
			}
			else if (ans[0] == '2') {
				// ask for entering the login details
				// take the login credentials.
				cout << "Enter the login details to continue \n";
				string username;
				cout << "Enter username >> ";
				getline(cin, username);
				string password;
				cout << "Enter password >> ";
				getline(cin, password);

				// check the login credentials
				// if wrong then show wrong message and re-iterates the loop.
				if (!DB_Func::isAuthValid(username, password)) {
					LOG::Log::logError("Invalid username or password - Restarting");
					continue;
				}

				// if the login auths are correct then show them the message to do operations in db.
				LOG::Log::logSuccess("Login done successfully");

				cout << "Choose the operation\n";
				cout << " 1. See your bank balance\n";
				cout << " 2. Change password\n";
				cout << " 3. Transfer money to another account.\n";

				string ans_inside;
				getline(cin, ans_inside);
				if (ans_inside.empty()) {
					LOG::Log::logError("Invalid input - Restarting");
					continue;
				}
				else if (ans_inside[0] == '1') {
					LOG::Log::logInfo("Your accout balance >> " + to_string(DB_Func::getBalance(username)));
					continue;
				}
				else if (ans_inside[0] == '2') {
					string new_passwd;
					cout << "Enter new password >> ";
					getline(cin, new_passwd);
					if (new_passwd.size() >= 1) {
						// set the new password;
						DB_Func::setNewPasswd(username, new_passwd);
					}
				}
				else if (ans_inside[0] == '3') {
					string money;
					cout << "Enter the amount to transfer >> ";
					getline(cin, money);
					string to_accno;
					cout << "Enter the account number to transfer >> ";
					getline(cin, to_accno);
					DB_Func::transferMoney(username, stoi(money),stoi(to_accno));
				}
				else {
					LOG::Log::logError("Invalid input - Restarting");
				}
			}
		}
		else if (ans[0] == '3') {
			// exit the application.	
			LOG::Log::logInfo("Thank you for visting.");
		} 
		else {
			LOG::Log::logError("Invalid input - Restarting");
		}
	}

	return 0;
}