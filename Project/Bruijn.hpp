#ifndef _BRUIJN_H
#define _BRUIJN_H

#include <string>
#include <unordered_map>
#include <set>

#include "P_string.hpp"

class GraphBruijn {
	public:
		GraphBruijn();
		GraphBruijn(int size);
		GraphBruijn(int size, int _mode);
		void set_size_of_file(int size);
		void set_size_of_file(std::string path);
		void set_size_k_mero(int size);
		int read_all(std::string file_name);

		bool present(p_string P);
		bool present(std::string P);
		int maxlength_present(p_string P, int _mode=0);
		bool error_present(p_string P);
		void print_all();
	private:
		std::unordered_map<std::string, std::vector<char> > grafo;
		std::set<std::string> set;
		int size_k_mero;
		int size_of_file;
		int mode;
};

#endif
