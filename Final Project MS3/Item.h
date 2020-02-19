// Name: Yevgeniya Anasheva
// Seneca Student ID: 119338192
// Seneca email: yanasheva@myseneca.ca
// Date of completion: 2019-11-11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <string>

class Item
{
	std::string m_name = "";
	std::string m_description = "";
	int m_serialNumber = 0;
	size_t m_quantity = 0u;
	static size_t m_widthField;
public:
	Item(const std::string&);
	const std::string& getName() const;
	const unsigned int getSerialNumber();
	const unsigned int getQuantity();
	void updateQuantity();
	void display(std::ostream& os, bool full) const;
};
