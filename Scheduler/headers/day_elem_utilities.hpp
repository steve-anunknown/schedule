/*
 * day_elem.hpp
 *
 *  Created on: Mar 3, 2021
 *      Author: stefanos
 */
#include <iostream>

#ifndef HEADERS_day_elem_HPP_
#define HEADERS_day_elem_HPP_

class cl_time
{
private:
	unsigned int hours;
	unsigned int minutes;
public:
	cl_time();
	cl_time(unsigned int const& hours,unsigned int const& minutes);
	cl_time& operator = (cl_time const& timeobj);

	unsigned int getHours(void) const ;
	unsigned int getMins(void) const ;

	bool setHours(unsigned int const& hours);
	bool setMins(unsigned int const& mins);
	friend bool operator == (cl_time const& a_time, cl_time const& b_time);
	friend bool operator != (cl_time const& a_time, cl_time const& b_time);
	friend bool operator < (cl_time const& a_time, cl_time const& b_time);
	friend bool operator > (cl_time const& a_time, cl_time const& b_time);
	friend bool operator <= (cl_time const& a_time, cl_time const& b_time);
	friend bool operator >= (cl_time const& a_time, cl_time const& b_time);

	friend std::istream& operator >> (std::istream &in , cl_time const& time);
	friend std::ostream& operator << (std::ostream &out, cl_time const& time);
};

class cal_date
{
private:
	unsigned int cal_day;
	unsigned int cal_month;
public:
	cal_date();
	cal_date(unsigned int const& day, unsigned int const& month);

	bool setCalDay(unsigned int const& day);
	bool setCalMonth(unsigned int const& month);

	unsigned int getCalDay() const;
	unsigned int getCalMonth() const;

	friend std::ostream & operator << (std::ostream &out, cal_date const& dateobj);
	friend std::istream & operator >> (std::istream &in , cal_date &dateobj);

	friend bool operator == (cal_date const& date_a , cal_date const& date_b);
	friend bool operator != (cal_date const& date_a , cal_date const& date_b);
	friend bool operator < (cal_date const& date_a , cal_date const& date_b);
	friend bool operator > (cal_date const& date_a , cal_date const& date_b);
};


class day_elem
{
private:
	std::string name;
	cl_time start_time,end_time;
	day_elem *next_day_elem;
public:
	day_elem();
	day_elem(std::string const& name , cl_time begin , cl_time finish , day_elem* next);
	day_elem& operator = (day_elem const& day_elemobj);

	std::string getName(void) const;
	cl_time getStart(void) const;
	cl_time getEnd(void) const;
	day_elem* getNextElem(void) const;

	bool setName(std::string const& day_elem_name) ;
	bool setStart(cl_time const& s_time) ;
	bool setEnd(cl_time const& e_time) ;
	bool setNextElem(day_elem *n_day_elem) ;

	friend std::istream& operator >> (std::istream &in , day_elem &day_elemobj);
	friend std::ostream& operator << (std::ostream &out, day_elem &day_elemobj);


};


class school_day
{
private:
	std::string dname;
	day_elem *lhead;
	school_day* next_school_day;
public:
	school_day();
	school_day(std::string const& name);
	school_day(std::string const& name , day_elem *head);
	school_day(std::string const& name , day_elem* head, school_day* next_day);
	~school_day();

	std::string getDay(void) const ;
	day_elem* getHead(void) const ;
	school_day* getNextDay(void) const;

	bool setDay(std::string const& name);
	bool setHead(day_elem *head);
	bool setNextDay(school_day* next_day);
	bool addElem(std::string const& el_name , cl_time const& s_time, cl_time const& e_time);
	bool remElem(std::string const& el_name , cl_time const& s_time, cl_time const& e_time);
	
	friend std::istream& operator >> (std::istream &in , school_day &school_day);
	friend std::ostream& operator << (std::ostream &out, school_day &school_day);
};

class week_program
{
private:
	school_day* days;
public:
	week_program();
	week_program(school_day* days);
	week_program(week_program const& program);
	~week_program();

	school_day getSchoolDay(unsigned int const& index) const;
	school_day getSchoolDay(std::string const& day_name) const;
	
	bool addSchoolDay(school_day const& new_day);
	bool remSchoolDay(school_day const& del_day);

	friend std::ostream& operator << (std::ostream& out, week_program const& programobj);
	friend std::istream& operator >> (std::istream& in, week_program& programobj);

};


#endif /* HEADERS_day_elem_HPP_ */
