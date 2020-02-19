// Name: Yevgeniya Anasheva
// Seneca Student ID: 119338192
// Seneca email: yanasheva@myseneca.ca
// Date of completion: 2019-12-1
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

//https://github.com/Seneca-345305/OOP-Project

#include <fstream>
#include <iostream>
#include "LineManager.h"
#include "Utilities.h"

/*
read the records from file and setup all the m_pNextTask references in the Task objects, 
Linking each Task object together to form the assembly line
Move all the CustomerOrder objects onto the front of the ToBeFilled queue
Copy all the Task objects into the AssemblyLine container
*/
LineManager::LineManager(const std::string& file_name, std::vector<Task*>& tasks, std::vector<CustomerOrder>& orders)
{
	std::ifstream file(file_name);
	if (!file)
		throw std::string("Unable to open [") + file_name + "] file.";

	std::string record;
	std::string first;
	std::string next;

	while (!file.eof())
	{
		std::getline(file, record);
		Utilities util;
		size_t pos = 0;
		util.setDelimiter('|');
		bool more;

		first = util.extractToken(record, pos, more);
		pos += first.size() + 1;
		if (pos < record.length())
			next = util.extractToken(record, pos, more);
		else
			next = "";

		for (auto task : tasks)
		{
			if (first == task->getName())
			{
				for (auto second : tasks)
				{
					if (next == second->getName())
						task->setNextTask(*second);
				}
			}
		}
	}
	
	file.close();
	//move Customer orders
		//get size
	//point to tasks
	for (auto &order : orders)
	{
		ToBeFilled.push_front(std::move(order));
		++m_cntCustomerOrder;
	}
	AssemblyLine = tasks;
}
/*
this function performs one cycle of operations on the assembly line by doing the following:
If there are any CustomerOrder objects in the ToBeFilled queue, move the last CustomerOrder object onto the starting point of the AssemblyLine 
(you have to identify which task is the starting point of your assembly line)
Loop through all tasks on the assembly line and run one cycle of the task's process
Loop through all tasks on the assembly line and move the CustomerOrder objects down the line.
Hint: completed orders should be moved into the Completed queue.
return true if all customer orders have been filled, otherwise returns false.
*/
bool LineManager::run(std::ostream& os)
{
	//if to be filled
		//last
			//first "Task"
	//loop through tasks
		//invoke each's runProcess
	//if move
		//check completion
			//move to completed
	//check if completed (final check)
	CustomerOrder order;
	if (!ToBeFilled.empty())
	{
		*AssemblyLine[4] += std::move(this->ToBeFilled.back());
		ToBeFilled.pop_back();
	}
	for (auto &task : AssemblyLine)
		task->runProcess(os);

	for (auto &task : AssemblyLine)
	{
		task->moveTask();
		if(task->getCompleted(order))
			Completed.push_back(std::move(order));
	}
	if (Completed.size() == m_cntCustomerOrder)
		return true;
	else
		return false;
}
//displays all the orders that were completed
void LineManager::displayCompleted(std::ostream& os) const
{
	for (auto &a : Completed)
		a.display(os);
}
//validates each task on the assembly line
void LineManager::validateTasks() const
{
	for (auto a : AssemblyLine)
		a->validate(std::cout);
}