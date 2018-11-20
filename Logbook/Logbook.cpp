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

		//loop through the description
		for (int j = 0; j < desc.size(); j++)
		{
			int jobNumber = 0; //give misc tasks jobNumber 0
			std::string taskDesc;
			//if task has a job number
			if (desc[j].find("J1") == 0)
			{
				jobNumber = std::stoi(desc[j].substr(1, 4)); 	//grab the job number

				int descLoc;
				int descLoc1 = desc[j].find_first_of("–"); //look for the first "–" to see where description is
				int descLoc2 = desc[j].find_first_of("-"); //look for the first "-" to see where description is

				//handle inconsistencies
				if (descLoc1 < descLoc2)
				{
					descLoc = descLoc1;
				}
				else
				{
					descLoc = descLoc2;
				}
				taskDesc = desc[j].substr(descLoc + 1, desc[j].size());	//grab the description of the job + time
			}
			else
			{
				taskDesc = desc[j].substr(0, desc[j].size());	//grab the description of the job + time 
			}
			int timeLoc;	//variable to store the actual timeLoc
			int timeLoc1 = desc[j].find_last_of("–"); //look for the last "–" to see where time is
			int timeLoc2 = desc[j].find_last_of("-"); //look for the last "-" to see where time is too since there are some inconsistencies with the character used

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
			if (timeLoc != desc[j].size())
			{
				std::string time = desc[j].substr(timeLoc + 1, desc[j].size()); //create substring to search for the time

				if (time.find("HOUR") != std::string::npos)
				{
					std::string actualTime = time.substr(0, time.find("HOUR"));
					actualTime.erase(std::remove(actualTime.begin(),actualTime.end(),' '),actualTime.end());  //remove spaces from substring
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
					for (int ii = 0; ii < desc.size(); ii++)
					{
						int timeLoc = desc[ii].find_last_of("–");
						std::string time = desc[ii].substr(timeLoc + 1, desc[ii].size());

						if (time.find("hour") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("hour"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime += std::stod(actualTime);
						}

						else if (time.find("min") != std::string::npos)
						{
							std::string actualTime = time.substr(0, time.find("min"));
							actualTime.erase(std::remove(actualTime.begin(), actualTime.end(), ' '), actualTime.end());  //remove spaces from substring
							restOfTime += std::stod(actualTime) / 60;	//convert mins to hours
						}
					}

					//full day - time taken up by other tasks
					jobTime = 8 - restOfTime;
				}

				if (time.find("REST") != std::string::npos)
				{
					double restOfTime = 0; //initialise to 0

										   //loop through the other tasks in
					for (int ii = 0; ii < desc.size(); ii++)
					{
						int timeLoc = desc[ii].find_last_of("–");
						std::string time = desc[ii].substr(timeLoc + 1, desc[ii].size());
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
					newJobNumber = false;
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
				Jobs.push_back(newJob);	//add it to the vector
			}
			
		}
	}

	std::string fileOutPath;
	//ask for input
	std::cout << "Enter the filepath that you would like to create the new file at in .txt format (e.g. C:'\'Users\Olivia\Documents\logbook.txt): " << std::endl;
	//use input as filepath
	std::cin >> fileOutPath;

	std::ofstream out(fileOutPath);

	//write to another file in the format we want
	for (int i = 0; i < Jobs.size(); i++)
	{
		if (Jobs[i].getjobNumber() == 0)
		{
			out << "Misc Tasks" << ":" << "\n";
		}
		else
		{
			out << "J" << Jobs[i].jobNumber << ":" << "\n";
		}

		for (int j = 0; j < Jobs[i].tasks.size(); j++)
		{
			out << Jobs[i].tasks[j] << "\n";
		}

		out << "Total time on job: " << Jobs[i].time << " hours" << "\n" << "\n";
	}


    return 0;
}

