// Logbook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	//declare ifstream to store file
	std::ifstream file;
	std::string filepath;
	//ask for input
	std::cout << "Enter the filepath (in .txt format): " << std::endl;
	//use input as filepath
	std::cin >> filepath;

	//open file
	file.open(filepath);

	//if invalid filepath, loop through again
	while(file.fail())
	{
		std::cout << "The file at location " << filepath << " failed to open" << std::endl;
		std::cout << "Please enter the location of the file: " <<std::endl;
		std::cin >> filepath;
		file.open(filepath);
	}
	std::vector<std::string> eachLine;

	//for every line
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			// don't read empty lines
			continue;
		}
		//store in vector of strings
		eachLine.push_back(line);
	}
	file.close();

	//create vector of entries
	std::vector<Entry> Logs;

	for (int i = 0; i < eachLine.size(); i++)
	{
		//if is a new entry determined by "Day *number*" at the beginning of a line
		if (eachLine[i].find("Day") == 0)
		{
			//Create substring for the numbers after "Day " and convert to int - Note: this will not account for numbers if they go to 4 digits here
			int dayNumber = std::stoi(eachLine[i].substr(4, 3));

			std::vector<std::string> description; //create vector for description of entries
			bool nextDayFound = false; //check to see if we've found the next entry

			while (nextDayFound == false)
			{
				//we get to the end of the file here so need to safeguard against going out of range of the subscript (-1 because size returns the actual number of elements)
				if (i == eachLine.size() - 1)
				{
					nextDayFound = true;
				}
				else
				{
					//increment i to check where the next "Day" is
					i++;
				}

				//check for "Day"
				if (eachLine[i].find("Day") == 0)
				{
					nextDayFound = true;
					//ensure we start from the next day otherwise the loop will miss the "Day" we have just found
					i--;
				}	
				if (nextDayFound == false)
				{
					//add line of the entry to the string vector
					description.push_back(eachLine[i]);
				}

			}
			Entry e(dayNumber, description);
			Logs.push_back(e); //store each entry into vector of entries

		}
	}

	//create vector of jobs
	std::vector<Job> Jobs;

	//loop through each entry
	for (int i = 0; i < Logs.size(); i++)
	{
		const int day = Logs[i].getdayNumber();
		const std::vector<std::string> desc = Logs[i].getDescription();

		//loop through the descrption
		for (int j = 0; j < desc.size(); j++)
		{
			//if task has a job number
			if (desc[j].find("J1") == 0)
			{
				int jobNumber = std::stoi(desc[j].substr(1, 4)); 	//grab the job number
				std::string taskDesc = desc[j].substr(desc[j].find_first_of("–"), desc[j].size() - 1);	//grab the description of the job + time

				int timeLoc = desc[j].find_last_of("–"); //look for the last "–" to see where time is
				double jobTime;

				if (timeLoc != desc[j].size())
				{
					std::string time = desc[j].substr(timeLoc + 1, desc[j].size());

					if (time.find("hour") != std::string::npos)
					{
						//TODO grab jobTime somehow
					}

					if (time.find("min") != std::string::npos)
					{
						//TODO grab jobTime somehow
					}

					if (time.find("all day") != std::string::npos)
					{
						//TODO grab jobTime somehow
					}

					if (time.find("rest") != std::string::npos)
					{
						//TODO grab jobTime somehow
					}
				}

				bool newJobNumber = true;
				int jobElement;

				//loop through our vector of jobs
				for (int k = 0; k < Jobs.size(); k++)
				{				
					//currentJobnumber is a job number we already have
					int currentJobNumber = Jobs[k].getjobNumber();

					//check if the job already exists
					if (currentJobNumber == jobNumber)
					{
						jobElement = k;
						bool newJobNumber = false;
					}
				}

				if (newJobNumber == false)
				{
					Jobs[jobElement].tasks.push_back(taskDesc); //add the task to the list of tasks for that job
					Jobs[jobElement].time += jobTime;			//add the time to the total job time
				}
				else
				{
					//create a new job object
					std::vector<std::string> tasks;
					tasks.push_back(taskDesc);
					Job newJob(jobNumber, tasks, jobTime);
					Jobs.push_back(newJob);
				}
				
	
			}
		}
	}
	//manipulate entries

	//write to another file in the format we want

    return 0;
}

