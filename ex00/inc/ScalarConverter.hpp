/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:41:29 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/20 17:42:43 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ansi.h"
#include <string>
#include <iostream>
#include <limits>
#include <iomanip>
#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstdlib>

// Error message macros
#define ERROR_EMPTY          RED "ERROR: Empty input" RESET
#define ERROR_INVALID_FORMAT RED "ERROR: Invalid numeric format" RESET
#define ERROR_IMPOSSIBLE     RED "ERROR: Impossible to convert this value" RESET
#define ERROR_PSEUDO         RED "ERROR: Invalid pseudo-literal" RESET

// Type check helper macro
#define IS_SIGN(c) (c == '+' || c == '-')

typedef bool (*CheckFunc)(const std::string &);
typedef void (*ConvertFunc)(const std::string &);

struct TypeHandler
{
	CheckFunc isType;
	ConvertFunc convert;
};

class ScalarConverter
{
	public:
		static void convert(const std::string &str);

	private:
		ScalarConverter();
		~ScalarConverter();
		ScalarConverter(const ScalarConverter &other);
		ScalarConverter &operator=(const ScalarConverter &other);

		static void convertChar(const std::string &str);
		static void convertInt(const std::string &str);
		static void convertFloat(const std::string &str);
		static void convertDouble(const std::string &str);
		static void convertPseudoLiteral(const std::string &str);

		static bool isChar(const std::string &str);
		static bool isInt(const std::string &str);
		static bool isFloat(const std::string &str);
		static bool isDouble(const std::string &str);
		static bool isPseudoLiteral(const std::string &str);

		template <typename T>
		static bool isOverflow(double value);

		static void printConversion(double value);
		static void printImpossible();

};
