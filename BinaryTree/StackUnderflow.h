#pragma once
#include <exception>
#include <string>

class StackUnderflow : public std::exception 
{
public:
	StackUnderflow() : reason_("Stack Underflow") {}
	const char* what() const { return reason_.c_str(); }

private:
	const std::string& reason_;
};