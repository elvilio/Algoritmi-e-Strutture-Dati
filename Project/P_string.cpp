#include <stdexcept>
#include <iostream>

#include "P_string.hpp"

p_string::p_string() {
	p = "";
	checkd = true;
}

p_string::p_string(std::string s){
	p = s;
	checkd = false;
}

void p_string::set_string(std::string s){
	p = s;
	checkd = false;
}

std::istream& operator >> (std::istream &input, p_string &P) {
	std::string temp;
	input >> temp;
	P.set_string(temp);
	return input;
}

void p_string::check(int size_k_mero){
	// Controlla la correttezza del k-mero
	// La classe p_string non conosce la dimensione di k e quindi è richiesta
	if(checkd) return;

	if (p.length()<size_k_mero)
		throw std::invalid_argument("String not long enough.");
	
	transform(p.begin(), p.end(), p.begin(), toupper);
	
	std::size_t found = p.find_first_not_of("TGCA");
	if (found!=std::string::npos)
		throw std::invalid_argument("String has non valid characters (valid characters: \"TGCA\").");

	checkd = true;
}

int p_string::length() {
	return p.length();
}

std::string p_string::substr(int start, int length){
	return p.substr(start, length);
}

std::string p_string::modify(int position, char N){
	// cambia la lettera nella posizione position con il carattere N
	std::string temp_p = p;
	temp_p[position] = N;
	return temp_p;
}
