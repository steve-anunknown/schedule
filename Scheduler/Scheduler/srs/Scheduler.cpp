/*
 * Scheduler.cpp
 *
 *  Created on: Mar 3, 2021
 *      Author: stefanos
 */
#include <iostream>

#include "../headers/day_elem_utilities.hpp"

int main(void)
{
	/*std::string day;
	std::cout<<"give day \n";
	std::cin>>day;
	unsigned int num_cour;
	std::cout<<"enter the amount of courses \n";
	std::cin>>num_cour;
	std::cout<<"enter the courses \n";
	day_elem courses[num_cour];
	std::cout<< courses[0].getName()<<'\n';
	school_day sch_day(day,nullptr);
	std::cout<< (sch_day.getHead() == nullptr);
	for (unsigned int i=0; i<num_cour; ++i)
	{
		std::cin>>courses[i];
		sch_day.addElem(courses[i].getName(),courses[i].getStart(),courses[i].getEnd());
	}
	std::cout<<"did i get that right? \n"<<sch_day;
	sch_day.remElem(courses[1].getName(),courses[1].getStart(),courses[1].getEnd());
	std::cout<<"what about now ? \n"<<sch_day;*/

	school_day sch_day;
	std::cin>>sch_day;
	std::cout<<"is this right? \n"<<sch_day;
	return 0;
}


