#pragma once
#include <string>

using namespace std;

namespace User {
	class Customer {
	private:
		int age;
		string name;
		string gender;
		string username;
		string password;
		int money;
		int accno;

	public:
		Customer(string name, int age, string gender, string username, string password, int money, int accno) {
			this->age = age;
			this->name = name;
			this->gender = gender;
			this->username = username;
			this->password = password;
			this->money = money;
			this->accno = accno;
		}

		int getAge() {
			return age;
		}

		string getName() {
			return name;
		}

		string getGender() {
			return gender;
		}

		string getUsername() {
			return username;
		}

		string getPassword() {
			return password;
		}

		int getMoney() {
			return money;
		}

		int getAccno() {
			return accno;
		}
	};
}