#pragma once
#include <exception>
#include <string>

class WrongStackSize : public std::exception
{
public:
	WrongStackSize() : reason_("Wrong Stack Size") {}
	const char* what() const { return reason_.c_str(); }
private:
	const std::string& reason_; // ! const
};

