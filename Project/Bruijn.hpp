#ifndef _BRUIJN_H
#define _BRUIJN_H

#include <string>
#include <unordered_map>
#include "P_string.hpp"

class GraphBrujn {
	public:
		GraphBrujn();
		int read_all(std::string file_name);
		void print_all();
		bool present(p_string P);
		bool present(std::string P);
		int maxlength_present(p_string P);
		bool error_present(p_string P);
		void set_size_of_file(int size);
		void set_size_of_file(std::string path);
	private:
		std::unordered_map<std::string, std::vector<std::string> > grafo;
		int size_k_mero;
		int size_of_file;
};

#endif