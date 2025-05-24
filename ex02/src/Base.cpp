/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:52:11 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/24 08:18:54 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

// Factory functions

/**
 * @brief Creates a new instance of class A
 *
 * @return Pointer to the new instance of A
 */
static Base* createA()
{
	return new A;
}

/**
 * @brief Creates a new instance of class B
 *
 * @return Pointer to the new instance of B
 */
static Base *createB()
{
	return new B;
}

/**
 * @brief Creates a new instance of class C
 *
 * @return Pointer to the new instance of C
 */
static Base* createC()
{
	return new C;
}

// Type checkers for pointers

typedef bool (*PointerCheck)(Base*);

/**
 * @brief Checks if the given Base pointer is of type A.
 *
 * @param p Pointer to a Base object.
 * @return true if the object is of type A, false otherwise.
 */
static bool isA(Base* p)
{
	return dynamic_cast<A *>(p);
}

/**
 * @brief Checks if the given Base pointer is of type B.
 *
 * @param p Pointer to a Base object.
 * @return true if the object is of type B, false otherwise.
 */
static bool isB(Base* p)
{
	return dynamic_cast<B *>(p);
}

/**
 * @brief Checks if the given Base pointer is of type C.
 *
 * @param p Pointer to a Base object.
 * @return true if the object is of type C, false otherwise.
 */
static bool isC(Base* p)
{
	return dynamic_cast<C *>(p);
}

// Type attemps for references
typedef void (*RefCheck)(Base&);

/**
 * @brief Tries to cast a Base reference to an A reference.
 *
 * @param ref Reference to a Base object.
 *
 * If the cast fails, a std::bad_cast exception is thrown.
 */
static void tryA(Base& ref)
{
	(void)dynamic_cast<A &>(ref);
}

/**
 * @brief Tries to cast a Base reference to a B reference.
 *
 * @param ref Reference to a Base object.
 *
 * If the cast fails, a std::bad_cast exception is thrown.
 */
static void tryB(Base& ref)
{
	(void)dynamic_cast<B &>(ref);
}

/**
 * @brief Tries to cast a Base reference to a C reference.
 *
 * @param ref Reference to a Base object.
 *
 * If the cast fails, a std::bad_cast exception is thrown.
 */
static void tryC(Base& ref)
{
	(void)dynamic_cast<C &>(ref);
}

// ========== Implementation ==========

/**
 * @brief Virtual destructor for Base class.
 *
 * The destructor is virtual to allow correct destruction of derived objects
 * when they are deleted through a pointer to the base class.
 */
Base::~Base()
{}

/**
 * @brief Randomly generates a new instance of A, B or C.
 *
 * This function uses the current time as a seed for the random number
 * generator, and then selects one of the createA, createB or createC functions
 * at random to generate a new instance of the corresponding class.
 *
 * The returned pointer must be deleted when it is no longer needed.
 *
 * @return Pointer to a new instance of A, B or C.
 */
Base* generate()
{
	std::srand(static_cast<unsigned>(std::time(0)));

	Base* (*factories[3])() = {createA, createB, createC};
	return factories[std::rand() % 3]();
}

/**
 * @brief Identifies the dynamic type of a Base pointer.
 *
 * This function takes a pointer to a Base object and outputs the name of its
 * dynamic type (i.e. the name of the class it was actually instantiated as).
 *
 * If the pointer is null or the dynamic type is unknown, the function outputs
 * "Unknown".
 */
void identify(Base* p)
{
	const PointerCheck checks[3] = {isA, isB, isC};
	const char* names[3] = {"A", "B", "C"};

	for (int i = 0; i < 3; ++i) {
		if (checks[i](p)) {
			std::cout << names[i] << std::endl;
			return;
		}
	}
	std::cout << "Unknown" << std::endl;
}

/**
 * @brief Identifies the dynamic type of a Base reference.
 *
 * This function takes a reference to a Base object and outputs the name of its
 * dynamic type (i.e. the name of the class it was actually instantiated as).
 *
 * If the reference is invalid or the dynamic type is unknown, the function
 * outputs "Unknown".
 */
void identify(Base& p)
{
	const RefCheck attempts[3] = {tryA, tryB, tryC};
	const char* names[3] = {"A", "B", "C"};

	for (int i = 0; i < 3; ++i) {
		try {
			attempts[i](p);
			std::cout << names[i] << std::endl;
			return;
		} catch (...) {}
	}
	std::cout << "Unknown" << std::endl;
}
