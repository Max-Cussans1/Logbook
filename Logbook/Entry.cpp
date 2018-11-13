#include "stdafx.h"
#include "Entry.h"


Entry::Entry(int jobNumber,std::string description,double timeSpent,int dayNumber): jobNumber(jobNumber), description(description), timeSpent(timeSpent), dayNumber(dayNumber)
{
}

Entry::~Entry()
{
}
