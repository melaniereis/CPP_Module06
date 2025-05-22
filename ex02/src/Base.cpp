/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meferraz <meferraz@student.42porto.pt>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:52:11 by meferraz          #+#    #+#             */
/*   Updated: 2025/05/22 17:25:55 by meferraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

// Factory functions
static Base* createA()
{
	return new A;
}

static Base *createB()
{
	return new B;
}

static Base* createC()
{
	return new C;
}

// Type checkers for pointers
typedef bool (*PointerCheck)(Base*);

static bool isA(Base* p)
{
	return dynamic_cast<A *>(p);
}

static bool isB(Base* p)
{
	return dynamic_cast<B *>(p);
}

static bool isC(Base* p)
{
	return dynamic_cast<C *>(p);
}

// Type attemps for references
typedef void (*RefCheck)(Base&);

static void tryA(Base& ref)
{
	(void)dynamic_cast<A &>(ref);
}

static void tryB(Base& ref)
{
	(void)dynamic_cast<B &>(ref);
}

static void tryC(Base& ref)
{
	(void)dynamic_cast<C &>(ref);
}

// ========== Implementation ==========
Base::~Base()
{}

Base* generate()
{
	std::srand(static_cast<unsigned>(std::time(0)));

	Base* (*factories[3])() = {createA, createB, createC};
	return factories[std::rand() % 3]();
}

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
