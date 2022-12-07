#include "InputData.h"

InputData::InputData() {}

InputData::InputData(std::string filePath)
{
	setFilePath(filePath);
}

void InputData::parseFile()
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

int InputData::getFMeasureIndex(double threshold)
{
	return floor(threshold * 255);
}

std::pair<double, double> InputData::getMaxScoreByThreshold()
{
	std::vector<int> scoreIndexes(thresholds.size());
	std::vector<double> scores;

	std::transform(thresholds.begin(), thresholds.end(), scoreIndexes.begin(), getFMeasureIndex);	
	for (auto index : scoreIndexes) {
		scores.push_back(getFMeasures()[index]);
	}

	std::pair<double, double> maxScoreByThreshold;
	double tempScore = 0;

	for (int i = 0; i < (int)scores.size(); ++i) {
		if (scores[i] > tempScore) {
			tempScore = maxScoreByThreshold.second =  scores[i];
			maxScoreByThreshold.first = thresholds[i];
		}
	}

	return maxScoreByThreshold;
}

double InputData::getMeanIdealFMeasure(std::vector<InputData> files)
{
	double sum = 0.0;
	
	for (auto file : files) {
		sum += file.getFMeasures()[InputData::getFMeasureIndex(file.getIdealThreshold())];
	}

	return sum / files.size();
}

void InputData::setFilePath(std::string filePath)
{
	this->filePath = filePath;
}

void InputData::setThresholds(std::vector<double> thresholds)
{
	this->thresholds = thresholds;
}

void InputData::setFMeasures(std::vector<double> fMeasures)
{
	this->fMeasures = fMeasures;
}
