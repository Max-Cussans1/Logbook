#include "stdafx.h"
#include "Job.h"


Job::Job(int jobNumber, std::vector<std::string> tasks, double time) : jobNumber(jobNumber), tasks(tasks), time(time)
{
}

Job Job::Split(std::string JOB_TO_SPLIT, int desiredJobNumber)
{
	std::vector<std::string> desiredTasks;
	double newTime = 0;
	Job splitJob = Job(desiredJobNumber, desiredTasks, newTime);


	for (int i = 0; i < tasks.size(); i++)
	{

		if (tasks[i].find(JOB_TO_SPLIT) != std::string::npos)
		{

			int timeLoc;	//variable to store the actual timeLoc
			int timeLoc1 = tasks[i].find_last_of("–"); //look for the last "–" to see where time is
			int timeLoc2 = tasks[i].find_last_of("-"); //look for the last "-" to see where time is too since there are some inconsistencies with the character used

			//which is found latest we will use to find the time
			if (timeLoc1 > timeLoc2)
			{
				timeLoc = timeLoc1;
			}
			else
			{
				timeLoc = timeLoc2;
			}


			double jobTime = 0;

			//check if we're not at the end of the string
			if (timeLoc != tasks[i].size())
			{
				std::string time = tasks[i].substr(timeLoc + 1, tasks[i].size()); //create substring to search for the time

				if (time.find("HOUR") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("HOUR"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime);
				}


				if (time.find("Hour") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("Hour"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime);
				}

				if (time.find("hour") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("hour"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime);
				}

				if (time.find("MIN") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("MIN"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime) / 60;
				}

				if (time.find("Min") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("min"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime) / 60;
				}

				if (time.find("min") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("min"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime) / 60;
				}

				if (time.find("all day") != std::string::npos)
				{
					jobTime = 8;	//a full day = 8 hours
				}

				if (time.find("ALL DAY") != std::string::npos)
				{
					jobTime = 8;	//a full day = 8 hours
				}

				if (time.find("rest") != std::string::npos)
				{
					double restOfTime = 0; //initialise to 0

										   //loop through the other tasks in
					for (int ii = 0; ii < tasks.size(); ii++)
					{
						int timeLoc = tasks[ii].find_last_of("–");
						std::string time = tasks[ii].substr(timeLoc + 1, tasks[ii].size());
						restOfTime = 0;	//in case we don't hit the conditions and we're reading no time

						if (time.find("hour") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("hour"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("Hour") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("Hour"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("HOUR") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("HOUR"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("min") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						if (time.find("Min") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						if (time.find("MIN") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						//add the rest of the time up
						restOfTime += restOfTime;
					}

					//full day - time taken up by other tasks
					jobTime = 8 - restOfTime;
				}

				if (time.find("REST") != std::string::npos)
				{
					double restOfTime = 0; //initialise to 0

										   //loop through the other tasks in
					for (int ii = 0; ii < tasks.size(); ii++)
					{
						int timeLoc = tasks[ii].find_last_of("–");
						std::string time = tasks[ii].substr(timeLoc + 1, tasks[ii].size());
						restOfTime = 0;	//in case we don't hit the conditions and we're reading no time

						if (time.find("hour") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("hour"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("Hour") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("Hour"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("HOUR") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("HOUR"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("min") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						if (time.find("Min") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						if (time.find("MIN") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						//add the rest of the time up
						restOfTime += restOfTime;
					}

					//full day - time taken up by other tasks
					jobTime = 8 - restOfTime;
				}
			}

			splitJob.time += jobTime;
			splitJob.tasks.push_back(tasks[i]);
			//delete the entry we have split off

			for (int j = i; j < tasks.size() - 1; j++)
			{
				tasks[j] = tasks[j + 1];
			}
			tasks.pop_back();
			
		}

	}

	return splitJob;
}

Job Job::Split(std::string JOB_TO_SPLIT, std::string JOB_TO_SPLIT_2, int desiredJobNumber)
{
	std::vector<std::string> desiredTasks;
	double newTime = 0;
	Job splitJob = Job(desiredJobNumber, desiredTasks, newTime);


	for (int i = 0; i < tasks.size(); i++)
	{

		if (tasks[i].find(JOB_TO_SPLIT) != std::string::npos || tasks[i].find(JOB_TO_SPLIT_2) != std::string::npos)
		{

			int timeLoc;	//variable to store the actual timeLoc
			int timeLoc1 = tasks[i].find_last_of("–"); //look for the last "–" to see where time is
			int timeLoc2 = tasks[i].find_last_of("-"); //look for the last "-" to see where time is too since there are some inconsistencies with the character used

			//which is found latest we will use to find the time
			if (timeLoc1 > timeLoc2)
			{
				timeLoc = timeLoc1;
			}
			else
			{
				timeLoc = timeLoc2;
			}


			double jobTime = 0;

			//check if we're not at the end of the string
			if (timeLoc != tasks[i].size())
			{
				std::string time = tasks[i].substr(timeLoc + 1, tasks[i].size()); //create substring to search for the time

				if (time.find("HOUR") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("HOUR"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime);
				}


				if (time.find("Hour") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("Hour"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime);
				}

				if (time.find("hour") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("hour"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime);
				}

				if (time.find("MIN") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("MIN"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime) / 60;
				}

				if (time.find("Min") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("min"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime) / 60;
				}

				if (time.find("min") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("min"));
					actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
					jobTime = std::stod(actualTime) / 60;
				}

				if (time.find("all day") != std::string::npos)
				{
					jobTime = 8;	//a full day = 8 hours
				}

				if (time.find("ALL DAY") != std::string::npos)
				{
					jobTime = 8;	//a full day = 8 hours
				}

				if (time.find("rest") != std::string::npos)
				{
					double restOfTime = 0; //initialise to 0

										   //loop through the other tasks in
					for (int ii = 0; ii < tasks.size(); ii++)
					{
						int timeLoc = tasks[ii].find_last_of("–");
						std::string time = tasks[ii].substr(timeLoc + 1, tasks[ii].size());
						restOfTime = 0;	//in case we don't hit the conditions and we're reading no time

						if (time.find("hour") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("hour"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("Hour") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("Hour"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("HOUR") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("HOUR"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("min") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						if (time.find("Min") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						if (time.find("MIN") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						//add the rest of the time up
						restOfTime += restOfTime;
					}

					//full day - time taken up by other tasks
					jobTime = 8 - restOfTime;
				}

				if (time.find("REST") != std::string::npos)
				{
					double restOfTime = 0; //initialise to 0

										   //loop through the other tasks in
					for (int ii = 0; ii < tasks.size(); ii++)
					{
						int timeLoc = tasks[ii].find_last_of("–");
						std::string time = tasks[ii].substr(timeLoc + 1, tasks[ii].size());
						restOfTime = 0;	//in case we don't hit the conditions and we're reading no time

						if (time.find("hour") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("hour"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("Hour") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("Hour"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("HOUR") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("HOUR"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime);
						}

						if (time.find("min") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						if (time.find("Min") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						if (time.find("MIN") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime = std::stod(actualTime) / 60;	//convert mins to hours
						}

						//add the rest of the time up
						restOfTime += restOfTime;
					}

					//full day - time taken up by other tasks
					jobTime = 8 - restOfTime;
				}
			}

			splitJob.time += jobTime;
			splitJob.tasks.push_back(tasks[i]);
			//delete the entry we have split off
			
			for (int j = i; j < tasks.size() - 1; j++)
			{
				tasks[j] = tasks[j + 1];
			}
			tasks.pop_back();

		}

	}

	return splitJob;
}

Job::~Job()
{
}
