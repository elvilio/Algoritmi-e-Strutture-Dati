#include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <stdexcept>

#include "P_string.hpp"
#include "Bruijn.hpp"

#define DEFAULT_SIZE_OF_KMERO 99

#define PBSTR "--------------------------------------------------------------------------------"
#define PBWIDTH 80

/* funzioni locali */

void printProgress(double percentage){
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
	std::unordered_map<std::string, std::vector<char> > grafo;
	std::set<std::string> set;
	size_k_mero = DEFAULT_SIZE_OF_KMERO;
	size_of_file = 0;
	mode = 0;
}

GraphBruijn::GraphBruijn(int size){
	std::unordered_map<std::string, std::vector<char> > grafo;
	grafo.reserve(size);
	std::set<std::string> set;
	size_k_mero = DEFAULT_SIZE_OF_KMERO;
	size_of_file = size;
	mode = 0;
}

GraphBruijn::GraphBruijn(int size, int _mode){
	std::unordered_map<std::string, std::vector<char> > grafo;
	grafo.reserve(size);
	std::set<std::string> set;
	size_k_mero = DEFAULT_SIZE_OF_KMERO;
	size_of_file = size;
	mode = _mode;
}

void GraphBruijn::set_size_of_file(int size){
	if(size_of_file<size) {
		grafo.reserve(size);
		size_of_file = size;
	}
	else {
		throw std::invalid_argument("Resize is smaller then already allocated space");
	}
}

void GraphBruijn::set_size_of_file(std::string path){
	int new_size = 0;
	FILE *infile = std::fopen(path.c_str(), "r");
	int ch;

	while (EOF != (ch=getc(infile)))
		if ('\n' == ch)
			++new_size;
	std::fclose(infile);
	try { set_size_of_file(new_size); }
	catch (const std::invalid_argument&) { ; }
}

void GraphBruijn::set_size_k_mero(int size){
	size_k_mero = size;
}

void GraphBruijn::set_size_k_mero(std::string path){
	FILE *infile = std::fopen(path.c_str(), "r");
	int ch;
	int new_size = 0;
	while (EOF != (ch=getc(infile)) && '\n' != ch)
		++new_size;
	std::fclose(infile);
	size_k_mero = new_size;
}

int GraphBruijn::read_all(std::string file_name){
	// Funzione che legge dal file file_name e aggiunge i k-meri al grafo,
	// l'output è il numero di linee lette.
	// Viene anche visualizzato il progresso della lettura attraverso la
	// funzione printProgress.
	// mode: 0       -> crea solo un dizionario (default)
	//		 1,2,3,4 -> crea anche un set ordinato di tutti i k-meri
	std::ifstream infile(file_name.c_str()); // aperto come oggetto
	int count = 0;
	int update = size_of_file/100;

	std::string line;

	switch(mode){
		case 0: {
			while (std::getline(infile, line)){
				if (count % update == 0)
					printProgress((float) count / size_of_file);

				if (grafo.count(line.substr(0, size_k_mero-1))) {
					grafo[line.substr(0, size_k_mero-1)].push_back(line[size_k_mero-1]);
				} else {
					grafo[line.substr(0, size_k_mero-1)] = std::vector<char>() ;
					grafo[line.substr(0, size_k_mero-1)].push_back(line[size_k_mero-1]);
				}
				++count;
			}
			break;
		}
		default: {
			while (std::getline(infile, line)){
				if (count % update == 0)
					printProgress((float) count / size_of_file);

				if (grafo.count(line.substr(0, size_k_mero-1))) {
					grafo[line.substr(0, size_k_mero-1)].push_back(line[size_k_mero-1]);
				} else {
					grafo[line.substr(0, size_k_mero-1)] = std::vector<char>() ;
					grafo[line.substr(0, size_k_mero-1)].push_back(line[size_k_mero-1]);
				}
				set.insert(line);
				++count;
			}
		}
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
	for (int i = 0; i < P.length()-size_k_mero+1; ++i) {
		const std::vector<char> v = grafo[P.substr(i,size_k_mero-1)];
		if(std::find(v.begin(), v.end(), P.substr(i+size_k_mero-1,1)[0]) == v.end())
			// true se la sottostringa di P a partire da i lunga size_k_mero
			// NON è presente nel grafo, cioè arriva fino alla fine della stringa
			// e non la trova.
			return false;
	}
	return true;
}

int GraphBruijn::maxlength_present(p_string P, int _mode){
	// Cerca la massima sottostringa di P presente
	// mode: 0 -> non cerca la sottostringa di P se è minore di k (default)
	//		 1 -> cerca la sottostringa di P come prefisso usando set
	//		 2 -> cerca la sottostringa di P come qualsiasi sottostringa di k-mero
	//		 3 -> cerca la sottostringa di P come suffisso usando set (non efficente)
	//		 4 -> usa la 1 e la 3 per ricavare il massimo effettivo

	if(!present(P.substr(0,size_k_mero))){
		if(_mode > 0 && mode == 0)
			throw std::invalid_argument("Not a valid construction of set");

		switch(_mode){
			case 1: {
				int max_present=1;
				bool found = false;

				for(;max_present<size_k_mero; ++max_present){
					found = false;
					for(std::set<std::string>::const_iterator it(set.lower_bound(P.substr(0,max_present)));
							it != set.end() && it->find(P.substr(0,max_present)) == 0 && !found;
							++it) {
						found = true;
					}
					if(!found){
						return max_present;
					}
				}
				throw std::range_error("Length in set is grater than that in grafo");
				break;
			}
			case 2:{
				int max_present = 1;
				for(std::set<std::string>::const_iterator it = set.begin();
					it != set.end();
					++it){
					if(it->find(P.substr(0,max_present)) == std::string::npos)
						continue;
					else{
						++max_present;
						--it;
					}
				}
				return max_present;
				break;
			}
			case 3:{
				int max_present = 1;
				for(std::set<std::string>::const_iterator it = set.begin();
					it != set.end() && max_present < size_k_mero; ++it){
					if((*it).compare(size_k_mero-max_present,max_present,P.substr(0,max_present))==0){
						++max_present;
						--it;
					}
					else
						continue;
				}
				return max_present;
				break;
			}
			case 4:{
				int max_present1 = 1;
				int max_present2 = 1;

				bool found = false;

				for(;max_present1<size_k_mero; ++max_present1){
					found = false;
					for(std::set<std::string>::const_iterator it(set.lower_bound(P.substr(0,max_present1)));
							it != set.end() && it->find(P.substr(0,max_present1)) == 0 && !found;
							++it) {
						found = true;
					}
					if(!found){
						break;
					}
				}
				for(std::set<std::string>::const_iterator it = set.begin();
					it != set.end() && max_present2 < size_k_mero; ++it){
					if((*it).compare(size_k_mero-max_present2,max_present2,P.substr(0,max_present2))==0){
						++max_present2;
						--it;
					}
					else
						continue;
				}

				return (max_present2 < max_present1) ? max_present1 : max_present2;
				break;
			}
			default:{
				throw std::invalid_argument("The string doesnt start with a valid k-mero");
				break;
			}
		}
	}

	P.check(size_k_mero);
	for (int i = 0; i < P.length()-size_k_mero+1; ++i) {
		const std::vector<char> v = grafo[P.substr(i,size_k_mero-1)];
		if(std::find(v.begin(), v.end(), P.substr(i+size_k_mero-1, 1)[0]) == v.end())
			return size_k_mero+i-1;
	}
	return P.length();
}

bool GraphBruijn::error_present(p_string P){
	// Cerca la stringa P con un errore
	// Utilizza la funzione maxlength_present per trovare la posizione dell'errore
	if(present(P))
		return true;

	int max = size_k_mero;

	try {
		max = maxlength_present(P,0);
	} catch(const std::invalid_argument&) {
		;
	}

	for (int s = max; s > -1; --s) {
		for(const char c: other_letters(P.substr(s,1))){
			if(present(P.modify(s,c)))
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
