#include "parser.h"

#define DEBUG 0

Parser::Parser() {}

std::vector<InputData> Parser::traverseFiles(std::string path)
{
	// int count = 0;
	std::vector<InputData> files;

	for (auto& entry : std::filesystem::directory_iterator(path)) {
		#if DEBUG == 1
			if (count == 0) {			
				InputData file(entry.path().string());
				file.parseFile();

				files.push_back(file);
			}
			count++;
		#endif

		#if DEBUG == 0
			InputData file(entry.path().string());
			file.parseFile();

			files.push_back(file);
		#endif
		
	}

	return files;
}
