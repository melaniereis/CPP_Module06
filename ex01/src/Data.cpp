/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:39:36 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/22 15:13:58 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data() : _name("unknown"), _profession("unknown"), _id(0)
{}

Data::Data(const std::string &name, const std::string &profession, const size_t &id)
: _name(name), _profession(profession), _id(id)
{}

Data::~Data() {}

Data::Data(const Data &other)
{
	*this = other;
}

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

std::string Data::getName() const
{
	return _name;
}

std::string Data::getProfession() const
{
	return _profession;
}

size_t Data::getId() const
{
	return _id;
}

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
