#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <algorithm>

class Parser
{
	private:
		std::string filePath;
		std::vector<double> thresholds;
		std::vector<double> fMeasures;
		double idealThreshold;

	public:
		Parser();
		Parser(std::string filePath);

		void parseFile();
	 	static int getFMeasureIndex(double threshold);
		std::pair<double, double> getMaxScoreByThreshold();

		std::string getFilePath() {	return filePath; }
		std::vector<double> getThresholds() { return thresholds; }
		std::vector<double> getFMeasures() { return fMeasures; }
		double getIdealThreshold() { return idealThreshold; }
		
		void setFilePath(std::string filePath);
		void setThresholds(std::vector<double> thresholds);
		void setFMeasures(std::vector<double> fMeasures);
};
