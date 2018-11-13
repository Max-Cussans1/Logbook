#pragma once
#include <string>

class Entry
{
private:
	const std::string description;
	const int dayNumber;

public:
	Entry(int dayNumber, std::string description);
	const int getdayNumber() { return dayNumber; };
	~Entry();
};

