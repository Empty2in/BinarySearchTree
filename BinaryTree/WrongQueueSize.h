#pragma once
#include <exception>

class WrongQueueSize : public std::exception
{
public:
	WrongQueueSize() : reason_("Wrong Queue Size") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};


