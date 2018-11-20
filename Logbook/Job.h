#pragma once
#include <string>
#include <vector>

class Job
{
public:
	std::vector<std::string> tasks;
	double time;
	const int jobNumber;

	Job(int jobNumber, std::vector<std::string> tasks, double time);
	const int getjobNumber() { return jobNumber; };
	~Job();
};

