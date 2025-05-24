/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 21:58:21 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/24 08:13:22 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Serializer.hpp"
#include "../inc/Data.hpp"


#define SEPARATOR(txt) std::cout << "\n" \
<< WHT "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" \
<< "📄 " << txt << "\n" \
<< "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" RESET "\n" << std::endl;

/**
 * @brief Main function to simulate serialization and deserialization of Data objects.
 *
 * This function demonstrates the creation of Data objects, their serialization to
 * uintptr_t using the Serializer class, and their deserialization back to Data objects.
 * It performs three tests, printing the results of each serialization and deserialization
 * process to the console. Each test involves creating a Data object, serializing it,
 * deserializing it, and then printing the original and deserialized objects to verify
 * the integrity of the serialization process.
 */
int main(void)
{
	std::cout << BGRN "\n\n📋=====  SERIALIZER SIMULATION =====📋\n\n" RESET;

	SEPARATOR("Test 1: Data creation and serialization");
	Data data1;
	uintptr_t serialized = Serializer::serialize(&data1);
	Data *deserialized = Serializer::deserialize(serialized);

	std::cout << data1 << std::endl;
	std::cout << *deserialized << std::endl;

	SEPARATOR("Test 2: Data creation and serialization");
	Data data2("John Doe", "Engineer", 42);
	serialized = Serializer::serialize(&data2);
	deserialized = Serializer::deserialize(serialized);

	std::cout << data2 << std::endl;
	std::cout << *deserialized << std::endl;

	SEPARATOR("Test 3: Data creation and serialization");
	Data data3("Lynn Morgan", "Manager", 24);
	serialized = Serializer::serialize(&data3);
	deserialized = Serializer::deserialize(serialized);

	std::cout << data3 << std::endl;
	std::cout << *deserialized << std::endl;

	std::cout << BGRN "\n\n✅ All tests complete!\n\n" RESET;
	return 0;
}
