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


cal_date::cal_date(): cal_day(0) , cal_month(0) {}
cal_date::cal_date(unsigned int const& day, unsigned int const& month): cal_day(day) , cal_month (month) {}

bool cal_date::setCalDay(unsigned int const& day)
{
	this->cal_day = day;
	return true;
}
bool cal_date::setCalMonth (unsigned int const& month)
{
	this->cal_month = month;
	return true;
}

unsigned int cal_date::getCalDay() const { return this->cal_day ; }
unsigned int cal_date::getCalMonth() const { return this->cal_month ; }

std::ostream& operator << (std::ostream &out , cal_date const& dateobj)
{
	out<<dateobj.cal_day<<'/'<<dateobj.cal_month<<std::endl;
	return out;
}
std::istream& operator >> (std::istream &in , cal_date & dateobj)
{
	in>>dateobj.cal_day>>dateobj.cal_month;
	return in;
}

bool operator == (cal_date const& date_a , cal_date const& date_b) { return (date_a.cal_day==date_b.cal_day && date_a.cal_month==date_b.cal_month); }
bool operator != (cal_date const& date_a , cal_date const& date_b) { return !(date_a==date_b); }
bool operator < (cal_date const& date_a , cal_date const& date_b) { return (date_a.cal_month<date_b.cal_month || (date_a.cal_month==date_b.cal_month && date_a.cal_day < date_b.cal_day)); }
bool operator > (cal_date const& date_a , cal_date const& date_b) { return (date_a!=date_b && !(date_a<date_b)); }


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
	day_elem* temp = lhead;
	while (temp)
	{
		day_elem* next = temp->getNextElem();
		delete temp;
		temp = next;
	}
}

std::string school_day::getDay(void) const { return this->dname; }
day_elem* school_day::getHead(void) const { return this->lhead; }
school_day* school_day::getNextDay(void) const { return this->next_school_day; }

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

bool school_day::setNextDay(school_day* next_day)
{
	this->next_school_day = next_day;
	return false;
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
	std::cout<<"Enter the amount of courses \n";
	std::cin>>num_day_elems;
	std::cout<<"Enter the courses \n";
	for (unsigned int i=0; i<num_day_elems; ++i)
	{
		day_elem* course = new day_elem;
		std::cin>>*course;
		school_day.addElem(course->getName(),course->getStart(), course->getEnd());
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

week_program::week_program() : school_day(nullptr) {}

week_program::week_program(school_day* days): school_day(days) {}

week_program::week_program(week_program const& program) : school_day(program.getDays()) {}

week_program::~week_program()
{
	for (unsigned int i = 0; i < this->num_days; ++i)
		delete this->days[i];
}

school_day week_program::getSchoolDay(unsigned int const& index) const
{
	if (index > sizeof(days) / sizeof(school_day)) return school_day();
	else return this->days[index];
}

school_day week_program::getSchoolDay(std::string const& day_name) const
{
	school_day* temp = this->days;
	while (temp && temp->getDay()!=day_name)
	{
		temp = temp->getNextDay();
	}
	if (temp) return *temp;
	return school_day();
}

school_day* week_program::getSchoolDays() const
{
	return this->days;
}

bool week_program::addSchoolDay(school_day const& new_day)
{
	if (!days)
	{
		days = new school_day(new_day.getDay(), new_day.getHead(), new_day.getNextDay());
		return true;
	}
	else
	{
		school_day* temp = days;
		school_day* prev = temp;
		while (temp)
		{
			prev = temp;
			temp = temp->getNextDay();
		}
		school_day* new_sch_day = new school_day(new_day.getDay(), new_day.getHead(), new_day.getNextDay());
		prev->setNextDay(new_sch_day);
		return true;
	}
	return false;
}

bool week_program::remSchoolDay(school_day const& del_day)
{
	school_day* temp = this->days;
	school_day* prev = temp;
	while (temp && temp->getDay()!=del_day.getDay())
	{
		prev = temp;
		temp = temp->getNextDay();
	}
	if (!temp) return false;
	else
	{
		prev->setNextDay(temp->getNextDay());
		delete temp;
		return true;
	}
	return false;
}




