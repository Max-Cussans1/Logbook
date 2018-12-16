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
	Job Split(std::string JOB_TO_SPLIT, int desiredJobNumber);
	Job Split(std::string JOB_TO_SPLIT, std::string JOB_TO_SPLIT_2, int desiredJobNumber);
	const int getjobNumber() { return jobNumber; };
	~Job();
};

