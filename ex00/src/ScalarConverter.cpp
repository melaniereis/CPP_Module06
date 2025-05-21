/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:47:04 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/20 17:42:45 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include "ScalarConverter.hpp"
#include <cerrno>
#include <climits>
#include <cmath>
#include <iomanip>
#include <iostream>

// Type checking functions remain unchanged
bool ScalarConverter::isChar(const std::string &str)
{
	return (str.length() == 1 && isprint(str[0]) &&
			!isdigit(str[0]));
}

bool ScalarConverter::isInt(const std::string &str)
{
	if (str.empty())
		return (false);
	size_t i = 0;
	if (IS_SIGN(str[i]))
		i++;
	if (i == str.length())
		return (false);
	for (; i < str.length(); ++i)
	{
		if (!isdigit(str[i]))
			return (false);
	}
	char *end;
	errno = 0;
	long val = std::strtol(str.c_str(), &end, 10);
	return (errno != ERANGE && *end == '\0' &&
		val >= std::numeric_limits<int>::min() &&
		val <= std::numeric_limits<int>::max());
}

bool ScalarConverter::isFloat(const std::string &str)
{
	if (str.length() < 2 || str.back() != 'f')
		return false;
	std::string core = str.substr(0, str.length() - 1);
	char *end;
	errno = 0;
	std::strtof(core.c_str(), &end);
	size_t i = 0;
	if (IS_SIGN(core[i]))
		i++;
	if (i == core.length() || (!isdigit(core[i]) && core[i] != '.'))
		return false;
	return errno != ERANGE && *end == '\0';
}

bool ScalarConverter::isDouble(const std::string &str)
{
	if (str == "+inf" || str == "-inf" || str == "nan")
		return true;
	char *end;
	errno = 0;
	std::strtod(str.c_str(), &end);
	return errno != ERANGE && *end == '\0';
}

bool ScalarConverter::isPseudoLiteral(const std::string &str)
{
	return (str == "nan" || str == "nanf" ||
			str == "-inf" || str == "+inf" ||
			str == "-inff" || str == "+inff");
}

// Helper function to check overflow
template <typename T>
bool ScalarConverter::isOverflow(double value)
{
	return std::isnan(value) || std::isinf(value) ||
		value < std::numeric_limits<T>::min() ||
		value > std::numeric_limits<T>::max();
}

// Helper function to print "impossible" for all types
void ScalarConverter::printImpossible()
{
	std::cout << BBLU "char: " RESET << "impossible" << std::endl;
	std::cout << BBLU "int: " RESET << "impossible" << std::endl;
	std::cout << BBLU "float: " RESET << "impossible" << std::endl;
	std::cout << BBLU "double: " RESET << "impossible" << std::endl;
}

// Helper function to print conversions
void ScalarConverter::printConversion(double value)
{
	// Char
	std::cout << BBLU "char: " RESET;
	if (isOverflow<char>(value) || std::floor(value) != value)
		std::cout << "impossible" << std::endl;
	else if (!isprint(static_cast<char>(value)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(value) << "'" << std::endl;

	// Int
	std::cout << BBLU "int: " RESET;
	if (isOverflow<int>(value) || std::floor(value) != value)
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(value) << std::endl;

	// Float
	std::cout << BBLU "float: " RESET;
	if (std::isnan(value))
		std::cout << "nanf" << std::endl;
	else if (std::isinf(value))
		std::cout << (value > 0 ? "+inff" : "-inff") << std::endl;
	else
		std::cout << std::fixed << std::setprecision(1) << static_cast<float>(value) << "f" << std::endl;

	// Double
	std::cout << BBLU "double: " RESET;
	if (std::isnan(value))
		std::cout << "nan" << std::endl;
	else if (std::isinf(value))
		std::cout << (value > 0 ? "+inf" : "-inf") << std::endl;
	else
	{
		std::cout << value;
		std::cout << std::endl;
	}
}

void ScalarConverter::convert(const std::string &str)
{
	if (str.empty())
	{
		std::cout << ERROR_EMPTY << std::endl;
		return;
	}

	if (isPseudoLiteral(str))
	{
		convertPseudoLiteral(str);
		return;
	}

	static const TypeHandler handlers[] =
	{
		{ &isChar,   &convertChar },
		{ &isInt,    &convertInt },
		{ &isFloat,  &convertFloat },
		{ &isDouble, &convertDouble }
	};

	for (size_t i = 0; i < sizeof(handlers)/sizeof(handlers[0]); ++i)
	{
		if (handlers[i].isType(str)) {
			handlers[i].convert(str);
			return;
		}
	}

	if (str.find_first_not_of("0123456789.eEfF+-") == std::string::npos)
		std::cout << ERROR_INVALID_FORMAT << std::endl;
	else
		std::cout << ERROR_IMPOSSIBLE << std::endl;
}

void ScalarConverter::convertChar(const std::string &str)
{
	char c = str[0];
	printConversion(static_cast<double>(c));
}

void ScalarConverter::convertInt(const std::string &str)
{
	char *end;
	errno = 0;
	long val = std::strtol(str.c_str(), &end, 10);
	if (errno != 0 || *end != '\0' ||
		val < std::numeric_limits<int>::min() ||
		val > std::numeric_limits<int>::max())
	{
		printImpossible();
		return;
	}
	printConversion(static_cast<double>(val));
}

void ScalarConverter::convertFloat(const std::string &str)
{
	std::string core = str.substr(0, str.length() - 1);
	char *end;
	errno = 0;
	float f = std::strtof(core.c_str(), &end);
	if (errno != 0 || *end != '\0')
	{
		printImpossible();
		return;
	}
	printConversion(static_cast<double>(f));
}

void ScalarConverter::convertDouble(const std::string &str)
{
	char *end;
	errno = 0;
	double d = std::strtod(str.c_str(), &end);
	if (errno != 0 || *end != '\0')
	{
		printImpossible();
		return;
	}
	printConversion(d);
}

void ScalarConverter::convertPseudoLiteral(const std::string &str)
{
	if (str == "nan" || str == "nanf")
		printConversion(std::numeric_limits<double>::quiet_NaN());
	else if (str == "-inf" || str == "-inff")
		printConversion(-std::numeric_limits<double>::infinity());
	else if (str == "+inf" || str == "+inff")
		printConversion(std::numeric_limits<double>::infinity());
	else
		std::cout << ERROR_PSEUDO << std::endl;
}
