/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:33:55 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/24 08:07:36 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

#define SEPARATOR(txt) std::cout << "\n" \
<< WHT "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" \
<< "📄 " << txt << "\n" \
<< "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n" << std::endl;

/**
 * @brief Main entry point of the ScalarConverter program.
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 * @return 0 on success, 1 on error.
 *
 * This program takes a single command line argument, which is a string
 * representing a scalar value (e.g. a char, an int, a float, a double).
 * The program will then attempt to convert the string to each of the
 * four scalar types, and print the results to the standard output.
 *
 * If the program is invoked with an invalid number of arguments, it will
 * print an error message to the standard error and return 1.
 */
int main(int argc, char **argv)
{
	std::cout << BGRN "\n\n📋===== SCALAR CONVERTER SIMULATION =====📋\n\n" RESET;

	if (argc != 2)
	{
		std::cerr << RED "❌ ERROR: Invalid number of arguments.\n" RESET;
		std::cerr << "Usage: ./ScalarConverter <value>\n";
		return 1;
	}

	ScalarConverter::convert(argv[1]);

	std::cout << BGRN "\n\n✅ All tests complete!\n\n" RESET;
	return 0;
}
