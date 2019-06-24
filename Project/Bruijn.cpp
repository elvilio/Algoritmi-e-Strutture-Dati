#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>

#include "P_string.hpp"
#include "Bruijn.hpp"

#define PBSTR "--------------------------------------------------------------------------------"
#define PBWIDTH 80
#define DEFAULT_SIZE_OF_KMERO 99

/* funzioni locali */

void printProgress (double percentage){
	int val = (int) (percentage * 100);
	int lpad = (int) (percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
	fflush(stdout);
}

std::string other_letters(std::string N){
	// switch non funziona con std::string
	std::string ALL;
	if(N=="T"){
		ALL = "GCA";
	} else if(N=="G") {
		ALL = "TCA";
	} else if(N=="C"){
		ALL = "GTA";
	} else if(N=="A"){
		ALL = "GCT";
	} else {
		ALL = "GCAT";
	} return ALL;
}

/* fine funzioni locali */

GraphBruijn::GraphBruijn(){
	std::unordered_map<std::string, std::vector<std::string> > grafo;
	size_k_mero = DEFAULT_SIZE_OF_KMERO;
	size_of_file = 0;
}

GraphBruijn::GraphBruijn(int size){
	std::unordered_map<std::string, std::vector<std::string> > grafo;
	size_k_mero = DEFAULT_SIZE_OF_KMERO;
	size_of_file = size;
}

void GraphBruijn::set_size_of_file(int size){
	size_of_file = size;
}

void GraphBruijn::set_size_of_file(std::string path){
	size_of_file = 0;
	FILE *infile = std::fopen(path.c_str(), "r");
	int ch;

	while (EOF != (ch=getc(infile)))
		if ('\n' == ch)
			++size_of_file;
	std::fclose(infile);
}

void GraphBruijn::set_size_k_mero(int size){
	size_k_mero = size;
}

int GraphBruijn::read_all(std::string file_name){
	// Funzione che legge dal file file_name e aggiunge i k-meri al grafo,
	// l'output è il numero di linee lette.
	// Viene anche visualizzato il progresso della lettura attraverso la
	// funzione printProgress.
	std::ifstream infile(file_name.c_str()); // aperto come oggetto
	int count = 0;
	int update = size_of_file/100;

	std::string line;
	while (std::getline(infile, line)) {
		if (count % update == 0) {
			printProgress((float) count / size_of_file);
		}

		if (grafo.count(line.substr(0, size_k_mero-1))) {
			grafo[line.substr(0, size_k_mero-1)].push_back(line);
		} else {
			grafo[line.substr(0, size_k_mero-1)] = std::vector<std::string>() ;
			grafo[line.substr(0, size_k_mero-1)].push_back(line);
		}
		++count;
	}
	printProgress((float) 1);
	infile.close();
	return count;
}

bool GraphBruijn::present(p_string P){
	// Cerca la stringa P dentro il grafo
	P.check(size_k_mero);
	return present(P.substr(0,P.length()));
}

bool GraphBruijn::present(std::string P){
	// Cerca la stringa P dentro il grafo
	// (assume che la stringa P possa comparire nel grafo)
	for (int i = 0; i < P.length()-size_k_mero; ++i) {
		if(std::find(grafo[P.substr(i, size_k_mero-1)].begin(),
					 grafo[P.substr(i, size_k_mero-1)].end(),
					 P.substr(i, size_k_mero)) == grafo[P.substr(i, size_k_mero-1)].end())
			return false;
	}
	return true;
}

int GraphBruijn::maxlength_present(p_string P) {
	// Cerca la massima sottostringa di P presente
	P.check(size_k_mero);
	for (int i = 0; i < P.length()-size_k_mero; ++i) {
		if(std::find(grafo[P.substr(i, size_k_mero-1)].begin(),
					 grafo[P.substr(i, size_k_mero-1)].end(),
					 P.substr(i, size_k_mero)) == grafo[P.substr(i, size_k_mero-1)].end())
			return size_k_mero+i;
	}
	return P.length();
}

bool GraphBruijn::error_present(p_string P){
	// Cerca la stringa P con un errore
	// Utilizza la funzione maxlength_present per trovare la posizione dell'errore
	if(present(P))
		return true;

	int max = maxlength_present(P);
	for(const char s: other_letters(P.substr(max,1))) {
		if(present(P.modify(max,s))) {
	 		return true;
	 	}
	}
	return false;
}

void GraphBruijn::print_all(){
	// "scorre" tutto il grafo ma non in modo ordinato
	for (const auto &p : grafo) {
		std::cout << p.first << " => ";
		for (const auto &s : p.second) {
			std::cout << s << " | ";
		}
		std::cout << std::endl;
	}
}
