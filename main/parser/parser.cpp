#include "parser.h"
#include "../tests/test_parser.h"

Parser::Parser() {}

Parser::Parser(std::string filePath)
{
	setFilePath(filePath);
}

void Parser::parseFile()
{
	std::fstream fs;

	fs.open(filePath, std::ios::in);

	std::string line, temp, word;
	int currLineIndex = 0;

	while (fs >> line) {
		std::stringstream str(line);

		if (!currLineIndex) {
			getline(str, word, ',');
			idealThreshold = std::stod(word);

			while (getline(str, word, ',')) {
				thresholds.push_back(std::stod(word));
			}
		} else {
			while (getline(str, word, ',')) {
				fMeasures.push_back(std::stod(word));
			}
		}

		currLineIndex++;
	}

	fs.close();
}

int Parser::getFMeasureIndex(double threshold)
{
	return floor(threshold * 255);
}

std::pair<double, double> Parser::getMaxScoreByThreshold()
{
	std::vector<int> scoreIndexes(thresholds.size());
	std::vector<double> scores;

	std::transform(thresholds.begin(), thresholds.end(), scoreIndexes.begin(), getFMeasureIndex);	
	for (auto index : scoreIndexes) {
		scores.push_back(getFMeasures()[index]);
	}

	std::pair<double, double> maxScoreByThreshold;
	double tempScore = 0;

	for (int i = 0; i < scores.size(); ++i) {
		if (scores[i] > tempScore) {
			tempScore = maxScoreByThreshold.second =  scores[i];
			maxScoreByThreshold.first = thresholds[i];
		}
	}

	return maxScoreByThreshold;
}

void Parser::setFilePath(std::string filePath)
{
	this->filePath = filePath;
}

void Parser::setThresholds(std::vector<double> thresholds)
{
	this->thresholds = thresholds;
}

void Parser::setFMeasures(std::vector<double> fMeasures)
{
	this->fMeasures = fMeasures;
}

int main(int argc, char* argv[])
{
	std::string mode;
	std::cin>>mode;

	if (mode.compare("run")) {
		Parser parser;
	
		parser.setFilePath("../../mps-global/MPS-Global/[AVE_INT] 2_1.CSV");
		parser.parseFile();

		auto pair = parser.getMaxScoreByThreshold();	
		std::cout.precision(12);
		std::cout << pair.first << " " << pair.second << "\n";\
	}
	

	if (mode.compare("test")) {
		return run_tests(argc, argv);
	}

	return 0;
}
