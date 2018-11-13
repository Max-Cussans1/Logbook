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

	for (auto i : eachLine.size)
	{
		//if is a new entry determined by "Day *number*" at the beginning of a line
		if (eachLine[i].find("Day") = 0)
		{
			//Create substring for the numbers after "Day " and cast to int - Note: this will not account for numbers if they go to 4 digits here
			int dayNumber = static_cast<int>(eachLine[i].substr(4, 3));
			std::string description = eachLine[i];
		}
	}


	//create entry from entry read in 
	//Entry e;


	//store entries in vector of Entries

	//manipulate entries

	//write to another file in the format we want

    return 0;
}

