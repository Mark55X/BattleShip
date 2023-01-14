

#include <iostream>
#include <random>
#include <chrono>
#include <exception>

int main()
{
	try {
		std::cout << static_cast<char>(('F'+'L')/2);
	}
	catch (const std::exception& ex) {
		std::cout << ex.what();
	}
}
