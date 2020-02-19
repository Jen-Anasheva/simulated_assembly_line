// Name: Yevgeniya Anasheva
// Seneca Student ID: 119338192
// Seneca email: yanasheva@myseneca.ca
// Date of completion: 2019-11-26
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <deque>
#include "Item.h"
#include "CustomerOrder.h"

class Task : public Item
{
	std::deque<CustomerOrder> m_orders;
	Task* m_pNextTask;
public: 
	Task(const std::string&);
	Task(const Task&) = delete;
	Task& operator=(const Task&) = delete;
	Task(Task&&) = delete;
	Task& operator=(Task&&) = delete;
	void runProcess(std::ostream&);
	bool moveTask();
	void setNextTask(Task&);
	bool getCompleted(CustomerOrder&);
	void validate(std::ostream&);
	Task& operator+=(CustomerOrder&&);
};
