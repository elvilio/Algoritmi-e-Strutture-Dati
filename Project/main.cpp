#include <iostream>
#include <string>
#include <vector>

#include "P_string.hpp"
#include "Bruijn.hpp"

std::string FILE_PATH = "test_files/7.txt";

/* to build: g++ -std=c++17 -Ofast *.cpp -o output */

int main()
{
	p_string P;
	std::cin >> P;

	GraphBruijn data_set(10000000);

	int count = data_set.read_all(FILE_PATH);
	
	std::cout << std::endl << count << " lines read." << std::endl;

	// std::cout << data_set.present(P) << std::endl;
	// std::cout << data_set.maxlength_present(P) << std::endl;
	// std::cout << data_set.error_present(P) << std::endl;

	return 0;
}
