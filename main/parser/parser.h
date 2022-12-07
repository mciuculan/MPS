#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>
#include <dirent.h>
#include "../inputData/inputData.h"
#include <filesystem>

class Parser
{
	private:

	public:
		Parser();

		std::vector<InputData> traverseFiles(std::string path);
};
