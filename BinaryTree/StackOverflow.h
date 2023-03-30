#pragma once
#include <exception>
#include <string>

class StackOverflow : public std::exception
{
public:
	StackOverflow() : reason_("Stack Overflow") {}
	const char* what() const { return reason_.c_str(); }

private:
	const std::string& reason_;

};


