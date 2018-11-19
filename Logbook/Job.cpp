#include "stdafx.h"
#include "Job.h"


Job::Job(int jobNumber, std::vector<std::string> tasks, double time) : jobNumber(jobNumber), tasks(tasks), time(time)
{
}


Job::~Job()
{
}
