#pragma once
#include <string>
#include <vector>

class Entry
{
private:
	const int jobNumber;
	const std::string description;
	const double timeSpent;
	const int dayNumber;

public:
	Entry(int jobNumber, std::string description, double timeSpent, int dayNumber);
	const int getJobNumber() { return jobNumber; }
	const double gettimeSpent() { return timeSpent; };
	const int getdayNumber() { return dayNumber; };
	~Entry();
};

