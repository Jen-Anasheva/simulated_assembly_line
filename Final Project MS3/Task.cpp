// Name: Yevgeniya Anasheva
// Seneca Student ID: 119338192
// Seneca email: yanasheva@myseneca.ca
// Date of completion: 2019-11-26
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <string>
#include <iomanip>
#include "Task.h"

/*
a custom constructor - upon instantiation, a Task object receives a reference to an unmodifiable std::string. 
This string contains a single record (one line) to be used for Item instantiation.
this constructor will also set the m_pNextTask to a safe state.
*/
Task::Task(const std::string& record) : Item(record)
{
	m_pNextTask = nullptr;
}
/*
 runs a single cycle of the assembly line for the current task.
If there are CustomerOrders in the queue, it will verify the fill status of the last CustomerOrder and fill it 
if the order contains the Item specified by the current Task
*/
/*
if the orders queue is NOT empty, check the fill state of the ITEM (hint a task IS an item), 
if the fill state of the item is FALSE, call fillItem()
*/
void Task::runProcess(std::ostream& os)
{
	if (!m_orders.empty())
	{
		if (!m_orders.back().getItemFillState(this->getName()))
		{
			m_orders.back().fillItem(*this, os);
		}
	}
}
/*
moves the last CustomerOrder in the queue to the next task on the assembly line if the orders fill state for the current Item is true. 
Otherwise, the CustomerOrder should remain in the queue for the next processing cycle. If the queue is empty, return false.
*/
bool Task::moveTask()
{
	if (this->m_orders.empty())
		return false;
	else 
	{
		if (m_orders.back().getItemFillState(this->getName()) && m_pNextTask != nullptr)
		{
			*this->m_pNextTask += std::move(m_orders.back());
			this->m_orders.pop_back();
			return true;
		}
		return false;
	}
}

//stores the provided Task object's reference into the m_pNextTask pointer.
void Task::setNextTask(Task& ref)
{
	m_pNextTask = &ref;
}
//Removes the last CustomerOrder from the queue, places it in the parameter and returns true. If the CustomerOrder queue is empty, return false.
bool Task::getCompleted(CustomerOrder& obj)
{
	if (m_orders.empty())
		return false;
	else if (m_orders.back().getOrderFillState())
	{
		obj = std::move(m_orders.back());
		m_orders.pop_back();
		return true;
	}
	return false;

}
/*
writes the name of the Item this Task is responsible for into the parameter: ITEM_NAME --> NEXT_ITEM_NAME
if m_pNextTask does not exist it writes: ITEM_NAME --> END OF LINE.
the messages are terminated with an endline
*/
void Task::validate(std::ostream& os)
{
	std::string curr_name = this->getName();

	if (m_pNextTask != nullptr)
		os << curr_name << " --> " << m_pNextTask->getName() << "\n";
	else
		os << curr_name << " --> " << "END OF LINE\n";
}

//Moves the parameter onto the front of the CustomerOrder queue.
Task& Task::operator+=(CustomerOrder&& obj)
{
	m_orders.push_front(std::move(obj));
	return *this;
}