#ifndef _P_STRING_H
#define _P_STRING_H

#include <string>

class p_string {
	public:
		p_string();
		p_string(std::string s);
		void check(int size_k_mero);
		void set_string(std::string s);
		int length();
		std::string substr(int start, int length);
		std::string modify(int position, char N);
	private:
		std::string p;
		bool checkd;
};

#endif
