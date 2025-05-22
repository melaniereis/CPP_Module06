/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:35:38 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/21 15:46:33 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>
#include "ansi.h"

class Data
{
	public:
		Data();
		Data(const std::string &name, const std::string &profession, const size_t &id);
		Data(const Data &other);
		Data &operator=(const Data &other);
		~Data();

		std::string getName() const;
		std::string getProfession() const;
		size_t getId() const;

	private:
		std::string _name;
		std::string _profession;
		size_t _id;
};

std::ostream &operator<<(std::ostream &os, const Data &data);
