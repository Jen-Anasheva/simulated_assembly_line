// Name: Yevgeniya Anasheva
// Seneca Student ID: 119338192
// Seneca email: yanasheva@myseneca.ca
// Date of completion: 2019-11-11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include "Item.h"
#include "Utilities.h"

size_t Item::m_widthField = 0;
/*
Custom constructor
	Upon instantiation, an Item object receives a reference to an unmodifiable std::string.
	This string contains a single record (one line) that has been retrieved from the input file specified by the user.

	The constructor uses an Utilities object (created local in the function) to extract each token from the record and populates
	the Item object accordingly.

	Note: a record from the file contains 4 fields separated by a delimiter, in the following order:
	• name of item
	• starting serial number
	• quantity in stock
	• description
	the delimiter of the tokens is a single character, specified by the client and stored into the Utilities object.

	Once the constructor has extracted all of the tokens from the record, it updates Item::m_widthField to the maximum value
	of Item::m_widthField and Utilities::m_widthField.

	Note: the display(...) member function uses this field width to align the output across all of the records retrieved from the file.
*/
Item::Item(const std::string& str)
{
	Utilities util;
	size_t pos = 0;
	bool more;

	m_name = util.extractToken(str, pos, more);
	pos += m_name.size() + 1;
	if (more)
	{
		m_serialNumber = std::stoi(util.extractToken(str, pos, more));
		pos += std::to_string(m_serialNumber).length() + 1;
	}
	if (more)
	{
		m_quantity = std::stoi(util.extractToken(str, pos, more));
		pos += std::to_string(m_quantity).length() + 1;
	}
	if (more)
		m_description = util.extractToken(str, pos, more);

	if (m_widthField < m_name.length())
		m_widthField = m_name.length();
}
//returns the name of the current Item object
const std::string& Item::getName() const
{
	return m_name;
}
//returns the next serial number to be used on the assembly line and increments m_serialNumber
const unsigned int Item::getSerialNumber()
{
	return m_serialNumber++;
}
//returns the remaining quantity of the current Item object
const unsigned int Item::getQuantity()
{
	return m_quantity;
}
//substracts 1 from the available quantity; should not go below 0.
void Item::updateQuantity()
{
	if (m_quantity > 0)
		m_quantity -= 1;
}
/*
Inserts the content of the current object into first parameter.
	• If the second parameter is false, this function inserts only the name and serial number in the format: NAME [######]
	• If the second parameter if true, this function uses the following format: NAME [######] Quantity: QTY Description: DESCRIPTION
	• The NAME and QTY fields will use m_widthField characters, serial number field will use 6 characters;
	the DESCRIPTION has no formatting options

	This function will terminate the printed message with an endline
*/
void Item::display(std::ostream& os, bool full) const
{
	if (!full)
	{
		os << std::setw(m_widthField) << std::left << m_name << std::setfill('0') << " [" << std::right << std::setw(6) << m_serialNumber << "]"
			<< std::setfill(' ');
	}
	else
	{
		os << std::setw(m_widthField) << std::left << m_name << " [" << std::setfill('0') << std::right << std::setw(6) << m_serialNumber << "]"
			<< std::setfill(' ') << std::left
			<< " Quantity: " << std::setw(m_widthField) << m_quantity << " Description: " << m_description;
	}
	os << "\n";
}