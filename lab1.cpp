#include <iostream>
#include <fstream>

const size_t IN_MAX{100};
const size_t STORE_MAX{50};

size_t strlen(const char * s){
	size_t i{};
	for (; s[i]; ++i){}
	return i;
}

bool streq(const char * s1, const char * s2){
	for (size_t i{}; s1[i] || s2[i]; ++i){
		if (s1[i] != s2[i]){
			return false;
		}
	}
	return true;
}

void strcopy(char * dest, const char * src){
	size_t i{};
	for (; src[i]; ++i){
		dest[i] = src[i];
	}
	dest[i] = '\0';
}

char * strdup(const char * s){
	char * s2 = new char[strlen(s)+1]{};
	strcopy(s2, s);
	return s2;
	delete[] s2;
}

int main(int argc, char * argv[]){
	//Load a file and report if successful.
	std::ifstream inputFile(argv[1]);
        if (inputFile.is_open()){
		std::cout << "File opened..." << "\n";
	}
	else{
		std::cerr << "File not found." << "\n";

		return 0;
	}
	//Allocate dynamic memory
	char * stats = new char[STORE_MAX]{"-S"};
	char * temp = new char[STORE_MAX]{};
	char ** saved = new char*[STORE_MAX]{};
	size_t wordFreq[STORE_MAX]{};
	size_t wordCount{};
	size_t savedTop{};	
	size_t sizeTotal{};
	std::cout << "Initialized..." << "\n";
	//Iterate through file.
	while(!inputFile.eof()){
		inputFile.getline(temp, IN_MAX);
		if(temp[0] > 32 ){
			std::cout << "Checking word: " << temp << '\n';
			sizeTotal += strlen(temp);
			size_t matches{};
			size_t i{};
			for(; saved[i]; ++i){
				if(streq(saved[i], temp) == true){
					std::cout << temp << " is the same as " << saved[i] << '\n';
					++matches;
					wordFreq[i] += 1;
				}
			}
			if(matches == 0){
				saved[savedTop] = strdup(temp);
				++savedTop;
				std::cout << "Saving new word..." << '\n';
				++wordFreq[i];
			}
			++wordCount;
		}
	}	
	std::cout.width(15);
	std::cout << "Word";
	std::cout.width(15);
	std::cout << "Frequency" << '\n';
	for(size_t i{}; saved[i]; ++i){
		std::cout.width(15);
		std::cout << saved[i];
		std::cout.width(15);
		std::cout << wordFreq[i] << '\n';
	}
	if (streq(argv[2], stats)){
		float i{sizeTotal/wordCount};
		std::cout.width(25);
		std::cout.precision(2);
		std::cout << "Average Word Length: " << i;
		for(size_t j{}; saved[j]; ++j){
			i = j;
		}
		std::cout.width(25);
		std::cout.precision(2);
		std::cout << "Type-Token Ratio: " << ((i+1)/wordCount);
		i = 0;
		for(size_t j{}; wordFreq[j]; ++j){
			if(wordFreq[j] = 1){
				++i;
			}
		}
		std::cout.width(25);
		std::cout.precision(2);
		std::cout << "Hapax Legomana Ratio: " << ((i+1)/wordCount) << '\n';
	}
	
	if (inputFile.is_open()){
		inputFile.close();
		std::cout << "File closed." << '\n';
	}
	delete[] temp;
	for (size_t i{}; i < STORE_MAX; ++i){
		delete[] saved[i];
	}
	delete[] saved;
	delete[] stats;
	std::cout << "Memory de-allocated." << '\n';
	return 0;
}
