#pragma once
#include <string>


namespace LOG {
	class Log {
	public:
		static void logSuccess(std::string txt);
		static void logError(std::string txt);
	};
}