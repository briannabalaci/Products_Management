#pragma once
#include <string.h>
#include <string>
using std::string;
class POSError {
	string msg;
public:
	POSError(string m) :msg(m) {

	}
	const string& getMessage() const {
		return msg;
	}
};
