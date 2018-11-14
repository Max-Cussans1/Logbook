#pragma once
#include <string>
#include <vector>

class Entry
{
private:
	const std::vector<std::string> description;
	const int dayNumber;

public:
	Entry(int dayNumber, std::vector<std::string> description);
	const int getdayNumber() { return dayNumber; };
	~Entry();
};

