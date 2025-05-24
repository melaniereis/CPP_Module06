/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:33:55 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/24 08:19:04 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Base.hpp"

#define SEPARATOR(txt) std::cout << "\n" \
<< WHT "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" \
<< "📄 " << txt << "\n" \
<< "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n" << std::endl;

/**
 * Program entry point.
 *
 * Generates a random Base pointer and prints it, then dereferences the pointer
 * and prints the resulting reference, and finally deletes the pointer.
 */
int main(void)
{
	std::cout << BGRN "\n\n📋===== IDENTIFY REAL TYPE SIMULATION =====📋\n\n" RESET;


	Base* obj = generate();

	std::cout << BBLU <<"Pointer type: " << RESET;
	identify(obj);

	std::cout << BMAG<< "Reference type: " << RESET;
	identify(*obj);

	delete obj;

	std::cout << BGRN "\n\n✅ All tests complete!\n\n" RESET;
	return 0;
}
