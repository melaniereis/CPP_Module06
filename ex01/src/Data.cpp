/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:39:36 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/24 08:12:59 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

/**
 * @brief Default constructor for the Data class.
 *
 * Initializes a Data object with default values:
 * - Name: "unknown"
 * - Profession: "unknown"
 * - ID: 0
 */

Data::Data() : _name("unknown"), _profession("unknown"), _id(0)
{}

/**
 * @brief Parameterized constructor for the Data class.
 *
 * Initializes a Data object with the given:
 * - Name
 * - Profession
 * - ID
 */
Data::Data(const std::string &name, const std::string &profession, const size_t &id)
: _name(name), _profession(profession), _id(id)
{}

/**
 * @brief Destructor for the Data class.
 */
Data::~Data() {}

/**
 * @brief Copy constructor for the Data class.
 *
 * Creates a new Data object as a copy of an existing one.
 *
 * @param other The Data object to copy from.
 */

Data::Data(const Data &other)
{
	*this = other;
}

/**
 * @brief Assignment operator for the Data class.
 *
 * Assigns the values of one Data object to another.
 *
 * @param other The Data object to copy from.
 * @return A reference to the current object.
 */
Data &Data::operator=(const Data &other)
{
	if (this != &other)
	{
		_name = other.getName();
		_profession = other.getProfession();
		_id = other.getId();
	}
	return *this;
}

/**
 * @brief Getter for the name attribute.
 *
 * @return The name of the Data object.
 */
std::string Data::getName() const
{
	return _name;
}

/**
 * @brief Getter for the profession attribute.
 *
 * @return The profession of the Data object.
 */
std::string Data::getProfession() const
{
	return _profession;
}

/**
 * @brief Getter for the id attribute.
 *
 * @return The id of the Data object.
 */
size_t Data::getId() const
{
	return _id;
}

/**
 * @brief Overloaded output operator for the Data class.
 *
 * Prints the Data object in a formatted way.
 *
 * @param os The output stream to write to.
 * @param data The Data object to print.
 * @return The output stream.
 */
std::ostream &operator<<(std::ostream &os, const Data &data)
{
	os << MAG "📊 "
		<< std::left << std::setw(10)
		<< "Name: " << data.getName()
		<< " | Profession: " << std::setw(3) << data.getProfession()
		<< " | ID: " << std::setw(3) << data.getId()
		<< RESET << std::endl;
	return os;
}
