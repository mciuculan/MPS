#include "../parser/parser.h"
#include "../inputData/inputData.h"
#include "../operation/operation.h"
#include "../randomTree/randomTree.h"

extern std::vector<OperationType> operations;

int main()
{
	Parser parser;
	std::vector<InputData> files;

	files = parser.traverseFiles("../../data/MPS-Global/");

	std::cout << files.size() << "\n";
	std::cout << InputData::getMeanIdealFMeasure(files) << "\n";

	return 0;
}
