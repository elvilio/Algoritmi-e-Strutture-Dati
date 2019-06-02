#include <iostream>
#include <string>
#include <vector>

#include "Bruijn.hpp"
#include "P_string.hpp"

std::string FILE_PATH = "test_files/7.txt";

/* to build: g++ -std=c++17 -Ofast *.cpp -o output */

int main()
{
	std::string temp_p;
	std::cin >> temp_p;
	p_string P;
	P.set_string(temp_p);

	GraphBrujn data_set;
	data_set.set_size_of_file(10000000);

	int count = data_set.read_all(FILE_PATH);
	
	std::cout << std::endl << count << " lines read." << std::endl;

	// std::cout << data_set.present(P) << std::endl;
	// std::cout << data_set.maxlength_present(P) << std::endl;
	// std::cout << data_set.error_present(P) << std::endl;

	return 0;
}
