/*
 * day_elem_utilities.cpp
 *
 *  Created on: Mar 4, 2021
 *      Author: stefanos
 */
#include "../headers/day_elem_utilities.hpp"

cl_time::cl_time(): hours(0) , minutes(0) {}
cl_time::cl_time(unsigned int const& hours , unsigned int const& minutes): hours(hours) , minutes(minutes) {}
cl_time& cl_time::operator = (cl_time const& timeobj)
{
	this->hours = timeobj.hours;
	this->minutes = timeobj.minutes;
	return *this;
}

unsigned int cl_time::getHours(void) const { return this->hours; }
unsigned int cl_time::getMins(void) const { return this->minutes; }

bool cl_time::setHours(unsigned int const& _hours)
{
	if (_hours>=0 && _hours<24)
	{
		this->hours=_hours;
		return true;
	}
	else
		return false;
}

bool cl_time::setMins(unsigned int const& _minutes)
{
	if (_minutes>=0 && _minutes<60)
	{
		this->minutes = _minutes;
		return true;
	}
	else
		return false;
}

std::istream& operator >> (std::istream &in , cl_time &time)
{
	unsigned int _hours;
	unsigned int _minutes;
	//char column;
	in>>_hours>>_minutes;
	time.setHours(_hours);
	time.setMins(_minutes);
	return in;
}
std::ostream& operator << (std::ostream &out , cl_time const& timeobj)
{
	out<<timeobj.getHours()<<':';
	if (timeobj.getMins()<10)
		out<<'0'<<timeobj.getMins();
	else
		out<<timeobj.getMins();
	return out;
}

day_elem::day_elem(): name("UNNAMED day_elem"), next_day_elem(nullptr) {}
day_elem::day_elem(std::string const& name , cl_time begin , cl_time finish, day_elem* next)
	: name(name) , start_time(begin) , end_time(finish) , next_day_elem(next) {}
day_elem& day_elem::operator = (day_elem const& day_elemobj)
{
	this->name = day_elemobj.name;
	this->start_time = day_elemobj.start_time;
	this->end_time = day_elemobj.end_time;
	this->next_day_elem = day_elemobj.next_day_elem;
	return *this;
}

std::string day_elem::getName(void) const { return this->name; }
cl_time day_elem::getStart(void) const { return this->start_time; }
cl_time day_elem::getEnd(void) const { return this->end_time; }
day_elem* day_elem::getNextElem(void) const { return this->next_day_elem; }

bool operator == (cl_time const& a_time, cl_time const& b_time) { return (a_time.hours==b_time.hours && a_time.minutes==b_time.minutes) ; }
bool operator != (cl_time const& a_time, cl_time const& b_time) { return !(a_time==b_time); }
bool operator < (cl_time const& a_time, cl_time const& b_time) { return (a_time.hours<b_time.hours || (a_time.hours==b_time.hours && a_time.minutes<b_time.minutes)); }
bool operator > (cl_time const& a_time, cl_time const& b_time) { return (a_time.hours>b_time.hours || (a_time.hours==b_time.hours && a_time.minutes>b_time.minutes)); }
bool operator <= (cl_time const& a_time, cl_time const& b_time) { return !(a_time>b_time); }
bool operator >= (cl_time const& a_time, cl_time const& b_time) { return !(a_time<b_time); }


bool day_elem::setName(std::string const& day_elem_name)
{
	this->name = day_elem_name;
	return true;
}
bool day_elem::setStart(cl_time const& s_time)
{
	this->start_time=s_time;
	return true;
}
bool day_elem::setEnd(cl_time const& e_time)
{
	this->end_time = e_time;
	return true;
}
bool day_elem::setNextElem (day_elem *n_day_elem)
{
	this->next_day_elem = n_day_elem;
	return true;
}

std::istream& operator >> (std::istream &in , day_elem &day_elemobj)
{
	std::string c_name;
	cl_time s_time,e_time;
	std::cout<<"Give course name \n";
	std::cin.ignore();
	std::getline(in,c_name);
	std::cout<<"Give course times \n";
	in>>s_time>>e_time;
	day_elemobj.setName(c_name);
	day_elemobj.setStart(s_time);
	day_elemobj.setEnd(e_time);
	return in;
}
std::ostream& operator << (std::ostream &out, day_elem &day_elemobj)
{
	out<<day_elemobj.getName()<<'\n'<<day_elemobj.getStart()<<'-'<<day_elemobj.getEnd()<<std::endl;
	return out;
}



school_day::school_day(): dname("UNNAMED SCHOOL DAY") , lhead(nullptr) {}
school_day::school_day(std::string const& name): dname(name) , lhead(nullptr) {}
school_day::school_day(std::string const& name , day_elem *head): dname(name) , lhead(head) {}
school_day::~school_day()
{
	if (!lhead) return;
	day_elem *temp = lhead->getNextElem();
	while (temp)
	{
		delete lhead;
		lhead = temp;
		temp = lhead->getNextElem();
	}
}

std::string school_day::getDay(void) const { return this->dname; }
day_elem* school_day::getHead(void) const { return this->lhead; }

bool school_day::setDay(std::string const& name)
{
	this->dname = name ;
	return true;
}
bool school_day::setHead(day_elem *head)
{
	this->lhead = head ;
	return true;
}
bool school_day::addElem(std::string const& el_name , cl_time const& s_time, cl_time const& e_time )
{
	if (!this->lhead)
	{
		this->lhead = new day_elem (el_name , s_time , e_time, nullptr);
		return true;
	}
	else
	{
		day_elem *temp = this->lhead;
		day_elem *prev = temp;
		while (temp && temp->getStart()<s_time)
		{
			prev = temp;
			temp = temp->getNextElem();
		}
		if (temp==this->lhead)
		{
			this->lhead = new day_elem (el_name , s_time , e_time , this->lhead);
			return true;
		}
		else
		{
			day_elem *new_elem = new day_elem (el_name , s_time , e_time , temp);
			prev->setNextElem(new_elem);
			return true;
		}
	}
	return false;
}
			
bool school_day::remElem(std::string const& el_name , cl_time const& s_time, cl_time const& e_time)
{
	if (!this->lhead) return true;
	day_elem *temp = this->lhead;
	day_elem *prev = temp;
	while (temp && temp->getName()!=el_name && temp->getStart()!=s_time && temp->getEnd()!=e_time)
	{
		prev = temp;
		temp = temp->getNextElem();
	}
	prev->setNextElem(temp->getNextElem());
	delete temp;
	return true;
}

std::istream& operator >> (std::istream &in , school_day &school_day)
{
	std::string day_name;
	std::cout<<"Enter the school day \n";
	std::cin>>day_name;
	school_day.setDay(day_name);
	unsigned int num_day_elems;
	std::cout<<"Enter the amount of day_elems \n";
	std::cin>>num_day_elems;
	day_elem *day_day_elems = new day_elem [num_day_elems];
	std::cout<<"Enter the day_elems \n";
	for (unsigned int i=0; i<num_day_elems; ++i)
	{
		std::cin>>day_day_elems[i];
	}
	return in;
}
std::ostream& operator << (std::ostream &out, school_day &school_day)
{
	day_elem *temp = school_day.getHead();
	out<<school_day.getDay()<<'\n';
	while (temp)
	{
		out<<*temp;
		temp=temp->getNextElem();
	}
	return out;
}




