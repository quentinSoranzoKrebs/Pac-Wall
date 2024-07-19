#include <fstream>

int main(void) {
	std::ifstream input( "../data/map1.txt" );
	for( std::string line; getline( input, line ); ){
		//for each line in input...
		printf("%s\n",line.c_str());
	}


}
