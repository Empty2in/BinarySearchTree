#pragma once
#include <exception>

class QueueOverflow : public std::exception 
{
public:
	QueueOverflow() : reason_("Queue Overflow") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

