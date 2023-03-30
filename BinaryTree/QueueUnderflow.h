#pragma once
#include <exception>
class QueueUnderflow : public std::exception
{
public:
	QueueUnderflow() : reason_("Queue Underflow") {}
	const char* what() const { return reason_; }
private:
	const char* reason_;
};

