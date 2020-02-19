// Name: Yevgeniya Anasheva
// Seneca Student ID: 119338192
// Seneca email: yanasheva@myseneca.ca
// Date of completion: 2019-11-11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <string>
#include "Item.h"

struct ItemInfo
{
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder
{
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	ItemInfo** m_lstItem;
	static size_t m_widthField;
public:
	CustomerOrder();
	CustomerOrder(std::string&);
	//deleting copy operations
	CustomerOrder(const CustomerOrder&);
	CustomerOrder& operator=(const CustomerOrder&) = delete;
	//move constructor
	CustomerOrder(CustomerOrder&&) noexcept;
	//move assignment operator
	CustomerOrder& operator=(CustomerOrder&&);
	~CustomerOrder();
	bool getItemFillState(std::string) const;
	bool getOrderFillState() const;
	void fillItem(Item& item, std::ostream&);
	void display(std::ostream&) const;
};