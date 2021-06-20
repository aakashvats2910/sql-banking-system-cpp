#pragma once
#include <string>
#include "Log.cpp"
#include "user.cpp"
#include "db_header.h"

class DB_Func {
public:
	static sql::Connection* initialize() {
		sql::Driver* driver;
		sql::Connection* con;
		sql::ResultSet* res;
		sql::Statement* stmt;
		
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "PASSWORD_HERE");
		stmt = con->createStatement();
		stmt->execute("use banking");

		return con;
	}

	static void addCustomerToDBv2(User::Customer c) {
		sql::ResultSet* res;
		sql::Statement* stmt;
		sql::Connection* con;
		con = initialize();
		stmt = con->createStatement();
		stmt->execute("use banking");

		stmt->execute("insert into details values("
			+ string("'") + c.getName() + "',"
			+ "'" + std::to_string(c.getAge()) + "',"
			+ "'" + c.getGender() + "',"
			+ "'" + c.getUsername() + "',"
			+ "'" + c.getPassword() + "',"
			+ "'" + std::to_string(c.getMoney()) + "',"
			+ "'" + std::to_string(c.getAccno()) + "')"
		);

		LOG::Log::logInfo("1000 amount auto initialized into your account");
		LOG::Log::logInfo("Your account number: ");

		LOG::Log::logSuccess("User created successfully - Log in again");
	}

	static void addCustomerToDB(User::Customer c) {
		sql::Driver* driver;
		sql::Connection* con;
		sql::ResultSet* res;
		sql::Statement* stmt;
		driver = get_driver_instance();
		con = driver->connect("tcp://127.0.0.1:3306", "root", "A@kash2910");
		stmt = con->createStatement();
		stmt->execute("use banking");

		stmt->execute("insert into details values("
			+ string("'") + c.getName() + "',"
			+ "'" + std::to_string(c.getAge()) + "',"
			+ "'" + c.getGender() + "',"
			+ "'" + c.getUsername() + "',"
			+ "'" + c.getPassword() + "',"
			+ "'" + std::to_string(c.getMoney()) + "',"
			+ "'" + std::to_string(c.getAccno()) + "')"
		);

		LOG::Log::logInfo("1000 amount auto initialized into your account");
		LOG::Log::logInfo("Your account number: ");

		LOG::Log::logSuccess("User created successfully - Log in again");
	}

	static int getLatestAccNo() {
		sql::Connection* con;
		sql::ResultSet* res;
		sql::Statement* stmt;

		con = initialize();
		stmt = con->createStatement();
		stmt->execute("use banking");

		// get the latest account number
		stmt->execute("use banking");
		res = stmt->executeQuery("select * from accno");
		int val;
		while (res->next()) {
			val = res->getInt("num");
			break;
		}

		// update the value by 1.
		stmt->executeUpdate("update accno set num=" + std::to_string(val+1));
		return val;
	}

	static bool username_exists(string username) {
		sql::Driver* driver;
		sql::Connection* con;
		sql::ResultSet* res;
		sql::Statement* stmt;

		con = initialize();
		stmt = con->createStatement();
		stmt->execute("use banking");

		// check if the username exists or not;
		res = stmt->executeQuery("select * from details where username='" + username + "'");
		while (res->next()) {
			return true;
		}
		return false;
		
	}

	static bool isAuthValid(string username, string password) {
		sql::Driver* driver;
		sql::Connection* con;
		sql::ResultSet* res;
		sql::Statement* stmt;

		con = initialize();
		stmt = con->createStatement();
		stmt->execute("use banking");

		// check if the username exists or not;
		if (username_exists(username)) {
			res = stmt->executeQuery("select * from details where username='" + username + "'");
			while (res->next()) {
				string db_password = res->getString("password");
				if (password == db_password) {
					return true;
				}
				else {
					return false;
				}
			}
		}
		else {
			return false;
		}
	}

	static int getBalance(string username) {
		sql::Driver* driver;
		sql::Connection* con;
		sql::ResultSet* res;
		sql::Statement* stmt;

		con = initialize();
		stmt = con->createStatement();
		stmt->execute("use banking");

		// get the bank balance;
		res = stmt->executeQuery("select * from details where username='" + username + "'");
		while (res->next()) {
			return res->getInt("money");
		}
	}

	static void setNewPasswd(string username, string new_passwd) {
		sql::Driver* driver;
		sql::Connection* con;
		sql::ResultSet* res;
		sql::Statement* stmt;

		con = initialize();
		stmt = con->createStatement();
		stmt->execute("use banking");

		// change password;
		stmt->execute("update details set password='" + new_passwd + "' where username='" + username + "'");
		LOG::Log::logSuccess("Password changed successfully");
	}

	static void transferMoney(string username, int amount_to_tf, int to_accno) {
		sql::Driver* driver;
		sql::Connection* con;
		sql::ResultSet* res;
		sql::Statement* stmt;

		con = initialize();
		stmt = con->createStatement();
		stmt->execute("use banking");

		// check if the user have available balance to tranfer;
		int amt = getBalance(username);

		//cout << "\nAMOUNT AMOUNT :: " << amt << '\n';
		cout << "\nTRANSFER TRANSFER :: " << amount_to_tf << '\n';

		if (amount_to_tf > amt) {
			LOG::Log::logError("Balance in your account less than transfer money");
			return;
		}

		bool accno_exists;
		// check if the other account with that number exists;
		cout << "TO ACCNO : " << to_accno;
		res = stmt->executeQuery("select accno from details where accno=" + to_string(to_accno));
		while (res->next()) {
			int tmpaccno = res->getInt("accno");
			if (tmpaccno == to_accno) {
				accno_exists = true;
				break;
			}
		}

		if (!accno_exists) {
			LOG::Log::logError("Seems like you enter invalid account number.");
			return;
		}

		//finally transfer the amount to 
		// cut from senders account
		stmt->executeUpdate("update details set money=money-" + to_string(amount_to_tf) + " where username='" + username + "'");
		// update the cutted amount in receivers balance;
		stmt->executeUpdate("update details set money=money+" + to_string(amount_to_tf) + " where accno=" + to_string(to_accno));
	}
};