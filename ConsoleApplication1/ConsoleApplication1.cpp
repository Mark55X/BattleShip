

#include <iostream>
#include <random>
#include <chrono>
#include <exception>

int main()
{
	try {
		throw std::invalid_argument("Test errorrrre!!");
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}
}
