#include <iostream>
#include <fstream>

const size_t inMax{100};
const size_t storeMax{50};

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

int main(argv){
	std::ifstream inputFile(argv);
        if (inputFile.is_open()){
		std::cout << "File opened..." << "\n";
	}
	else{
		std::cout << "File not found." << "\n";
		return 0;
	}
	return 0;
}

