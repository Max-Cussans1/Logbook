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

	//store each entry into vector of entries
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
			Logs.push_back(e);

		}
	}


	//create entry from entry read in 


	//store entries in vector of Entries

	//manipulate entries

	//write to another file in the format we want

    return 0;
}

