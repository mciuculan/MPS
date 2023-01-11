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

class InputData
{
	private:
		std::string filePath;
		std::vector<double> thresholds;
		std::vector<double> fMeasures;
		double idealThreshold;

	public:
		InputData();
		InputData(std::string filePath);

		void parseFile();
	 	static int getFMeasureIndex(double threshold);
		static double getMeanIdealFMeasure(std::vector<InputData> files);
		std::pair<double, double> getMaxScoreByThreshold();

		std::string getFilePath() {	return filePath; };
		std::vector<double> getThresholds() { return thresholds; };
		std::vector<double> getFMeasures() { return fMeasures; };
		double getIdealThreshold() { return idealThreshold; };
		
		void setFilePath(std::string filePath);
		void setThresholds(std::vector<double> thresholds);
		void setFMeasures(std::vector<double> fMeasures);
};

class InputDataLocal
{
	private:
		std::string filePath;
		std::vector<std::vector<double>> thresholds;
		std::vector<int> pixelsClass;
		std::vector<double> pixelsValue;

	public:
		InputDataLocal();
		InputDataLocal(std::string filePath);
		
		
		int noLines = 0;
		void parseFile();
		std::vector<int> getPixelsClass() { return pixelsClass; };
		std::string getFilePath() {	return filePath; };
		std::vector<std::vector<double>> getThresholds() { return thresholds; };
		std::vector<double> getPixelsValue() { return pixelsValue; };
		
		void setFilePath(std::string filePath);
		void setThresholds(std::vector<std::vector<double>> thresholds);
		void setPixelsClass(std::vector<int> pixelsClass);
		void setPixelsValue(std::vector<double> pixelsValue);
};
