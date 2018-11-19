#pragma once
#include <string>
#include <vector>

class Job
{
private:
	const int jobNumber;

public:
	std::vector<std::string> tasks;
	double time;

	Job(int jobNumber, std::vector<std::string> tasks, double time);
	const int getjobNumber() { return jobNumber; };
	~Job();
};

