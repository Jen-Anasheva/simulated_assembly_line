// Name: Yevgeniya Anasheva
// Seneca Student ID: 119338192
// Seneca email: yanasheva@myseneca.ca
// Date of completion: 2019-11-11
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <sstream>
#include <string>
#include "Utilities.h"

char Utilities::m_delimiter = ' ';
//sets the field width of the current object to the value of the parameter
void Utilities::setFieldWidth(size_t width)
{
	m_widthField = width;
}
//returns the field width of the current object
size_t Utilities::getFieldWidth() const
{
	return m_widthField;
}
/*
  Extracts tokens from the first parameter
  • This function uses the delimiter to extract the next token from str starting at next_pos.
  • If successful, it returns the extracted token found and sets more to true; false otherwise.
  • This function reports an exception if there are two delimiters with no token between them.
  • This function updates the current object's m_widthField data member if its current value is less than the size of the token extracted.
	Note: str represents a single line read from an input file
*/
const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
{
	std::string token;
	auto pos = str.find(m_delimiter, next_pos);
	token = str.substr(next_pos, pos - next_pos);
	if (!token.empty())
	{
		more = true;
		if (m_widthField < token.length())
			m_widthField = token.length();
		return token;
	}
	else
	{
		more = false;
		throw "No token found";
	}
}
//sets the delimiter for this class to the character received
void Utilities::setDelimiter(const char delimiter)
{
	m_delimiter = delimiter;
}
//returns the delimiter character of the current object
const char Utilities::getDelimiter() const
{
	return m_delimiter;
}