/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:33:55 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/20 16:35:44 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ScalarConverter.hpp"

#define SEPARATOR(txt) std::cout << "\n" \
<< WHT "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" \
<< "📄 " << txt << "\n" \
<< "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n" << std::endl;

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
