// Name: Yevgeniya Anasheva
// Seneca Student ID: 119338192
// Seneca email: yanasheva@myseneca.ca
// Date of completion: 2019-11-11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include <algorithm>
#include "CustomerOrder.h"
#include "Utilities.h"

size_t CustomerOrder::m_widthField = 0;
CustomerOrder::CustomerOrder() : m_name{ "" }, m_product{ "" }, m_cntItem{ 0 }, m_lstItem{ nullptr } {}

/*
A custom constructor that takes as a parameter a reference to a string containing a single record from the input file.
This constructor uses a Utilities object to extract the tokens and populate the current instance.
After the extraction, updates CustomerOrder::m_widthField if the value stored there is smaller than the value stored in Utilities::m_widthField.
	Fields in the record are (separated by a delimiter):
	• Customer Name
	• Order Name
	• the list of items making up the order (at least one item)
*/
CustomerOrder::CustomerOrder(std::string& record) : CustomerOrder()
{
	Utilities util;
	size_t pos = 0;
	bool more;

	m_name = util.extractToken(record, pos, more);
	pos += m_name.size() + 1;
	if (more)
	{
		m_product = util.extractToken(record, pos, more);
		pos += m_product.length() + 1;
	}
	if (more)
	{
		std::string sub_items = record.substr(pos, record.find('\n'));
		m_cntItem = std::count(sub_items.begin(), sub_items.end(), util.getDelimiter()) + 1;
		m_lstItem = new ItemInfo*[m_cntItem];

		for (size_t i = 0; i < m_cntItem; i++)
		{
			std::string str_item = util.extractToken(record, pos, more);
			ItemInfo* item = new ItemInfo(str_item);
			m_lstItem[i] = item;
			pos += str_item.length() + 1;
		}
	}

	if (this->m_widthField < util.getFieldWidth())
		this->m_widthField = util.getFieldWidth();
}
//copy constructor 
CustomerOrder::CustomerOrder(const CustomerOrder&)
{
	throw "Error";
}

//move constructor
CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept : CustomerOrder()
{
	*this = std::move(src);
}
//move assignment operator
CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src)
{
	if (this != &src)
	{
		this->m_name = src.m_name;
		this->m_product = src.m_product;
		this->m_cntItem = src.m_cntItem;
		delete[] this->m_lstItem;
		this->m_lstItem = src.m_lstItem;
		src.m_lstItem = nullptr;
	}
	return *this;
}
CustomerOrder::~CustomerOrder()
{
	delete[] this->m_lstItem;
}
//returns the ItemInfo::m_fillState of the item specified as a parameter. If the item doesn't exist in the order, return true
bool CustomerOrder::getItemFillState(std::string str) const
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i]->m_itemName == str)
			return m_lstItem[i]->m_fillState;
	}
	return true;
}
//returns true if all the items in the order have been filled; false otherwise
bool CustomerOrder::getOrderFillState() const
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (m_lstItem[i]->m_fillState == false)
			return false;
	}
	return true;
}
/*
Fills the item in the current order that corresponds to the item passed into the function
(the parameter item represents what is available in the inventory).
	if item cannot be found in the current order, this function does nothing
	if item is found, and the inventory contains at least one element, then this function substracts 1 from the inventory and updates
	ItemInfo::m_serialNumber and ItemInfo::m_fillState. Also it prints the message Filled NAME, PRODUCT[ITEM_NAME].
	if item is found, and the inventory is empty, then this function prints the message Unable to fill NAME, PRODUCT[ITEM_NAME].
	all messages printed should be terminated by an endline
*/
void CustomerOrder::fillItem(Item& item, std::ostream& os)
{
	for (size_t i = 0; i < m_cntItem; i++)
	{
		if (item.getName() == m_lstItem[i]->m_itemName && item.getQuantity() > 0)
		{
			item.updateQuantity();
			m_lstItem[i]->m_serialNumber = item.getSerialNumber();
			m_lstItem[i]->m_fillState = true;
			os << "Filled " << this->m_name << ", " << this->m_product << "[" << m_lstItem[i]->m_itemName << "]\n";
		}
		else if (item.getName() == m_lstItem[i]->m_itemName && item.getQuantity() == 0)
		{
			os << "Unable to fill " << this->m_name << ", " << this->m_product << "[" << m_lstItem[i]->m_itemName << "]\n";
		}
		else
			continue;
	}
}
/*
displays the state of the current object in the format (see the sample output for details)
	CUSTOMER_NAME - PRODUCT
	[SERIAL] ITEM_NAME - STATUS
	[SERIAL] ITEM_NAME - STATUS
*/
void CustomerOrder::display(std::ostream& os) const
{
	os << m_name << " - " << m_product << "\n";
	for (size_t i = 0; i < m_cntItem; i++)
	{
		os << std::right << std::setfill('0') << "[" << std::setw(6) << m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ');
		os << std::left << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
		if (m_lstItem[i]->m_fillState)
			os << "FILLED\n";
		else
			os << "MISSING\n";
	}

}