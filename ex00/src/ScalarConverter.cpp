/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:47:04 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/24 16:13:49 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

// Type checking functions

/**
 * @brief Checks if the given string represents a printable non-digit character.
 *
 * This function evaluates whether the input string is a single character
 * that is printable and not a digit. It is used to identify if the string
 * can be treated as a character type in the context of scalar conversion.
 *
 * @param str The input string to check.
 * @return true if the string is a single printable non-digit character,
 *         false otherwise.
 */
bool ScalarConverter::isChar(const std::string &str)
{
	return (str.length() == 1 && isprint(str[0]) &&
			!isdigit(str[0]));
}

/**
 * @brief Checks if the given string represents an integer.
 *
 * This function evaluates whether the input string is a valid integer
 * value. It is used to identify if the string can be treated as an integer
 * type in the context of scalar conversion.
 *
 * @param str The input string to check.
 * @return true if the string is a valid integer,
 *         false otherwise.
 */
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

/**
 * @brief Checks if the given string represents a floating point number.
 *
 * This function evaluates whether the input string is a valid floating
 * point value. It is used to identify if the string can be treated as a
 * floating point type in the context of scalar conversion.
 *
 * @param str The input string to check.
 * @return true if the string is a valid floating point number,
 *         false otherwise.
 */
bool ScalarConverter::isFloat(const std::string &str)
{
	if (str.length() < 2 || str[str.length() - 1] != 'f')
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

/**
 * @brief Checks if the given string represents a double precision floating point number.
 *
 * This function evaluates whether the input string is a valid double precision
 * floating point value. It is used to identify if the string can be treated as a
 * double precision floating point type in the context of scalar conversion.
 *
 * @param str The input string to check.
 * @return true if the string is a valid double precision floating point number,
 *         false otherwise.
 */
bool ScalarConverter::isDouble(const std::string &str)
{
	if (str == "+inf" || str == "-inf" || str == "nan")
		return true;
	char *end;
	errno = 0;
	std::strtod(str.c_str(), &end);
	return errno != ERANGE && *end == '\0';
}

/**
 * @brief Checks if the given string represents a pseudo-literal.
 *
 * This function determines whether the input string is one of the
 * special floating point pseudo-literals such as "nan", "nanf",
 * "-inf", "+inf", "-inff", or "+inff". These pseudo-literals are used
 * to represent special cases of floating point numbers in scalar
 * conversion.
 *
 * @param str The input string to check.
 * @return true if the string is a pseudo-literal, false otherwise.
 */
bool ScalarConverter::isPseudoLiteral(const std::string &str)
{
	return (str == "nan" || str == "nanf" ||
			str == "-inf" || str == "+inf" ||
			str == "inf" || str == "inff" ||
			str == "-inff" || str == "+inff");
}

// Helper function to check overflow

/**
 * @brief Checks if the given value is outside the range of type T.
 *
 * This function takes a double precision floating point value and determines
 * whether it is outside the range of type T. The range of T is determined by
 * the numeric_limits of T.
 *
 * @param value The double precision floating point value to check.
 * @return true if the value is outside the range of T, false otherwise.
 */
template <typename T>
bool ScalarConverter::isOverflow(double value)
{
	return std::isnan(value) || std::isinf(value) ||
		   value < std::numeric_limits<T>::min() ||
		   value > std::numeric_limits<T>::max();
}

// Helper function to print "impossible" for all types

/**
 * @brief Prints "impossible" for all four scalar types.
 *
 * This function prints "impossible" for the char, int, float, and double
 * scalar types, indicating that the input string cannot be converted to
 * any of these types.
 */
void ScalarConverter::printImpossible()
{
	std::cout << BBLU "char: " RESET << "impossible" << std::endl;
	std::cout << BBLU "int: " RESET << "impossible" << std::endl;
	std::cout << BBLU "float: " RESET << "impossible" << std::endl;
	std::cout << BBLU "double: " RESET << "impossible" << std::endl;
}

// Helper function to print conversions

/**
 * @brief Prints the conversions of the given double precision
 *        floating point value for all four scalar types.
 *
 * This function takes a double precision floating point value and
 * prints the conversions of this value for all four scalar types:
 * char, int, float, and double. The conversions are printed to the
 * standard output stream.
 *
 * @param value The double precision floating point value to print
 *              conversions for.
 */
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

/**
 * @brief Converts the given string to all four scalar types (char, int, float, double).
 *
 * This function takes a string and attempts to convert it to all four scalar
 * types: char, int, float, and double. The conversions are printed to the
 * standard output stream.
 *
 * @param str The string to convert.
 *
 * If the string is empty, the function prints an error message to the standard
 * error stream and returns. If the string is a pseudo-literal (i.e. one of
 * "nan", "nanf", "-inf", "+inf", "-inff", or "+inff"), the function prints
 * the conversions directly and returns. Otherwise, the function iterates over
 * an array of handlers and checks if the string matches the type of each
 * handler. If a match is found, the function calls the corresponding conversion
 * function. If no match is found, the function prints an error message to the
 * standard error stream.
 */
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
			{&isChar, &convertChar},
			{&isInt, &convertInt},
			{&isFloat, &convertFloat},
			{&isDouble, &convertDouble}};

	for (size_t i = 0; i < sizeof(handlers) / sizeof(handlers[0]); ++i)
	{
		if (handlers[i].isType(str))
		{
			handlers[i].convert(str);
			return;
		}
	}

	if (str.find_first_not_of("0123456789.eEfF+-") == std::string::npos)
		std::cout << ERROR_INVALID_FORMAT << std::endl;
	else
		std::cout << ERROR_IMPOSSIBLE << std::endl;
}

/**
 * @brief Converts the given string to a character scalar type.
 *
 * This function takes a string and attempts to convert it to a character
 * scalar type. The conversion is printed to the standard output stream.
 *
 * @param str The string to convert.
 *
 * If the string does not contain a single character, the function prints an
 * error message to the standard error stream and returns.
 */
void ScalarConverter::convertChar(const std::string &str)
{
	char c = str[0];
	printConversion(static_cast<double>(c));
}

/**
 * @brief Converts the given string to an integer scalar type.
 *
 * This function takes a string and attempts to convert it to an integer
 * scalar type. The conversion is printed to the standard output stream.
 *
 * @param str The string to convert.
 *
 * If the string contains a malformed integer, the function prints an
 * error message to the standard error stream and returns.
 */
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

/**
 * @brief Converts the given string to a float scalar type.
 *
 * This function takes a string representation of a floating-point number
 * followed by 'f' (e.g., "123.45f") and attempts to convert it to a float
 * scalar type. The conversion is printed to the standard output stream.
 *
 * @param str The string to convert.
 *
 * If the string contains a malformed float or if the conversion results
 * in an error, the function prints "impossible" to the standard output
 * stream and returns.
 */
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

/**
 * @brief Converts the given string to a double scalar type.
 *
 * This function takes a string representation of a double precision
 * floating-point number and attempts to convert it to a double scalar
 * type. The conversion is printed to the standard output stream.
 *
 * @param str The string to convert.
 *
 * If the string contains a malformed double or if the conversion results
 * in an error, the function prints "impossible" to the standard output
 * stream and returns.
 */
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

/**
 * @brief Converts the given string to a double scalar type, where the
 * string is one of the special pseudo-literals "nan", "nanf", "-inf",
 * "+inf", "-inff", or "+inff".
 *
 * This function takes a string and attempts to convert it to a double
 * scalar type, where the string is one of the special pseudo-literals
 * "nan", "nanf", "-inf", "+inf", "-inff", or "+inff". The conversion is
 * printed to the standard output stream.
 *
 * @param str The string to convert.
 *
 * If the string is not one of the special pseudo-literals, the function
 * prints an error message to the standard error stream and returns.
 */
void ScalarConverter::convertPseudoLiteral(const std::string &str)
{
	if (str == "nan" || str == "nanf")
		printConversion(std::numeric_limits<double>::quiet_NaN());
	else if (str == "-inf" || str == "-inff")
		printConversion(-std::numeric_limits<double>::infinity());
	else if (str == "+inf" || str == "+inff" || str == "inf" || str == "inff")
		printConversion(std::numeric_limits<double>::infinity());
	else
		std::cout << ERROR_PSEUDO << std::endl;
}
