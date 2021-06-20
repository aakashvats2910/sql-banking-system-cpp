#pragma once
#include <iostream>
#include <string>

using namespace std;

 namespace LOG {
	 class Log {
	 public:
		 static void logSuccess(string txt) {
			 cout << "[SUCCESS] " << txt << "\n";
		 }

		 static void logError(string txt) {
			 cout << "[ERROR] " << txt << '\n';
		 }

		 static void logInfo(string txt) {
			 cout << "[INFO] " << txt << '\n';
		 }
	 };
}