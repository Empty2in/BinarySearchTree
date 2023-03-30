#pragma once
#include <string>
class StackException {
public:
	StackException(const std::string&) : message_() {};
	std::string getMessage() const { return message_; }
private:
	std::string message_;
};
