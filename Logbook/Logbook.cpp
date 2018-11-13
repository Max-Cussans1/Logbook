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

	//for every line
	for (std::string line; getline(file, line); )
	{
		
	}
	//read in file


	//create entry from entry read in 
	//Entry e;


	//store entries in vector of Entries

	//manipulate entries

	//write to another file in the format we want

    return 0;
}

